#ifndef TOOLS_H
#define TOOLS_H

#include "StartupConfig.h"
#include "ThreadHandler.h"

using namespace common_Tools;

namespace sys_startup
{
    StartupConfig& s_config();
    ThreadHandler& s_tHandler();
}

#endif