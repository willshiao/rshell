#!/usr/bin/env bash

./setup.sh

../bin/rshell < input/exit.txt &> exit_output.txt
if cmp -s exit_output.txt expected/exit_output.txt; then
  echo "Exit Test Passed.";
else
  echo "Exit Test FAILED!";
fi
rm -rf exit_output.txt

./cleanup.sh
