// EPOS Memory Map

#ifndef __memory_map_h
#define __memory_map_h

#include <system/config.h>

namespace EPOS_Kernel {

template <class Machine>
struct Memory_Map {};

template <class Machine>
struct IO_Map {};

} // namespace EPOS_Kernel

#include __HEADER_MACH(memory_map)

#endif
