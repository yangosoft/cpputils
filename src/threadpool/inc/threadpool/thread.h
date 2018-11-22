
#include "ithread.h"
#include <mutex>

#ifndef  __CPPUTILS_THREAD_H
#define	 __CPPUTILS_THREAD_H

namespace CppUtils
{
class Thread : public IThread {
public:

    enum class ThreadStatus {PAUSED, STOPPED, STARTED};
    
    Thread();
    void operator()() override;
    void start() override;
    void pause() override;
    void stop() override;
    ~Thread() override;
    
    static void *run_helper(void *context)
    {
//         return ((Thread*)context);
        return static_cast<Thread*>(context);
    }
    
private:
    std::mutex m_mutex;
    ThreadStatus m_status;
    
    
};
}
#endif	/*  __CPPUTILS_THREAD_H */
