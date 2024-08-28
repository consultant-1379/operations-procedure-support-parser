#!/bin/bash
export LD_LIBRARY_PATH=../ops-parser-lib/target/visibroker/lib/:/usr/local/lib/:/usr/local/lib64/
valgrind --log-file=val.log ../ops-parser-lib/unit_test/make/gmock_test
