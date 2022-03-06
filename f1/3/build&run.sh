#!/usr/bin/env bash

rm -- *.o *.a *.s *.so *.out 2>/dev/null

echo '============== Compiling program =============='

gcc -Wall -o pointers1.out pointers1.c

echo '=============== Running program ==============='

./pointers1.out
