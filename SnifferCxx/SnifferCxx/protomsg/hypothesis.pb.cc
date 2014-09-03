// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hypothesis.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "hypothesis.pb.h"

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

namespace ProtoMsg {

namespace {

const ::google::protobuf::Descriptor* Leak_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Leak_reflection_ = NULL;
const ::google::protobuf::Descriptor* Hypothesis_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Hypothesis_reflection_ = NULL;
const ::google::protobuf::Descriptor* Hypotheses_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Hypotheses_reflection_ = NULL;
const ::google::protobuf::Descriptor* Hypotheses_history_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Hypotheses_history_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_hypothesis_2eproto() {
  protobuf_AddDesc_hypothesis_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "hypothesis.proto");
  GOOGLE_CHECK(file != NULL);
  Leak_descriptor_ = file->message_type(0);
  static const int Leak_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Leak, location_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Leak, concentration_),
  };
  Leak_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Leak_descriptor_,
      Leak::default_instance_,
      Leak_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Leak, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Leak, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Leak));
  Hypothesis_descriptor_ = file->message_type(1);
  static const int Hypothesis_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Hypothesis, probability_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Hypothesis, leak_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Hypothesis, methane_history_),
  };
  Hypothesis_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Hypothesis_descriptor_,
      Hypothesis::default_instance_,
      Hypothesis_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Hypothesis, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Hypothesis, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Hypothesis));
  Hypotheses_descriptor_ = file->message_type(2);
  static const int Hypotheses_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Hypotheses, hyp_),
  };
  Hypotheses_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Hypotheses_descriptor_,
      Hypotheses::default_instance_,
      Hypotheses_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Hypotheses, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Hypotheses, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Hypotheses));
  Hypotheses_history_descriptor_ = file->message_type(3);
  static const int Hypotheses_history_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Hypotheses_history, hyps_),
  };
  Hypotheses_history_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Hypotheses_history_descriptor_,
      Hypotheses_history::default_instance_,
      Hypotheses_history_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Hypotheses_history, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Hypotheses_history, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Hypotheses_history));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_hypothesis_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Leak_descriptor_, &Leak::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Hypothesis_descriptor_, &Hypothesis::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Hypotheses_descriptor_, &Hypotheses::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Hypotheses_history_descriptor_, &Hypotheses_history::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_hypothesis_2eproto() {
  delete Leak::default_instance_;
  delete Leak_reflection_;
  delete Hypothesis::default_instance_;
  delete Hypothesis_reflection_;
  delete Hypotheses::default_instance_;
  delete Hypotheses_reflection_;
  delete Hypotheses_history::default_instance_;
  delete Hypotheses_history_reflection_;
}

void protobuf_AddDesc_hypothesis_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::ProtoMsg::protobuf_AddDesc_cell_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\020hypothesis.proto\022\010ProtoMsg\032\ncell.proto"
    "\"E\n\004Leak\022&\n\010location\030\001 \002(\0132\024.ProtoMsg.Co"
    "ordinate\022\025\n\rconcentration\030\002 \002(\001\"i\n\nHypot"
    "hesis\022\023\n\013probability\030\001 \002(\001\022\034\n\004leak\030\002 \003(\013"
    "2\016.ProtoMsg.Leak\022(\n\017methane_history\030\003 \003("
    "\0132\017.ProtoMsg.Cells\"/\n\nHypotheses\022!\n\003hyp\030"
    "\001 \003(\0132\024.ProtoMsg.Hypothesis\"8\n\022Hypothese"
    "s_history\022\"\n\004hyps\030\001 \003(\0132\024.ProtoMsg.Hypot"
    "hesesB\002H\001", 329);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "hypothesis.proto", &protobuf_RegisterTypes);
  Leak::default_instance_ = new Leak();
  Hypothesis::default_instance_ = new Hypothesis();
  Hypotheses::default_instance_ = new Hypotheses();
  Hypotheses_history::default_instance_ = new Hypotheses_history();
  Leak::default_instance_->InitAsDefaultInstance();
  Hypothesis::default_instance_->InitAsDefaultInstance();
  Hypotheses::default_instance_->InitAsDefaultInstance();
  Hypotheses_history::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_hypothesis_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_hypothesis_2eproto {
  StaticDescriptorInitializer_hypothesis_2eproto() {
    protobuf_AddDesc_hypothesis_2eproto();
  }
} static_descriptor_initializer_hypothesis_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Leak::kLocationFieldNumber;
const int Leak::kConcentrationFieldNumber;
#endif  // !_MSC_VER

Leak::Leak()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Leak::InitAsDefaultInstance() {
  location_ = const_cast< ::ProtoMsg::Coordinate*>(&::ProtoMsg::Coordinate::default_instance());
}

Leak::Leak(const Leak& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Leak::SharedCtor() {
  _cached_size_ = 0;
  location_ = NULL;
  concentration_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Leak::~Leak() {
  SharedDtor();
}

void Leak::SharedDtor() {
  if (this != default_instance_) {
    delete location_;
  }
}

void Leak::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Leak::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Leak_descriptor_;
}

const Leak& Leak::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_hypothesis_2eproto();
  return *default_instance_;
}

Leak* Leak::default_instance_ = NULL;

Leak* Leak::New() const {
  return new Leak;
}

void Leak::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_location()) {
      if (location_ != NULL) location_->::ProtoMsg::Coordinate::Clear();
    }
    concentration_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Leak::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .ProtoMsg.Coordinate location = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_location()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(17)) goto parse_concentration;
        break;
      }

      // required double concentration = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
         parse_concentration:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &concentration_)));
          set_has_concentration();
        } else {
          goto handle_uninterpreted;
        }
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

void Leak::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required .ProtoMsg.Coordinate location = 1;
  if (has_location()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->location(), output);
  }

  // required double concentration = 2;
  if (has_concentration()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(2, this->concentration(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Leak::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required .ProtoMsg.Coordinate location = 1;
  if (has_location()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->location(), target);
  }

  // required double concentration = 2;
  if (has_concentration()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(2, this->concentration(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Leak::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required .ProtoMsg.Coordinate location = 1;
    if (has_location()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->location());
    }

    // required double concentration = 2;
    if (has_concentration()) {
      total_size += 1 + 8;
    }

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

void Leak::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Leak* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Leak*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Leak::MergeFrom(const Leak& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_location()) {
      mutable_location()->::ProtoMsg::Coordinate::MergeFrom(from.location());
    }
    if (from.has_concentration()) {
      set_concentration(from.concentration());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Leak::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Leak::CopyFrom(const Leak& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Leak::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  if (has_location()) {
    if (!this->location().IsInitialized()) return false;
  }
  return true;
}

void Leak::Swap(Leak* other) {
  if (other != this) {
    std::swap(location_, other->location_);
    std::swap(concentration_, other->concentration_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Leak::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Leak_descriptor_;
  metadata.reflection = Leak_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Hypothesis::kProbabilityFieldNumber;
const int Hypothesis::kLeakFieldNumber;
const int Hypothesis::kMethaneHistoryFieldNumber;
#endif  // !_MSC_VER

Hypothesis::Hypothesis()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Hypothesis::InitAsDefaultInstance() {
}

Hypothesis::Hypothesis(const Hypothesis& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Hypothesis::SharedCtor() {
  _cached_size_ = 0;
  probability_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Hypothesis::~Hypothesis() {
  SharedDtor();
}

void Hypothesis::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Hypothesis::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Hypothesis::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Hypothesis_descriptor_;
}

const Hypothesis& Hypothesis::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_hypothesis_2eproto();
  return *default_instance_;
}

Hypothesis* Hypothesis::default_instance_ = NULL;

Hypothesis* Hypothesis::New() const {
  return new Hypothesis;
}

void Hypothesis::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    probability_ = 0;
  }
  leak_.Clear();
  methane_history_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Hypothesis::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required double probability = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_FIXED64) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &probability_)));
          set_has_probability();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_leak;
        break;
      }

      // repeated .ProtoMsg.Leak leak = 2;
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
        if (input->ExpectTag(26)) goto parse_methane_history;
        break;
      }

      // repeated .ProtoMsg.Cells methane_history = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_methane_history:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_methane_history()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_methane_history;
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

void Hypothesis::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required double probability = 1;
  if (has_probability()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(1, this->probability(), output);
  }

  // repeated .ProtoMsg.Leak leak = 2;
  for (int i = 0; i < this->leak_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->leak(i), output);
  }

  // repeated .ProtoMsg.Cells methane_history = 3;
  for (int i = 0; i < this->methane_history_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->methane_history(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Hypothesis::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required double probability = 1;
  if (has_probability()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(1, this->probability(), target);
  }

  // repeated .ProtoMsg.Leak leak = 2;
  for (int i = 0; i < this->leak_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->leak(i), target);
  }

  // repeated .ProtoMsg.Cells methane_history = 3;
  for (int i = 0; i < this->methane_history_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->methane_history(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Hypothesis::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required double probability = 1;
    if (has_probability()) {
      total_size += 1 + 8;
    }

  }
  // repeated .ProtoMsg.Leak leak = 2;
  total_size += 1 * this->leak_size();
  for (int i = 0; i < this->leak_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->leak(i));
  }

  // repeated .ProtoMsg.Cells methane_history = 3;
  total_size += 1 * this->methane_history_size();
  for (int i = 0; i < this->methane_history_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->methane_history(i));
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

void Hypothesis::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Hypothesis* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Hypothesis*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Hypothesis::MergeFrom(const Hypothesis& from) {
  GOOGLE_CHECK_NE(&from, this);
  leak_.MergeFrom(from.leak_);
  methane_history_.MergeFrom(from.methane_history_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_probability()) {
      set_probability(from.probability());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Hypothesis::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Hypothesis::CopyFrom(const Hypothesis& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Hypothesis::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  for (int i = 0; i < leak_size(); i++) {
    if (!this->leak(i).IsInitialized()) return false;
  }
  for (int i = 0; i < methane_history_size(); i++) {
    if (!this->methane_history(i).IsInitialized()) return false;
  }
  return true;
}

void Hypothesis::Swap(Hypothesis* other) {
  if (other != this) {
    std::swap(probability_, other->probability_);
    leak_.Swap(&other->leak_);
    methane_history_.Swap(&other->methane_history_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Hypothesis::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Hypothesis_descriptor_;
  metadata.reflection = Hypothesis_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Hypotheses::kHypFieldNumber;
#endif  // !_MSC_VER

Hypotheses::Hypotheses()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Hypotheses::InitAsDefaultInstance() {
}

Hypotheses::Hypotheses(const Hypotheses& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Hypotheses::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Hypotheses::~Hypotheses() {
  SharedDtor();
}

void Hypotheses::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Hypotheses::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Hypotheses::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Hypotheses_descriptor_;
}

const Hypotheses& Hypotheses::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_hypothesis_2eproto();
  return *default_instance_;
}

Hypotheses* Hypotheses::default_instance_ = NULL;

Hypotheses* Hypotheses::New() const {
  return new Hypotheses;
}

void Hypotheses::Clear() {
  hyp_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Hypotheses::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .ProtoMsg.Hypothesis hyp = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_hyp:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_hyp()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_hyp;
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

void Hypotheses::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .ProtoMsg.Hypothesis hyp = 1;
  for (int i = 0; i < this->hyp_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->hyp(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Hypotheses::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .ProtoMsg.Hypothesis hyp = 1;
  for (int i = 0; i < this->hyp_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->hyp(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Hypotheses::ByteSize() const {
  int total_size = 0;

  // repeated .ProtoMsg.Hypothesis hyp = 1;
  total_size += 1 * this->hyp_size();
  for (int i = 0; i < this->hyp_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->hyp(i));
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

void Hypotheses::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Hypotheses* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Hypotheses*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Hypotheses::MergeFrom(const Hypotheses& from) {
  GOOGLE_CHECK_NE(&from, this);
  hyp_.MergeFrom(from.hyp_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Hypotheses::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Hypotheses::CopyFrom(const Hypotheses& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Hypotheses::IsInitialized() const {

  for (int i = 0; i < hyp_size(); i++) {
    if (!this->hyp(i).IsInitialized()) return false;
  }
  return true;
}

void Hypotheses::Swap(Hypotheses* other) {
  if (other != this) {
    hyp_.Swap(&other->hyp_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Hypotheses::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Hypotheses_descriptor_;
  metadata.reflection = Hypotheses_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Hypotheses_history::kHypsFieldNumber;
#endif  // !_MSC_VER

Hypotheses_history::Hypotheses_history()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Hypotheses_history::InitAsDefaultInstance() {
}

Hypotheses_history::Hypotheses_history(const Hypotheses_history& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Hypotheses_history::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Hypotheses_history::~Hypotheses_history() {
  SharedDtor();
}

void Hypotheses_history::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Hypotheses_history::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Hypotheses_history::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Hypotheses_history_descriptor_;
}

const Hypotheses_history& Hypotheses_history::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_hypothesis_2eproto();
  return *default_instance_;
}

Hypotheses_history* Hypotheses_history::default_instance_ = NULL;

Hypotheses_history* Hypotheses_history::New() const {
  return new Hypotheses_history;
}

void Hypotheses_history::Clear() {
  hyps_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Hypotheses_history::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .ProtoMsg.Hypotheses hyps = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_hyps:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_hyps()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(10)) goto parse_hyps;
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

void Hypotheses_history::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // repeated .ProtoMsg.Hypotheses hyps = 1;
  for (int i = 0; i < this->hyps_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->hyps(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Hypotheses_history::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // repeated .ProtoMsg.Hypotheses hyps = 1;
  for (int i = 0; i < this->hyps_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->hyps(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Hypotheses_history::ByteSize() const {
  int total_size = 0;

  // repeated .ProtoMsg.Hypotheses hyps = 1;
  total_size += 1 * this->hyps_size();
  for (int i = 0; i < this->hyps_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->hyps(i));
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

void Hypotheses_history::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Hypotheses_history* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Hypotheses_history*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Hypotheses_history::MergeFrom(const Hypotheses_history& from) {
  GOOGLE_CHECK_NE(&from, this);
  hyps_.MergeFrom(from.hyps_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Hypotheses_history::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Hypotheses_history::CopyFrom(const Hypotheses_history& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Hypotheses_history::IsInitialized() const {

  for (int i = 0; i < hyps_size(); i++) {
    if (!this->hyps(i).IsInitialized()) return false;
  }
  return true;
}

void Hypotheses_history::Swap(Hypotheses_history* other) {
  if (other != this) {
    hyps_.Swap(&other->hyps_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Hypotheses_history::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Hypotheses_history_descriptor_;
  metadata.reflection = Hypotheses_history_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace ProtoMsg

// @@protoc_insertion_point(global_scope)
