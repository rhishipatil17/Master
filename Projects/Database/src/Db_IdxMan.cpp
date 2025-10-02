#include "Db_IdxMan.h"

DbMain::DbIdxMan& DbMain::DbIdxMan::getInstance()
{
    static DbIdxMan instance;
    return instance;
}
