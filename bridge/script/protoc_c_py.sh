#!/bin/sh
#

protoc241=/usr/local/Cellar/protobuf241/2.4.1/bin/protoc
protoc250=/usr/local/Cellar/protobuf/2.5.0/bin/protoc
proto_dir=/Users/kding/Desktop/Sniffer2/bridge/interface
cxx_dir=/Users/kding/Desktop/Sniffer2/SnifferCxx/SnifferCxx/protomsg
py_dir=/Users/kding/Desktop/Sniffer2/SnifferPy/src/protomsg

$protoc250 -I=$proto_dir --cpp_out=$cxx_dir $proto_dir/*.proto
$protoc250 -I=$proto_dir --python_out=$py_dir $proto_dir/*.proto

palmc $proto_dir $py_dir