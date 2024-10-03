#ifndef SERVICE_LAUNCHER
#define SERVICE_LAUNCHER

#include "services.h"
#include "sys_manager.h"

namespace sys_manager
{
    enum return_codes
    {
        FAILURE = -1,
        SUCCESS
    };

    class service_launcher: public sys_man
    {
        public:
            static service_launcher& getInstance();
            return_codes launch_services();

        private:
            service_launcher();

            inline void clear_Service(struct service &service);
            long int exec_service(struct service &s_service);

    };
}

#endif