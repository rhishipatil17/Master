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
            std::vector<std::string> args;
            bool running;
        };
    }

    enum launcher_codes
    {
        launch_ConfigSuccess,
        launch_ConfigFailure,
        launch_NoServices,
        launch_RunningServices,
        launch_Success,
        launch_Failure
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
            launcher_codes launch_services();

        private:
            service_launcher();

            std::vector<service> service_list;
            struct service service_security;
            sys_SecurityCodes security_status;
            launcher_codes launcher_status;

            sys_SecurityCodes read_SecurityServiceConfig();
            launcher_codes read_LaunchConfig();
            short int extract_LaunchConfig(std::string FileName, struct service &service);
            void clear_Service(struct service &service);
            long int exec_service(struct service &s_service);
    };
}

#endif