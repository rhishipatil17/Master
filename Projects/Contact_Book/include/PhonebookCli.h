#ifndef PHONEBOOKCLI_H
#define PHONEBOOKCLI_H

#include "Phonebook.h"
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
