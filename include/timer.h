// EPOS Timer Mediator Common Package

#ifndef __timer_h
#define __timer_h

#include <tsc.h>

namespace EPOS_Kernel {

class Timer_Common
{
protected:
    Timer_Common() {}

public:
    typedef TSC::Hertz Hertz;
    typedef TSC::Hertz Tick;
    typedef void (Handler)();
    typedef unsigned int Channel;
};

} // namespace EPOS_Kernel

#ifdef __TIMER_H
#include __TIMER_H
#endif

#endif
