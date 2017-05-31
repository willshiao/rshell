#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"

function finish() {
  ./cleanup.sh
  exit $1
}

./setup.sh

../bin/rshell < input/test_command.txt &> test_output.txt
if cmp -s test_output.txt expected/test_output.txt; then
  echo "Test Command Test Passed.";
  finish 0
else
  echo "Test Command Test FAILED!";
  finish 1
fi
