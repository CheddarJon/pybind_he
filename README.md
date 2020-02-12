# pybind_he
Repo to try out using pybind11 to wrap parts of a c++ library.

Requirements: Install HElib, and place helib_pack in the project lib/ directory.
pybind11 installed.

Add to shell init file:
export PYTHONPATH=/path/to/this/repo/lib
export LD_LIBRARY_PATH=/path/to/this/repo/lib/helib_pack/lib

To build run: python setup.py build

Copy .so file from build directory into lib/
