#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

// TEST

namespace rp
{
    template<typename qType>
    class ThreadSafeQueue
    {
        public:
            ThreadSafeQueue()
            { 
                m_done = false;
            }
            ~ThreadSafeQueue() = default;
            ThreadSafeQueue(const ThreadSafeQueue& other) = delete;
            ThreadSafeQueue(ThreadSafeQueue&& other) = delete;
            ThreadSafeQueue& operator=(const ThreadSafeQueue& other) = delete;
            ThreadSafeQueue& operator=(ThreadSafeQueue&& other) = delete;

            bool empty()
            {
                std::lock_guard<std::mutex> lock(m_mtx);
                return m_queue.empty();
            }
            std::size_t size()
            {
                std::lock_guard<std::mutex> lock(m_mtx);
                return m_queue.size();
            }
            void done()
            {
                {
                    std::lock_guard<std::mutex> lock(m_mtx);
                    m_done = true;
                }
                m_cv.notify_all();
            }
            void addData(const qType& data)
            {
                {
                    std::lock_guard<std::mutex> lock(m_mtx);
                    m_queue.emplace(data);
                }
                m_cv.notify_one();
            }
            bool try_getData(qType& data)
            {
                std::lock_guard<std::mutex> lock(m_mtx);
                if(m_queue.empty())
                {
                    return false;
                }

                data = std::move(m_queue.front());
                m_queue.pop();
                return true;
            }
            bool wait_getData(qType& data)
            {
                std::unique_lock<std::mutex> lock(m_mtx);
                m_cv.wait(lock, [this]{ return (!m_queue.empty() || m_done); });

                if(m_queue.empty() && m_done)
                {
                    return false;
                }

                data = std::move(m_queue.front());
                m_queue.pop();
                return true;
            }
        private:
            std::queue<qType> m_queue;
            std::condition_variable m_cv;
            std::mutex m_mtx;
            bool m_done;
    };
}

#endif
