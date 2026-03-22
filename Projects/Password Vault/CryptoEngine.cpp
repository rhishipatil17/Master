#include "CryptoEngine.h"
#include <openssl/rand.h>
#include <openssl/err.h>
#include <stdexcept>
#include <cstring>

// Constants for our cryptography settings
constexpr int SALT_LEN = 16;
constexpr int IV_LEN = 12; // 12 bytes is standard for GCM
constexpr int TAG_LEN = 16;
constexpr int KEY_LEN = 32; // 256 bits for AES-256
constexpr int PBKDF2_ITERATIONS = 210000; // Recommended minimum for SHA-256

void CryptoEngine::deriveKey(const std::string& password, const unsigned char* salt, unsigned char* key) {
    // PBKDF2 takes the password and salt, hashes it 210,000 times, and outputs a 32-byte key
    if (!PKCS5_PBKDF2_HMAC(password.c_str(), password.length(),
                           salt, SALT_LEN, PBKDF2_ITERATIONS,
                           EVP_sha256(), KEY_LEN, key)) {
        throw std::runtime_error("Key derivation failed!");
    }
}

std::vector<unsigned char> CryptoEngine::encrypt(const std::string& masterPassword, const std::string& plaintext) {
    unsigned char salt[SALT_LEN];
    unsigned char iv[IV_LEN];
    unsigned char key[KEY_LEN];

    // 1. Generate random Salt and IV
    RAND_bytes(salt, SALT_LEN);
    RAND_bytes(iv, IV_LEN);

    // 2. Derive the 256-bit AES key
    deriveKey(masterPassword, salt, key);

    // 3. Set up the OpenSSL Context
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) throw std::runtime_error("Failed to create OpenSSL context");

    std::vector<unsigned char> ciphertext(plaintext.length() + EVP_MAX_BLOCK_LENGTH);
    int len = 0;
    int ciphertext_len = 0;

    // 4. Initialize the Encryption operation (AES-256-GCM)
    EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, key, iv);

    // 5. Provide the plaintext message to be encrypted
    EVP_EncryptUpdate(ctx, ciphertext.data(), &len, 
                     reinterpret_cast<const unsigned char*>(plaintext.data()), plaintext.length());
    ciphertext_len = len;

    // 6. Finalize the encryption (GCM math finishes here)
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len);
    ciphertext_len += len;

    // 7. Extract the Authentication Tag
    unsigned char tag[TAG_LEN];
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, TAG_LEN, tag);

    EVP_CIPHER_CTX_free(ctx);

    // 8. Assemble the final payload: [Salt][IV][Tag][Ciphertext]
    std::vector<unsigned char> finalPayload;
    finalPayload.reserve(SALT_LEN + IV_LEN + TAG_LEN + ciphertext_len);
    
    finalPayload.insert(finalPayload.end(), salt, salt + SALT_LEN);
    finalPayload.insert(finalPayload.end(), iv, iv + IV_LEN);
    finalPayload.insert(finalPayload.end(), tag, tag + TAG_LEN);
    finalPayload.insert(finalPayload.end(), ciphertext.begin(), ciphertext.begin() + ciphertext_len);

    return finalPayload;
}

std::string CryptoEngine::decrypt(const std::string& masterPassword, const std::vector<unsigned char>& payload) {
    // Basic validation to ensure the file isn't too small to even contain our headers
    if (payload.size() < (SALT_LEN + IV_LEN + TAG_LEN)) {
        throw std::runtime_error("Vault file is corrupted or too small.");
    }

    unsigned char salt[SALT_LEN];
    unsigned char iv[IV_LEN];
    unsigned char tag[TAG_LEN];
    unsigned char key[KEY_LEN];

    // 1. Unpack the payload
    std::memcpy(salt, payload.data(), SALT_LEN);
    std::memcpy(iv, payload.data() + SALT_LEN, IV_LEN);
    std::memcpy(tag, payload.data() + SALT_LEN + IV_LEN, TAG_LEN);

    const unsigned char* encryptedData = payload.data() + SALT_LEN + IV_LEN + TAG_LEN;
    int encryptedLen = payload.size() - (SALT_LEN + IV_LEN + TAG_LEN);

    // 2. Derive the key using the extracted Salt
    deriveKey(masterPassword, salt, key);

    // 3. Set up the OpenSSL Context
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) throw std::runtime_error("Failed to create OpenSSL context");

    std::vector<unsigned char> plaintext(encryptedLen);
    int len = 0;
    int plaintext_len = 0;

    // 4. Initialize Decryption
    EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, key, iv);

    // 5. Provide the ciphertext to be decrypted
    EVP_DecryptUpdate(ctx, plaintext.data(), &len, encryptedData, encryptedLen);
    plaintext_len = len;

    // 6. Set the expected Authentication Tag
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, TAG_LEN, tag);

    // 7. Finalize Decryption. THIS IS THE MOST IMPORTANT STEP!
    // If the password is wrong, or a single byte was changed, this returns <= 0
    int ret = EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len);
    
    EVP_CIPHER_CTX_free(ctx);

    if (ret > 0) {
        plaintext_len += len;
        return std::string(plaintext.begin(), plaintext.begin() + plaintext_len);
    } else {
        throw std::runtime_error("Authentication failed! Wrong master password or corrupted vault.");
    }
}