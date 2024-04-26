#include "StartupConfig.h"
#include <fstream>

using namespace startup_config;

StartupConfig& StartupConfig::getInstance(void)
{
    static StartupConfig startupconfig;
    return startupconfig;
}