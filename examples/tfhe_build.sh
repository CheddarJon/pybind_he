#!/bin/sh
gcc tutorial_tfhe.c -o bin/tutorial_tfhe -ltfhe-spqlios-fma
gcc client_tfhe.c -o bin/client_tfhe -ltfhe-spqlios-fma
