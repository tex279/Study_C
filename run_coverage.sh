#!/usr/bin/env bash

LOG_TEST="test.log"

lcov -t "test.out" -o coverage.info -c -d build/project/CMakeFiles/blanks_lib.dir/blanks_lib/src
(genhtml -o report coverage.info --output-directory coverage-report/) > "${LOG_TEST}"

cat "${LOG_TEST}"

VAR=$(cat "${LOG_TEST}")

SUB1="lines......: "
SUB2="functions..: "

if [[ "$VAR" == *"$SUB1""100.0%"* || "$VAR" == *"$SUB1"["$@"][0-9].[0-9]%* ]]; then
  echo "  LINES_SUCCESS"
else
  exit 1
fi

if [[ "$VAR" == *"$SUB2""100.0%"* || "$VAR" == *"$SUB2"["$@"][0-9].[0-9]%* ]]; then
  echo "  FUNCTION_SUCCESS"
else
  exit 1
fi