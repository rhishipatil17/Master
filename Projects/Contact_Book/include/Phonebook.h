#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <vector>
#include <string>
#include "Contact.h"
#include "FileHandler.h"

class Phonebook
{
    public:
        Phonebook(const std::string& storageFile);
        ~Phonebook();

        void addContact(const std::string& name, const std::string& phone, const std::string& email);
        void displayAllContacts() const;
        // void searchContact(const std::string& name) const;
        // void deleteContact(const std::string& name);
    
    private:
        std::vector<Contact> contacts;
        FileHandler fileHandler;
};

#endif
