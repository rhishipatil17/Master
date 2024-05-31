#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

long int number = 0;
mutex mtx;

void increment()
{
    // mtx.lock();
    cout << "thread id: " << this_thread::get_id() << endl;
    for(int i=0; i<1000000; i++)
    {
        number++;
    }
    // mtx.unlock();
}

int main()
{
    thread th1(increment);
    thread th2(increment);

    th1.join();
    th2.join();

    cout << "number: " << number << endl;
}