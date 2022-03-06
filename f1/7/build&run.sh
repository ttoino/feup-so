#!/usr/bin/env bash

rm -- *.o *.a *.s *.so *.out 2>/dev/null

echo '============== Compiling program =============='

gcc -rdynamic -Wall -o trace.out trace.c

echo '=============== Running program ==============='

./trace.out
