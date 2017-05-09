#!/usr/bin/env bash

./setup.sh

../bin/rshell < input/multi_command.txt > multi_output.txt
if cmp -s multi_output.txt expected/multi_output.txt; then
  echo "Multiple Command Test Passed.";
else
  echo "Multiple Command Test FAILED!";
fi
# rm -rf multi_output.txt

./cleanup.sh
