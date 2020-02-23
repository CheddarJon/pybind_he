#!/bin/bash

# DON'T FORGET TO CHECKOUT THE SUBMODULES (!)

mkdir ../submodules/HElib/build
cd ../submodules/HElib/
pwd
#export CMAKE_INSTALL_PREFIX=/home/shit
cmake -DPACKAGE_BUILD=ON -DCMAKE_INSTALL_PREFIX=/build
make -j16
make test