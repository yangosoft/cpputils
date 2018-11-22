#include "threadpool/threadpool.h"

#include <algorithm>
#include <thread>

using namespace CppUtils;

ThreadPool::ThreadPool() : m_poolLength( std::thread::hardware_concurrency() )
{
    
}

ThreadPool::~ThreadPool()
{
    stop();
}

void ThreadPool::pause()
{
    std::for_each(m_threadList.begin(), m_threadList.end(), [this](auto thread){
        thread->pause();
    }); 
}


void ThreadPool::start()
{
    std::for_each(m_threadList.begin(), m_threadList.end(), [this](auto thread){
        thread->start();
    }); 
}

void ThreadPool::stop()
{
    std::for_each(m_threadList.begin(), m_threadList.end(), [this](auto thread){
        thread->stop();
    }); 
}

void ThreadPool::add(Thread &thread)
{
     if ( m_threadList.end() == std::find(std::begin(m_threadList), std::end(m_threadList), &thread))
     {
         std::thread t(Thread::run_helper, &thread); 
         
         m_mapId.insert( std::pair< IThread*, std::thread*>( &thread, &t ));
         m_threadList.push_back(&thread);
     }
}

void ThreadPool::remove(Thread &thread)
{
     m_threadList.erase(std::remove(m_threadList.begin(), m_threadList.end(), &thread), m_threadList.end());
}
