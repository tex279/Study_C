#!/usr/bin/env bash

LOG_TEST="../test.log"

cd build

./test.out
lcov -t "test.out" -o coverage.info -c -d CMakeFiles/lib.dir/
(genhtml -o report coverage.info --output-directory ../coverage-report/) > "${LOG_TEST}"

cat "${LOG_TEST}"

tail -n 2  ${LOG_TEST} > tmp.txt

VAR=$(cat tmp.txt)

SUB1="lines......: 8"
SUB2="functions..: 9"

if [[ "$VAR" == *"$SUB1"* ]]; then
  echo "LINES_SUCCESS"
else
  echo "LINES_FAILED"
  exit 1
fi

if [[ "$VAR" == *"$SUB2"* ]]; then
  echo "FUNCTION_SUCCESS"
else
  echo "FUNCTION_FAILED"
  exit 1
fi
