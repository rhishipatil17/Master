#ifndef CONTACT_2_H
#define CONTACT_2_H

#include <string>

struct contact
{
    std::string name;
    std::string phoneNumber;
    std::string email;

    contact(const std::string& n, const std::string& p, const std::string& e) : 
            name(n), phoneNumber(p), email(e) {}
};

#endif
