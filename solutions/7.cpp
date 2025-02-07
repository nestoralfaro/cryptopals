/*
# S1C7 - AES in ECB mode
Write a C++ program that decrypts the Base64-encoded content in 7.txt,
which has been encrypted via AES-128 in ECB mode under the key
(case-sensitive, without the quotes; exactly 16 characters; exactly 16 bytes long)
```
"YELLOW SUBMARINE".
```

While possible using OpenSSL::Cipher and giving it AES-128-ECB as the cipher; do this with code.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

// Function to decode Base64
std::vector<unsigned char> decodeBase64(const std::string &b64input) {
  BIO *bio, *b64;
  int decodeLen = b64input.length();
  std::vector<unsigned char> buffer(decodeLen);

  bio = BIO_new_mem_buf(b64input.data(), decodeLen);
  b64 = BIO_new(BIO_f_base64());
  bio = BIO_push(b64, bio);

  BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // No newlines
  int len = BIO_read(bio, buffer.data(), decodeLen);
  buffer.resize(len);

  BIO_free_all(bio);
  return buffer;
}

// Function to decrypt AES-128-ECB using OpenSSL's EVP API
std::vector<unsigned char> aesEcbDecrypt(const std::vector<unsigned char> &ciphertext, const std::string &key) {
  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  if (!ctx) {
    throw std::runtime_error("Failed to create EVP_CIPHER_CTX");
  }

  std::vector<unsigned char> plaintext(ciphertext.size());
  int len = 0, plaintextLen = 0;

  // Initialize AES-128-ECB decryption
  if (EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), nullptr,
                         reinterpret_cast<const unsigned char *>(key.c_str()), nullptr) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("EVP_DecryptInit_ex failed");
  }

  EVP_CIPHER_CTX_set_padding(ctx, 0); // No padding for exact block decryption

  // Decrypt the data
  if (EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext.size()) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("EVP_DecryptUpdate failed");
  }
  plaintextLen += len;

  if (EVP_DecryptFinal_ex(ctx, plaintext.data() + plaintextLen, &len) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("EVP_DecryptFinal_ex failed");
  }
  plaintextLen += len;
  plaintext.resize(plaintextLen);

  EVP_CIPHER_CTX_free(ctx);
  return plaintext;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " <filename> <key>" << std::endl;
    return 1;
  }
  const std::string key = argv[2];// AES-128 key (16 bytes)

  // Read Base64-encoded ciphertext from file
  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cerr << "Error: Unable to open file " << argv[1] << std::endl;
    return 1;
  }

  std::string base64Ciphertext((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  // Remove newlines and carriage returns from the Base64 string before decoding
  base64Ciphertext.erase(std::remove(base64Ciphertext.begin(), base64Ciphertext.end(), '\n'), base64Ciphertext.end());
  base64Ciphertext.erase(std::remove(base64Ciphertext.begin(), base64Ciphertext.end(), '\r'), base64Ciphertext.end());

  file.close();

  // std::cout << "Processed file " << argv[1] << " successfully." << std::endl;

  // Decode Base64
  std::vector<unsigned char> ciphertext = decodeBase64(base64Ciphertext);

  // std::cout << "Decoded ciphertext (hex): " << ciphertext.size() << " many characters." << std::endl;
  // for (unsigned char c : ciphertext) {
  //   std::cout << std::hex << (int)c << " ";
  // }
  // std::cout << std::endl;

  // Decrypt AES-128-ECB
  std::vector<unsigned char> plaintext = aesEcbDecrypt(ciphertext, key);

  // Print the decrypted text
  std::cout << std::string(plaintext.begin(), plaintext.end()) << std::endl;

  return 0;
}
