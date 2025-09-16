#ifndef DATA_H
#define DATA_H

#include <memory>
#include "Common.h"
#include "Dbll.h"

class Data
{
    public:
    Db_key get_Key() { return key; };
    Db_offset get_Offset() { return offset; }

    private:
        Data();
        Data(Db_key &Mkey, Db_offset &Moffset, std::shared_ptr<Data> Node = nullptr);
        Data(Data &node);
        Data& operator=(Data &node);

        Db_key key;
        Db_offset offset;
        std::shared_ptr<Data> NextNode;

        friend class Dbll;
};

#endif
