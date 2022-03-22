#!/usr/bin/env bash

if [[ ! -x mywc.out ]]; then
    ./build.sh
fi

echo -e '\e[34mecho '\''This is a test'\'' > file.txt\e[0m'
echo 'This is a test' >file.txt

echo -e '\e[34m./mywc.out file.txt\e[0m'
./mywc.out file.txt

echo -e '\e[34m./mywc.out -c file.txt\e[0m'
./mywc.out -c file.txt

echo -e '\e[34m./mywc.out -w file.txt\e[0m'
./mywc.out -w file.txt

echo -e '\e[34m./mywc.out -l file.txt\e[0m'
./mywc.out -l file.txt

rm file.txt
