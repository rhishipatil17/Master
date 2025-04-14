#ifndef SERVICES
#define SERVICES

#include <vector>
#include <string>

#define SERVICE_COUNT 1

#define SER1_NAME   "sys_comms"
#define SER1_DIR    "sys_comms/"
#define SER1_EXEC   "./sys_comms"

#define MAX_ARG_SIZE 20

namespace sys_manager
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