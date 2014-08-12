// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: dect.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "dect.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace Filesystem {

namespace {

const ::google::protobuf::Descriptor* Detection_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Detection_reflection_ = NULL;
const ::google::protobuf::Descriptor* Detections_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Detections_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_dect_2eproto() {
  protobuf_AddDesc_dect_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "dect.proto");
  GOOGLE_CHECK(file != NULL);
  Detection_descriptor_ = file->message_type(0);
  static const int Detection_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Detection, time_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Detection, leak_),
  };
  Detection_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Detection_descriptor_,
      Detection::default_instance_,
      Detection_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Detection, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Detection, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Detection));
  Detections_descriptor_ = file->message_type(1);
  static const int Detections_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Detections, dect_),
  };
  Detections_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Detections_descriptor_,
      Detections::default_instance_,
      Detections_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Detections, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Detections, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Detections));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_dect_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Detection_descriptor_, &Detection::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Detections_descriptor_, &Detections::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_dect_2eproto() {
  delete Detection::default_instance_;
  delete Detection_reflection_;
  delete Detections::default_instance_;
  delete Detections_reflection_;
}

void protobuf_AddDesc_dect_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::Filesystem::protobuf_AddDesc_hypothesis_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\ndect.proto\022\nFilesystem\032\020hypothesis.pro"
    "to\"9\n\tDetection\022\014\n\004time\030\001 \002(\005\022\036\n\004leak\030\002 "
    "\003(\0132\020.Filesystem.Leak\"1\n\nDetections\022#\n\004d"
    "ect\030\001 \003(\0132\025.Filesystem.Detection", 152);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "dect.proto", &protobuf_RegisterTypes);
  Detection::default_instance_ = new Detection();
  Detections::default_instance_ = new Detections();
  Detection::default_instance_->InitAsDefaultInstance();
  Detections::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_dect_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_dect_2eproto {
  StaticDescriptorInitializer_dect_2eproto() {
    protobuf_AddDesc_dect_2eproto();
  }
} static_descriptor_initializer_dect_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Detection::kTimeFieldNumber;
const int Detection::kLeakFieldNumber;
#endif  // !_MSC_VER

Detection::Detection()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Detection::InitAsDefaultInstance() {
}

Detection::Detection(const Detection& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Detection::SharedCtor() {
  _cached_size_ = 0;
  time_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Detection::~Detection() {
  SharedDtor();
}

void Detection::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Detection::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Detection::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Detection_descriptor_;
}

const Detection& Detection::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_dect_2eproto();
  return *default_instance_;
}

Detection* Detection::default_instance_ = NULL;

Detection* Detection::New() const {
  return new Detection;
}

void Detection::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    time_ = 0;
  }
  leak_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Detection::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 time = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &time_)));
          set_has_time();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_leak;
        break;
      }

      // repeated .Filesystem.Leak leak = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_leak:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_leak()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_leak;
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Detection::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int32 time = 1;
  if (has_time()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->time(), output);
  }

  // repeated .Filesystem.Leak leak = 2;
  for (int i = 0; i < this->leak_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->leak(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Detection::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required int32 time = 1;
  if (has_time()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->time(), target);
  }

  // repeated .Filesystem.Leak leak = 2;
  for (int i = 0; i < this->leak_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->leak(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Detection::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 time = 1;
    if (has_time()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->time());
    }

  }
  // repeated .Filesystem.Leak leak = 2;
  total_size += 1 * this->leak_size();
  for (int i = 0; i < this->leak_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->leak(i));
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Detection::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Detection* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Detection*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Detection::MergeFrom(const Detection& from) {
  GOOGLE_CHECK_NE(&from, this);
  leak_.MergeFrom(from.leak_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_time()) {
      set_time(from.time());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Detection::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Detection::CopyFrom(const Detection& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Detection::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  for (int i = 0; i < leak_size(); i++) {
    if (!this->leak(i).IsInitialized()) return false;
  }
  return true;
}

void Detection::Swap(Detection* other) {
  if (other != this) {
    std::swap(time_, other->time_);
    leak_.Swap(&other->leak_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Detection::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Detection_descriptor_;
  metadata.reflection = Detection_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Detections::kDectFieldNumber;
#endif  // !_MSC_VER

Detections::Detections()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Detections::InitAsDefaultInstance() {
}

Detections::Detections(const Detections& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Detections::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Detections::~Detections() {
  SharedDtor();
}

void Detections::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Detections::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Detections::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Detections_descriptor_;
}

const Detections& Detections::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_dect_2eproto();
  return *default_instance_;
}

Detections* Detections::default_instance_ = NULL;

Detections* Detections::New() const {
  return new Detections;
}

void Detections::Clear() {
  dect_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Detections::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .Filesystem.Detection dect = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_dect:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_dect()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_dect;
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Detections::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .Filesystem.Detection dect = 1;
  for (int i = 0; i < this->dect_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->dect(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Detections::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .Filesystem.Detection dect = 1;
  for (int i = 0; i < this->dect_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->dect(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Detections::ByteSize() const {
  int total_size = 0;

  // repeated .Filesystem.Detection dect = 1;
  total_size += 1 * this->dect_size();
  for (int i = 0; i < this->dect_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->dect(i));
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Detections::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Detections* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Detections*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Detections::MergeFrom(const Detections& from) {
  GOOGLE_CHECK_NE(&from, this);
  dect_.MergeFrom(from.dect_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Detections::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Detections::CopyFrom(const Detections& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Detections::IsInitialized() const {

  for (int i = 0; i < dect_size(); i++) {
    if (!this->dect(i).IsInitialized()) return false;
  }
  return true;
}

void Detections::Swap(Detections* other) {
  if (other != this) {
    dect_.Swap(&other->dect_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Detections::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Detections_descriptor_;
  metadata.reflection = Detections_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Filesystem

// @@protoc_insertion_point(global_scope)