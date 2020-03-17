# pybind_he
Repo to try out using pybind11 to wrap parts of a c++ library.

Requirements: Install HElib, and place helib_pack in the project lib/ directory.
pybind11 installed.

Add to shell init file:
export PYTHONPATH=/path/to/this/repo/lib
export LD_LIBRARY_PATH=/path/to/this/repo/lib/helib_pack/lib

To build run: python setup.py build

Copy .so file from build directory into lib/

###  For sanity check:

[SANITY](docs/SANITY_CHECK.md) 

### Procedure 

[PROCEDURE](docs/WSL_PROCEDURE.md) 

### Visual Studio

[Visual Studio](vs/VS.md)

### Install TFHE globally as root (optional)

[Install Script](script/tfhe_local_computer_install.sh)