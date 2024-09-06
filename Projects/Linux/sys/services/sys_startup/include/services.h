#ifndef SERVICES
#define SERVICES

#include <vector>
#include <string>

#define SERVICE_COUNT 2

#define SER1_NAME   "sys_security"
#define SER1_DIR    "sys_security/"
#define SER1_EXEC   "./sys_security"

#define SER2_NAME   "sys_manager"
#define SER2_DIR    "sys_manager/"
#define SER2_EXEC   "./sys_manager"

namespace sys_startup
{
    struct service
    {
        std::string name;
        std::string directory;
        std::string exec;
        std::vector<std::string> args;
        long int pid;
    };
}

#endif