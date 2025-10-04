#include "Db_HashTable.h"

DbMain::DbHashTable& DbMain::DbHashTable::getInstance()
{
    static DbHashTable instance;
    return instance;
}

Db_idx DbMain::DbHashTable::calc_Idx(const Db_key &Mkey)
{
    Db_hash dbh = 0;        //Todo: actual hash calculation function
    Db_idx idx;

    idx = dbh % DB_HT_SIZE;
    return idx;
}

return_codes DbMain::DbHashTable::get_Data(const Db_key &Mkey, Db_offset &Moffset)
{
    return_codes ret = Failure;
    Db_idx idx;

    do
    {
        idx = calc_Idx(Mkey);
        if(idx > DB_HT_SIZE || idx < 0)
        {
            break;
        }

        DbLl &idxBucket = HtBucket[idx];
        Db_offset tmpOffset;

        if( idxBucket.get_Data(Mkey, tmpOffset) == Success )
        {
            Moffset = tmpOffset;
            tmpOffset = 0;
        }
        else
        {
            break;
        }

        ret = Success;
    }while(0);
    
    return ret;
}

return_codes DbMain::DbHashTable::get_KeyPresent(const Db_key &Mkey, bool &Present)
{
    return_codes ret = Failure;
    Db_idx idx;

    do
    {
        idx = calc_Idx(Mkey);
        if(idx > DB_HT_SIZE || idx < 0)
        {
            break;
        }

        DbLl &idxBucket = HtBucket[idx];
        Present = idxBucket.get_KeyPresent(Mkey);
        ret = Success;
    }while(0);
    
    return ret;
}

return_codes DbMain::DbHashTable::data_Insert(const Db_key &Mkey, const Db_offset &Moffset)
{
    return_codes ret = Failure;
    Db_idx idx;

    do
    {
        idx = calc_Idx(Mkey);
        if(idx > DB_HT_SIZE || idx < 0)
        {
            break;
        }

        DbLl &idxBucket = HtBucket[idx];

        if( idxBucket.data_Insert(Mkey, Moffset) == KeyAlreadyPresent )
        {
            if( idxBucket.data_Replace(Mkey, Moffset) != Success )
            {
                break;
            }
        }
        ret = Success;
    }while(0);
    
    return ret;
}

return_codes DbMain::DbHashTable::data_Remove(const Db_key &Mkey)
{
    return_codes ret = Failure;
    Db_idx idx;

    do
    {
        idx = calc_Idx(Mkey);
        if(idx > DB_HT_SIZE || idx < 0)
        {
            break;
        }

        DbLl &idxBucket = HtBucket[idx];

        if( idxBucket.data_Remove(Mkey) != Success)
        {
            break;
        }

        ret = Success;
    }while(0);
    
    return ret;
}

return_codes DbMain::DbHashTable::data_Replace(const Db_key &Mkey, const Db_offset &Moffset)
{
    return_codes ret = Failure;
    Db_idx idx;

    do
    {
        idx = calc_Idx(Mkey);
        if(idx > DB_HT_SIZE || idx < 0)
        {
            break;
        }

        DbLl &idxBucket = HtBucket[idx];

        if( idxBucket.data_Replace(Mkey, Moffset) != Success)
        {
            break;
        }

        ret = Success;
    }while(0);
    
    return ret;
}
