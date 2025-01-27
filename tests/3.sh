#!/bin/bash

binary="build/3"
expected_key="X"
expected_text="Cooking MC's like a pound of bacon"

# Ensure the binary exists
if [[ ! -x "$binary" ]]; then
  echo "Executable $binary does not exist or is not executable."
  exit 1
fi

# Run the binary and capture its output
output=$("$binary")
if [[ $? -ne 0 ]]; then
  echo -e "\033[31;41mProgram execution failed.\033[0m"
  exit 1
fi

# Extract key and plaintext from the output
key=$(echo "$output" | grep "Best key:" | awk -F'[()]' '{print $2}')
plaintext=$(echo "$output" | grep "Decrypted text:" | cut -d':' -f2- | xargs)

# Validate the key and plaintext
if [[ "$key" == "$expected_key" && "$plaintext" == "$expected_text" ]]; then
  echo -e "\033[32;42mTest Passed!\033[0m"
else
  echo -e "\033[31;41mTest Failed.\033[0m"
  echo "Expected key: $expected_key"
  echo "Got key: $key"
  echo "Expected text: $expected_text"
  echo "Got text: $plaintext"
  exit 1
fi
