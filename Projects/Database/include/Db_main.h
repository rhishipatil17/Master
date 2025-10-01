#ifndef DB_MAIN_H
#define DB_MAIN_H

#include <array>
#include "Common.h"
#include "Db_ll.h"

class DbMain
{
    return_codes Db_DataInsert(const Db_key &Mkey, const Db_offset &Moffset);
    return_codes Db_DataRemove();
    return_codes Db_getData();

    private:
        void calculate_hash(const Db_key &Mkey);

        std::array<DbLl, DB_SIZE> DbHashTable;
};

#endif