#include <iostream>
// #include <chrono>
#include <unistd.h>
#include <thread>
#include <semaphore>

using namespace std;
long long unsigned int number = 0;

// binary_semaphore semaphore(1);
counting_semaphore<10> semaphore(2);

void func(int x)
{
    semaphore.acquire();
    cout << "Thread number: " << x << " ID: " << this_thread::get_id() << endl;
    for(int i=0; i<1000000; i++)
    {
        number++;
    }
    semaphore.release();
}

int main()
{
    thread th1(func, 1);
    thread th2(func, 2);

    th1.join();
    th2.join();

    cout << endl;
    cout << "number: " << number << endl;

    return 0;
}