// C malloc function
#include <new>
#include <utility/string.h>

extern "C"
{
    using namespace EPOS;

    // Standard C Library allocators
    inline void * malloc(size_t bytes) {
        return operator new(bytes);
    }

    inline void * calloc(size_t n, unsigned int bytes) {
        void * ptr = malloc(n * bytes);
        memset(ptr, 0, n * bytes);
        return ptr;
    }

    inline void free(void * ptr) {
        operator delete(ptr);
    }
}
