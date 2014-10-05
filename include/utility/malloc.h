// EPOS Application-level Dynamic Memory Utility Declarations

#ifndef __malloc_h
#define __malloc_h

#include <utility/string.h>
#include <application.h>

extern "C"
{
    using namespace EPOS;

    // Standard C Library allocators
    inline void * malloc(size_t bytes) {
	return Application::_heap->alloc(bytes);
    }

    inline void * calloc(size_t n, unsigned int bytes) {
        void * ptr = malloc(n * bytes);
        memset(ptr, 0, n * bytes);
        return ptr;
    }

    inline void free(void * ptr) {
        Application::_heap->free(ptr);
    }
}

// C++ dynamic memory allocators and deallocators
/*inline void * operator new(size_t bytes) {
    void * ptr = malloc(bytes);
    db<Application>(TRC) << "operator new(bytes=" << bytes << ") => " << ptr << "\n";
    return ptr;
}

inline void * operator new[](size_t bytes) {
    void * ptr = malloc(bytes);
    db<Application>(TRC) << "operator new[](bytes=" << bytes << ") => " << ptr << "\n";
    return ptr;
}

inline void operator delete(void * ptr) {
    db<Application>(TRC) << "operator delete(ptr=" << ptr << ")\n";
    free(ptr);
}
inline void operator delete[](void * ptr) {
    db<Application>(TRC) << "operator delete(ptr=" << ptr << ")\n";
    free(ptr);
}*/

inline void * operator new(size_t bytes, Heap * heap) {
    db<Application>(TRC) << "operator new(bytes=" << bytes << ",heap=" <<
            static_cast<void*>(heap) << ") => \n";

    void * ptr = heap->alloc(bytes + sizeof(Heap*));
    *static_cast<Heap**>(ptr) = heap;
    ptr = static_cast<void*>(static_cast<char*>(ptr) + sizeof(Heap*));

    db<Application>(TRC) << " => " << ptr << "\n";

    return ptr;
}

inline void * operator new[](size_t bytes, Heap * heap) {
    db<Application>(TRC) << "operator new(bytes=" << bytes << ",heap=" <<
            static_cast<void*>(heap) << ") => \n";

    void * ptr = heap->alloc(bytes + sizeof(Heap*));
    *static_cast<Heap**>(ptr) = heap;
    ptr = static_cast<void*>(static_cast<char*>(ptr) + sizeof(Heap*));

    db<Application>(TRC) << " => " << ptr << "\n";

    return ptr;
}

inline void * operator new(size_t bytes) {
    db<Application>(TRC) << "operator new(bytes=" << bytes << ") => \n";
    void * ptr = operator new(bytes, APPLICATION);
    db<Application>(TRC) << " => " << ptr << "\n";
    return ptr;
}

inline void * operator new[](size_t bytes) {
    db<Application>(TRC) << "operator new[](bytes=" << bytes << ") => \n";
    void * ptr = operator new[](bytes, APPLICATION);
    db<Application>(TRC) << " => " << ptr << "\n";
    return ptr;
}

// C++ dynamic memory deallocators
inline void operator delete(void * object) {
    db<Application>(TRC) << "operator delete(ptr=" << object << ")\n";
    object = static_cast<void*>(static_cast<char*>(object) - sizeof(Heap*));
    Heap * heap = *static_cast<Heap**>(object);
    heap->free(object);
}

inline void operator delete[](void * object) {
    db<Application>(TRC) << "operator delete(ptr=" << object << ")\n";
    object = static_cast<void*>(static_cast<char*>(object) - sizeof(Heap*));
    Heap * heap = *static_cast<Heap**>(object);
    heap->free(object);
}

#endif
