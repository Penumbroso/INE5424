// EPOS Global Application Abstraction Declarations

#ifndef __application_h
#define __application_h

#include <utility/heap.h>
#include <segment.h>

extern "C"
{
    void * malloc(size_t);
    void free(void *);
}

namespace EPOS_Kernel {

class Application
{
    friend class Init_Application;
    friend void * ::malloc(size_t);
    friend void ::free(void *);

private:
    static void init();

private:
    static char _preheap[sizeof(Heap)];
    static Heap * _heap;
};

} // namespace EPOS_Kernel

#include <utility/malloc.h>

#endif
