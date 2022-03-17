#!/usr/bin/env bash

cd build

function print_header() {
    echo -e "\n***** ${1} *****"
}

valgrind --tool=memcheck --leak-check=full -s ./test.out