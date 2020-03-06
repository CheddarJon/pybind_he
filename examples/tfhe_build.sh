#!/bin/sh
gcc tutorial_tfhe.c -o bin/tutorial_tfhe -ltfhe-spqlios-fma
gcc client_tfhe.c -o bin/client_tfhe -ltfhe-spqlios-fma
gcc server_tfhe.c -o bin/server_tfhe -ltfhe-spqlios-fma
