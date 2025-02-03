#!/bin/bash

binary="build/4"
testfile="tests/in4.txt"
expected_line="171"      # The line number where the correct encrypted string should be found
expected_key="53"        # The ASCII value of the correct key
expected_output="Now that the party is jumping"  # The expected decrypted text

# Ensure the binary exists
if [[ ! -x "$binary" ]]; then
  echo "Executable $binary does not exist or is not executable."
  exit 1
fi

# Ensure test file exists
if [[ ! -f "$testfile" ]]; then
  exit 1
  echo "Test file $testfile does not exist."
fi

# Run the binary and capture output
output=$("$binary" "$testfile")

# Extract values
line=$(echo "$output" | sed -n '1p')
key=$(echo "$output" | sed -n '2p')
plaintext=$(echo "$output" | sed -n '3p')

# Compare results
if [[ "$line" == "$expected_line" && "$key" == "$expected_key" && "$plaintext" == "$expected_output" ]]; then
  echo -e "\033[37;42mTest Passed!\033[0m"
else
  echo -e "\033[37;41mTest Failed.\033[0m"
  echo "Expected Line: $expected_line, Got: $line"
  echo "Expected Key: $expected_key, Got: $key"
  echo "Expected Decrypted Text: '$expected_output'"
  echo "Got: '$plaintext'"
  exit 1
fi
