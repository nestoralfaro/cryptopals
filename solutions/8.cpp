/*
# S1C8 - Detect AES in ECB mode
In 8.txt (attached file) are a bunch of hex-encoded ciphertexts.
One of them has been encrypted with ECB. Detect it using C++.

Remember that the problem with ECB is that it is stateless and deterministic;
the same 16 byte plaintext block will always produce the same 16 byte ciphertext.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

// Function to split a string into 16-byte blocks
std::vector<std::string> splitIntoBlocks(const std::string &hexString, size_t blockSize) {
  std::vector<std::string> blocks;
  for (size_t i = 0; i < hexString.length(); i += blockSize) {
    blocks.push_back(hexString.substr(i, blockSize));
  }
  return blocks;
}

// Function to detect repeated blocks in a vector
bool hasRepeatedBlocks(const std::vector<std::string> &blocks) {
  std::set<std::string> uniqueBlocks(blocks.begin(), blocks.end());
  return uniqueBlocks.size() < blocks.size();
}

int main() {
  std::string filename;
  std::cin >> filename;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return 1;
  }

  std::string line;
  size_t lineNumber = 0;
  size_t blockSize = 32; // 16 bytes = 32 hex characters

  while (std::getline(file, line)) {
    lineNumber++;

    // Split the line into 16-byte blocks
    std::vector<std::string> blocks = splitIntoBlocks(line, blockSize);

    // Check for repeated blocks
    if (hasRepeatedBlocks(blocks)) {
      std::cout << "ECB-encrypted line detected at line number: " << lineNumber << std::endl;
      std::cout << "Ciphertext: " << line << std::endl;
      break;
    }
  }

  file.close();
  return 0;
}
