#!/bin/bash

# SO YOU'VE (!) 
# 1. GENERATED THE HELIB_PATH
# 2. PLACED IT UNDER LIB
# good ;)


prefix=$(realpath ../lib/helib_path)
export CMAKE_PREFIX_PATH="$prefix"
cd ../examples/
./build.sh
sleep 1 # BUILD STEP DONE
./bin/bgv_matrix_op