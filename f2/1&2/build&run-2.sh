#!/usr/bin/env bash

rm -- *.o *.a *.so *.out 2>/dev/null

echo '========== Compiling complex library =========='

gcc -Wall -c -fPIC -o complex.o complex.c

gcc -shared -o libcomplex.so complex.o

echo '============== Compiling program =============='

gcc -Wall use_complex.c -o use_complex.out -L. -lcomplex -lm

echo '=============== Running program ==============='

export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

./use_complex.out
