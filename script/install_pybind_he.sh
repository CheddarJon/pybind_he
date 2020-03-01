#!/bin/bash


if [ $1 ]
then
	python3 ../setup.py install --home="../lib"
else
	python3 ../setup.py install
fi

rm -r -f build