#!/bin/sh
#
/usr/local/Cellar/protobuf/2.5.0/bin/protoc -I=/Users/kding/Desktop/Sniffer2/bridge/interface/ --cpp_out=/Users/kding/Desktop/Sniffer2/SnifferCxx/SnifferCxx/message /Users/kding/Desktop/Sniffer2/bridge/interface/cell.proto /Users/kding/Desktop/Sniffer2/bridge/interface/hypothesis.proto /Users/kding/Desktop/Sniffer2/bridge/interface/dect.proto
/usr/local/Cellar/protobuf/2.5.0/bin/protoc -I=/Users/kding/Desktop/Sniffer2/bridge/interface/ --python_out=/Users/kding/Desktop/Sniffer2/SnifferPy/src/message /Users/kding/Desktop/Sniffer2/bridge/interface/cell.proto /Users/kding/Desktop/Sniffer2/bridge/interface/hypothesis.proto /Users/kding/Desktop/Sniffer2/bridge/interface/dect.proto
