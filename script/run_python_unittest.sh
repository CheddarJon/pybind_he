#!/bin/bash


sleep 10

#export PYTHONPATH=$(realpath ${PWD}/../lib)
python3 -m unittest discover ../
