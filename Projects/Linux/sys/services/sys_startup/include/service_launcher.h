#ifndef SERVICE_LAUNCHER
#define SERVICE_LAUNCHER

#include <string>
#include <vector>

#define service_run             ".run"
#define service_name            "name"
#define service_enabled         "enabled"
#define service_directory       "directory"
#define service_exec            "exec"

#define enabled_true            "true"
#define enabled_false           "false"

namespace sys_startup
{
    struct service
    {
        std::string name;
        std::string enabled;
        std::string directory;
        std::string exec;
        bool running;
    };

    class service_launcher
    {
        public:
            service_launcher();

            void launch_services();

        private:
            std::vector<service> service_list;
            std::vector<std::string> 

            bool read_launch_config();
            int exec_service(struct service &s_service);
    };
}

#endif