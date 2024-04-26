#ifndef STARTUP_CONFIG
#define STARTUP_CONFIG

#include <vector>
#include <string>


namespace startup_config
{
    class StartupConfig
    {
        public:
            static StartupConfig& getInstance(void);

        private:
            StartupConfig() {}
    };
}

#endif