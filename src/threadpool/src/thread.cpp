#include "threadpool/thread.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

using namespace CppUtils;

Thread::Thread(): m_status(ThreadStatus::STOPPED)
{
    
}

void Thread::operator()()
{
        while( m_status != ThreadStatus::STOPPED)
        {
            std::cout << "Sleep 1" << std::endl;
            std::this_thread::sleep_for (std::chrono::seconds(1));
        }
}

void Thread::start()
{
    m_status = ThreadStatus::STARTED;
}

void Thread::pause()
{
    m_status = ThreadStatus::PAUSED;
}

void Thread::stop()
{
    m_status = ThreadStatus::STOPPED;
}

Thread::~Thread()
{
    stop();
}
