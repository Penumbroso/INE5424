// EPOS System Initializer

#include <machine.h>
#include <system.h>

extern "C" { void __epos_library_app_entry(void); }

__BEGIN_SYS

Heap * const SYSTEM = 0;

class Init_System
{
public:
    Init_System() {
        db<Init>(TRC) << "Init_System()" << endl;

        // Initialize the processor
        db<Init>(INF) << "Initializing the CPU: " << endl;
        CPU::init();
        db<Init>(INF) << "done!" << endl;

        // Initialize System's heap
        db<Init>(INF) << "Initializing system's heap: " << endl;
        System::_heap = new (&System::_preheap[0]) Heap(MMU::alloc(MMU::pages(Traits<System>::HEAP_SIZE)),
                                                        Traits<System>::HEAP_SIZE);
        const_cast<Heap*&>(SYSTEM) = System::_heap;
        db<Init>(INF) << "done!" << endl;

        // Initialize the machine
        db<Init>(INF) << "Initializing the machine: " << endl;
        Machine::init();
        db<Init>(INF) << "done!" << endl;

        // Initialize system abstractions
        db<Init>(INF) << "Initializing system abstractions: " << endl;
        System::init();
        db<Init>(INF) << "done!" << endl;

        // Initialization continues at init_first
    }
    static Heap * const _heap;
};

// Global object "init_system" must be constructed first.
Init_System init_system;

__END_SYS
