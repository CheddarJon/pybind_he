#!/bin/sh
cflags=$(python-config --cflags)
ldflags=$(python-config --ldflags)
gcc ${cflags} -o vhle_test ${ldflags} "-lpython3.8" vhle_test.c
gcc ${cflags} -o pe_test ${ldflags} "-lpython3.8" pe_test.c
