#!/bin/bash

# DON'T FORGET TO CHECKOUT THE SUBMODULES (!)

mkdir ../submodules/HElib/build
cd ../submodules/HElib/
pwd

cmake -DPACKAGE_BUILD=ON -DENABLE_TEST=ON -DCMAKE_INSTALL_PREFIX=/build
make -j16
make test
