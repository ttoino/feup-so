#!/usr/bin/env bash

if [[ ! -x naughty.out ]]; then
    ./build.sh
fi

echo -e '\e[34m./naughty a\e[0m'
./naughty.out a
echo -e '\e[34m./naughty ab\e[0m'
./naughty.out ab
echo -e '\e[34m./naughty abc\e[0m'
./naughty.out abc
echo -e '\e[34m./naughty abcd\e[0m'
./naughty.out abcd
echo -e '\e[34m./naughty abcde\e[0m'
./naughty.out abcde
echo -e '\e[34m./naughty abcdef\e[0m'
./naughty.out abcdef
echo -e '\e[34m./naughty abcdefg\e[0m'
./naughty.out abcdefg
echo -e '\e[34m./naughty abcdefgh\e[0m'
./naughty.out abcdefgh
echo -e '\e[34m./naughty abcdefghi\e[0m'
./naughty.out abcdefghi
echo -e '\e[34m./naughty abcdefghij\e[0m'
./naughty.out abcdefghij
