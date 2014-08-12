# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: dect.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)


import hypothesis_pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='dect.proto',
  package='Filesystem',
  serialized_pb='\n\ndect.proto\x12\nFilesystem\x1a\x10hypothesis.proto\"9\n\tDetection\x12\x0c\n\x04time\x18\x01 \x02(\x05\x12\x1e\n\x04leak\x18\x02 \x03(\x0b\x32\x10.Filesystem.Leak\"1\n\nDetections\x12#\n\x04\x64\x65\x63t\x18\x01 \x03(\x0b\x32\x15.Filesystem.Detection')




_DETECTION = _descriptor.Descriptor(
  name='Detection',
  full_name='Filesystem.Detection',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='time', full_name='Filesystem.Detection.time', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='leak', full_name='Filesystem.Detection.leak', index=1,
      number=2, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=44,
  serialized_end=101,
)


_DETECTIONS = _descriptor.Descriptor(
  name='Detections',
  full_name='Filesystem.Detections',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='dect', full_name='Filesystem.Detections.dect', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=103,
  serialized_end=152,
)

_DETECTION.fields_by_name['leak'].message_type = hypothesis_pb2._LEAK
_DETECTIONS.fields_by_name['dect'].message_type = _DETECTION
DESCRIPTOR.message_types_by_name['Detection'] = _DETECTION
DESCRIPTOR.message_types_by_name['Detections'] = _DETECTIONS

class Detection(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _DETECTION

  # @@protoc_insertion_point(class_scope:Filesystem.Detection)

class Detections(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _DETECTIONS

  # @@protoc_insertion_point(class_scope:Filesystem.Detections)


# @@protoc_insertion_point(module_scope)
