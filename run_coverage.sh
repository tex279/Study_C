#!/usr/bin/env bash

LOG_TEST="../test.log"

cd build

./test.out
lcov -t "test.out" -o coverage.info -c -d CMakeFiles/lib.dir/
(genhtml -o report coverage.info --output-directory ../coverage-report/) > "${LOG_TEST}"

cat ${LOG_TEST}
