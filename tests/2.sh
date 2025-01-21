#!/bin/bash

binary="build/2"
input1="1c0111001f010100061a024b53535009181c"
input2="686974207468652062756c6c277320657965"
expected_output="746865206b696420646f6e277420706c6179"

# Ensure the binary exists
if [[ ! -x "$binary" ]]; then
  echo "Executable $binary does not exist or is not executable."
  exit 1
fi

# Run the binary and capture its output
output=$("$binary" "$input1" "$input2")

# Check the output
if [[ "$output" == "$expected_output" ]]; then
  echo -e "\033[37;42mTest Passed!\033[0m"
else
  echo -e "\033[37;41mTest Failed.\033[0m"
  echo "Expected: $expected_output"
  echo "Got: $output"
  exit 1
fi

