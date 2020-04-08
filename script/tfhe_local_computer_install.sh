#!/bin/bash

if [ "$EUID" -ne 0 ]
  then echo "To install tfhe globally in your computer, run as root"
  exit
fi

cd ../submodules/tfhe
make install
