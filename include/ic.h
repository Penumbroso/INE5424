// EPOS IC Mediator Common Package

#ifndef __ic_h
#define __ic_h

#include <system/config.h>

namespace EPOS_Kernel {

class IC_Common
{
protected:
    IC_Common() {}

public:
    typedef unsigned int Interrupt_Id;
    typedef void (* Interrupt_Handler)(const Interrupt_Id &);
};

} // namespace EPOS_Kernel

#ifdef __IC_H
#include __IC_H
#endif

#endif
