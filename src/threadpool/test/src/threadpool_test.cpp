#include <limits.h>

#include <threadpool/thread.h>
#include <threadpool/threadpool.h>



#include <gtest/gtest.h>


#include <chrono>
#include <iostream>
#include <thread>


namespace
{
    


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



TEST(ThreadPoolTest, TestAdd)
{
    CppUtils::ThreadPool pool;
    MyThread t;
    pool.add(t);
    pool.start();
    pool.remove(t);
    pool.stop();
     
    
    
    
    EXPECT_TRUE(true);
}

};
