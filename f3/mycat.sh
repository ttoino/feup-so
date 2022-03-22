#!/usr/bin/env bash

if [[ ! -x mycat.out ]]; then
    ./build.sh
fi

echo -e '\e[34mecho '\''This is a test'\'' > file1\e[0m'
echo 'This is a test' >file1
echo -e '\e[34mecho '\''Another test'\'' > file2\e[0m'
echo 'Another test' >file2
echo -e '\e[34mecho '\''And yet another'\'' > file3\e[0m'
echo 'And yet another' >file3

echo -e '\e[34m./mycat.out file1\e[0m'
./mycat.out file1
echo -e '\e[34m./mycat.out file1 file3\e[0m'
./mycat.out file1 file3
echo -e '\e[34m./mycat.out file1 file2 file3\e[0m'
./mycat.out file1 file2 file3

rm file{1,2,3}
