#!/usr/bin/env bash

cd build
./test.out
lcov -t "test.out" -o coverage.info -c -d
genhtml -o report coverage.info --output-directory ../coverage-report/