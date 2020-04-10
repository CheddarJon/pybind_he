#!/bin/sh

mkdir run &&
cp bin/server_tfhe bin/client_tfhe run &&
cd run &&
echo "Running client" &&
./client_tfhe &&
echo "Running server" &&
./server_tfhe &&
echo "Running client" &&
./client_tfhe &&
rm * &&
cd .. &&
rmdir run
