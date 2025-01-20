/*
S1C1 - Convert Hex to Base64
The string:
49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d

Should produce:
SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t

testing for git
*/

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

const string base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

int hexToDecimal(const char &c) {
  if (c >= '0' && c <= '9') return c - '0';
  /* to account for case insensitivity */
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;
  throw std::invalid_argument("invalid hex character: ");
}

vector<unsigned char> hexToBytes(const string &hex) {
  if (hex.size() % 2 == 1) throw std::invalid_argument("invalid hex string size");
  vector<unsigned char> bytes;
  for (size_t i = 0; i < hex.size(); i += 2) {
    /*
      create byte by merging two nybbles-.e.g., bbbb 0000 | 0000 bbbb = bbbb bbbb:
      1. pad (bitwise right shift) with 4 bits; making room for the second nybble
      2. OR (merging) second nibble
    */
    bytes.push_back((hexToDecimal(hex[i]) << 4) | hexToDecimal(hex[i + 1]));
  }
  return bytes;
}

string bytesToBase64(const vector<unsigned char> &bytes) {
  string base64;
  size_t i = 0;
  while (i < bytes.size()) {
    /* read 3 bytes (24 bits) */
    int b1 = bytes[i++];
    int b2 = (i < bytes.size()) ? bytes[i++] : 0;
    int b3 = (i < bytes.size()) ? bytes[i++] : 0;

    /* convert to 4 6-bit base64 characters */
    base64 += base64Chars[(b1 >> 2) & 0x3F]; /* 1st 6-bit Chunk: shift right and mask with 0x3F (111111) to grab 6-bits */
    base64 += base64Chars[((b1 << 4) | (b2 >> 4)) & 0x3F]; /* 2nd 6-bit Chunk: last 2 bits of b1 + first 4 bits of b2 */
    base64 += (i > bytes.size()) ? '=' : base64Chars[((b2 << 2) | (b3 >> 6)) & 0x3F]; /* 3rd 6-bit Chunk:  */
    base64 += (i > bytes.size()) ? '=' : base64Chars[b3 & 0x3F]; /* 4th 6-bit Chunk: */
  }
  return base64;
}

int main() {
  // "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
  string input;
  std::cin >> input;
  cout << bytesToBase64(hexToBytes(input)) << endl;
  return 0;
}
