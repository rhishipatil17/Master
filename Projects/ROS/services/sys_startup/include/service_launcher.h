#ifndef SERVICE_LAUNCHER
#define SERVICE_LAUNCHER

#include <vector>

#include "services.h"

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
            //launch processes from the list
            return_codes launch_services();

        private:
            service_launcher();

            std::vector<service> service_list;
            //maintaining a count of successfully started proceses
            unsigned short int running_process_count;

            //clear details stored for each process
            inline void clear_Service(struct service &service);
            //start each process from the list
            long int exec_service(struct service &s_service);
    };
}

#endif