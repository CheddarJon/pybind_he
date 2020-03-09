#!/bin/sh
gcc -g -pg tutorial_tfhe.c -o bin/tutorial_tfhe -ltfhe-fftw
gcc -g -pg client_tfhe.c -o bin/client_tfhe -ltfhe-fftw
gcc -g -pg server_tfhe.c -o bin/server_tfhe -ltfhe-fftw
