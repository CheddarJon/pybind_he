#!/bin/sh

if [ -e ../bin ];
then
    echo "bin already exists."
else
    mkdir -v ../bin;
fi

PYTHON_PATH="/usr/include/python3.6m"

g++ \
-pthread -DNDEBUG -g -fwrapv -O2 -Wall -g -fstack-protector-strong -Wformat -Werror=format-security \
-Wdate-time -D_FORTIFY_SOURCE=2 \
-fPIC -I ../lib/pybind11 \
-I ../lib/helib_pack/include \
-I "${PYTHON_PATH}" \
-c ../pybind_he/pybind_he.cpp \
-o ../build/pybind_he.o -D BARE_BONE

g++ ../build/pybind_he.o -o ../build/pybind_he -Wl,-rpath,../lib/helib_pack/lib \
../lib/helib_pack/lib/libhelib.a \
../lib/helib_pack/lib/libntl.so \
../lib/helib_pack/lib/libgmp.so -lpthread

