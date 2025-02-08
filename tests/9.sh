#!/bin/bash

binary="build/9"
msg1="YELLOW SUBMARINE"
blockSize1=20
expectedToContainOutput1="\x59\x45\x4c\x4c\x4f\x57\x20\x53\x55\x42\x4d\x41\x52\x49\x4e\x45\x04\x04\x04\x04"

if [[ ! -x "$binary" ]]; then
  echo "Executable $binary does not exist or has not been chmod'd"
  exit 1
fi

output=$(echo -e "$msg1\n$blockSize1" | "$binary")

if [[ "$output" == *"$expectedToContainOutput1"* ]]; then
  echo -e "\033[37;42mTest Passed!\033[0m"
else
  echo -e "\033[37;41mTest Failed.\033[0m"
  echo "Expected to contain: $expectedToContainOutput1"
  echo "Got: $output"
  exit 1
fi
