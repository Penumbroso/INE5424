// EPOS Active Object Abstraction Declarations

#ifndef __active_h
#define __active_h

#include <thread_kernel.h>

namespace EPOS_Kernel {

class Active: public Thread
{
public:
    Active() : Thread(&entry, this, Thread::SUSPENDED) {}
    virtual ~Active() {}

    virtual int run() = 0;

    void start() { resume(); }

private:
    static int entry(Active * runnable) { return runnable->run(); }
};

} // namespace EPOS_Kernel

#endif
