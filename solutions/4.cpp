/*
S1C4 - Detect single-character XOR
One of the 60-character strings in the input has been encrypted by single-character XOR.
Find it.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

// Convert a hex string to a vector of bytes
vector<unsigned char> hexToBytes(const string &hex) {
  vector<unsigned char> bytes;
  for (size_t i = 0; i < hex.size(); i += 2) {
    string byteString = hex.substr(i, 2);
    unsigned char byte = (unsigned char)std::stoi(byteString, nullptr, 16);
    bytes.push_back(byte);
  }
  return bytes;
}

// Apply a single-byte XOR to the input bytes
string singleByteXor(const vector<unsigned char> &input, unsigned char key) {
  string output;
  for (unsigned char byte : input) {
    output += (char)(byte ^ key);
  }
  return output;
}

// Score plaintext for English readability
double scoreEnglish(const string &text) {
  const string commonChars = " etaoinshrdlcumwfgypbvkjxqz";
  double score = 0.0;
  for (char c : text) {
    c = std::tolower(c);
    if (commonChars.find(c) != string::npos) {
      score += 1;
    }
  }
  return score;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }

  // Read file containing hex-encoded strings
  ifstream file(argv[1]);
  if (!file.is_open()) {
    cout << "Failed to open the file." << endl;
    return 1;
  }

  string line;
  double bestScore = 0.0;
  string bestPlaintext;
  unsigned char bestKey = 0;
  int bestLineNumber = 0;
  int lineNumber = 0;

  while (std::getline(file, line)) {
    ++lineNumber;
    vector<unsigned char> bytes = hexToBytes(line);
    for (unsigned char key = 0; key < 128; ++key) { // Test ASCII keys only
      string plaintext = singleByteXor(bytes, key);
      double score = scoreEnglish(plaintext);
      
      if (score > bestScore) {
        bestScore = score;
        bestPlaintext = plaintext;
        bestKey = key;
        bestLineNumber = lineNumber;
      }
    }
  }

  file.close();

  // Output the best result
  cout << bestLineNumber << endl;
  cout << (int)bestKey << endl;
  cout << bestPlaintext << endl;

  return 0;
}
