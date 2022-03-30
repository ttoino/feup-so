#!/usr/bin/env bash

if [[ ! -x mychmod.out ]]; then
    ./build.sh
fi

echo -e '\e[34mtouch test\e[0m'
touch 'test'
echo -e '\e[34mls -l test\e[0m'
ls -l 'test'
echo -e '\e[34m./mychmod 755 test\e[0m'
./mychmod 755 'test'
echo -e '\e[34mls -l test\e[0m'
ls -l 'test'
echo -e '\e[34m./mychmod 799 test\e[0m'
./mychmod 799 'test'

rm 'test'
