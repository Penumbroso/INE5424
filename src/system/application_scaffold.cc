// EPOS Application Scaffold and Application Abstraction Implementation

#include <utility/ostream.h>
#include <application.h>
#include <system/framework.h>

extern "C" { void user_display_puts(const char * s); }
extern "C" { void _exec(void * msg); }

extern "C" {
    void _panic() {
        _API::Thread::exit(-1); // Could be replaced by a throw, since exceptions should not be a problem for user space
    }

    void _exit(int s) {
        _API::Thread::exit(s); //for(;;);
    }

    void _print(const char * s) {
        user_display_puts(s);
    }

    int _syscall(void * m) {
        int ret = 0;
        ASM("int $49; \n");
        return ret;

    }
}

__BEGIN_SYS

// Application class attributes
System_Info<Machine> * System::_si = reinterpret_cast<System_Info<Machine> *>(Memory_Map<Machine>::SYS_INFO);
char Application::_preheap[];
Heap * Application::_heap;

OStream kerr;

__END_SYS

__BEGIN_API

// Global objects
OStream cout;
OStream cerr;

__END_API
