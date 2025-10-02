#pragma once

#include <memory>
#include "Common.h"
#include "Db_ll.h"

class DbData
{
    public:
    Db_key get_Key() { return key; };
    Db_offset get_Offset() { return offset; }

    private:
        DbData();
        DbData(const Db_key &Mkey, const Db_offset &Moffset, const std::shared_ptr<DbData> NextNode = nullptr);     //parameterised constructor: creates a LL node with key, offset, and pointer to next node
        DbData(const DbData &node);                                                                                 //copy constructor
        DbData& operator=(const DbData &node);                                                                      //assignment operator overload

        Db_key key;                                                                                                 //Node stores key, Db offset and pointer to next node
        Db_offset offset;
        std::shared_ptr<DbData> NextNode;

        friend class DbLl;                                                                                          //Only the LL class should be able to create a node
};

