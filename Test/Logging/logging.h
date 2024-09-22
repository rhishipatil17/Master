#ifndef LOGGING_H
#define LOGGING_H

#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>

#define MAXDATA 50

namespace sLogger
{
    class MasterLogger
    {
        public:
            static MasterLogger& getInstance();
            void init(std::string name);
            void log_msg(std::string msg);

        private:
            std::queue<std::string> m_data;
            std::mutex m_mtx;
            std::condition_variable m_available;
            std::condition_variable m_full;
            std::thread m_logger;
            std::string fName;
            bool runThread;

            MasterLogger();
            MasterLogger(const MasterLogger &obj) = delete;
            MasterLogger& operator=(const MasterLogger &obj) = delete;
            ~MasterLogger();
            void mLoggingThread(const std::string fName);
    };
}

#endif