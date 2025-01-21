/*
# S1C2 - Fixed XOR

Write a function that takes two equal-length buffers and produces their XOR combination.

If your function works properly, then when you feed it the string:
1c0111001f010100061a024b53535009181c

... after hex decoding, and when XOR'd against:
686974207468652062756c6c277320657965

... should produce:
746865206b696420646f6e277420706c6179
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdexcept>

using std::cout;
using std::endl;
using std::string;
using std::vector;

int hexCharToDecimal(char c);
vector<unsigned char> hexToBytes(const string &hex);
string bytesToHex(const vector<unsigned char> &bytes);
string fixedXor(const string &hex1, const string &hex2);

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage " << argv[0] << " <hex1> <hex2>" << endl;
    return 1;
  }
  string hex1 = argv[1];
  string hex2 = argv[2];
  
  try {
    cout << fixedXor(hex1, hex2) << endl;
  }
  catch (const std::exception &e) {
    cout << "Error: " << e.what() << endl;
  }

  return 0;
}

int hexCharToDecimal(char c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;
  throw std::invalid_argument("invalid hex argument");
}

vector<unsigned char> hexToBytes(const string &hex) {
  if (hex.size() % 2 != 0) {
    throw std::invalid_argument("hex string must have an even length");
  }
  vector<unsigned char> bytes;
  for (size_t i = 0; i < hex.size(); i += 2) {
    unsigned char byte = (hexCharToDecimal(hex[i]) << 4) | hexCharToDecimal(hex[i + 1]);
    bytes.push_back(byte);
  }
  return bytes;
}

string bytesToHex(const vector<unsigned char> &bytes) {
  std::ostringstream hexStream;
  for (unsigned char byte : bytes) {
    hexStream << std::hex << std::setfill('0') << std::setw(2) << (int)byte;
  }
  return hexStream.str();
}

string fixedXor(const string &hex1, const string &hex2) {
  vector<unsigned char> bytes1 = hexToBytes(hex1);
  vector<unsigned char> bytes2 = hexToBytes(hex2);
  
  if (bytes1.size() != bytes2.size()) {
    throw std::invalid_argument("input buffers must have the same length");
  }
  
  vector<unsigned char> result;
  for (size_t i = 0; i < bytes1.size(); ++i) {
    result.push_back(bytes1[i] ^ bytes2[i]);
  }
  
  return bytesToHex(result);
}
