#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"

function finish() {
  ./cleanup.sh
  exit $1
}

./setup.sh

../bin/rshell < input/output_command.txt &> output_output.txt
if cmp -s output_output.txt expected/output_output.txt; then
  echo "Output Redirect Test Passed.";
  finish 0
else
  echo "Output Redirect Test FAILED!";
  diff -y output_output.txt expected/output_output.txt;
  finish 1
fi
