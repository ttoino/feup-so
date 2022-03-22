#!/usr/bin/env bash

if [[ ! -x mycp.out ]]; then
    ./build.sh
fi

echo -e '\e[34mecho '\''This is a test'\'' > file1\e[0m'
echo 'This is a test' >file1

echo -e '\e[34m./mycp.out file1 file2\e[0m'
./mycp.out file1 file2

echo -e '\e[34mcat file2\e[0m'
cat file2

echo -e '\e[34mecho '\''And yet another'\'' > file3\e[0m'
echo 'And yet another' >file3

echo -e '\e[34m./mycp.out file3 file2\e[0m'
./mycp.out file3 file2

echo -e '\e[34mcat file2\e[0m'
cat file2

rm file{1,2,3}
