#include "PhonebookCli.h"
#include <iostream>

PhonebookCli::PhonebookCli(const std::string& file_name) : phonebook(file_name) {}

void PhonebookCli::displayMenu() const
{
    std::cout << "========Phonebook========" << std::endl;
    std::cout << "1. Display all contacts" << std::endl;
    std::cout << "2. Add a contact" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "=========================" << std::endl;
}

void PhonebookCli::clearScreen() const
{
    std::cout << "\033[2J\033[3J\033[1;1H";
}

void PhonebookCli::run()
{
    bool running = true;
    std::string choice;

    clearScreen();

    while(running)
    {
        displayMenu();
        std::cout << "Choose an option (1-5): " << std::endl << "-> ";

        std::getline(std::cin, choice);
        clearScreen();

        if( choice == "1" )
        {
            std::cout << std::endl;
            phonebook.displayAllContacts();
        }
        else if( choice == "2" )
        {
            std::string name, phone, email;

            std::cout << "Adding new contact--->" << std::endl << std::endl;
            
            std::cout << "Enter name: ";
            std::getline(std::cin, name);

            std::cout << "Enter phone number: ";
            std::getline(std::cin, phone);

            std::cout << "Enter email: ";
            std::getline(std::cin, email);

            phonebook.addContact(name, phone, email);
        }
        else if( choice == "3" )
        {
            std::cout << "Saving and exiting" << std::endl;
            running = false;
        }

        std::cout << std::endl;
    }
}