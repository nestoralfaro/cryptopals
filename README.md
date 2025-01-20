# [Cryptopals Challenges](https://cryptopals.com/)
This repository contains solutions to sets 1 and 2 from the Cryptopals challenges. Each solution is written in C++ and is accompanied by test scripts to verify correctness.

## Structure
- `solutions/`: Contains solution files.
- `tests/`: Contains test scripts.
- `build/`: Created on the file (`.gitignore`d)

## CI/CD
Pushes to the `main` branch automatically trigger a GitHub Actions workflow to:
1. Build all solutions using `CMake`.
2. Run corresponding test scripts in `tests/`.

## Usage
To build and test locally, simply run `build-and-test.sh < | path/to/source >`.
