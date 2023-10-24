// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: model/storage/storage_resource_info.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_model_2fstorage_2fstorage_5fresource_5finfo_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_model_2fstorage_2fstorage_5fresource_5finfo_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>

#include "google/protobuf/port_def.inc"
#if PROTOBUF_VERSION < 4024000
#error "This file was generated by a newer version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please update"
#error "your headers."
#endif  // PROTOBUF_VERSION

#if 4024000 < PROTOBUF_MIN_PROTOC_VERSION
#error "This file was generated by an older version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please"
#error "regenerate this file with a newer version of protoc."
#endif  // PROTOBUF_MIN_PROTOC_VERSION
#include "google/protobuf/port_undef.inc"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/message_lite.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_model_2fstorage_2fstorage_5fresource_5finfo_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_model_2fstorage_2fstorage_5fresource_5finfo_2eproto {
  static const ::uint32_t offsets[];
};
namespace turms {
namespace client {
namespace model {
namespace proto {
class StorageResourceInfo;
struct StorageResourceInfoDefaultTypeInternal;
extern StorageResourceInfoDefaultTypeInternal _StorageResourceInfo_default_instance_;
}  // namespace proto
}  // namespace model
}  // namespace client
}  // namespace turms
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace turms {
namespace client {
namespace model {
namespace proto {

// ===================================================================


// -------------------------------------------------------------------

class StorageResourceInfo final :
    public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:turms.client.model.proto.StorageResourceInfo) */ {
 public:
  inline StorageResourceInfo() : StorageResourceInfo(nullptr) {}
  ~StorageResourceInfo() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR StorageResourceInfo(::google::protobuf::internal::ConstantInitialized);

  StorageResourceInfo(const StorageResourceInfo& from);
  StorageResourceInfo(StorageResourceInfo&& from) noexcept
    : StorageResourceInfo() {
    *this = ::std::move(from);
  }

  inline StorageResourceInfo& operator=(const StorageResourceInfo& from) {
    CopyFrom(from);
    return *this;
  }
  inline StorageResourceInfo& operator=(StorageResourceInfo&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const std::string& unknown_fields() const {
    return _internal_metadata_.unknown_fields<std::string>(::google::protobuf::internal::GetEmptyString);
  }
  inline std::string* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<std::string>();
  }

  static const StorageResourceInfo& default_instance() {
    return *internal_default_instance();
  }
  static inline const StorageResourceInfo* internal_default_instance() {
    return reinterpret_cast<const StorageResourceInfo*>(
               &_StorageResourceInfo_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(StorageResourceInfo& a, StorageResourceInfo& b) {
    a.Swap(&b);
  }
  inline void Swap(StorageResourceInfo* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(StorageResourceInfo* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  StorageResourceInfo* New(::google::protobuf::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<StorageResourceInfo>(arena);
  }
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)  final;
  void CopyFrom(const StorageResourceInfo& from);
  void MergeFrom(const StorageResourceInfo& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(StorageResourceInfo* other);

  private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "turms.client.model.proto.StorageResourceInfo";
  }
  protected:
  explicit StorageResourceInfo(::google::protobuf::Arena* arena);
  public:

  std::string GetTypeName() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kIdStrFieldNumber = 2,
    kNameFieldNumber = 3,
    kMediaTypeFieldNumber = 4,
    kIdNumFieldNumber = 1,
    kUploaderIdFieldNumber = 5,
    kCreationDateFieldNumber = 6,
  };
  // optional string id_str = 2;
  bool has_id_str() const;
  void clear_id_str() ;
  const std::string& id_str() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_id_str(Arg_&& arg, Args_... args);
  std::string* mutable_id_str();
  PROTOBUF_NODISCARD std::string* release_id_str();
  void set_allocated_id_str(std::string* ptr);

  private:
  const std::string& _internal_id_str() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_id_str(
      const std::string& value);
  std::string* _internal_mutable_id_str();

  public:
  // optional string name = 3;
  bool has_name() const;
  void clear_name() ;
  const std::string& name() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_name(Arg_&& arg, Args_... args);
  std::string* mutable_name();
  PROTOBUF_NODISCARD std::string* release_name();
  void set_allocated_name(std::string* ptr);

  private:
  const std::string& _internal_name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_name(
      const std::string& value);
  std::string* _internal_mutable_name();

  public:
  // optional string media_type = 4;
  bool has_media_type() const;
  void clear_media_type() ;
  const std::string& media_type() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_media_type(Arg_&& arg, Args_... args);
  std::string* mutable_media_type();
  PROTOBUF_NODISCARD std::string* release_media_type();
  void set_allocated_media_type(std::string* ptr);

  private:
  const std::string& _internal_media_type() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_media_type(
      const std::string& value);
  std::string* _internal_mutable_media_type();

  public:
  // optional int64 id_num = 1;
  bool has_id_num() const;
  void clear_id_num() ;
  ::int64_t id_num() const;
  void set_id_num(::int64_t value);

  private:
  ::int64_t _internal_id_num() const;
  void _internal_set_id_num(::int64_t value);

  public:
  // int64 uploader_id = 5;
  void clear_uploader_id() ;
  ::int64_t uploader_id() const;
  void set_uploader_id(::int64_t value);

  private:
  ::int64_t _internal_uploader_id() const;
  void _internal_set_uploader_id(::int64_t value);

  public:
  // int64 creation_date = 6;
  void clear_creation_date() ;
  ::int64_t creation_date() const;
  void set_creation_date(::int64_t value);

  private:
  ::int64_t _internal_creation_date() const;
  void _internal_set_creation_date(::int64_t value);

  public:
  // @@protoc_insertion_point(class_scope:turms.client.model.proto.StorageResourceInfo)
 private:
  class _Internal;

  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<3, 6, 0, 73, 2> _table_;
  template <typename T> friend class ::google::protobuf::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::google::protobuf::internal::HasBits<1> _has_bits_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    ::google::protobuf::internal::ArenaStringPtr id_str_;
    ::google::protobuf::internal::ArenaStringPtr name_;
    ::google::protobuf::internal::ArenaStringPtr media_type_;
    ::int64_t id_num_;
    ::int64_t uploader_id_;
    ::int64_t creation_date_;
    PROTOBUF_TSAN_DECLARE_MEMBER;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_model_2fstorage_2fstorage_5fresource_5finfo_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// StorageResourceInfo

// optional int64 id_num = 1;
inline bool StorageResourceInfo::has_id_num() const {
  bool value = (_impl_._has_bits_[0] & 0x00000008u) != 0;
  return value;
}
inline void StorageResourceInfo::clear_id_num() {
  _impl_.id_num_ = ::int64_t{0};
  _impl_._has_bits_[0] &= ~0x00000008u;
}
inline ::int64_t StorageResourceInfo::id_num() const {
  // @@protoc_insertion_point(field_get:turms.client.model.proto.StorageResourceInfo.id_num)
  return _internal_id_num();
}
inline void StorageResourceInfo::set_id_num(::int64_t value) {
  _internal_set_id_num(value);
  // @@protoc_insertion_point(field_set:turms.client.model.proto.StorageResourceInfo.id_num)
}
inline ::int64_t StorageResourceInfo::_internal_id_num() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.id_num_;
}
inline void StorageResourceInfo::_internal_set_id_num(::int64_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000008u;
  _impl_.id_num_ = value;
}

// optional string id_str = 2;
inline bool StorageResourceInfo::has_id_str() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline void StorageResourceInfo::clear_id_str() {
  _impl_.id_str_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline const std::string& StorageResourceInfo::id_str() const {
  // @@protoc_insertion_point(field_get:turms.client.model.proto.StorageResourceInfo.id_str)
  return _internal_id_str();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void StorageResourceInfo::set_id_str(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.id_str_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:turms.client.model.proto.StorageResourceInfo.id_str)
}
inline std::string* StorageResourceInfo::mutable_id_str() {
  std::string* _s = _internal_mutable_id_str();
  // @@protoc_insertion_point(field_mutable:turms.client.model.proto.StorageResourceInfo.id_str)
  return _s;
}
inline const std::string& StorageResourceInfo::_internal_id_str() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.id_str_.Get();
}
inline void StorageResourceInfo::_internal_set_id_str(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.id_str_.Set(value, GetArenaForAllocation());
}
inline std::string* StorageResourceInfo::_internal_mutable_id_str() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000001u;
  return _impl_.id_str_.Mutable( GetArenaForAllocation());
}
inline std::string* StorageResourceInfo::release_id_str() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:turms.client.model.proto.StorageResourceInfo.id_str)
  if ((_impl_._has_bits_[0] & 0x00000001u) == 0) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000001u;
  auto* released = _impl_.id_str_.Release();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.id_str_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return released;
}
inline void StorageResourceInfo::set_allocated_id_str(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }
  _impl_.id_str_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.id_str_.IsDefault()) {
          _impl_.id_str_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:turms.client.model.proto.StorageResourceInfo.id_str)
}

// optional string name = 3;
inline bool StorageResourceInfo::has_name() const {
  bool value = (_impl_._has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline void StorageResourceInfo::clear_name() {
  _impl_.name_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000002u;
}
inline const std::string& StorageResourceInfo::name() const {
  // @@protoc_insertion_point(field_get:turms.client.model.proto.StorageResourceInfo.name)
  return _internal_name();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void StorageResourceInfo::set_name(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000002u;
  _impl_.name_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:turms.client.model.proto.StorageResourceInfo.name)
}
inline std::string* StorageResourceInfo::mutable_name() {
  std::string* _s = _internal_mutable_name();
  // @@protoc_insertion_point(field_mutable:turms.client.model.proto.StorageResourceInfo.name)
  return _s;
}
inline const std::string& StorageResourceInfo::_internal_name() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.name_.Get();
}
inline void StorageResourceInfo::_internal_set_name(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000002u;
  _impl_.name_.Set(value, GetArenaForAllocation());
}
inline std::string* StorageResourceInfo::_internal_mutable_name() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000002u;
  return _impl_.name_.Mutable( GetArenaForAllocation());
}
inline std::string* StorageResourceInfo::release_name() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:turms.client.model.proto.StorageResourceInfo.name)
  if ((_impl_._has_bits_[0] & 0x00000002u) == 0) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000002u;
  auto* released = _impl_.name_.Release();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.name_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return released;
}
inline void StorageResourceInfo::set_allocated_name(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000002u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000002u;
  }
  _impl_.name_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.name_.IsDefault()) {
          _impl_.name_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:turms.client.model.proto.StorageResourceInfo.name)
}

// optional string media_type = 4;
inline bool StorageResourceInfo::has_media_type() const {
  bool value = (_impl_._has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline void StorageResourceInfo::clear_media_type() {
  _impl_.media_type_.ClearToEmpty();
  _impl_._has_bits_[0] &= ~0x00000004u;
}
inline const std::string& StorageResourceInfo::media_type() const {
  // @@protoc_insertion_point(field_get:turms.client.model.proto.StorageResourceInfo.media_type)
  return _internal_media_type();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void StorageResourceInfo::set_media_type(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000004u;
  _impl_.media_type_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:turms.client.model.proto.StorageResourceInfo.media_type)
}
inline std::string* StorageResourceInfo::mutable_media_type() {
  std::string* _s = _internal_mutable_media_type();
  // @@protoc_insertion_point(field_mutable:turms.client.model.proto.StorageResourceInfo.media_type)
  return _s;
}
inline const std::string& StorageResourceInfo::_internal_media_type() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.media_type_.Get();
}
inline void StorageResourceInfo::_internal_set_media_type(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000004u;
  _impl_.media_type_.Set(value, GetArenaForAllocation());
}
inline std::string* StorageResourceInfo::_internal_mutable_media_type() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_._has_bits_[0] |= 0x00000004u;
  return _impl_.media_type_.Mutable( GetArenaForAllocation());
}
inline std::string* StorageResourceInfo::release_media_type() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:turms.client.model.proto.StorageResourceInfo.media_type)
  if ((_impl_._has_bits_[0] & 0x00000004u) == 0) {
    return nullptr;
  }
  _impl_._has_bits_[0] &= ~0x00000004u;
  auto* released = _impl_.media_type_.Release();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.media_type_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  return released;
}
inline void StorageResourceInfo::set_allocated_media_type(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000004u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000004u;
  }
  _impl_.media_type_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.media_type_.IsDefault()) {
          _impl_.media_type_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:turms.client.model.proto.StorageResourceInfo.media_type)
}

// int64 uploader_id = 5;
inline void StorageResourceInfo::clear_uploader_id() {
  _impl_.uploader_id_ = ::int64_t{0};
}
inline ::int64_t StorageResourceInfo::uploader_id() const {
  // @@protoc_insertion_point(field_get:turms.client.model.proto.StorageResourceInfo.uploader_id)
  return _internal_uploader_id();
}
inline void StorageResourceInfo::set_uploader_id(::int64_t value) {
  _internal_set_uploader_id(value);
  // @@protoc_insertion_point(field_set:turms.client.model.proto.StorageResourceInfo.uploader_id)
}
inline ::int64_t StorageResourceInfo::_internal_uploader_id() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.uploader_id_;
}
inline void StorageResourceInfo::_internal_set_uploader_id(::int64_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.uploader_id_ = value;
}

// int64 creation_date = 6;
inline void StorageResourceInfo::clear_creation_date() {
  _impl_.creation_date_ = ::int64_t{0};
}
inline ::int64_t StorageResourceInfo::creation_date() const {
  // @@protoc_insertion_point(field_get:turms.client.model.proto.StorageResourceInfo.creation_date)
  return _internal_creation_date();
}
inline void StorageResourceInfo::set_creation_date(::int64_t value) {
  _internal_set_creation_date(value);
  // @@protoc_insertion_point(field_set:turms.client.model.proto.StorageResourceInfo.creation_date)
}
inline ::int64_t StorageResourceInfo::_internal_creation_date() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.creation_date_;
}
inline void StorageResourceInfo::_internal_set_creation_date(::int64_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.creation_date_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto
}  // namespace model
}  // namespace client
}  // namespace turms


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_model_2fstorage_2fstorage_5fresource_5finfo_2eproto_2epb_2eh