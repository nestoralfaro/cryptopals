/* 
# S1C3 - Single-byte XOR cipher
The hex encoded string:
1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
...has been XOR'd against a single character. Find the key, decrypt the message.
You can do this by hand. But don't: write code to do it for you.

How? Devise some method for "scoring" a piece of English plaintext.
Character frequency is a good metric. Evaluate each output and choose the one with the best score.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using std::cout;
using std::endl;
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
    std::cerr << "Usage " << argv[0] << " <hex1>" << endl;
    return 1;
  }
  string input = argv[1]; // = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

  vector<unsigned char> bytes = hexToBytes(input);
  double bestScore = 0.0;
  string bestPlaintext;
  unsigned char bestKey = 0;

  for (unsigned char key = 0; key < 128; ++key) {
    string plaintext = singleByteXor(bytes, key);
    double score = scoreEnglish(plaintext);
    if (score > bestScore) {
      bestScore = score;
      bestPlaintext = plaintext;
      bestKey = key;
    }
  }

  cout << "Best key:" << bestKey << endl;
  cout << "Decrypted text:" << bestPlaintext << endl;

  return 0;
}
