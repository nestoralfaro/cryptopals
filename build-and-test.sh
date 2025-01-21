#!/bin/bash

set -e

if [[ $# -ne 1 ]]; then
  echo "Usage: $0 <solution-number>"
  exit 1
fi

solution="$1"

solutionCpp="solutions/${solution}.cpp"
if [[ ! -f "$solutionCpp" ]]; then
  echo "Solution file $solutionCpp does not exist."
  exit 1
fi

mkdir -p build

echo "Build solution: $solution"
g++ -std=c++17 -o "build/$solution" "$solutionCpp"
chmod +x "build/$solution"

testSh="tests/${solution}.sh"
if [[ ! -f "$testSh" ]]; then
  echo "Test script $testSh does not exist. Removing build:"
  rm -v "build/$solution"
  exit 1
fi

echo "Running tests for solution: $solution"
bash "$testSh"
echo "Removing build below:"
rm -v "build/$solution"
