#ifndef SYS_MANAGER
#define SYS_MANAGER

#include <vector>
#include "service_launcher.h"

namespace sys_manager
{
    class sys_man
    {
        public:
            sys_man();

        protected:
            std::vector<service> service_list;
            unsigned short int running_process_count;
    };
}

#endif