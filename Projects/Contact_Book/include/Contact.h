#ifndef CONTACT_H
#define CONTACT_H

#include <string>

struct Contact
{
    std::string name;
    std::string phoneNumber;
    std::string email;

    Contact(std::string n, std::string pn, std::string e)
    : name(n), phoneNumber(pn), email(e) {}
};

#endif
