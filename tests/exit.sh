#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"

function finish() {
  ./cleanup.sh
  exit $1
}

./setup.sh

../bin/rshell < input/exit.txt > exit_output.txt;
../bin/rshell < input/exit2.txt >> exit_output.txt;
../bin/rshell < input/exit3.txt >> exit_output.txt;

if cmp -s exit_output.txt expected/exit_output.txt; then
  echo "Exit Test Passed.";
  finish 0
else
  echo "Exit Test FAILED!";
  finish 1
fi
