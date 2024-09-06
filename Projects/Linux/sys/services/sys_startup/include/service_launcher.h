#ifndef SERVICE_LAUNCHER
#define SERVICE_LAUNCHER

#include <vector>

#include "services.h"

#define EMPTY_STR ""

namespace sys_startup
{
    enum return_codes
    {
        FAILURE = -1,
        SUCCESS
    };

    class service_launcher
    {
        public:
            static service_launcher& getInstance();
            return_codes launch_services();

        private:
            service_launcher();

            std::vector<service> service_list;
            unsigned short int running_process_count;

            inline void clear_Service(struct service &service);
            long int exec_service(struct service &s_service);
    };
}

#endif