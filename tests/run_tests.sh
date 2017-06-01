#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"
RES=""
./commented_command.sh
RES=$(($RES+$?))
./multi_command.sh
RES=$(($RES+$?))
./exit.sh
RES=$(($RES+$?))
./single_command.sh
RES=$(($RES+$?))
./test_command.sh
RES=$(($RES+$?))
./precedence.sh
RES=$(($RES+$?))

if [[ "$RES" = "0" ]]; then
  echo "All tests passed!"
  exit 0;
else
  echo "At least one test failed!"
  exit 1;
fi
