#ifndef PHONEBOOK_2_H
#define PHONEBOOK_2_H

#include "Contact2.h"
#include "FileHandler2.h"
#include <string>
#include <vector>

class Phonebook
{
    public:
        Phonebook(const std::string& file_name);
        ~Phonebook();

        void displayAllContacts() const;
        void addContact(const std::string& name, const std::string& phone, const std::string& email);

    private:
        std::vector<contact> contacts;
        FileHandler file_handler;
};

#endif
