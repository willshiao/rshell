#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"

function finish() {
  ./cleanup.sh
  exit $1
}

./setup.sh

../bin/rshell < input/single_command.txt &> single_output.txt
if cmp -s single_output.txt expected/single_output.txt; then
  echo "Single Command Test Passed.";
  finish 0
else
  echo "Single Command Test FAILED!";
  finish 1
fi
