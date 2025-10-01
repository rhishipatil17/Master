#ifndef DB_HASHTABLE_H
#define DB_HAsHTABLE_H

#include <array>
#include "Common.h"
#include "Db_ll.h"

class DbHashTable
{
    private:
        DbHashTable();
        DbHashTable(const DbHashTable &obj) = delete;
        DbHashTable& operator=(const DbHashTable& obj) = delete;
        static DbHashTable& getInstance();

        friend class DbMain;

        std::array<DbLl, DB_HT_SIZE> HtBucket;

        return_codes calc_Idx(const Db_key &Mkey, Db_idx &Midx);

    public:
        return_codes data_Insert(const Db_key &Mkey, Db_offset &Moffset);
};

#endif
