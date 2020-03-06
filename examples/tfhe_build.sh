#!/bin/sh
gcc tutorial_tfhe.c -o bin/tutorial_tfhe -ltfhe-fftw
gcc client_tfhe.c -o bin/client_tfhe -ltfhe-fftw
gcc server_tfhe.c -o bin/server_tfhe -ltfhe-fftw
