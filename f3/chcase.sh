#!/usr/bin/env bash

if [[ ! -x chcase.out ]]; then
    ./build.sh
fi

TEST="Ads fTsfsdsR DSda BVHGIsdssdeSds
Dfcdfd 45343f rerTEuk
qqfFGfhuymIOu 95r342"

echo -e '\e[34mecho '\'"$TEST"\'' > test.txt\e[0m'
echo "$TEST" >test.txt

echo -e '\e[34m./chcase.out test.txt\e[0m'
./chcase.out test.txt
echo -e '\e[34m./chcase.out -l test.txt\e[0m'
./chcase.out -l test.txt
echo -e '\e[34m./chcase.out -u test.txt\e[0m'
./chcase.out -u test.txt

rm test.txt
