// EPOS Scratchpad Memory Mediator Declarations

#ifndef __scratchpad_h
#define __scratchpad_h

#include <utility/heap.h>
#include <segment.h>

namespace EPOS_Kernel {

class Scratchpad_Common
{
    friend void * ::operator new(size_t, const EPOS_Kernel::Scratchpad_Allocator &);
    friend void * ::operator new[](size_t, const EPOS_Kernel::Scratchpad_Allocator &);

public:
    static void * alloc(unsigned int bytes) { return _heap->alloc(bytes); }

protected:
    static Segment * _segment;
    static Heap * _heap;
};

} // namespace EPOS_Kernel

#ifdef __SCRATCHPAD_H
#include __SCRATCHPAD_H

inline void * operator new(size_t bytes, const EPOS_Kernel::Scratchpad_Allocator & allocator) {
    return EPOS_Kernel::Scratchpad::_heap->alloc(bytes);
}

inline void * operator new[](size_t bytes, const EPOS_Kernel::Scratchpad_Allocator & allocator) {
    return EPOS_Kernel::Scratchpad::_heap->alloc(bytes);
}

#endif

#endif
