#ifndef VAULT_CLI_H
#define VAULT_CLI_H

#include <string>
#include "VaultManager.h"

class VaultCLI
{
    public:
        VaultCLI(const std::string& vaultPath);
        
        void run();

    private:
        VaultManager manager;
        
        std::string getHiddenPassword(const std::string& prompt);
        std::string getInput(const std::string& prompt);
        void displayMenu();
};

#endif
