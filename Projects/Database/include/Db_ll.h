#pragma once

#include <memory>
#include "Common.h"
#include "Db_data.h"

class DbLl
{
    public:
        Db_ll_length get_Length() { return length; }
        return_codes get_Data(const Db_key &Mkey, Db_offset &Moffset);                //returns the offset for a particular key
        bool get_KeyPresent(const Db_key &Mkey);                              //checks if the key is present in the LL
        return_codes data_Insert(const Db_key &Mkey, const Db_offset &Moffset);        //creates a node at the end of the LL and adds the key
        return_codes data_Remove(const Db_key &Mkey);
        return_codes data_Replace(const Db_key &Mkey, const Db_offset &Moffset);

    private:
        DbLl();
        
        std::shared_ptr<DbData> hptr;
        Db_ll_length length;
};
