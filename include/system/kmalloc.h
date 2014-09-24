// EPOS System-level Dynamic Memory Declarations

#ifndef __kmalloc_h
#define __kmalloc_h

#include <system.h>

__BEGIN_SYS

inline void * kmalloc(size_t bytes) {
    return System::_heap->alloc(bytes);
}

inline void kfree(void * ptr) {
    System::_heap->free(ptr);
}

template< typename T, typename ... Ts >
T * knew( Ts&&...ts ) {
    return new( kmalloc(sizeof(T)) ) T( ts... );
}

__END_SYS

#endif
