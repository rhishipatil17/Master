#pragma once

#include <array>
#include "Common.h"
#include "Db_main.h"
#include "Db_ll.h"

class DbMain::DbHashTable
{
    public:
        static DbHashTable& getInstance();
        return_codes get_Data(const Db_key &Mkey, Db_offset &Moffset);
        return_codes get_KeyPresent(const Db_key &Mkey, bool &Present);
        return_codes data_Insert(const Db_key &Mkey, const Db_offset &Moffset);
        return_codes data_Remove(const Db_key &Mkey);
        return_codes data_Replace(const Db_key &Mkey, const Db_offset &Moffset);

    private:
        DbHashTable();
        DbHashTable(const DbHashTable &obj) = delete;
        DbHashTable& operator=(const DbHashTable& obj) = delete;
        Db_idx calc_Idx(const Db_key &Mkey);

        std::array<DbLl, DB_HT_SIZE> HtBucket;
};

