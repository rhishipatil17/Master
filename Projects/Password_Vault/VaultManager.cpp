#include "VaultManager.h"
#include "StorageHandler.h"
#include <iostream>

VaultManager::VaultManager(const std::string& filePath) : vaultFilePath(filePath) {}

bool VaultManager::unlockVault(const std::string& masterPassword)
{
    StorageHandler storage(vaultFilePath);

    if (storage.vaultExists())
    {
        try
        {
            // Attempt to load and decrypt the vault
            credentials = storage.loadVault(masterPassword);
            masterPasswordCache = masterPassword; // Temporarily store in memory
            return true;
        } 
        catch (const std::exception& e)
        {
            // This catches the "Authentication failed!" error from CryptoEngine
            std::cerr << "[-] Unlock failed: " << e.what() << "\n";
            return false;
        }
    }
    else
    {
        // If the file doesn't exist, treat this as setting up a new vault
        std::cout << "[*] No existing vault found. Creating a new one.\n";
        masterPasswordCache = masterPassword;
        return true;
    }
}

void VaultManager::addCredential(const std::string& service, const std::string& user, const std::string& pass)
{
    // Add the new credential to our active memory
    credentials.push_back({service, user, pass});
    
    // Automatically encrypt and save to disk so data isn't lost
    saveVault(); 
}

Credential VaultManager::getCredential(const std::string& service)
{
    for (const auto& cred : credentials)
    {
        if (cred.serviceName == service)
        {
            return cred; // Found it!
        }
    }
    // Return an empty struct if not found
    return {"", "", ""}; 
}

void VaultManager::saveVault()
{
    if (masterPasswordCache.empty())
    {
        std::cerr << "[-] Error: Cannot save. Vault is locked.\n";
        return;
    }
    
    StorageHandler storage(vaultFilePath);
    try
    {
        storage.saveVault(credentials, masterPasswordCache);
    } 
    catch (const std::exception& e)
    {
        std::cerr << "[-] Save failed: " << e.what() << "\n";
    }
}
