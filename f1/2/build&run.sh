#!/usr/bin/env bash

rm -- *.o *.a *.s *.so *.out 2>/dev/null

echo '============== Compiling program =============='

gcc -Wall -lm -o trig.out trig.c

echo '=============== Running program ==============='

./trig.out
