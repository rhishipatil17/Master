#pragma once

#include <string>
#include "Common.h"
#include "Db_main.h"

class DbMain::DbIdxMan
{
    private:
        DbIdxMan();
        DbIdxMan(const DbIdxMan& obj) = delete;
        DbIdxMan& operator=(const DbIdxMan &obj) = delete;
        static DbIdxMan& getInstance();

        std::string idx_file;
};

