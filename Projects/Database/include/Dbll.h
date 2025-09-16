#ifndef DBLL_H
#define DBLL_H

#include <memory>
#include "Common.h"
#include "data.h"

class Dbll
{
    public:
        Db_ll_length get_Length() { return length; }
        return_codes get_Data(Db_key &Mkey, Db_offset &Moffset);
        return_codes DataInsert(Db_key &Mkey, Db_offset &Moffset);
        return_codes DataRemove(Db_key &Mkey);

    private:
        Dbll();
        
        std::shared_ptr<Data> hptr;
        Db_ll_length length;
};

#endif
