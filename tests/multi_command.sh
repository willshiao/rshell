#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"

function finish() {
  ./cleanup.sh
  exit $1
}

./setup.sh

../bin/rshell < input/multi_command.txt &> multi_output.txt
if cmp -s multi_output.txt expected/multi_output.txt; then
  echo "Multiple Command Test Passed.";
  finish 0
else
  echo "Multiple Command Test FAILED!";
  finish 1
fi
