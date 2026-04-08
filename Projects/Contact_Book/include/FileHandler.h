#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string> 
#include <vector>
#include "Contact.h"

class FileHandler
{
    public:
        FileHandler(const std::string& file_name);

        std::vector<Contact> loadContacts();

        void saveContacts(const std::vector<Contact>& contacts);

    private:
        std::string filePath;
};

#endif
