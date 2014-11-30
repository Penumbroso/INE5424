// EPOS First Thread Initializer

#include <utility/heap.h>
#include <mmu.h>
#include <thread_kernel.h>

namespace EPOS_Kernel {

class Init_First
{
public:
    Init_First() {

        db<Init>(TRC) << "Init_First()" << endl;

        // Initialize the Thread abstraction,
        // thus creating the first application thread
        db<Init>(INF) << "INIT ends here!" << endl;
        if(Traits<Thread>::enabled)
            Thread::init();
    }
};

// Global object "init_first" must be constructed last in the context of the
// OS, for it activates the first application thread (usually main()) 
Init_First init_first;

} // namespace EPOS_Kernel
