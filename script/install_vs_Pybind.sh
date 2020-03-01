#!/bin/bash

# DON'T FORGET TO CHECKOUT THE SUBMODULES (!)


mkdir ../submodules/Pybind/build
cd ../submodules/Pybind/build
cmake ..
cmake --build . --config Release --target check
