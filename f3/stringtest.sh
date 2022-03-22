#!/usr/bin/env bash

if [[ ! -x stringtest.out ]]; then
    ./build.sh
fi

echo -e '\e[34m./stringtest.out '\''Hello world!'\'' '\''Hello world!'\''\e[0m'
./stringtest.out 'Hello world!' 'Hello world!'

echo -e '\e[34m./stringtest.out '\''Hello World!'\'' '\''Hello world!'\''\e[0m'
./stringtest.out 'Hello World!' 'Hello world!'

echo -e '\e[34m./stringtest.out '\''Hi world!'\'' '\''Hello world!'\''\e[0m'
./stringtest.out 'Hi world!' 'Hello world!'

echo -e '\e[34m./stringtest.out '\''A'\'' '\''B'\''\e[0m'
./stringtest.out 'A' 'B'

echo -e '\e[34m./stringtest.out '\''B'\'' '\''A'\''\e[0m'
./stringtest.out 'B' 'A'
