#ifndef VAULT_CLI_H
#define VAULT_CLI_H

#include <string>
#include "VaultManager.h" // Include the manager

class VaultCLI {
public:
    // Constructor now takes the path where the vault file will be saved
    VaultCLI(const std::string& vaultPath);
    
    void run();

private:
    VaultManager manager; // The brain of our application
    
    std::string getHiddenPassword(const std::string& prompt);
    std::string getInput(const std::string& prompt);
    void displayMenu();
};

#endif