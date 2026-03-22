#ifndef STORAGE_HANDLER_H
#define STORAGE_HANDLER_H

#include <string>
#include <vector>
#include "VaultManager.h" // Gives us access to the Credential struct

class StorageHandler {
public:
    // Initialize with the path where the .vault file will be saved
    // (e.g., "/home/user/.local/share/myvault.vault")
    StorageHandler(const std::string& filePath);

    // Helper to check if a vault already exists at the given path
    bool vaultExists() const;

    // 1. Converts the vector of Credentials to a JSON string
    // 2. Passes the JSON and master password to CryptoEngine
    // 3. Writes the resulting encrypted bytes to the file system
    void saveVault(const std::vector<Credential>& credentials, const std::string& masterPassword);

    // 1. Reads the raw encrypted bytes from the file system
    // 2. Passes the bytes and master password to CryptoEngine
    // 3. Parses the decrypted JSON string back into a vector of Credentials
    // Note: This should throw an exception if the password is wrong!
    std::vector<Credential> loadVault(const std::string& masterPassword);

private:
    std::string filePath;
};

#endif