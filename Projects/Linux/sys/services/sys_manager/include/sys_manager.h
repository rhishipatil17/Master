#ifndef SYS_MANAGER
#define SYS_MANAGER

namespace sys_manager
{
    class sys_man
    {
        public:
            sys_man();

        private:
            service_launcher &launcher;
    };
}

#endif