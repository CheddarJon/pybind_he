#!/bin/bash

export helib_DIR=$(realpath ${PWD}/lib/helib_pack/share/cmake/helib)
echo "helib_DIR ${helib_DIR}"

mkdir build
cd build
cmake ..
make
rm -r -f build