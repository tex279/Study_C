#!/usr/bin/env bash

LOG_TEST="../test.log"

cd build

./test.out
lcov -t "test.out" -o coverage.info -c -d CMakeFiles/lib.dir/
(genhtml -o report coverage.info --output-directory ../coverage-report/) > "${LOG_TEST}"

cat "${LOG_TEST}"

VAR=$(cat "${LOG_TEST}")

SUB1="lines......: "
SUB2="functions..: "

if [[ "$VAR" == *"$SUB1"["1"][0-9][0-9].[0-9]%* ]]; then
  echo "  LINES_SUCCESS"
else
  if [[ "$VAR" == *"$SUB1"["$@"][0-9].[0-9]%* ]]; then
    echo "  LINES_SUCCESS"
  else
    echo "L INES_FAILED"
    exit 1
  fi
fi

if [[ "$VAR" == *"$SUB2"["1"][0-9][0-9].[0-9]%* ]]; then
  echo "  FUNCTION_SUCCESS"
else
  if [[ "$VAR" == *"$SUB2"["$@"][0-9].[0-9]%* ]]; then
    echo "  FUNCTION_SUCCESS"
  else
    echo "  LINES_FAILED"
    exit 1
  fi
fi
