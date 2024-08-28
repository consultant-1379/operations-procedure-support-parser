#!/bin/bash
SRC_DIR=/parser/ops-parser-lib/lib/proto_sles
DST_DIR=/parser/ops-parser-lib/lib/proto_sles
sudo protoc -I/usr/local/include -I=$SRC_DIR --grpc_out=$DST_DIR --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin $SRC_DIR/winfiolAxeMed.proto
sudo protoc -I/usr/local/include -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/winfiolAxeMed.proto
