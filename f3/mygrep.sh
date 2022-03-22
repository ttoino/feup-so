#!/usr/bin/env bash

TEST="This is a long string to test mygrep
test test test
I am testing"

if [[ ! -x mygrep.out ]]; then
    ./build.sh
fi

echo -e '\e[34mecho '\'"$TEST"\'' > test.txt\e[0m'
echo "$TEST" >test.txt

echo -e '\e[34m./mygrep.out '\''test'\'' test.txt\e[0m'
./mygrep.out 'test' test.txt
echo -e '\e[34m./mygrep.out '\''a'\'' test.txt\e[0m'
./mygrep.out 'a' test.txt
echo -e '\e[34m./mygrep.out '\'' test '\'' test.txt\e[0m'
./mygrep.out ' test ' test.txt

rm test.txt
