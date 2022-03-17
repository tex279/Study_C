#!/usr/bin/env bash

cd build

./test.out
lcov -t "test.out" -o coverage.info -c -d CMakeFiles/lib.dir/
genhtml -o report coverage.info