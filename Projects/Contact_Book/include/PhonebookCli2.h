#ifndef PHONEBOOK_CLI_2_H
#define PHONEBOOK_CLI_2_H

#include "Phonebook2.h"
#include <string>

class PhonebookCli
{
    public:
        PhonebookCli(const std::string& file_name);
        void run();

    private:
        Phonebook phonebook;

        void displayMenu() const;
        void clearScreen() const;
};

#endif
