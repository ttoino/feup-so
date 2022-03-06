#!/usr/bin/env bash

rm -- *.o *.a *.so *.out 2>/dev/null

echo '=========== Compiling list library ============'

gcc -Wall -c list.c

ar -rc liblist.a list.o

ar -t liblist.a

echo '============== Compiling program =============='

gcc -Wall use_list.c -o use_list.out -L. -llist -lm

echo '=============== Running program ==============='

./use_list.out
