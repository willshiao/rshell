#!/usr/bin/env bash

# Sets up files for testing
mkdir testdir
for ((i = 1; i <= 5; ++i)); do
  touch "testdir/file$i";
done
