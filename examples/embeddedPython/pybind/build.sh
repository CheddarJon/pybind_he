#!/bin/sh

build()
{
    echo "Building..."
    mkdir build
    cd build
    cmake ..
    make
    mv pb_int ..
    cd ..
}

run_test()
{
    echo "--------------------------------------------------------"
    echo "Running tests: should run c++ first and then python..."
    echo "--------------------------------------------------------"
    unset PYTHON_OVERLAY
    ./pb_int

    echo "Setting PYTHON_OVERLAY..."
    export PYTHON_OVERLAY=MockFPGA
    ./pb_int
}

cleanup()
{
    echo "Cleaning up files..."
    rm -rf __pycache__ build/ pb_int
    unset PYTHON_OVERLAY
}

build
run_test
cleanup
