#ifndef CRYPTO_ENGINE_H
#define CRYPTO_ENGINE_H

#include <string>
#include <vector>
#include <openssl/evp.h>

class CryptoEngine {
public:
    // Takes the master password and raw JSON string, returns encrypted bytes
    static std::vector<unsigned char> encrypt(const std::string& masterPassword, const std::string& plaintext);

    // Takes the master password and encrypted bytes, returns raw JSON string
    // Throws an exception if the password is wrong or data is tampered with
    static std::string decrypt(const std::string& masterPassword, const std::vector<unsigned char>& ciphertext);

private:
    // Helper function to turn the string password into a 256-bit AES key
    static void deriveKey(const std::string& password, const unsigned char* salt, unsigned char* key);
};

#endif