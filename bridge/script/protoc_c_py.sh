#!/bin/sh
#

protoc_bin=/usr/local/Cellar/protobuf241/2.4.1/bin/protoc
proto_dir=/Users/kding/Desktop/Sniffer2/bridge/interface
cxx_dir=/Users/kding/Desktop/Sniffer2/SnifferCxx/SnifferCxx/message
py_dir=/Users/kding/Desktop/Sniffer2/SnifferPy/src/message

$protoc_bin -I=$proto_dir --cpp_out=$cxx_dir $proto_dir/*.proto
$protoc_bin -I=$proto_dir --python_out=$py_dir $proto_dir/*.proto

palmc $proto_dir $py_dir