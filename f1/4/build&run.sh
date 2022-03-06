#!/usr/bin/env bash

rm -- *.o *.a *.s *.so *.out 2>/dev/null

echo '============ Compiling char_array ============='

gcc -Wall -o char_array.out char_array.c

echo '============= Running char_array =============='

./char_array.out

echo '============= Compiling int_array ============='

gcc -Wall -o int_array.out int_array.c

echo '============== Running int_array =============='

./int_array.out
