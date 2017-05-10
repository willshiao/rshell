#!/usr/bin/env bash

# Sets up files for testing
mkdir testdir;
for ((i = 1; i <= 5; ++i)); do
  touch "testdir/file$i";
done

(
cat <<EOF
This is a test file.
The contents of this file are for testing purposes.
I like to test things.
This file is created for CS100.
EOF
) > testdir/file1;
