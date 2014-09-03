
set protoc250=C:\tools\protobuf250\bin\protoc.exe
set protoc241=C:\tools\protobuf241\bin\protoc.exe

set proto_dir=../interface
set cxx_dir=../../SnifferCxx/SnifferCxx/protomsg
set py_dir=../../SnifferPy/src/message/protobuf

%protoc250% -I=%proto_dir% --cpp_out=%cxx_dir% %proto_dir%/cell.proto %proto_dir%/hypothesis.proto %proto_dir%/dect.proto
%protoc250% -I=%proto_dir% --python_out=%py_dir% %proto_dir%/cell.proto %proto_dir%/hypothesis.proto %proto_dir%/dect.proto