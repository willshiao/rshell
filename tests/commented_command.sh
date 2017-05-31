#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"

function finish() {
  ./cleanup.sh
  exit $1
}

./setup.sh

../bin/rshell < input/commented_command.txt &> commented_output.txt
if cmp -s commented_output.txt expected/commented_output.txt; then
  echo "Commented Command Test Passed.";
  finish 0
else
  echo "Commented Command Test FAILED!";
  diff -y commented_output.txt expected/commented_output.txt;
  finish 1
fi
