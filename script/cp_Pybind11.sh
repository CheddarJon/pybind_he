#!/bin/bash

DEST=$(realpath ../lib)

mkdir -p $DEST/pybind11
cp -r ../submodules/Pybind/include/pybind11 $DEST/pybind11