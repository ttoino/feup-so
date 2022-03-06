#!/usr/bin/env bash

rm -- *.o *.a *.so *.out 2>/dev/null

echo '========== Compiling vector library ==========='

gcc -Wall -c vector.c

ar -rc libvector.a vector.o

ar -t libvector.a

echo '============== Compiling program =============='

gcc -Wall use_vector.c -o use_vector.out -L. -lvector -lm

echo '=============== Running program ==============='

./use_vector.out
