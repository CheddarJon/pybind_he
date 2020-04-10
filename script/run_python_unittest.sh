#!/bin/bash

export PYTHONPATH=$(realpath ${PWD}/../lib)
python3 -m unittest discover ../
