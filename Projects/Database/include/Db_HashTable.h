#pragma once

#include <array>
#include "Common.h"
#include "Db_main.h"
#include "Db_ll.h"

class DbMain::DbHashTable
{
    public:
        static DbHashTable& getInstance();
        return_codes calc_Idx(const Db_key &Mkey, Db_idx &Midx);
        return_codes data_Insert(const Db_key &Mkey, Db_offset &Moffset);

    private:
        DbHashTable();
        DbHashTable(const DbHashTable &obj) = delete;
        DbHashTable& operator=(const DbHashTable& obj) = delete;

        std::array<DbLl, DB_HT_SIZE> HtBucket;
};

