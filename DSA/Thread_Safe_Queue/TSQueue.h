#include <mutex>
#include <condition_variable>
#include <atomic>
#include <queue>

template<typename T>
class ThreadSafeQueue
{
    private:
        std::mutex mtx;
        std::condition_variable cv;
        std::queue<T> TSQ;
        
    public:
        ThreadSafeQueue();
        void push(const T &val);
        bool try_pop(T& val);
        void wait_and_pop(T& val);
};

void push(const T &val)
{
    {
        std::lock_guard<mutex> lock(mtx);
        TSQ.push(val)
    }
    cv.notify_one();
}

bool try_pop(T& val)
{
    std::lock_guard<mutex> lock(mtx);
    
    if(TSQ.empty())
    {
        return false;
    }
    
    val = TSQ.front();
    TSQ.pop();
    return true;
}

void wait_and_pop(T& val)
{
    std::unique_lock<mutex> lock(mtx);
    cv.wait(lock, [this]{ return !TSQ.empty(); })
    
    val = TSQ.front();
    TSQ.pop();
}
