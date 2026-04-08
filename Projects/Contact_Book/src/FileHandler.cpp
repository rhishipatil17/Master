#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>

FileHandler::FileHandler(const std::string& file_name) : filePath(file_name) {}

std::vector<Contact> FileHandler::loadContacts()
{
    std::vector<Contact> contacts;
    do
    {
        std::ifstream inFile(filePath);
        if(!inFile.is_open())
        {
            break;
        }

        std::string line;
        while(std::getline(inFile, line))
        {
            std::stringstream ss(line);
            std::string name, phone, email;

            if(std::getline(ss, name, ',') &&
                std::getline(ss, phone, ',') &&
                std::getline(ss, email, ','))
            {
                contacts.emplace_back(Contact(name, phone, email));
            }
        }
        inFile.close();

    }while(false);

    return contacts;
}

void FileHandler::saveContacts(const std::vector<Contact>& contacts)
{
    std::ofstream outFile(filePath);
    
    if(!outFile.is_open())
    {
        std::cerr << "Error: Could not open file to save contacts\n";
        return;
    }

    for(const auto& contact : contacts)
    {
        outFile << contact.name << ","
                << contact.phoneNumber << ","
                << contact.email << std::endl;
    }

    outFile.close();
}
