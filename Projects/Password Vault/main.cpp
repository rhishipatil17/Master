#include "VaultCLI.h"

int main() {
    // We will save the encrypted file in the current directory as "my_passwords.vault"
    VaultCLI cli("my_passwords.vault");
    cli.run();
    return 0;
}