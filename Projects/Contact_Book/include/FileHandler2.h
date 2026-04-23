#ifndef FILE_HANDLER_2_H
#define FILE_HANDLER_2_H

#include "Contact2.h"
#include <string>
#include <vector>

class FileHandler
{
    public:
        FileHandler(const std::string& file_name) : file(file_name) {};

        std::vector<contact> loadContacts();

        void saveContacts(const std::vector<contact>& contacts);

    private:
        std::string file;
};

#endif
