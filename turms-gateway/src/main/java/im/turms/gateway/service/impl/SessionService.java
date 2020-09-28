/*
 * Copyright (C) 2019 The Turms Project
 * https://github.com/turms-im/turms
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package im.turms.gateway.service.impl;

import com.google.common.collect.HashMultimap;
import com.google.common.collect.SetMultimap;
import im.turms.common.constant.DeviceType;
import im.turms.common.constant.UserStatus;
import im.turms.common.constant.statuscode.SessionCloseStatus;
import im.turms.common.constant.statuscode.TurmsStatusCode;
import im.turms.gateway.access.websocket.dto.CloseStatusFactory;
import im.turms.gateway.manager.UserSessionsManager;
import im.turms.gateway.plugin.extension.UserOnlineStatusChangeHandler;
import im.turms.gateway.plugin.manager.TurmsPluginManager;
import im.turms.gateway.pojo.bo.session.UserSession;
import im.turms.gateway.service.impl.log.UserLoginActionService;
import im.turms.server.common.bo.session.UserSessionsStatus;
import im.turms.server.common.cluster.node.Node;
import im.turms.server.common.cluster.service.idgen.ServiceType;
import im.turms.server.common.constraint.DeviceTypeConstraint;
import im.turms.server.common.property.TurmsProperties;
import im.turms.server.common.property.env.gateway.SessionProperties;
import im.turms.server.common.rpc.request.SetUserOfflineRequest;
import im.turms.server.common.rpc.service.ISessionService;
import im.turms.server.common.service.session.SessionLocationService;
import im.turms.server.common.service.session.UserStatusService;
import im.turms.server.common.util.DeviceTypeUtil;
import im.turms.server.common.util.ReactorUtil;
import io.micrometer.core.instrument.Counter;
import io.micrometer.core.instrument.MeterRegistry;
import io.micrometer.core.instrument.Tags;
import org.springframework.data.geo.Point;
import org.springframework.stereotype.Service;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.reactive.socket.CloseStatus;
import reactor.core.publisher.Flux;
import reactor.core.publisher.Mono;

import javax.annotation.Nullable;
import javax.annotation.PreDestroy;
import javax.validation.constraints.NotEmpty;
import javax.validation.constraints.NotNull;
import java.time.Duration;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

import static im.turms.gateway.constant.MetricsConstant.LOGGED_IN_USERS_COUNTER_NAME;
import static im.turms.gateway.constant.MetricsConstant.ONLINE_USERS_GAUGE_NAME;

/**
 * @author James Chen
 */
@Service
@Validated
public class SessionService implements ISessionService {

    private final Node node;
    private final TurmsPluginManager turmsPluginManager;
    private final ReasonCacheService reasonCacheService;
    private final SessionLocationService sessionLocationService;
    private final UserStatusService userStatusService;
    private final UserLoginActionService userLoginActionService;
    private final UserSimultaneousLoginService userSimultaneousLoginService;
    private final boolean pluginEnabled;
    private final Map<Long, UserSessionsManager> sessionsManagerByUserId;
    private int closeIdleSessionAfterMillis;
    private Duration closeIdleSessionAfterDuration;
    private int minHeartbeatIntervalMillis;
    private int switchProtocolAfterMillis;

    private final Counter loggedInUsersCounter;

    public SessionService(
            Node node,
            TurmsPluginManager turmsPluginManager,
            UserLoginActionService userLoginActionService,
            SessionLocationService sessionLocationService,
            ReasonCacheService reasonCacheService,
            UserStatusService userStatusService,
            UserSimultaneousLoginService userSimultaneousLoginService,
            MetricsService metricsService) {
        this.node = node;
        this.userLoginActionService = userLoginActionService;
        this.sessionLocationService = sessionLocationService;
        this.turmsPluginManager = turmsPluginManager;
        this.userStatusService = userStatusService;
        this.userSimultaneousLoginService = userSimultaneousLoginService;
        TurmsProperties turmsProperties = node.getSharedProperties();
        // Use ConcurrentHashMap to avoid overwriting an existing sessions manager by accident
        sessionsManagerByUserId = new ConcurrentHashMap<>(4096);
        pluginEnabled = turmsProperties.getPlugin().isEnabled();
        this.reasonCacheService = reasonCacheService;

        SessionProperties sessionProperties = turmsProperties.getGateway().getSession();
        closeIdleSessionAfterMillis = sessionProperties.getCloseIdleSessionAfterSeconds() * 1000;
        closeIdleSessionAfterDuration = Duration.ofMillis(closeIdleSessionAfterMillis);
        minHeartbeatIntervalMillis = sessionProperties.getMinHeartbeatIntervalSeconds() * 1000;
        switchProtocolAfterMillis = sessionProperties.getSwitchProtocolAfterSeconds() * 1000;
        node.addPropertiesChangeListener(newProperties -> {
            SessionProperties newSessionProperties = newProperties.getGateway().getSession();
            closeIdleSessionAfterMillis = newSessionProperties.getCloseIdleSessionAfterSeconds() * 1000;
            closeIdleSessionAfterDuration = Duration.ofMillis(closeIdleSessionAfterMillis);
            minHeartbeatIntervalMillis = newSessionProperties.getMinHeartbeatIntervalSeconds() * 1000;
            switchProtocolAfterMillis = newSessionProperties.getSwitchProtocolAfterSeconds() * 1000;
        });

        MeterRegistry registry = metricsService.getRegistry();
        loggedInUsersCounter = registry.counter(LOGGED_IN_USERS_COUNTER_NAME);
        registry.gaugeMapSize(ONLINE_USERS_GAUGE_NAME, Tags.empty(), sessionsManagerByUserId);
    }

    @PreDestroy
    public void destroy() {
        clearAllLocalSessions(new Date(), CloseStatusFactory.get(SessionCloseStatus.SERVER_CLOSED))
                .subscribe();
    }

    /**
     * @return true if the user was online
     */
    public Mono<Boolean> setLocalSessionOfflineByUserIdAndDeviceType(
            @NotNull Long userId,
            @NotNull @DeviceTypeConstraint DeviceType deviceType,
            @NotNull CloseStatus closeStatus) {
        return setLocalSessionOfflineByUserIdAndDeviceTypes(userId, Collections.singleton(deviceType), closeStatus, new Date());
    }

    /**
     * @return true if the user was online
     */
    @Override
    public Mono<Boolean> setLocalSessionOfflineByUserIdAndDeviceTypes(
            @NotNull Long userId,
            @NotEmpty Set<@DeviceTypeConstraint DeviceType> deviceTypes,
            @NotNull CloseStatus closeStatus) {
        return setLocalSessionOfflineByUserIdAndDeviceTypes(userId, deviceTypes, closeStatus, new Date());
    }

    public Mono<Boolean> authAndSetLocalSessionOfflineByUserIdAndDeviceType(Long userId, DeviceType deviceType, CloseStatus closeStatus, int sessionId) {
        UserSessionsManager manager = getUserSessionsManager(userId);
        if (manager == null) {
            return Mono.just(false);
        }
        UserSession session = manager.getSession(deviceType);
        if (session.getId() == sessionId) {
            return setLocalSessionOfflineByUserIdAndDeviceTypes0(userId, Collections.singleton(deviceType), closeStatus, new Date(), manager);
        } else {
            return Mono.just(false);
        }
    }

    public Mono<Boolean> setLocalSessionOfflineByUserIdAndDeviceTypes(
            @NotNull Long userId,
            @NotEmpty Set<@DeviceTypeConstraint DeviceType> deviceTypes,
            @NotNull CloseStatus closeStatus,
            @NotNull Date disconnectionDate) {
        UserSessionsManager manager = getUserSessionsManager(userId);
        if (manager == null) {
            return Mono.just(false);
        }
        return setLocalSessionOfflineByUserIdAndDeviceTypes0(userId, deviceTypes, closeStatus, disconnectionDate, manager);
    }

    public Mono<Boolean> setLocalSessionOfflineByUserIdAndDeviceTypes0(
            @NotNull Long userId,
            @NotEmpty Set<@DeviceTypeConstraint DeviceType> deviceTypes,
            @NotNull CloseStatus closeStatus,
            @NotNull Date disconnectionDate,
            @NotNull UserSessionsManager manager) {
        // Don't close the real session (connection) first and then remove the session status in Redis
        // because it will make problem if a client logins again while the session status in Redis hasn't been removed
        return userStatusService.removeStatusByUserIdAndDeviceTypes(userId, deviceTypes)
                .flatMap(ignored -> {
                    List<Mono<UserSession>> disconnectMonos = new ArrayList<>(deviceTypes.size());
                    for (DeviceType deviceType : deviceTypes) {
                        UserSession session = manager.getSession(deviceType);
                        if (session != null) {
                            boolean cacheDisconnectionReason = reasonCacheService.shouldCacheDisconnectionReason(userId, deviceType);
                            if (sessionLocationService.isLocationEnabled()) {
                                if (cacheDisconnectionReason) {
                                    int sessionId = session.getId();
                                    disconnectMonos.add(reasonCacheService.cacheDisconnectionReason(userId, deviceType, sessionId, closeStatus)
                                            .then(sessionLocationService.removeUserLocation(userId, deviceType))
                                            .thenReturn(session));
                                } else {
                                    disconnectMonos.add(sessionLocationService.removeUserLocation(userId, deviceType)
                                            .thenReturn(session));
                                }
                            } else if (cacheDisconnectionReason) {
                                int sessionId = session.getId();
                                disconnectMonos.add(reasonCacheService.cacheDisconnectionReason(userId, deviceType, sessionId, closeStatus)
                                        .thenReturn(session));
                            }
                        }
                    }
                    return Flux.merge(disconnectMonos)
                            .doOnNext(session -> {
                                userLoginActionService.tryLogLogoutActionAndTriggerHandlers(session.getLogId(), userId, disconnectionDate);
                                manager.setDeviceOffline(session.getDeviceType(), closeStatus);
                                removeSessionsManagerIfEmpty(closeStatus, manager, userId);
                            })
                            .then(Mono.just(true));
                });
    }

    public Mono<Void> clearAllLocalSessions(Date disconnectionDate, CloseStatus closeStatus) {
        List<Mono<Boolean>> monos = new LinkedList<>();
        for (Map.Entry<Long, UserSessionsManager> entry : sessionsManagerByUserId.entrySet()) {
            Long userId = entry.getKey();
            Set<DeviceType> loggedInDeviceTypes = entry.getValue().getLoggedInDeviceTypes();
            Mono<Boolean> mono = setLocalSessionOfflineByUserIdAndDeviceTypes(userId, loggedInDeviceTypes, closeStatus, disconnectionDate);
            monos.add(mono);
        }
        return Mono.when(monos);
    }

    @Override
    public Mono<Boolean> setLocalUserOffline(
            @NotNull Long userId,
            @NotNull CloseStatus closeStatus) {
        return setLocalSessionOfflineByUserIdAndDeviceTypes(userId, DeviceTypeUtil.ALL_AVAILABLE_DEVICE_TYPES_SET, closeStatus, new Date());
    }

    /**
     * @return true if the session exists and the update operation was successful
     */
    public Mono<Boolean> updateHeartbeatTimestamp(
            @NotNull Long userId,
            @NotNull @DeviceTypeConstraint DeviceType deviceType) {
        UserSessionsManager userSessionsManager = getUserSessionsManager(userId);
        if (userSessionsManager != null) {
            UserSession session = userSessionsManager.getSession(deviceType);
            if (session != null && !session.isConnectionRecovering()) {
                return updateHeartbeatTimestamp(userId, session);
            }
        }
        return Mono.just(false);
    }

    public Mono<Boolean> updateHeartbeatTimestamp(@NotNull Long userId, @NotNull UserSession session) {
        long lastHeartbeatTimestampMillis = session.getLastHeartbeatTimestampMillis();
        boolean isAllowedToUpdate = System.currentTimeMillis() - lastHeartbeatTimestampMillis > minHeartbeatIntervalMillis;
        return isAllowedToUpdate
                ? userStatusService.updateTtl(userId, closeIdleSessionAfterDuration)
                .doOnNext(exists -> session.setLastHeartbeatTimestampMillis(System.currentTimeMillis()))
                : Mono.just(true);
    }

    public Mono<UserSession> authAndUpdateHeartbeatTimestamp(long userId, DeviceType deviceType, int sessionId) {
        UserSessionsManager userSessionsManager = getUserSessionsManager(userId);
        if (userSessionsManager != null) {
            UserSession session = userSessionsManager.getSession(deviceType);
            if (session != null && session.getId() == sessionId && !session.isConnectionRecovering()) {
                return updateHeartbeatTimestamp(userId, session)
                        .flatMap(updated -> updated ? Mono.just(session) : Mono.empty());
            }
        }
        return Mono.empty();
    }

    public Mono<TurmsStatusCode> tryRegisterOnlineUser(
            @NotNull Long userId,
            @NotNull DeviceType deviceType,
            @Nullable UserStatus userStatus,
            @Nullable Point userLocation,
            @Nullable String ip,
            @Nullable Map<String, String> deviceDetails) {
        // Must fetch the latest status instead of the status in the cache
        return userStatusService.fetchUserSessionsStatus(userId)
                .flatMap(sessionsStatus -> {
                    // Check the current sessions status
                    if (sessionsStatus.getUserStatus() == UserStatus.OFFLINE) {
                        return addOnlineDeviceIfAbsent(userId, deviceType, userStatus, userLocation, ip, deviceDetails, sessionsStatus);
                    } else {
                        boolean conflicts = sessionsStatus.getLoggedInDeviceTypes().contains(deviceType);
                        if (conflicts && userSimultaneousLoginService.shouldDisconnectLoggingInDeviceIfConflicts()) {
                            return Mono.just(TurmsStatusCode.SESSION_SIMULTANEOUS_CONFLICTS_DECLINE);
                        } else {
                            return disconnectConflictedDeviceTypes(userId, deviceType, sessionsStatus)
                                    .flatMap(wasSuccessful -> wasSuccessful
                                            ? addOnlineDeviceIfAbsent(userId, deviceType, userStatus, userLocation, ip, deviceDetails, sessionsStatus)
                                            : Mono.just(TurmsStatusCode.SESSION_SIMULTANEOUS_CONFLICTS_DECLINE));
                        }
                    }
                });
    }

    @Nullable
    public UserSessionsManager getUserSessionsManager(@NotNull Long userId) {
        return sessionsManagerByUserId.get(userId);
    }

    @Nullable
    public UserSession getLocalUserSession(@NotNull Long userId, @NotNull DeviceType deviceType) {
        UserSessionsManager userSessionsManager = sessionsManagerByUserId.get(userId);
        return userSessionsManager != null ? userSessionsManager.getSession(deviceType) : null;
    }

    public int countLocalOnlineUsers() {
        return sessionsManagerByUserId.size();
    }

    private Mono<Boolean> disconnectConflictedDeviceTypes(Long userId, DeviceType deviceType, UserSessionsStatus sessionsStatus) {
        Set<DeviceType> conflictedDeviceTypes = userSimultaneousLoginService.getConflictedDeviceTypes(deviceType);
        SetMultimap<String, DeviceType> nodeIdAndDeviceTypesMap = null;
        for (DeviceType conflictedDeviceType : conflictedDeviceTypes) {
            String nodeId = sessionsStatus.getNodeIdByDeviceType(conflictedDeviceType);
            if (nodeId != null) {
                if (nodeIdAndDeviceTypesMap == null) {
                    nodeIdAndDeviceTypesMap = HashMultimap.create(3, 3);
                }
                nodeIdAndDeviceTypesMap.put(nodeId, deviceType);
            }
        }
        if (nodeIdAndDeviceTypesMap != null) {
            List<Mono<Boolean>> disconnectionRequests = new LinkedList<>();
            for (String nodeId : nodeIdAndDeviceTypesMap.keySet()) {
                Set<DeviceType> deviceTypes = nodeIdAndDeviceTypesMap.get(nodeId);
                SetUserOfflineRequest request = new SetUserOfflineRequest(userId, deviceTypes, CloseStatusFactory.get(SessionCloseStatus.DISCONNECTED_BY_CLIENT));
                disconnectionRequests.add(node.getRpcService().requestResponse(nodeId, request));
            }
            return ReactorUtil.areAllTrue(disconnectionRequests);
        } else {
            return Mono.just(true);
        }
    }

    public void onSessionEstablished(UserSessionsManager userSessionsManager, DeviceType deviceType) {
        loggedInUsersCounter.increment();
        if (node.getSharedProperties().getGateway().getSession().isNotifyClientsOfSessionInfoAfterConnected()) {
            userSessionsManager.pushSessionNotification(deviceType);
        }
    }

    private Mono<TurmsStatusCode> addOnlineDeviceIfAbsent(
            @NotNull Long userId,
            @NotNull DeviceType deviceType,
            @Nullable UserStatus userStatus,
            @Nullable Point userLocation,
            @Nullable String ip,
            @Nullable Map<String, String> deviceDetails,
            @NotNull UserSessionsStatus sessionsStatus) {
        // Try to update the global user status
        return userStatusService.addOnlineDeviceIfAbsent(userId, deviceType, userStatus, closeIdleSessionAfterDuration, sessionsStatus)
                .flatMap(wasSuccessful -> {
                    if (wasSuccessful) {
                        UserStatus finalUserStatus = userStatus != null ? userStatus : UserStatus.AVAILABLE;
                        boolean[] managerExists = new boolean[]{true};
                        UserSessionsManager manager = sessionsManagerByUserId.computeIfAbsent(userId, key -> {
                            managerExists[0] = false;
                            return new UserSessionsManager(userId, finalUserStatus, deviceType, userLocation, closeIdleSessionAfterMillis, switchProtocolAfterMillis, null);
                        });
                        if (managerExists[0]) {
                            boolean added = manager.addSessionIfAbsent(deviceType, userLocation, null, closeIdleSessionAfterMillis, switchProtocolAfterMillis);
                            // This should never happen
                            if (!added) {
                                manager.setDeviceOffline(deviceType, CloseStatusFactory.get(SessionCloseStatus.LOGIN_CONFLICT));
                                manager.addSessionIfAbsent(deviceType, userLocation, null, closeIdleSessionAfterMillis, switchProtocolAfterMillis);
                            }
                        }

                        long logId = node.getFlakeIdService().nextId(ServiceType.LOG);
                        Date now = new Date();
                        if (userLocation != null && sessionLocationService.isLocationEnabled()) {
                            return sessionLocationService.upsertUserLocation(userId, deviceType, userLocation, now)
                                    .doOnSuccess(hasUpsertedLocation -> {
                                        if (hasUpsertedLocation) {
                                            userLoginActionService
                                                    .tryLogLoginActionAndTriggerHandlers(logId, userId, finalUserStatus, deviceType, userLocation, ip, deviceDetails, now);
                                        }
                                    })
                                    .thenReturn(TurmsStatusCode.OK);
                        } else {
                            userLoginActionService
                                    .tryLogLoginActionAndTriggerHandlers(logId, userId, finalUserStatus, deviceType, userLocation, ip, deviceDetails, now);
                            return Mono.just(TurmsStatusCode.OK);
                        }
                    } else {
                        return Mono.just(TurmsStatusCode.SESSION_SIMULTANEOUS_CONFLICTS_DECLINE);
                    }
                });
    }

    private void removeSessionsManagerIfEmpty(@NotNull CloseStatus closeStatus, UserSessionsManager manager, Long userId) {
        if (manager.getSessionsNumber() == 0) {
            sessionsManagerByUserId.remove(userId);
        }
        if (pluginEnabled) {
            List<UserOnlineStatusChangeHandler> handlerList = turmsPluginManager.getUserOnlineStatusChangeHandlerList();
            if (!handlerList.isEmpty()) {
                for (UserOnlineStatusChangeHandler handler : handlerList) {
                    handler.goOffline(manager, closeStatus).subscribe();
                }
            }
        }
    }

}