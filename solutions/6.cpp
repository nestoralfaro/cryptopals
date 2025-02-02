/*
# S1C6 – Break repeating-key XOR

Open 6.txt. Its content has been base64'd after being encrypted with repeating-key XOR.

Decrypt it. Here's how:

1. Let `KEYSIZE` be the guessed length of the key; try values from 2 to (say) 40.
2. Write a function to compute the edit/hamming distance between two strings. The Hamming distance is the number of different bits. For example, the distance between:
  `this is a test`
  and 
  `wokka wokka!!!`
  is `37`.
3. For each KEYSIZE, take the first KEYSIZE worth of bytes, and the second KEYSIZE worth of bytes, and find the edit distance between them. Normalize this result by dividing by KEYSIZE.
4. The KEYSIZE with the smallest normalized edit distance is probably the key. You could proceed perhaps with the smallest 2-3 KEYSIZE values. Or take 4 KEYSIZE blocks instead of 2 and average the distance.
5. Now that you probably know the KEYSIZE: break the ciphertext into blocks of KEYSIZE length.
6. Now transpose the blocks: make a block that is the first byte of every block, and a block that is the second byte of every block, and so on.
7. Solve each block as if it was single-character XOR. You already have code to do this.
8. For each block, the single-byte XOR key that produces the best looking histogram is the repeating-key XOR key byte for that block. Put them together and you have the key.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <stdexcept>
#include <cctype>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

// Base64 character map
const string base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Decode a single Base64 character
int base64CharToValue(char c) {
  if ('A' <= c && c <= 'Z') return c - 'A';
  if ('a' <= c && c <= 'z') return c - 'a' + 26;
  if ('0' <= c && c <= '9') return c - '0' + 52;
  if (c == '+') return 62;
  if (c == '/') return 63;
  if (c == '=') return 0; // Padding character
  throw std::invalid_argument("Invalid Base64 character");
}

// Decode a Base64 string into raw binary data
vector<unsigned char> decodeBase64(const string &base64) {
  vector<unsigned char> binaryData;
  int val = 0, bits = 0;

  for (char c : base64) {
    if (c == '\n') continue; // Skip newline characters
    val = (val << 6) | base64CharToValue(c);
    bits += 6;

    if (bits >= 8) {
      bits -= 8;
      binaryData.push_back((val >> bits) & 0xFF);
    }
  }
  return binaryData;
}

// Compute the Hamming distance (number of differing bits) between two strings
int hammingDistance(const string &str1, const string &str2) {
  if (str1.size() != str2.size()) {
    throw std::invalid_argument("Strings must be of equal length.");
  }
  int distance = 0;
  for (size_t i = 0; i < str1.size(); ++i) {
    unsigned char xorResult = str1[i] ^ str2[i];
    distance += std::bitset<8>(xorResult).count();
  }
  return distance;
}

// Calculate the normalized Hamming distance for a given KEYSIZE
double calculateNormalizedDistance(const vector<unsigned char> &data, int keysize) {
  vector<string> blocks;
  for (int i = 0; i < 4 && i * keysize + keysize <= data.size(); ++i) {
    blocks.emplace_back(data.begin() + i * keysize, data.begin() + (i + 1) * keysize);
  }

  double totalDistance = 0.0;
  int comparisons = 0;
  for (size_t i = 0; i < blocks.size() - 1; ++i) {
    for (size_t j = i + 1; j < blocks.size(); ++j) {
      totalDistance += hammingDistance(blocks[i], blocks[j]);
      ++comparisons;
    }
  }
  return totalDistance / (keysize * comparisons);
}

// Solve single-character XOR cipher
unsigned char solveSingleByteXOR(const vector<unsigned char> &block) {
  double bestScore = 0.0;
  unsigned char bestKey = 0;

  for (unsigned char key = 0; key < 128; ++key) {
    string decoded;
    for (unsigned char byte : block) {
      decoded += (byte ^ key);
    }

    double score = 0.0;
    for (char c : decoded) {
      if (std::isalpha(c) || c == ' ') score += 1; // Simplistic scoring
    }

    if (score > bestScore) {
      bestScore = score;
      bestKey = key;
    }
  }
  return bestKey;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << "<base64FileName>" << endl;
    return 1;
  }
  // Read the Base64 content from 6.txt
  string base64Content;
  ifstream file(argv[1]);
  if (!file.is_open()) {
    cout << "Error: Could not open file in6.txt" << endl;
    return 1;
  }

  string line;
  while (std::getline(file, line)) {
    base64Content += line;
  }
  file.close();

  // Decode the Base64 content into binary data
  vector<unsigned char> ciphertext = decodeBase64(base64Content);

  // Step 1-4: Find the best KEYSIZE in the range [2, 40]
  vector<int> likelyKeysizes;
  vector<std::pair<int, double>> distances;

  for (int keysize = 2; keysize <= 40; ++keysize) {
    double normalizedDistance = calculateNormalizedDistance(ciphertext, keysize);
    distances.emplace_back(keysize, normalizedDistance);
  }

  std::sort(distances.begin(), distances.end(), [](const auto &a, const auto &b) {
    return a.second < b.second;
  });

  // Select the most likely KEYSIZE
  int bestKeySize = distances[0].first;

  // Step 5-8: Decrypt the ciphertext using the most likely KEYSIZE
  vector<vector<unsigned char>> blocks(bestKeySize);
  for (size_t i = 0; i < ciphertext.size(); ++i) {
    blocks[i % bestKeySize].push_back(ciphertext[i]);
  }

  string key;
  for (const auto &block : blocks) {
    key += solveSingleByteXOR(block);
  }

  // Decrypt the ciphertext using the key
  string plaintext;
  for (size_t i = 0; i < ciphertext.size(); ++i) {
    plaintext += (ciphertext[i] ^ key[i % key.size()]);
  }

  cout << plaintext << endl;
  return 0;
}
