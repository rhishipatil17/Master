#ifndef STARTUP_CONFIG
#define STARTUP_CONFIG

#include <vector>
#include <string>


namespace sys_startup
{
    class StartupConfig
    {
        public:
            static StartupConfig& getInstance(void);
            void readConfig();

        private:
            StartupConfig();

            bool runServices;
    };
}

#endif