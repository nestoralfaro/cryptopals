#!/bin/bash

binary="build/3"

input1="1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"
expectedKey1="X"
expectedText1="Cooking MC's like a pound of bacon"

# Ensure the binary exists
if [[ ! -x "$binary" ]]; then
  echo "Executable $binary does not exist or is not executable."
  exit 1
fi

# Run the binary and capture its output
output=$("$binary" "$input1")
if [[ $? -ne 0 ]]; then
  echo -e "\033[31;41mProgram execution failed.\033[0m"
  exit 1
fi

# Extract key and plaintext from the output
key=$(echo "$output" | grep "Best key:" | awk -F':' '{print $NF}')
plaintext=$(echo "$output" | grep "Decrypted text:" | cut -d':' -f2)

# Validate the key and plaintext
if [[ "$key" == "$expectedKey1" && "$plaintext" == "$expectedText1" ]]; then
  echo -e "\033[37;42mTest Passed!\033[0m"
else
  echo -e "\033[37;41mTest Failed.\033[0m"
  echo "Expected key: $expectedKey1"
  echo "Got key: $key"
  echo "Expected text: $expectedText1"
  echo "Got text: $plaintext"
  exit 1
fi
