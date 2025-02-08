/*
# S2C9-Implement PKCS#7 padding
A block cipher transforms a fixed-sized block (usually 8 or 16 bytes) of plaintext into ciphertext.
But we almost never want to transform a single block; we encrypt irregularly-sized messages.

One way we account for irregularly-sized messages is by padding,
creating a plaintext that is an even multiple of the blocksize. The most popular padding scheme is called PKCS#7.

So: using C++, pad any block to a specific block length, by appending the number of bytes of padding to the end of the block.
For instance,
```
"YELLOW SUBMARINE"
```
...padded to 20 bytes would be:
```
"YELLOW SUBMARINE\x04\x04\x04\x04"
```
*/

#include <iostream>
#include <string>

bool isPowerOfTwo(const size_t n) {
  return (n != 0) && ((n & (n - 1)) == 0);
}

// Function to apply PKCS#7 padding
std::string pkcs7Pad(const std::string &input, size_t blockSize) {
  if (blockSize == 0 || blockSize > 255) {
    throw std::invalid_argument("Block size must be between 1 and 255.");
  }

  size_t paddingSize = isPowerOfTwo(blockSize)
    ? blockSize - (input.size() & blockSize)
    : blockSize - (input.size() % blockSize);

  if (paddingSize == 0) {
    paddingSize = blockSize; // Add a full block of padding if already aligned
  }

  std::string padded = input;
  padded.append(paddingSize, static_cast<char>(paddingSize));
  return padded;
}

int main() {

  std::string input; // = "YELLOW SUBMARINE";
  std::getline(std::cin, input);
  size_t blockSize; // = 20;
  std::cin >> blockSize;

  std::cout << "input: " << input << " blockSize: " << blockSize << std::endl;

  try {
    std::string padded = pkcs7Pad(input, blockSize);
    
    std::cout << "Original (" << input.size() << "): \"" << input << "\"" << std::endl;
    std::cout << "Padded (" << padded.size() << "): \"" << padded << "\"" << std::endl;

    // Show padding in hexadecimal for clarity
    std::cout << "Padded (hex): ";
    for (unsigned char c : padded) {
      printf("\\x%02x", c);
    }
    std::cout << std::endl;

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
