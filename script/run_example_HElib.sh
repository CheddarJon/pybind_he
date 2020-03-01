#!/bin/bash

# SO YOU'VE (!)
# 1. GENERATED THE HELIB_PATH
# 2. PLACED IT UNDER LIB
# good ;)

export CMAKE_VERBOSE_MAKEFILE=TRUE
export helib_DIR=$(realpath ${PWD}/../lib/helib_pack/share/cmake/helib)
cd ../examples/
./build.sh
sleep 1 # BUILD STEP DONE
./bin/bgv_matrix_op
