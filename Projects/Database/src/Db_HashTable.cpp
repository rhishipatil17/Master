#include "Db_HashTable.h"

DbMain::DbHashTable& DbMain::DbHashTable::getInstance()
{
    static DbHashTable instance;
    return instance;
}

return_codes DbMain::DbHashTable::calc_Idx(const Db_key &key, Db_idx &Midx)
{
    Db_hash dbh = 0;        //Todo: actual hash calculation function

    Midx = dbh % DB_HT_SIZE;

    return Success;
}

return_codes DbMain::DbHashTable::data_Insert(const Db_key &Mkey, Db_offset &Moffset)
{
    return_codes ret = Failure;
    Db_idx idx;

    do
    {
        if(calc_Idx(Mkey, idx) != Success)
        {
            break;
        }

        if(idx > DB_HT_SIZE || idx < 0)
        {
            break;
        }
        
    }while(0);
    
    return ret;
}
