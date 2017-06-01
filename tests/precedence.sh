#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"

function finish() {
  ./cleanup.sh
  exit $1
}

./setup.sh

../bin/rshell < input/precedence.txt &> precedence_output.txt
if cmp -s precedence_output.txt expected/precedence_output.txt; then
  echo "Precedence Command Test Passed.";
  finish 0
else
  echo "Precedence Command Test FAILED!";
  diff -y precedence_output.txt expected/precedence_output.txt;
  finish 1
fi
