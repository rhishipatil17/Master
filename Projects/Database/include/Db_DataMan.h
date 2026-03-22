#pragma once

#include "Common.h"
#include "Db_main.h"

class DbMain::DbDataMan
{
    private:
        DbDataMan();
        DbDataMan(const DbDataMan &obj) = delete;
        DbDataMan& operator=(const DbDataMan &obj) = delete;
        static DbDataMan& getInstance();
};
