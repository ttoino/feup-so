#!/usr/bin/env bash

rm -- *.o *.a *.so *.out 2>/dev/null

echo '========== Compiling complex library =========='

gcc -Wall -c complex.c

ar -rc libcomplex.a complex.o

ar -t libcomplex.a

echo '============== Compiling program =============='

gcc -Wall use_complex.c -o use_complex.out -L. -lcomplex -lm

echo '=============== Running program ==============='

./use_complex.out
