#!/bin/bash

binary="build/5"
input="Burning 'em, if you ain't quick and nimble
I go crazy when I hear a cymbal"
key="ICE"
expected_output="0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f"

# Ensure the binary exists
if [[ ! -x "$binary" ]]; then
  echo "Executable $binary does not exist or is not executable."
  exit 1
fi

# Run the binary and capture its output
output=$("$binary" "$input" "$key")

# Check the output
if [[ "$output" == "$expected_output" ]]; then
  echo -e "\033[37;42mTest Passed!\033[0m"
else
  echo -e "\033[37;41mTest Failed.\033[0m"
  echo "Exp: $expected_output"
  echo "Got: $output"
  exit 1
fi
