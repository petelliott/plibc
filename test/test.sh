#!/usr/bin/env bash

mkdir -p test/bin


run_test() {
    gcc -Wall -nostdlib test/$1.c bin/plibc.a -o test/bin/$1 
    test/bin/$1
    if [ $? == 0 ]
    then
        echo -e "$1: \e[32mpassed\e[00m"
        return 0
    else
        echo -e "$1: \e[31mfailed\e[00m"
        return 1
    fi
}

FAILURE=0

if [ -f test/$1.c ]
then
    run_test $1
    exit $?
else
    for f in test/*.c
    do
        run_test $(basename $f .c)
        FAILURE=$(($FAILURE || $?))
    done
fi
exit $FAILURE
