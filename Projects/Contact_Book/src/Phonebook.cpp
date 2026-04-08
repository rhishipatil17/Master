#include "Phonebook.h"
#include <iostream>
#include <algorithm>

Phonebook::Phonebook(const std::string& storageFile) : fileHandler(storageFile)
{
    contacts = fileHandler.loadContacts();
}

Phonebook::~Phonebook()
{
    fileHandler.saveContacts(contacts);
}

void Phonebook::addContact(const std::string& name, const std::string& phone, const std::string& email)
{
    contacts.emplace_back(Contact(name, phone, email));
    std::cout << std::endl << "Contact added successfully" << std::endl;
}

void Phonebook::displayAllContacts() const
{
    if(contacts.empty())
    {
        std::cout << "Contact book is empty" << std::endl;
        return;
    }

    std::cout << "------- Contact List -------" << std::endl;
    for(const auto& contact : contacts)
    {
        std::cout << "Name:         " << contact.name << std::endl
                  << "Phone Number: " << contact.phoneNumber << std::endl
                  << "Email:        " << contact.email << std::endl
                  << "--------------------" << std::endl;
    }
}
