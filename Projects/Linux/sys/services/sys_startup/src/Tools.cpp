#include "Tools.h"


using namespace sys_startup;
using namespace common_Tools;

StartupConfig& s_config()
{
    return StartupConfig::getInstance();
}

ThreadHandler& s_tHandler()
{
    return ThreadHandler::getInstance();
}