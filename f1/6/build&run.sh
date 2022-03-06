#!/usr/bin/env bash

rm -- *.o *.a *.s *.so *.out 2>/dev/null

echo '============ Compiling bad_pointer ============'

gcc -w -o bad_pointer.out bad_pointer.c

echo '============= Running bad_pointer ============='

./bad_pointer.out

echo '=========== Compiling good_pointer ============'

gcc -Wall -o good_pointer.out good_pointer.c

echo '============ Running good_pointer ============='

./good_pointer.out
