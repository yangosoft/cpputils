
#include "ithread.h"
#include "thread.h"

#include <cstdint>
#include <map>
#include <thread>
#include <vector>


#ifndef __CPPUTILS_THREADPOOL_H
#define	__CPPUTILS_THREADPOOL_H



namespace CppUtils
{


class ThreadPool  {
public:
    ThreadPool();
    
    void pause();
    void start();
    void stop();
    
    void add(Thread &thread);
    void remove(Thread &thread);
    
    ~ThreadPool();

protected:
    
    using ThreadList = std::vector<IThread *>;
    using MapThreadId = std::map<IThread *, std::thread *>;
    
    int32_t m_poolLength;
    ThreadList m_threadList;
    MapThreadId m_mapId;

};
};
#endif	/* __CPPUTILS_THREADPOOL_H */
