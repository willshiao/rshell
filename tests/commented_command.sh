#!/usr/bin/env bash

./setup.sh

../bin/rshell < input/commented_command.txt &> commented_output.txt
if cmp -s commented_output.txt expected/commented_output.txt; then
  echo "Commented Command Test Passed.";
else
  echo "Commented Command Test FAILED!";
fi
rm -rf commented_output.txt

./cleanup.sh
