#include "Db_DataMan.h"

DbDataMan& DbDataMan::getInstance()
{
    static DbDataMan instance;
    return instance;
}
