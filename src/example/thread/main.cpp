
#include "cpputils/threadpool/thread.h"
#include "cpputils/threadpool/threadpool.h"

#include <thread>
#include <iostream>

class MyThread : public CppUtils::Thread
{
public:
    void operator()() override
    {
        
        while( m_status != ThreadStatus::STOPPED)
        {
            std::cout << "Sleep 300ms" << std::endl;
            std::this_thread::sleep_for (std::chrono::milliseconds(300));
        }
    }
};


int main(int /*argc*/, char ** /*argv*/)
{
    CppUtils::ThreadPool pool;
    MyThread t;
    
    std::cout << "Created thread" << std::endl;
    pool.add(t);
    
    pool.start();
    
    
    std::this_thread::sleep_for (std::chrono::seconds(2));
    pool.remove(t);
    pool.stop();
    
    return 0;
}
