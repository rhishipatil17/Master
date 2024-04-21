#ifndef STARTUP_CONFIG
#define STARTUP_CONFIG

#include <vector>
#include <string>

namespace startup_config
{
    namespace
    {
        class service
        {
            std::string name;
            std::string location;

            public:
                friend class StartupConfig;
        };
    }

    class StartupConfig
    {
        public:
            static StartupConfig& getInstance(void);

        private:
            StartupConfig();

            std::vector<service> service_list;
    };
}

#endif