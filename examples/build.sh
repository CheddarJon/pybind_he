#!/bin/sh
if [ -e ${PWD}/bin ];
then
    echo "bin already exists."
else
    mkdir -v bin;
fi

if [ -e ${PWD}/build ];
then
    cd build
else
    mkdir -v build && cd build;
fi

if [ -e ${helib_DIR} ];
then
    cmake ..
else
    echo "set helib_DIR: export helib_DIR=/path/to/helib_pack/share/cmake/helib";
fi

if [ -e ${PWD}/Makefile ];
then
    make all && cd ..
else
    echo "No makefile.";
fi

if [ -e ${PWD}/build ];
then
    echo "Removing build files from "$(realpath build/);
    rm -rI build/
else
    echo "Build does not exist.";
fi


