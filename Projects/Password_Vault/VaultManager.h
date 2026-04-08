#ifndef VAULT_MANAGER_H
#define VAULT_MANAGER_H

#include <string>
#include <vector>

// A simple struct to hold one entry
struct Credential 
{
    std::string serviceName;
    std::string username;
    std::string password;
};

class VaultManager
{
    public:
        VaultManager(const std::string& filePath);
        
        bool unlockVault(const std::string& masterPassword);
        void addCredential(const std::string& service, const std::string& user, const std::string& pass);
        Credential getCredential(const std::string& service);
        void saveVault(); // Serializes to JSON, encrypts, and writes to disk

    private:
        std::string masterPasswordCache; // Kept in memory only while unlocked
        std::string vaultFilePath;
        std::vector<Credential> credentials;
};

#endif