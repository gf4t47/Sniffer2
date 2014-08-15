// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: cell.proto

#ifndef PROTOBUF_cell_2eproto__INCLUDED
#define PROTOBUF_cell_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace Msg {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_cell_2eproto();
void protobuf_AssignDesc_cell_2eproto();
void protobuf_ShutdownFile_cell_2eproto();

class Coordinate;
class Cell;
class Cell_WindVector;
class Cell_Wind;
class Cell_Methane;
class Cells;
class Map;

enum CellTag {
  Air = 1,
  Ground = 2,
  Building = 3
};
bool CellTag_IsValid(int value);
const CellTag CellTag_MIN = Air;
const CellTag CellTag_MAX = Building;
const int CellTag_ARRAYSIZE = CellTag_MAX + 1;

const ::google::protobuf::EnumDescriptor* CellTag_descriptor();
inline const ::std::string& CellTag_Name(CellTag value) {
  return ::google::protobuf::internal::NameOfEnum(
    CellTag_descriptor(), value);
}
inline bool CellTag_Parse(
    const ::std::string& name, CellTag* value) {
  return ::google::protobuf::internal::ParseNamedEnum<CellTag>(
    CellTag_descriptor(), name, value);
}
// ===================================================================

class Coordinate : public ::google::protobuf::Message {
 public:
  Coordinate();
  virtual ~Coordinate();
  
  Coordinate(const Coordinate& from);
  
  inline Coordinate& operator=(const Coordinate& from) {
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
  static const Coordinate& default_instance();
  
  void Swap(Coordinate* other);
  
  // implements Message ----------------------------------------------
  
  Coordinate* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Coordinate& from);
  void MergeFrom(const Coordinate& from);
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
  
  // required int32 coord_x = 1;
  inline bool has_coord_x() const;
  inline void clear_coord_x();
  static const int kCoordXFieldNumber = 1;
  inline ::google::protobuf::int32 coord_x() const;
  inline void set_coord_x(::google::protobuf::int32 value);
  
  // required int32 coord_y = 2;
  inline bool has_coord_y() const;
  inline void clear_coord_y();
  static const int kCoordYFieldNumber = 2;
  inline ::google::protobuf::int32 coord_y() const;
  inline void set_coord_y(::google::protobuf::int32 value);
  
  // required int32 coord_z = 3;
  inline bool has_coord_z() const;
  inline void clear_coord_z();
  static const int kCoordZFieldNumber = 3;
  inline ::google::protobuf::int32 coord_z() const;
  inline void set_coord_z(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:Msg.Coordinate)
 private:
  inline void set_has_coord_x();
  inline void clear_has_coord_x();
  inline void set_has_coord_y();
  inline void clear_has_coord_y();
  inline void set_has_coord_z();
  inline void clear_has_coord_z();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::int32 coord_x_;
  ::google::protobuf::int32 coord_y_;
  ::google::protobuf::int32 coord_z_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_cell_2eproto();
  friend void protobuf_AssignDesc_cell_2eproto();
  friend void protobuf_ShutdownFile_cell_2eproto();
  
  void InitAsDefaultInstance();
  static Coordinate* default_instance_;
};
// -------------------------------------------------------------------

class Cell_WindVector : public ::google::protobuf::Message {
 public:
  Cell_WindVector();
  virtual ~Cell_WindVector();
  
  Cell_WindVector(const Cell_WindVector& from);
  
  inline Cell_WindVector& operator=(const Cell_WindVector& from) {
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
  static const Cell_WindVector& default_instance();
  
  void Swap(Cell_WindVector* other);
  
  // implements Message ----------------------------------------------
  
  Cell_WindVector* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Cell_WindVector& from);
  void MergeFrom(const Cell_WindVector& from);
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
  
  // required double wv_x = 1;
  inline bool has_wv_x() const;
  inline void clear_wv_x();
  static const int kWvXFieldNumber = 1;
  inline double wv_x() const;
  inline void set_wv_x(double value);
  
  // required double wv_y = 2;
  inline bool has_wv_y() const;
  inline void clear_wv_y();
  static const int kWvYFieldNumber = 2;
  inline double wv_y() const;
  inline void set_wv_y(double value);
  
  // required double wv_z = 3;
  inline bool has_wv_z() const;
  inline void clear_wv_z();
  static const int kWvZFieldNumber = 3;
  inline double wv_z() const;
  inline void set_wv_z(double value);
  
  // @@protoc_insertion_point(class_scope:Msg.Cell.WindVector)
 private:
  inline void set_has_wv_x();
  inline void clear_has_wv_x();
  inline void set_has_wv_y();
  inline void clear_has_wv_y();
  inline void set_has_wv_z();
  inline void clear_has_wv_z();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  double wv_x_;
  double wv_y_;
  double wv_z_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_cell_2eproto();
  friend void protobuf_AssignDesc_cell_2eproto();
  friend void protobuf_ShutdownFile_cell_2eproto();
  
  void InitAsDefaultInstance();
  static Cell_WindVector* default_instance_;
};
// -------------------------------------------------------------------

class Cell_Wind : public ::google::protobuf::Message {
 public:
  Cell_Wind();
  virtual ~Cell_Wind();
  
  Cell_Wind(const Cell_Wind& from);
  
  inline Cell_Wind& operator=(const Cell_Wind& from) {
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
  static const Cell_Wind& default_instance();
  
  void Swap(Cell_Wind* other);
  
  // implements Message ----------------------------------------------
  
  Cell_Wind* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Cell_Wind& from);
  void MergeFrom(const Cell_Wind& from);
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
  
  // required .Msg.Cell.WindVector wind = 1;
  inline bool has_wind() const;
  inline void clear_wind();
  static const int kWindFieldNumber = 1;
  inline const ::Msg::Cell_WindVector& wind() const;
  inline ::Msg::Cell_WindVector* mutable_wind();
  inline ::Msg::Cell_WindVector* release_wind();
  
  // required .Msg.Cell.WindVector potential = 2;
  inline bool has_potential() const;
  inline void clear_potential();
  static const int kPotentialFieldNumber = 2;
  inline const ::Msg::Cell_WindVector& potential() const;
  inline ::Msg::Cell_WindVector* mutable_potential();
  inline ::Msg::Cell_WindVector* release_potential();
  
  // @@protoc_insertion_point(class_scope:Msg.Cell.Wind)
 private:
  inline void set_has_wind();
  inline void clear_has_wind();
  inline void set_has_potential();
  inline void clear_has_potential();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::Msg::Cell_WindVector* wind_;
  ::Msg::Cell_WindVector* potential_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_cell_2eproto();
  friend void protobuf_AssignDesc_cell_2eproto();
  friend void protobuf_ShutdownFile_cell_2eproto();
  
  void InitAsDefaultInstance();
  static Cell_Wind* default_instance_;
};
// -------------------------------------------------------------------

class Cell_Methane : public ::google::protobuf::Message {
 public:
  Cell_Methane();
  virtual ~Cell_Methane();
  
  Cell_Methane(const Cell_Methane& from);
  
  inline Cell_Methane& operator=(const Cell_Methane& from) {
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
  static const Cell_Methane& default_instance();
  
  void Swap(Cell_Methane* other);
  
  // implements Message ----------------------------------------------
  
  Cell_Methane* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Cell_Methane& from);
  void MergeFrom(const Cell_Methane& from);
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
  
  // required double concentration = 1;
  inline bool has_concentration() const;
  inline void clear_concentration();
  static const int kConcentrationFieldNumber = 1;
  inline double concentration() const;
  inline void set_concentration(double value);
  
  // @@protoc_insertion_point(class_scope:Msg.Cell.Methane)
 private:
  inline void set_has_concentration();
  inline void clear_has_concentration();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  double concentration_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_cell_2eproto();
  friend void protobuf_AssignDesc_cell_2eproto();
  friend void protobuf_ShutdownFile_cell_2eproto();
  
  void InitAsDefaultInstance();
  static Cell_Methane* default_instance_;
};
// -------------------------------------------------------------------

class Cell : public ::google::protobuf::Message {
 public:
  Cell();
  virtual ~Cell();
  
  Cell(const Cell& from);
  
  inline Cell& operator=(const Cell& from) {
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
  static const Cell& default_instance();
  
  void Swap(Cell* other);
  
  // implements Message ----------------------------------------------
  
  Cell* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Cell& from);
  void MergeFrom(const Cell& from);
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
  
  typedef Cell_WindVector WindVector;
  typedef Cell_Wind Wind;
  typedef Cell_Methane Methane;
  
  // accessors -------------------------------------------------------
  
  // required .Msg.Coordinate coord = 1;
  inline bool has_coord() const;
  inline void clear_coord();
  static const int kCoordFieldNumber = 1;
  inline const ::Msg::Coordinate& coord() const;
  inline ::Msg::Coordinate* mutable_coord();
  inline ::Msg::Coordinate* release_coord();
  
  // required .Msg.CellTag tag = 2;
  inline bool has_tag() const;
  inline void clear_tag();
  static const int kTagFieldNumber = 2;
  inline Msg::CellTag tag() const;
  inline void set_tag(Msg::CellTag value);
  
  // required .Msg.Cell.Methane mtn = 3;
  inline bool has_mtn() const;
  inline void clear_mtn();
  static const int kMtnFieldNumber = 3;
  inline const ::Msg::Cell_Methane& mtn() const;
  inline ::Msg::Cell_Methane* mutable_mtn();
  inline ::Msg::Cell_Methane* release_mtn();
  
  // required .Msg.Cell.Wind wind = 4;
  inline bool has_wind() const;
  inline void clear_wind();
  static const int kWindFieldNumber = 4;
  inline const ::Msg::Cell_Wind& wind() const;
  inline ::Msg::Cell_Wind* mutable_wind();
  inline ::Msg::Cell_Wind* release_wind();
  
  // @@protoc_insertion_point(class_scope:Msg.Cell)
 private:
  inline void set_has_coord();
  inline void clear_has_coord();
  inline void set_has_tag();
  inline void clear_has_tag();
  inline void set_has_mtn();
  inline void clear_has_mtn();
  inline void set_has_wind();
  inline void clear_has_wind();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::Msg::Coordinate* coord_;
  ::Msg::Cell_Methane* mtn_;
  ::Msg::Cell_Wind* wind_;
  int tag_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];
  
  friend void  protobuf_AddDesc_cell_2eproto();
  friend void protobuf_AssignDesc_cell_2eproto();
  friend void protobuf_ShutdownFile_cell_2eproto();
  
  void InitAsDefaultInstance();
  static Cell* default_instance_;
};
// -------------------------------------------------------------------

class Cells : public ::google::protobuf::Message {
 public:
  Cells();
  virtual ~Cells();
  
  Cells(const Cells& from);
  
  inline Cells& operator=(const Cells& from) {
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
  static const Cells& default_instance();
  
  void Swap(Cells* other);
  
  // implements Message ----------------------------------------------
  
  Cells* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Cells& from);
  void MergeFrom(const Cells& from);
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
  
  // repeated .Msg.Cell cell = 1;
  inline int cell_size() const;
  inline void clear_cell();
  static const int kCellFieldNumber = 1;
  inline const ::Msg::Cell& cell(int index) const;
  inline ::Msg::Cell* mutable_cell(int index);
  inline ::Msg::Cell* add_cell();
  inline const ::google::protobuf::RepeatedPtrField< ::Msg::Cell >&
      cell() const;
  inline ::google::protobuf::RepeatedPtrField< ::Msg::Cell >*
      mutable_cell();
  
  // @@protoc_insertion_point(class_scope:Msg.Cells)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::Msg::Cell > cell_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_cell_2eproto();
  friend void protobuf_AssignDesc_cell_2eproto();
  friend void protobuf_ShutdownFile_cell_2eproto();
  
  void InitAsDefaultInstance();
  static Cells* default_instance_;
};
// -------------------------------------------------------------------

class Map : public ::google::protobuf::Message {
 public:
  Map();
  virtual ~Map();
  
  Map(const Map& from);
  
  inline Map& operator=(const Map& from) {
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
  static const Map& default_instance();
  
  void Swap(Map* other);
  
  // implements Message ----------------------------------------------
  
  Map* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Map& from);
  void MergeFrom(const Map& from);
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
  
  // required .Msg.Coordinate startIndex = 1;
  inline bool has_startindex() const;
  inline void clear_startindex();
  static const int kStartIndexFieldNumber = 1;
  inline const ::Msg::Coordinate& startindex() const;
  inline ::Msg::Coordinate* mutable_startindex();
  inline ::Msg::Coordinate* release_startindex();
  
  // required .Msg.Coordinate boundary = 2;
  inline bool has_boundary() const;
  inline void clear_boundary();
  static const int kBoundaryFieldNumber = 2;
  inline const ::Msg::Coordinate& boundary() const;
  inline ::Msg::Coordinate* mutable_boundary();
  inline ::Msg::Coordinate* release_boundary();
  
  // repeated .Msg.Cell cell = 3;
  inline int cell_size() const;
  inline void clear_cell();
  static const int kCellFieldNumber = 3;
  inline const ::Msg::Cell& cell(int index) const;
  inline ::Msg::Cell* mutable_cell(int index);
  inline ::Msg::Cell* add_cell();
  inline const ::google::protobuf::RepeatedPtrField< ::Msg::Cell >&
      cell() const;
  inline ::google::protobuf::RepeatedPtrField< ::Msg::Cell >*
      mutable_cell();
  
  // @@protoc_insertion_point(class_scope:Msg.Map)
 private:
  inline void set_has_startindex();
  inline void clear_has_startindex();
  inline void set_has_boundary();
  inline void clear_has_boundary();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::Msg::Coordinate* startindex_;
  ::Msg::Coordinate* boundary_;
  ::google::protobuf::RepeatedPtrField< ::Msg::Cell > cell_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];
  
  friend void  protobuf_AddDesc_cell_2eproto();
  friend void protobuf_AssignDesc_cell_2eproto();
  friend void protobuf_ShutdownFile_cell_2eproto();
  
  void InitAsDefaultInstance();
  static Map* default_instance_;
};
// ===================================================================


// ===================================================================

// Coordinate

// required int32 coord_x = 1;
inline bool Coordinate::has_coord_x() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Coordinate::set_has_coord_x() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Coordinate::clear_has_coord_x() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Coordinate::clear_coord_x() {
  coord_x_ = 0;
  clear_has_coord_x();
}
inline ::google::protobuf::int32 Coordinate::coord_x() const {
  return coord_x_;
}
inline void Coordinate::set_coord_x(::google::protobuf::int32 value) {
  set_has_coord_x();
  coord_x_ = value;
}

// required int32 coord_y = 2;
inline bool Coordinate::has_coord_y() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Coordinate::set_has_coord_y() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Coordinate::clear_has_coord_y() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Coordinate::clear_coord_y() {
  coord_y_ = 0;
  clear_has_coord_y();
}
inline ::google::protobuf::int32 Coordinate::coord_y() const {
  return coord_y_;
}
inline void Coordinate::set_coord_y(::google::protobuf::int32 value) {
  set_has_coord_y();
  coord_y_ = value;
}

// required int32 coord_z = 3;
inline bool Coordinate::has_coord_z() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Coordinate::set_has_coord_z() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Coordinate::clear_has_coord_z() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Coordinate::clear_coord_z() {
  coord_z_ = 0;
  clear_has_coord_z();
}
inline ::google::protobuf::int32 Coordinate::coord_z() const {
  return coord_z_;
}
inline void Coordinate::set_coord_z(::google::protobuf::int32 value) {
  set_has_coord_z();
  coord_z_ = value;
}

// -------------------------------------------------------------------

// Cell_WindVector

// required double wv_x = 1;
inline bool Cell_WindVector::has_wv_x() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Cell_WindVector::set_has_wv_x() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Cell_WindVector::clear_has_wv_x() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Cell_WindVector::clear_wv_x() {
  wv_x_ = 0;
  clear_has_wv_x();
}
inline double Cell_WindVector::wv_x() const {
  return wv_x_;
}
inline void Cell_WindVector::set_wv_x(double value) {
  set_has_wv_x();
  wv_x_ = value;
}

// required double wv_y = 2;
inline bool Cell_WindVector::has_wv_y() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Cell_WindVector::set_has_wv_y() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Cell_WindVector::clear_has_wv_y() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Cell_WindVector::clear_wv_y() {
  wv_y_ = 0;
  clear_has_wv_y();
}
inline double Cell_WindVector::wv_y() const {
  return wv_y_;
}
inline void Cell_WindVector::set_wv_y(double value) {
  set_has_wv_y();
  wv_y_ = value;
}

// required double wv_z = 3;
inline bool Cell_WindVector::has_wv_z() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Cell_WindVector::set_has_wv_z() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Cell_WindVector::clear_has_wv_z() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Cell_WindVector::clear_wv_z() {
  wv_z_ = 0;
  clear_has_wv_z();
}
inline double Cell_WindVector::wv_z() const {
  return wv_z_;
}
inline void Cell_WindVector::set_wv_z(double value) {
  set_has_wv_z();
  wv_z_ = value;
}

// -------------------------------------------------------------------

// Cell_Wind

// required .Msg.Cell.WindVector wind = 1;
inline bool Cell_Wind::has_wind() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Cell_Wind::set_has_wind() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Cell_Wind::clear_has_wind() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Cell_Wind::clear_wind() {
  if (wind_ != NULL) wind_->::Msg::Cell_WindVector::Clear();
  clear_has_wind();
}
inline const ::Msg::Cell_WindVector& Cell_Wind::wind() const {
  return wind_ != NULL ? *wind_ : *default_instance_->wind_;
}
inline ::Msg::Cell_WindVector* Cell_Wind::mutable_wind() {
  set_has_wind();
  if (wind_ == NULL) wind_ = new ::Msg::Cell_WindVector;
  return wind_;
}
inline ::Msg::Cell_WindVector* Cell_Wind::release_wind() {
  clear_has_wind();
  ::Msg::Cell_WindVector* temp = wind_;
  wind_ = NULL;
  return temp;
}

// required .Msg.Cell.WindVector potential = 2;
inline bool Cell_Wind::has_potential() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Cell_Wind::set_has_potential() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Cell_Wind::clear_has_potential() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Cell_Wind::clear_potential() {
  if (potential_ != NULL) potential_->::Msg::Cell_WindVector::Clear();
  clear_has_potential();
}
inline const ::Msg::Cell_WindVector& Cell_Wind::potential() const {
  return potential_ != NULL ? *potential_ : *default_instance_->potential_;
}
inline ::Msg::Cell_WindVector* Cell_Wind::mutable_potential() {
  set_has_potential();
  if (potential_ == NULL) potential_ = new ::Msg::Cell_WindVector;
  return potential_;
}
inline ::Msg::Cell_WindVector* Cell_Wind::release_potential() {
  clear_has_potential();
  ::Msg::Cell_WindVector* temp = potential_;
  potential_ = NULL;
  return temp;
}

// -------------------------------------------------------------------

// Cell_Methane

// required double concentration = 1;
inline bool Cell_Methane::has_concentration() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Cell_Methane::set_has_concentration() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Cell_Methane::clear_has_concentration() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Cell_Methane::clear_concentration() {
  concentration_ = 0;
  clear_has_concentration();
}
inline double Cell_Methane::concentration() const {
  return concentration_;
}
inline void Cell_Methane::set_concentration(double value) {
  set_has_concentration();
  concentration_ = value;
}

// -------------------------------------------------------------------

// Cell

// required .Msg.Coordinate coord = 1;
inline bool Cell::has_coord() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Cell::set_has_coord() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Cell::clear_has_coord() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Cell::clear_coord() {
  if (coord_ != NULL) coord_->::Msg::Coordinate::Clear();
  clear_has_coord();
}
inline const ::Msg::Coordinate& Cell::coord() const {
  return coord_ != NULL ? *coord_ : *default_instance_->coord_;
}
inline ::Msg::Coordinate* Cell::mutable_coord() {
  set_has_coord();
  if (coord_ == NULL) coord_ = new ::Msg::Coordinate;
  return coord_;
}
inline ::Msg::Coordinate* Cell::release_coord() {
  clear_has_coord();
  ::Msg::Coordinate* temp = coord_;
  coord_ = NULL;
  return temp;
}

// required .Msg.CellTag tag = 2;
inline bool Cell::has_tag() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Cell::set_has_tag() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Cell::clear_has_tag() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Cell::clear_tag() {
  tag_ = 1;
  clear_has_tag();
}
inline Msg::CellTag Cell::tag() const {
  return static_cast< Msg::CellTag >(tag_);
}
inline void Cell::set_tag(Msg::CellTag value) {
  GOOGLE_DCHECK(Msg::CellTag_IsValid(value));
  set_has_tag();
  tag_ = value;
}

// required .Msg.Cell.Methane mtn = 3;
inline bool Cell::has_mtn() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Cell::set_has_mtn() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Cell::clear_has_mtn() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Cell::clear_mtn() {
  if (mtn_ != NULL) mtn_->::Msg::Cell_Methane::Clear();
  clear_has_mtn();
}
inline const ::Msg::Cell_Methane& Cell::mtn() const {
  return mtn_ != NULL ? *mtn_ : *default_instance_->mtn_;
}
inline ::Msg::Cell_Methane* Cell::mutable_mtn() {
  set_has_mtn();
  if (mtn_ == NULL) mtn_ = new ::Msg::Cell_Methane;
  return mtn_;
}
inline ::Msg::Cell_Methane* Cell::release_mtn() {
  clear_has_mtn();
  ::Msg::Cell_Methane* temp = mtn_;
  mtn_ = NULL;
  return temp;
}

// required .Msg.Cell.Wind wind = 4;
inline bool Cell::has_wind() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Cell::set_has_wind() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Cell::clear_has_wind() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Cell::clear_wind() {
  if (wind_ != NULL) wind_->::Msg::Cell_Wind::Clear();
  clear_has_wind();
}
inline const ::Msg::Cell_Wind& Cell::wind() const {
  return wind_ != NULL ? *wind_ : *default_instance_->wind_;
}
inline ::Msg::Cell_Wind* Cell::mutable_wind() {
  set_has_wind();
  if (wind_ == NULL) wind_ = new ::Msg::Cell_Wind;
  return wind_;
}
inline ::Msg::Cell_Wind* Cell::release_wind() {
  clear_has_wind();
  ::Msg::Cell_Wind* temp = wind_;
  wind_ = NULL;
  return temp;
}

// -------------------------------------------------------------------

// Cells

// repeated .Msg.Cell cell = 1;
inline int Cells::cell_size() const {
  return cell_.size();
}
inline void Cells::clear_cell() {
  cell_.Clear();
}
inline const ::Msg::Cell& Cells::cell(int index) const {
  return cell_.Get(index);
}
inline ::Msg::Cell* Cells::mutable_cell(int index) {
  return cell_.Mutable(index);
}
inline ::Msg::Cell* Cells::add_cell() {
  return cell_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Msg::Cell >&
Cells::cell() const {
  return cell_;
}
inline ::google::protobuf::RepeatedPtrField< ::Msg::Cell >*
Cells::mutable_cell() {
  return &cell_;
}

// -------------------------------------------------------------------

// Map

// required .Msg.Coordinate startIndex = 1;
inline bool Map::has_startindex() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Map::set_has_startindex() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Map::clear_has_startindex() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Map::clear_startindex() {
  if (startindex_ != NULL) startindex_->::Msg::Coordinate::Clear();
  clear_has_startindex();
}
inline const ::Msg::Coordinate& Map::startindex() const {
  return startindex_ != NULL ? *startindex_ : *default_instance_->startindex_;
}
inline ::Msg::Coordinate* Map::mutable_startindex() {
  set_has_startindex();
  if (startindex_ == NULL) startindex_ = new ::Msg::Coordinate;
  return startindex_;
}
inline ::Msg::Coordinate* Map::release_startindex() {
  clear_has_startindex();
  ::Msg::Coordinate* temp = startindex_;
  startindex_ = NULL;
  return temp;
}

// required .Msg.Coordinate boundary = 2;
inline bool Map::has_boundary() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Map::set_has_boundary() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Map::clear_has_boundary() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Map::clear_boundary() {
  if (boundary_ != NULL) boundary_->::Msg::Coordinate::Clear();
  clear_has_boundary();
}
inline const ::Msg::Coordinate& Map::boundary() const {
  return boundary_ != NULL ? *boundary_ : *default_instance_->boundary_;
}
inline ::Msg::Coordinate* Map::mutable_boundary() {
  set_has_boundary();
  if (boundary_ == NULL) boundary_ = new ::Msg::Coordinate;
  return boundary_;
}
inline ::Msg::Coordinate* Map::release_boundary() {
  clear_has_boundary();
  ::Msg::Coordinate* temp = boundary_;
  boundary_ = NULL;
  return temp;
}

// repeated .Msg.Cell cell = 3;
inline int Map::cell_size() const {
  return cell_.size();
}
inline void Map::clear_cell() {
  cell_.Clear();
}
inline const ::Msg::Cell& Map::cell(int index) const {
  return cell_.Get(index);
}
inline ::Msg::Cell* Map::mutable_cell(int index) {
  return cell_.Mutable(index);
}
inline ::Msg::Cell* Map::add_cell() {
  return cell_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Msg::Cell >&
Map::cell() const {
  return cell_;
}
inline ::google::protobuf::RepeatedPtrField< ::Msg::Cell >*
Map::mutable_cell() {
  return &cell_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Msg

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< Msg::CellTag>() {
  return Msg::CellTag_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_cell_2eproto__INCLUDED
