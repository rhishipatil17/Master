#ifndef DB_DATAMAN_H
#define DB_DATAMAN_H

#include "Common.h"

class DbDataMan
{
    private:
        DbDataMan();
        DbDataMan(const DbDataMan &obj) = delete;
        DbDataMan& operator=(const DbDataMan &obj) = delete;
        static DbDataMan& getInstance();

        friend class DbMain;
};

#endif
