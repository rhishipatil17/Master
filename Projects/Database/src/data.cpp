#include "data.h"

Data::Data()
{
    key = 0;
    offset = 0;
    NextNode = std::make_shared<Data>();
}

Data::Data(Db_key &Mkey, Db_offset &Moffset, std::shared_ptr<Data> Node = nullptr)
{
    key = Mkey;
    offset = Moffset;
    NextNode = Node;
}

Data::Data(Data &node)
{
    key = node.key;
    offset = node.offset;
    NextNode = node.NextNode;
}

Data& Data::operator=(Data &node)
{
    key = node.key;
    offset = node.offset;
    NextNode = node.NextNode;
}
