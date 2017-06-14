#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"

function finish() {
  ./cleanup.sh
  exit $1
}

./setup.sh

../bin/rshell < input/input_command.txt &> input_output.txt
if cmp -s input_output.txt expected/input_output.txt; then
  echo "Input Redirect Test Passed.";
  finish 0
else
  echo "Input Redirect Test FAILED!";
  diff -y input_output.txt expected/input_output.txt;
  finish 1
fi
