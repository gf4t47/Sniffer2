// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hypothesis.proto

#ifndef PROTOBUF_hypothesis_2eproto__INCLUDED
#define PROTOBUF_hypothesis_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
#include "cell.pb.h"
// @@protoc_insertion_point(includes)

namespace Filesystem {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_hypothesis_2eproto();
void protobuf_AssignDesc_hypothesis_2eproto();
void protobuf_ShutdownFile_hypothesis_2eproto();

class Hypothesis;
class Hypothesis_Leak;
class Hypotheses;
class Hypotheses_history;

// ===================================================================

class Hypothesis_Leak : public ::google::protobuf::Message {
 public:
  Hypothesis_Leak();
  virtual ~Hypothesis_Leak();

  Hypothesis_Leak(const Hypothesis_Leak& from);

  inline Hypothesis_Leak& operator=(const Hypothesis_Leak& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Hypothesis_Leak& default_instance();

  void Swap(Hypothesis_Leak* other);

  // implements Message ----------------------------------------------

  Hypothesis_Leak* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Hypothesis_Leak& from);
  void MergeFrom(const Hypothesis_Leak& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .Filesystem.Coordinate location = 1;
  inline bool has_location() const;
  inline void clear_location();
  static const int kLocationFieldNumber = 1;
  inline const ::Filesystem::Coordinate& location() const;
  inline ::Filesystem::Coordinate* mutable_location();
  inline ::Filesystem::Coordinate* release_location();
  inline void set_allocated_location(::Filesystem::Coordinate* location);

  // required double concentration = 2;
  inline bool has_concentration() const;
  inline void clear_concentration();
  static const int kConcentrationFieldNumber = 2;
  inline double concentration() const;
  inline void set_concentration(double value);

  // @@protoc_insertion_point(class_scope:Filesystem.Hypothesis.Leak)
 private:
  inline void set_has_location();
  inline void clear_has_location();
  inline void set_has_concentration();
  inline void clear_has_concentration();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::Filesystem::Coordinate* location_;
  double concentration_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_hypothesis_2eproto();
  friend void protobuf_AssignDesc_hypothesis_2eproto();
  friend void protobuf_ShutdownFile_hypothesis_2eproto();

  void InitAsDefaultInstance();
  static Hypothesis_Leak* default_instance_;
};
// -------------------------------------------------------------------

class Hypothesis : public ::google::protobuf::Message {
 public:
  Hypothesis();
  virtual ~Hypothesis();

  Hypothesis(const Hypothesis& from);

  inline Hypothesis& operator=(const Hypothesis& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Hypothesis& default_instance();

  void Swap(Hypothesis* other);

  // implements Message ----------------------------------------------

  Hypothesis* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Hypothesis& from);
  void MergeFrom(const Hypothesis& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef Hypothesis_Leak Leak;

  // accessors -------------------------------------------------------

  // required double probability = 1;
  inline bool has_probability() const;
  inline void clear_probability();
  static const int kProbabilityFieldNumber = 1;
  inline double probability() const;
  inline void set_probability(double value);

  // repeated .Filesystem.Hypothesis.Leak leak = 2;
  inline int leak_size() const;
  inline void clear_leak();
  static const int kLeakFieldNumber = 2;
  inline const ::Filesystem::Hypothesis_Leak& leak(int index) const;
  inline ::Filesystem::Hypothesis_Leak* mutable_leak(int index);
  inline ::Filesystem::Hypothesis_Leak* add_leak();
  inline const ::google::protobuf::RepeatedPtrField< ::Filesystem::Hypothesis_Leak >&
      leak() const;
  inline ::google::protobuf::RepeatedPtrField< ::Filesystem::Hypothesis_Leak >*
      mutable_leak();

  // repeated .Filesystem.Cells methene_cells = 3;
  inline int methene_cells_size() const;
  inline void clear_methene_cells();
  static const int kMetheneCellsFieldNumber = 3;
  inline const ::Filesystem::Cells& methene_cells(int index) const;
  inline ::Filesystem::Cells* mutable_methene_cells(int index);
  inline ::Filesystem::Cells* add_methene_cells();
  inline const ::google::protobuf::RepeatedPtrField< ::Filesystem::Cells >&
      methene_cells() const;
  inline ::google::protobuf::RepeatedPtrField< ::Filesystem::Cells >*
      mutable_methene_cells();

  // @@protoc_insertion_point(class_scope:Filesystem.Hypothesis)
 private:
  inline void set_has_probability();
  inline void clear_has_probability();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  double probability_;
  ::google::protobuf::RepeatedPtrField< ::Filesystem::Hypothesis_Leak > leak_;
  ::google::protobuf::RepeatedPtrField< ::Filesystem::Cells > methene_cells_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_hypothesis_2eproto();
  friend void protobuf_AssignDesc_hypothesis_2eproto();
  friend void protobuf_ShutdownFile_hypothesis_2eproto();

  void InitAsDefaultInstance();
  static Hypothesis* default_instance_;
};
// -------------------------------------------------------------------

class Hypotheses : public ::google::protobuf::Message {
 public:
  Hypotheses();
  virtual ~Hypotheses();

  Hypotheses(const Hypotheses& from);

  inline Hypotheses& operator=(const Hypotheses& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Hypotheses& default_instance();

  void Swap(Hypotheses* other);

  // implements Message ----------------------------------------------

  Hypotheses* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Hypotheses& from);
  void MergeFrom(const Hypotheses& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .Filesystem.Hypothesis hyp = 1;
  inline int hyp_size() const;
  inline void clear_hyp();
  static const int kHypFieldNumber = 1;
  inline const ::Filesystem::Hypothesis& hyp(int index) const;
  inline ::Filesystem::Hypothesis* mutable_hyp(int index);
  inline ::Filesystem::Hypothesis* add_hyp();
  inline const ::google::protobuf::RepeatedPtrField< ::Filesystem::Hypothesis >&
      hyp() const;
  inline ::google::protobuf::RepeatedPtrField< ::Filesystem::Hypothesis >*
      mutable_hyp();

  // @@protoc_insertion_point(class_scope:Filesystem.Hypotheses)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::Filesystem::Hypothesis > hyp_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_hypothesis_2eproto();
  friend void protobuf_AssignDesc_hypothesis_2eproto();
  friend void protobuf_ShutdownFile_hypothesis_2eproto();

  void InitAsDefaultInstance();
  static Hypotheses* default_instance_;
};
// -------------------------------------------------------------------

class Hypotheses_history : public ::google::protobuf::Message {
 public:
  Hypotheses_history();
  virtual ~Hypotheses_history();

  Hypotheses_history(const Hypotheses_history& from);

  inline Hypotheses_history& operator=(const Hypotheses_history& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Hypotheses_history& default_instance();

  void Swap(Hypotheses_history* other);

  // implements Message ----------------------------------------------

  Hypotheses_history* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Hypotheses_history& from);
  void MergeFrom(const Hypotheses_history& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .Filesystem.Hypotheses hyps = 1;
  inline int hyps_size() const;
  inline void clear_hyps();
  static const int kHypsFieldNumber = 1;
  inline const ::Filesystem::Hypotheses& hyps(int index) const;
  inline ::Filesystem::Hypotheses* mutable_hyps(int index);
  inline ::Filesystem::Hypotheses* add_hyps();
  inline const ::google::protobuf::RepeatedPtrField< ::Filesystem::Hypotheses >&
      hyps() const;
  inline ::google::protobuf::RepeatedPtrField< ::Filesystem::Hypotheses >*
      mutable_hyps();

  // @@protoc_insertion_point(class_scope:Filesystem.Hypotheses_history)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::Filesystem::Hypotheses > hyps_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_hypothesis_2eproto();
  friend void protobuf_AssignDesc_hypothesis_2eproto();
  friend void protobuf_ShutdownFile_hypothesis_2eproto();

  void InitAsDefaultInstance();
  static Hypotheses_history* default_instance_;
};
// ===================================================================


// ===================================================================

// Hypothesis_Leak

// required .Filesystem.Coordinate location = 1;
inline bool Hypothesis_Leak::has_location() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Hypothesis_Leak::set_has_location() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Hypothesis_Leak::clear_has_location() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Hypothesis_Leak::clear_location() {
  if (location_ != NULL) location_->::Filesystem::Coordinate::Clear();
  clear_has_location();
}
inline const ::Filesystem::Coordinate& Hypothesis_Leak::location() const {
  return location_ != NULL ? *location_ : *default_instance_->location_;
}
inline ::Filesystem::Coordinate* Hypothesis_Leak::mutable_location() {
  set_has_location();
  if (location_ == NULL) location_ = new ::Filesystem::Coordinate;
  return location_;
}
inline ::Filesystem::Coordinate* Hypothesis_Leak::release_location() {
  clear_has_location();
  ::Filesystem::Coordinate* temp = location_;
  location_ = NULL;
  return temp;
}
inline void Hypothesis_Leak::set_allocated_location(::Filesystem::Coordinate* location) {
  delete location_;
  location_ = location;
  if (location) {
    set_has_location();
  } else {
    clear_has_location();
  }
}

// required double concentration = 2;
inline bool Hypothesis_Leak::has_concentration() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Hypothesis_Leak::set_has_concentration() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Hypothesis_Leak::clear_has_concentration() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Hypothesis_Leak::clear_concentration() {
  concentration_ = 0;
  clear_has_concentration();
}
inline double Hypothesis_Leak::concentration() const {
  return concentration_;
}
inline void Hypothesis_Leak::set_concentration(double value) {
  set_has_concentration();
  concentration_ = value;
}

// -------------------------------------------------------------------

// Hypothesis

// required double probability = 1;
inline bool Hypothesis::has_probability() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Hypothesis::set_has_probability() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Hypothesis::clear_has_probability() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Hypothesis::clear_probability() {
  probability_ = 0;
  clear_has_probability();
}
inline double Hypothesis::probability() const {
  return probability_;
}
inline void Hypothesis::set_probability(double value) {
  set_has_probability();
  probability_ = value;
}

// repeated .Filesystem.Hypothesis.Leak leak = 2;
inline int Hypothesis::leak_size() const {
  return leak_.size();
}
inline void Hypothesis::clear_leak() {
  leak_.Clear();
}
inline const ::Filesystem::Hypothesis_Leak& Hypothesis::leak(int index) const {
  return leak_.Get(index);
}
inline ::Filesystem::Hypothesis_Leak* Hypothesis::mutable_leak(int index) {
  return leak_.Mutable(index);
}
inline ::Filesystem::Hypothesis_Leak* Hypothesis::add_leak() {
  return leak_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Filesystem::Hypothesis_Leak >&
Hypothesis::leak() const {
  return leak_;
}
inline ::google::protobuf::RepeatedPtrField< ::Filesystem::Hypothesis_Leak >*
Hypothesis::mutable_leak() {
  return &leak_;
}

// repeated .Filesystem.Cells methene_cells = 3;
inline int Hypothesis::methene_cells_size() const {
  return methene_cells_.size();
}
inline void Hypothesis::clear_methene_cells() {
  methene_cells_.Clear();
}
inline const ::Filesystem::Cells& Hypothesis::methene_cells(int index) const {
  return methene_cells_.Get(index);
}
inline ::Filesystem::Cells* Hypothesis::mutable_methene_cells(int index) {
  return methene_cells_.Mutable(index);
}
inline ::Filesystem::Cells* Hypothesis::add_methene_cells() {
  return methene_cells_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Filesystem::Cells >&
Hypothesis::methene_cells() const {
  return methene_cells_;
}
inline ::google::protobuf::RepeatedPtrField< ::Filesystem::Cells >*
Hypothesis::mutable_methene_cells() {
  return &methene_cells_;
}

// -------------------------------------------------------------------

// Hypotheses

// repeated .Filesystem.Hypothesis hyp = 1;
inline int Hypotheses::hyp_size() const {
  return hyp_.size();
}
inline void Hypotheses::clear_hyp() {
  hyp_.Clear();
}
inline const ::Filesystem::Hypothesis& Hypotheses::hyp(int index) const {
  return hyp_.Get(index);
}
inline ::Filesystem::Hypothesis* Hypotheses::mutable_hyp(int index) {
  return hyp_.Mutable(index);
}
inline ::Filesystem::Hypothesis* Hypotheses::add_hyp() {
  return hyp_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Filesystem::Hypothesis >&
Hypotheses::hyp() const {
  return hyp_;
}
inline ::google::protobuf::RepeatedPtrField< ::Filesystem::Hypothesis >*
Hypotheses::mutable_hyp() {
  return &hyp_;
}

// -------------------------------------------------------------------

// Hypotheses_history

// repeated .Filesystem.Hypotheses hyps = 1;
inline int Hypotheses_history::hyps_size() const {
  return hyps_.size();
}
inline void Hypotheses_history::clear_hyps() {
  hyps_.Clear();
}
inline const ::Filesystem::Hypotheses& Hypotheses_history::hyps(int index) const {
  return hyps_.Get(index);
}
inline ::Filesystem::Hypotheses* Hypotheses_history::mutable_hyps(int index) {
  return hyps_.Mutable(index);
}
inline ::Filesystem::Hypotheses* Hypotheses_history::add_hyps() {
  return hyps_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Filesystem::Hypotheses >&
Hypotheses_history::hyps() const {
  return hyps_;
}
inline ::google::protobuf::RepeatedPtrField< ::Filesystem::Hypotheses >*
Hypotheses_history::mutable_hyps() {
  return &hyps_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Filesystem

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_hypothesis_2eproto__INCLUDED