#include "StartupConfig.h"
#include <fstream>

using namespace sys_startup;

StartupConfig::StartupConfig()
{
    runServices = false;
    //TODO_work: read from file
}

StartupConfig& StartupConfig::getInstance(void)
{
    static StartupConfig startupconfig;
    return startupconfig;
}