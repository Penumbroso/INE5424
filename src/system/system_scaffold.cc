// EPOS System Scaffold and System Abstraction Implementation

#include <utility/ostream.h>
#include <utility/heap.h>
#include <machine.h>
#include <display.h>
#include <system.h>
#include <thread.h>
#include <system/agent.h>

// LIBC Heritage
extern "C" {
    void _panic() {
        _SYS::Machine::panic();
    }

    void _exit(int s) {
        _SYS::Thread::exit(s);
    }

    void _exec(_SYS::Message * msg) {
        _SYS::db<_SYS::Framework>(_SYS::TRC) << ":=>(" << *msg << ")" << _SYS::endl;

        switch(msg->id().type()) {
        case _SYS::THREAD_ID: _SYS::Agent<_SYS::Thread>::act(msg); break;
        case _SYS::TASK_ID: _SYS::Agent<_SYS::Task>::act(msg); break;
        case _SYS::ADDRESS_SPACE_ID: _SYS::Agent<_SYS::Address_Space>::act(msg); break;
        case _SYS::SEGMENT_ID: _SYS::Agent<_SYS::Segment>::act(msg); break;
        case _SYS::DISPLAY_ID: _SYS::Agent<_SYS::Display>::act(msg); break;
        default: msg->reply(_SYS::Result(-1));
        }

        _SYS::db<_SYS::Framework>(_SYS::TRC) << "   (" << *msg << ") <=:" << _SYS::endl;
    }

    void _print(const char * s) {
        _SYS::Display::puts(s);
    }

    void __cxa_pure_virtual() {
        _SYS::db<void>(_SYS::ERR) << "Pure Virtual method called!" << _SYS::endl;
    }
}

__BEGIN_SYS

// This class purpose is simply to define a well-known entry point for
// the system. It must be declared as the first global object in
// system_scaffold.cc
class First_Object
{
public:
    First_Object() {
	Display::init();
    }
};

// Global objects
// These objects might be reconstructed several times in SMP configurations,
// so their constructors must be stateless!
First_Object __entry;
OStream kout;
OStream kerr;

// System class attributes
System_Info<Machine> * System::_si = reinterpret_cast<System_Info<Machine> *>(Memory_Map<Machine>::SYS_INFO);
char System::_preheap[];
Segment * System::_heap_segment;
Heap * System::_heap;

__END_SYS
