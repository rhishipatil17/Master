#include "StartupConfig.h"

using namespace startup_config;

StartupConfig::StartupConfig()
{

}

StartupConfig& StartupConfig::getInstance(void)
{
    static StartupConfig startupconfig;
    return startupconfig;
}