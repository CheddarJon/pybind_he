#!/bin/bash

mkdir ../build

g++ \
-pthread -DNDEBUG -g -fwrapv -O2 -Wall -g -fstack-protector-strong -Wformat -Werror=format-security \
-Wdate-time -D_FORTIFY_SOURCE=2 \
-fPIC -I/mnt/c/git/pybind_he/lib/pybind11 \
-I/mnt/c/git/pybind_he/lib/helib_pack/include \
-I/usr/include/python3.6m \
-c /mnt/c/git/pybind_he/pybind_he/pybind_he.cpp \
-o ../build/pybind_he.o -D BARE_BONE

g++ ../build/pybind_he.o -o ../build/pybind_he -Wl,-rpath,../lib/helib_pack/lib \
../lib/helib_pack/lib/libhelib.a \
../lib/helib_pack/lib/libntl.so \
../lib/helib_pack/lib/libgmp.so -lpthread

