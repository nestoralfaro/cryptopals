#!/bin/bash

set -e

if [[ $# -ne 1 ]]; then
  echo "Usage: $0 <solution-number>"
  exit 1
fi

solution="$1"
echo "#################### BUILD SOLUTION $solution ####################"
echo "Current OS: $OS_NAME"
echo "OpenSSL Version: $(openssl version)"

solutionCpp="solutions/${solution}.cpp"
if [[ ! -f "$solutionCpp" ]]; then
  echo "Solution file $solutionCpp does not exist."
  exit 1
fi

mkdir -p build

# detect OS
OS_NAME=$(uname -s)
if [[ "$OS_NAME" == "Darwin" ]]; then
  OPENSSL_DIR="/opt/homebrew/opt/openssl/"
elif [[ "$OS_NAME" == "Linux" ]]; then
  echo "Running Linux. Checking OpenSSL Installation Path"
  pkg-config --cflags --libs openssl
  OPENSSL_DIR="/usr"
else
  echo "Unsupported OS: $OS_NAME"
  exit 1
fi


# compile with OpenSSL
g++ -std=c++17 -o "build/$solution" "$solutionCpp" \
  -I"$OPENSSL_DIR"/include -L"$OPENSSL_DIR"/lib -lcrypto -lssl
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
echo "#################### BUILD SOLUTION $solution ####################"
