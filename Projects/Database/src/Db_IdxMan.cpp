#include "Db_IdxMan.h"

DbIdxMan& DbIdxMan::getInstance()
{
    static DbIdxMan instance;
    return instance;
}
