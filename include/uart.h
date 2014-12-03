// EPOS UART Mediator Common Package

#ifndef __uart_h
#define __uart_h

#include <system/config.h>

namespace EPOS_Kernel {

class UART_Common
{
protected:
    UART_Common() {}

public:
    // Parity
    enum {
        NONE = 0,
        ODD = 1,
        EVEN = 2
    };
};

} // namespace EPOS_Kernel

#ifdef __UART_H
#include __UART_H
#endif

#endif
