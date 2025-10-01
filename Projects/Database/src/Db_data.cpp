#include "Db_data.h"

DbData::DbData()
{
    key = 0;
    offset = 0;
    NextNode = std::make_shared<DbData>(nullptr);
}

DbData::DbData(const Db_key &Mkey, const Db_offset &Moffset, const std::shared_ptr<DbData> NextNode = nullptr)
{
    key = Mkey;
    offset = Moffset;
    this->NextNode = NextNode;
}

DbData::DbData(const DbData &node)
{
    key = node.key;
    offset = node.offset;
    NextNode = node.NextNode;
}

DbData& DbData::operator=(const DbData &node)
{
    key = node.key;
    offset = node.offset;
    NextNode = node.NextNode;
}
