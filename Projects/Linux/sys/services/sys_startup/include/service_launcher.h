#ifndef SERVICE_LAUNCHER
#define SERVICE_LAUNCHER

#include <string>
#include <vector>

#define SERVICE_LIST            "service_list.ini"
#define SERVICE_RUN             ".run"

#define SERVICE_LABEL           "[service]"

#define SERVICE_NAME            "name"
#define SERVICE_ENABLED         "enabled"
#define SERVICE_DIRECTORY       "directory"
#define SERVICE_EXEC            "exec"
#define SERVICE_ARGS            "args"

#define ENABLED_TRUE            "true"
#define ENABLED_FALSE           "false"

namespace sys_startup
{
    struct service
    {
        std::string name;
        std::string enabled;
        std::string directory;
        std::string exec;
        std::vector<std::string> args;
        bool running;
    };

    class service_launcher
    {
        public:
            service_launcher();

            void launch_services();

        private:
            std::vector<service> service_list;

            void read_LaunchConfig();
            long int exec_service(struct service &s_service);
    };
}

#endif