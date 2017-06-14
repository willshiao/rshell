#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"

function finish() {
  ./cleanup.sh
  exit $1
}

./setup.sh

../bin/rshell < input/pipe_command.txt &> pipe_output.txt
if cmp -s pipe_output.txt expected/pipe_output.txt; then
  echo "Output Redirect Test Passed.";
  finish 0
else
  echo "Output Redirect Test FAILED!";
  diff -y pipe_output.txt expected/pipe_output.txt;
  finish 1
fi
