protoc -I=../interface/ --cpp_out=../../SnifferCxx/SnifferCxx/message ../interface/*.proto
protoc -I=../interface/ --python_out=../../SnifferPy/src/message ../interface/*.proto