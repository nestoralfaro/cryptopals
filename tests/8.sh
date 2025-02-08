#!/bin/bash

binary="build/8"
testFile1="tests/in8.txt"
expectedToContainOutput="line number: 133"

if [[! -x "$binary" ]]; then
  echo "Executable $binary does not exist or is not executable."
  exit 1
fi

output=$(echo  "$testFile1" | "$binary")

if [[ "$output" == *"$expectedToContainOutput"* ]]; then
  echo -e "\033[37;42mTest Passed!\033[0m"
else
  echo -e "\033[37;41mTest Failed.\033[0m"
  echo "Expected to contain: $expectedToContainOutput"
  echo "Got: $output"
  exit 1
fi
