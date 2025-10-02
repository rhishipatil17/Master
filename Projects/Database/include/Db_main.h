#pragma once

#include <array>
#include "Common.h"
#include "Db_ll.h"
#include "Db_IdxMan.h"
#include "Db_DataMan.h"
#include "Db_HashTable.h"

typedef class DbMain
{
    private:
        class DbIdxMan;
        class DbDataMan;
        class DbHashTable;
}Db;
