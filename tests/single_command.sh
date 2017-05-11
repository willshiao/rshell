#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"

./setup.sh

../bin/rshell < input/single_command.txt &> single_output.txt
if cmp -s single_output.txt expected/single_output.txt; then
  echo "Single Command Test Passed.";
else
  echo "Single Command Test FAILED!";
fi
rm -rf single_output.txt

./cleanup.sh
