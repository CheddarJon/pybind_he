#!/bin/sh
root=$(realpath $(dirname $(readlink -f $0))/..)
src="${root}/src/tfhe"
bin="${root}/bin"
fft="-ltfhe-fftw"
gcc -g -pg ${src}/client_tfhe.c -o ${bin}/client_tfhe $fft
echo "${src}/client_tfhe.c -> ${bin}/client_tfhe"
gcc -g -pg ${src}/server_tfhe.c -o ${bin}/server_tfhe $fft
echo "${src}/server_tfhe.c -> ${bin}/server_tfhe"
