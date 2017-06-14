#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"

function finish() {
  ./cleanup.sh
  exit $1
}

./setup.sh

../bin/rshell < input/append_command.txt &> append_output.txt
if cmp -s append_output.txt expected/append_output.txt; then
  echo "Output Redirect Test Passed.";
  finish 0
else
  echo "Output Redirect Test FAILED!";
  diff -y append_output.txt expected/append_output.txt;
  finish 1
fi
