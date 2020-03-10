#!/bin/sh
root=$(realpath $(dirname $(readlink -f $0))/..)
src="${root}/src/baseline"
bin="${root}/bin"
lflags="-lcrypto"
gcc -g -pg ${src}/client_bl.c -o ${bin}/client_bl $lflags
echo "${src}/client_bl.c -> ${bin}/client_bl"
gcc -g -pg ${src}/server_bl.c -o ${bin}/server_bl $lflags
echo "${src}/server_bl.c -> ${bin}/server_bl"
