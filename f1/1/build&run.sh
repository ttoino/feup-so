#!/usr/bin/env bash

rm -- *.o *.a *.s *.so *.out 2>/dev/null

echo '============ Running pre-processor ============'

gcc -E hello.c

echo '=========== Compiling into assembly ==========='

gcc -S hello.c
cat hello.s

echo '============== Compiling program =============='

gcc -Wall -o hello.out hello.c

echo '=============== Running program ==============='

./hello.out
