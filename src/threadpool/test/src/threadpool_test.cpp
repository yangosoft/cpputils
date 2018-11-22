#include <limits.h>

#include <cpputils/threadpool/thread.h>
#include <cpputils/threadpool/threadpool.h>



#include <gtest/gtest.h>


#include <chrono>
#include <thread>


namespace
{


TEST(ThreadPoolTest, TestAdd)
{
    CppUtils::ThreadPool pool;
    CppUtils::Thread t;
    pool.add(t);
    pool.start();
    pool.remove(t);
    pool.stop();
     
    
    
    
    EXPECT_TRUE(true);
}

};
