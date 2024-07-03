#ifndef THREADHANDLER
#define THREADHANDLER

#include <map>
#include <thread>
#include <vector>

namespace common_Tools
{
    class ThreadHandler
    {
        private:
            ThreadHandler();

        public:
            static ThreadHandler& getInstance();
            void create(void (*func)(void));

            std::vector<std::thread> children;
    };
}

#endif