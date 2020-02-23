#!/bin/bash

# SO YOU'VE (!) 
# 1. GENERATED THE HELIB_PATH
# 2. PLACED IT UNDER LIB
# good ;)


./export_HElib_pack_path.sh
cd ../examples/
./build.sh
sleep 1 # BUILD STEP DONE
./bin/bgv_matrix_op