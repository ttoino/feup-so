#!/usr/bin/env bash

rm -- *.o *.a *.s *.so *.out 2>/dev/null

echo '=========== Compiling call_by_value ==========='

gcc -Wall -o call_by_value.out call_by_value.c

echo '============ Running call_by_value ============'

./call_by_value.out

echo '========= Compiling call_by_reference ========='

gcc -Wall -o call_by_reference.out call_by_reference.c

echo '========== Running call_by_reference =========='

./call_by_reference.out
