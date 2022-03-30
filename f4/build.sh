#!/usr/bin/env bash

rm -- *.o *.a *.so *.out 2>/dev/null

for src in *.c; do
    echo "Building $src"

    gcc -Wall -o "${src::-2}.out" "$src"

    echo
done
