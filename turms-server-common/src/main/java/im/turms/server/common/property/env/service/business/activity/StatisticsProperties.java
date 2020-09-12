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

package im.turms.server.common.property.env.service.business.activity;

import im.turms.server.common.constant.CronConstant;
import im.turms.server.common.constraint.CronConstraint;
import im.turms.server.common.property.metadata.annotation.Description;
import lombok.Data;

/**
 * @author James Chen
 */
@Data
public class StatisticsProperties {

    @Description("The cron expression to specify the time to log online users' number")
    @CronConstraint
    private String onlineUsersNumberLoggingCron = CronConstant.DEFAULT_ONLINE_USERS_NUMBER_LOGGING_CRON;

    @Description("Whether to log online users number")
    private boolean logOnlineUsersNumber = true;

}