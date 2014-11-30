// EPOS Run-Time System Information

#ifndef __info_h
#define __info_h

#include <system/config.h>

namespace EPOS_Kernel {

template <class Machine>
struct System_Info {};

} // namespace EPOS_Kernel

#include __HEADER_MACH(info)

#endif
