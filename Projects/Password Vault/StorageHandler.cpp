#include "StorageHandler.h"
#include "CryptoEngine.h"
#include <fstream>
#include <stdexcept>

// Include the nlohmann JSON library (make sure json.hpp is in your project folder)
#include "json.hpp"
using json = nlohmann::json;

StorageHandler::StorageHandler(const std::string& filePath) : filePath(filePath) {}

bool StorageHandler::vaultExists() const {
    std::ifstream file(filePath);
    return file.good();
}

void StorageHandler::saveVault(const std::vector<Credential>& credentials, const std::string& masterPassword) {
    // 1. Serialize C++ vector into a JSON object
    json j = json::array();
    for (const auto& cred : credentials) {
        j.push_back({
            {"service", cred.serviceName},
            {"user", cred.username},
            {"pass", cred.password}
        });
    }
    std::string jsonString = j.dump();

    // 2. Encrypt the JSON string using our OpenSSL wrapper
    std::vector<unsigned char> encryptedData = CryptoEngine::encrypt(masterPassword, jsonString);

    // 3. Write the raw encrypted bytes to the filesystem
    std::ofstream outFile(filePath, std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Failed to open vault file for writing.");
    }
    outFile.write(reinterpret_cast<const char*>(encryptedData.data()), encryptedData.size());
    outFile.close();
}

std::vector<Credential> StorageHandler::loadVault(const std::string& masterPassword) {
    // 1. Open the file at the end (ios::ate) so we can easily get the file size
    std::ifstream inFile(filePath, std::ios::binary | std::ios::ate);
    if (!inFile) {
        throw std::runtime_error("Failed to open vault file for reading.");
    }

    std::streamsize size = inFile.tellg();
    inFile.seekg(0, std::ios::beg); // Go back to the beginning to read

    std::vector<unsigned char> encryptedData(size);
    if (inFile.read(reinterpret_cast<char*>(encryptedData.data()), size)) {
        
        // 2. Decrypt the binary payload. 
        // This will throw an exception if the master password is wrong!
        std::string decryptedJson = CryptoEngine::decrypt(masterPassword, encryptedData);

        // 3. Parse the JSON back into our C++ struct
        auto j = json::parse(decryptedJson);
        std::vector<Credential> credentials;
        for (const auto& item : j) {
            credentials.push_back({
                item["service"],
                item["user"],
                item["pass"]
            });
        }
        return credentials;
    } else {
        throw std::runtime_error("Failed to read vault file.");
    }
}