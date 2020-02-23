#!/bin/bash


ABSPATH=$(readlink -f $0)
ABSDIR=$(dirname $ABSPATH)
# Populate all paths
HELIBPACK=$(realpath $ABSDIR/../lib/helib_pack)
HELIBCMAKE=$(realpath $ABSDIR/../lib/helib_pack/share/cmake)

export CMAKE_PREFIX_PATH="$HELIBPACK"
export helib_DIR="$HELIBCMAKE"

echo "|====================================================|"
echo "CMAKE_PREFIX_PATH SET(!): ${CMAKE_PREFIX_PATH}"
echo "HELIB_DIR PATH SET(!): ${helib_DIR}"
echo "|====================================================|"