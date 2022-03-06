#!/usr/bin/env bash

rm -- *.o *.a *.so *.out 2>/dev/null

echo '========== Compiling matrix library ==========='

gcc -Wall -c matrix.c

ar -rc libmatrix.a matrix.o

ar -t libmatrix.a

echo '============== Compiling program =============='

gcc -Wall use_matrix.c -o use_matrix.out -L. -lmatrix -lm

echo '=============== Running program ==============='

./use_matrix.out
