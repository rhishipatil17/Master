#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include <atomic>


template<typename Qtype>
class ThreadSafeQueue
{
    public:
        ThreadSafeQueue() = delete;
        ThreadSafeQueue(const std::queue<Qtype>&) = delete;
        ThreadSafeQueue(const std::queue<Qtype>&&) = delete;
        std::queue<Qtype>& operator=(const std::queue<Qtype>&) = delete;
        std::queue<Qtype>& operator=(const std::queue<Qtype>&&) = delete;
        ~ThreadSafeQueue();

        void push(const Qtype& element);
        bool try_pop(Qtype& val);
        void wait_and_pop(Qtype& val);

    private:
        std::condition_variable cv;
        std::mutex mtx;
        std::queue<Qtype> queue;
        std::atomic<bool> done;
};

#endif
