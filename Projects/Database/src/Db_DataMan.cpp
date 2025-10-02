#include "Db_DataMan.h"

DbMain::DbDataMan& DbMain::DbDataMan::getInstance()
{
    static DbDataMan instance;
    return instance;
}
