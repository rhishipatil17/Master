#ifndef SERVICE_LAUNCHER
#define SERVICE_LAUNCHER

#include <string>
#include <vector>

#include "startup_security.h"

#define SERVICE_SECURITY        "service_security.ini"
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

#define DIR_SEPERATOR           "/"

namespace sys_startup
{
    namespace
    {
        struct service
        {
            std::string name;
            std::string enabled;
            std::string directory;
            std::string exec;
            std::vector<char[20]> args;
            bool running;
            long int pid;
        };
    }

    enum launcher_codes
    {
        launch_Success,
        launch_Failure,
        launch_ConfigSuccess,
        launch_ConfigFailure,
        launch_NoServices,
        launch_RunningServices
    };

    enum return_codes
    {
        FAILURE = -1,
        SUCCESS = 0
    };

    class service_launcher
    {
        public:
            static service_launcher& getInstance();
            sys_SecurityCodes get_SecurityStatus() { return security_status; }
            launcher_codes get_LauncherStatus() { return launcher_status; }
            sys_SecurityCodes launch_security();
            launcher_codes launch_services();

        private:
            service_launcher();

            std::vector<service> service_list;
            struct service service_security;
            sys_SecurityCodes security_status;
            launcher_codes launcher_status;
            unsigned short int total_process_count;
            unsigned short int running_process_count;

            sys_SecurityCodes read_SecurityServiceConfig();
            launcher_codes read_LaunchConfig();
            short int extract_LaunchConfig(std::string FileName, struct service &service);
            void clear_Service(struct service &service);
            long int exec_service(struct service &s_service);
    };
}

#endif