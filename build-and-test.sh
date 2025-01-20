#!/bin/bash

# Function to find solutions to build/test
find_solutions() {
    local source_files=("$@")
    solutions=()

    if [[ ${#source_files[@]} -eq 0 ]]; then
        # Get the list of changed .cpp files in the commit
        source_files=$(git diff --name-only HEAD~1 HEAD | grep '\.cpp$')
    fi

    for file in $source_files; do
        if [[ $file == solutions/* ]]; then
            solution=$(echo $file | cut -d'/' -f2)
            solutions+=("$solution")
        fi
    done

    # Remove duplicates
    solutions=($(echo "${solutions[@]}" | tr ' ' '\n' | sort -u | tr '\n' ' '))
}

# Function to build solutions
build_solutions() {
    local solutions=("$@")
    if [[ ${#solutions[@]} -eq 0 ]]; then
        echo "No solutions to build."
        return
    fi

    echo "Solutions to build: ${solutions[@]}"
    for solution in "${solutions[@]}"; do
        echo "Building solution: $solution"
        mkdir -p build/$solution
        cd build/$solution
        cmake ../../solutions/$solution
        if ! make; then
            echo "Build failed for solution: $solution"
            exit 1
        fi
        cd -
    done
}

# Function to test solutions
test_solutions() {
    local solutions=("$@")
    if [[ ${#solutions[@]} -eq 0 ]]; then
        echo "No solutions to test."
        return
    fi

    echo "Solutions to test: ${solutions[@]}"
    for solution in "${solutions[@]}"; do
        echo "Testing solution: $solution"
        cd build/$solution
        if ! ctest --output-on-failure; then
            echo "Tests failed for solution: $solution"
            exit 1
        fi
        cd -
    done
}

# Main script
if [[ $# -gt 0 ]]; then
    # Source files passed as arguments
    find_solutions "$@"
else
    # No arguments, use git diff
    # find_solutions
    echo "Please provide path to source solution."
    exit 1
fi

build_solutions "${solutions[@]}"
test_solutions "${solutions[@]}"
