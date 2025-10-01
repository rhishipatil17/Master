#include "Db_HashTable.h"

DbHashTable& DbHashTable::getInstance()
{
    static DbHashTable instance;
    return instance;
}

return_codes calc_Idx(const Db_key &key, Db_idx &Midx)
{
    Db_hash dbh = 0;        //Todo: actual hash calculation function

    Midx = dbh % DB_HT_SIZE;

    return Success;
}

return_codes data_Insert(const Db_key &Mkey, Db_offset &Moffset)
{
    Db_idx idx;
    if(calc_Idx(Mkey, idx) != Success)
    {
        return Failure;
    }
    
    if(idx > DB_HT_SIZE || idx < 0)
    {
        return Failure;
    }


}

