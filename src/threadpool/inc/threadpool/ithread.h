#ifndef  __CPPUTILS_ITHREAD_H
#define	 __CPPUTILS_ITHREAD_H


namespace CppUtils
{
class IThread {
public:

    IThread() = default;
    virtual void operator()() = 0;
    virtual void start() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual ~IThread() = default;
};
}
#endif	/*  __CPPUTILS_ITHREAD_H */
