#ifndef DB_IDXMAN_H
#define DB_IDXMAN_H

#include <string>
#include "Common.h"

class DbIdxMan
{
    private:
        DbIdxMan();
        DbIdxMan(const DbIdxMan& obj) = delete;
        DbIdxMan& operator=(const DbIdxMan &obj) = delete;
        static DbIdxMan& getInstance();

        friend class DbMain;

        std::string idx_file;
};

#endif
