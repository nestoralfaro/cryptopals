#!/bin/bash

binary="build/1"
input="49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
expected_output="SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"

# Ensure the binary exists
if [[ ! -x "$binary" ]]; then
  echo "Executable $binary does not exist or is not executable."
  exit 1
fi

# Run the binary and capture its output
output=$(echo "$input" | "$binary")

# Check the output
if [[ "$output" == "$expected_output" ]]; then
  echo -e "\033[37;42mTest Passed!\033[0m"
else
  echo -e "\033[31;42mTest Failed.\033[0m"
  echo "Expected: $expected_output"
  echo "Got: $output"
  exit 1
fi
