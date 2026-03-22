#include "thread_safe_queue.h"

template<typename Qtype>
void ThreadSafeQueue<Qtype>::push(const Qtype& element)
{
    {
        std::lock_guard<mutex> lock(mtx);
        queue.emplace(element);
    }
    cv.notify_one();
}

template<typename Qtype>
bool ThreadSafeQueue<Qtype>::try_pop(Qtype& val)
{
    {
        std::lock_guard<mutex> lock(mtx);
        if(queue.empty())
        {
            return false;
        }

        val = queue.front();
        queue.pop();
        return true;
    }
}

template<typename Qtype>
void wait_and_pop(Qtype& val)
{
    std::unique_lock<mutex> lock(mtx);
    cv.wait(lock, [this]{ return !queue.empty() || done; });

    if(done)
    {
        return;
    }

    val = queue.front();
    queue.pop();
}
