#!/bin/sh
mkdir build &&
cd build &&
cmake -Dhelib_DIR="${PWD}/../../lib/helib_pack/share/cmake/helib" .. &&
make &&
mv bgv_matrix_op .. &&
cd .. && rm -rf build/
