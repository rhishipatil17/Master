#include "VaultCLI.h"
#include <iostream>
#include <termios.h> // For terminal I/O control
#include <unistd.h>  // For STDIN_FILENO

// Initialize the VaultManager with the file path
VaultCLI::VaultCLI(const std::string& vaultPath) : manager(vaultPath) {}

// Standard visible input
std::string VaultCLI::getInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

// Secure hidden input (The Linux Magic)
std::string VaultCLI::getHiddenPassword(const std::string& prompt) {
    std::string password;
    std::cout << prompt;

    termios oldt; // Struct to hold the original terminal settings
    termios newt; // Struct to hold the modified settings

    // 1. Get the current terminal settings for Standard Input (keyboard)
    tcgetattr(STDIN_FILENO, &oldt);
    
    // 2. Make a copy of the settings to modify
    newt = oldt;
    
    // 3. Disable the ECHO flag using a bitwise NOT operator
    newt.c_lflag &= ~ECHO;
    
    // 4. Apply the new settings immediately (TCSANOW)
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // 5. Read the user's password while the terminal is "blind"
    std::getline(std::cin, password);

    // 6. Restore the original terminal settings so the user's terminal isn't broken!
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    // Print a newline because the user's 'Enter' keypress was also hidden
    std::cout << std::endl;

    return password;
}

void VaultCLI::displayMenu() {
    std::cout << "\n=== Local Password Vault ===\n";
    std::cout << "1. Unlock Vault\n";
    std::cout << "2. Add New Credential\n";
    std::cout << "3. Get Credential\n";
    std::cout << "4. Exit\n";
    std::cout << "============================\n";
}

// The main loop of the application
void VaultCLI::run() {
    bool running = true;
    bool isUnlocked = false;

    while (running) {
        displayMenu();
        std::string choice = getInput("Choose an option (1-4): ");

        if (choice == "1") {
            std::string masterPassword = getHiddenPassword("Enter Master Password: ");
            std::cout << "[*] Attempting to unlock vault...\n";
            
            // Call the manager!
            isUnlocked = manager.unlockVault(masterPassword);
            
            if (isUnlocked) {
                std::cout << "[+] Vault unlocked successfully!\n";
            }

        } else if (choice == "2") {
            if (!isUnlocked) {
                std::cout << "[-] Error: Vault is locked. Please unlock first.\n";
                continue;
            }
            std::string service = getInput("Service Name (e.g., github): ");
            std::string user = getInput("Username: ");
            std::string pass = getHiddenPassword("Password to store (input hidden): ");
            
            // Pass the data to the manager to encrypt and save
            manager.addCredential(service, user, pass);
            std::cout << "[+] Credential securely added and saved to disk!\n";

        } else if (choice == "3") {
            if (!isUnlocked) {
                std::cout << "[-] Error: Vault is locked. Please unlock first.\n";
                continue;
            }
            std::string service = getInput("Enter Service Name to retrieve: ");
            
            // Fetch the credential
            Credential cred = manager.getCredential(service);
            
            if (cred.serviceName.empty()) {
                std::cout << "[-] No credential found for " << service << ".\n";
            } else {
                std::cout << "\n--- Credential Found ---\n";
                std::cout << "Service:  " << cred.serviceName << "\n";
                std::cout << "Username: " << cred.username << "\n";
                std::cout << "Password: " << cred.password << "\n";
                std::cout << "------------------------\n";
            }

        } else if (choice == "4") {
            std::cout << "Locking vault and exiting. Goodbye!\n";
            running = false;

        } else {
            std::cout << "[-] Invalid choice. Please try again.\n";
        }
    }
}