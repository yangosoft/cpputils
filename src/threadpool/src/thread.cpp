#include "threadpool/thread.h"

#include <algorithm>
#include <chrono>
#include <thread>

using namespace CppUtils;

Thread::Thread(): m_status(ThreadStatus::STOPPED)
{
    
}

void Thread::operator()()
{
    
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
