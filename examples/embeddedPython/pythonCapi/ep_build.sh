#!/bin/sh
cflags=$(python-config --cflags)
ldflags=$(python-config --ldflags)
gcc ${cflags} -o bin/vhle_test ${ldflags} "-lpython3.8" vhle_test.c
gcc ${cflags} -o bin/pe_test ${ldflags} "-lpython3.8" pe_test.c
gcc ${cflags} -o bin/eep ${ldflags} "-lpython3.8" eep.c
