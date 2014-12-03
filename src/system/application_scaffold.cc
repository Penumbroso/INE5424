// EPOS Application Scaffold and Application Abstraction Implementation

#include <utility/ostream_kernel.h>
#include <application.h>

__BEGIN_SYS

// Global objects
OStream cout;
OStream cerr;

// Application class attributes
System_Info<Machine> * System::_si = reinterpret_cast<System_Info<Machine> *>(Memory_Map<Machine>::SYS_INFO);
char Application::_preheap[];
Heap * Application::_heap;

__END_SYS
