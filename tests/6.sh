#!/bin/bash

binary="build/6"
testFile="tests/in6.txt"
expected_key="Terminator X: Bring the noise"
expected_plaintext="I'm back and I'm ringin' the bell"

# Ensure the binary exists
if [[ ! -x "$binary" ]]; then
  echo "Executable $binary does not exist or is not executable."
  exit 1
fi

# Run the binary and capture its output
output=$("$binary" "$testFile")

# Check the output contains the expected plaintext
if [[ "$output" == *"$expected_plaintext"* ]]; then
  echo -e "\033[37;42mTest Passed!\033[0m"
else
  echo -e "\033[37;41mTest Failed.\033[0m"
  echo "Expected to contain: $expected_plaintext"
  echo "Got: $output"
  exit 1
fi
