/*
S1C5 - Implement repeating-key XOR
Here is the opening stanza of an important work of the english language

```
Burning 'em, if you ain't quick and nimble
I go crazy when I hear a cymbal
```

Encrypt it, under the key "ICE", using repeating-key XOR.

In repeating-key XOR, you'll sequentially apply each byte of the key;
the first byte of plaintext will be XOR'd against I, the next C, the next
E, then I again for the 4th byte, and so on

It should come out to:
```
0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f
```

Side note: Encrypt a bunch of stuff using your repeating-key XOR function.
Encrypt your mail. Encrypt your password file. Your .sig file.
Get a feel for it. I promise, we aren't wasting your time with this.
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// Helper to convert a byte to a 2-digit hexadecimal string
string byteToHex(unsigned char byte) {
  std::ostringstream hexStream;
  hexStream << std::hex << std::setfill('0') << std::setw(2) << (int)byte;
  return hexStream.str();
}

// Function to encrypt text with a repeating key using XOR
string encrypt(const string &text, const string &key) {
  string result;
  size_t keyLength = key.size();
  for (size_t i = 0; i < text.size(); ++i) {
    // XOR each character of the text with the corresponding key character
    unsigned char encryptedChar = text[i] ^ key[i % keyLength];
    result += byteToHex(encryptedChar); // Convert XOR result to hex
  }
  return result;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <plaintext> <key>" << endl;
    return 1;
  }
  string plaintext = argv[1]; /* "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal"*/ 
  string key = argv[2]; /* "ICE" */

  // Encrypt the plaintext
  string encryptedText = encrypt(plaintext, key);

  // Output the result
  cout << encryptedText << endl;

  return 0;
}
