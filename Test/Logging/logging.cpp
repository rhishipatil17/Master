#include "logging.h"

#include <fstream>

using namespace sLogger;

MasterLogger::MasterLogger()
{
    runThread = false;
}

MasterLogger::~MasterLogger()
{
    {
        std::lock_guard<std::mutex> lock(m_mtx);
        runThread = false;
        m_available.notify_all();
    }
    m_logger.join();
    fName.clear();
}

MasterLogger& MasterLogger::getInstance()
{
    static MasterLogger LogObj;
    return LogObj;
}

void MasterLogger::init(std::string name)
{
    runThread = true;
    fName = name;
    m_logger = std::thread(&MasterLogger::mLoggingThread, this, fName);
}

void MasterLogger::mLoggingThread(const std::string fName)
{
    std::ofstream m_file(fName.c_str());

    while(true)
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_available.wait(lock, [&]{ return (!m_data.empty() || !runThread); });

        if(!runThread && m_data.empty())
        {
            break;
        }

        std::string data = m_data.front();
        m_data.pop();

        lock.unlock();
        m_full.notify_one();

        m_file << data << std::endl;
    }

    m_file.close();
}

void MasterLogger::log_msg(std::string msg)
{
    if(runThread)
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_full.wait(lock, [&]{ return (m_data.size() != MAXDATA); });
        m_data.push(msg);
        lock.unlock();
        m_available.notify_one();
    }
}