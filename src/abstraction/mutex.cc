// EPOS Mutex Abstraction Implementation

#include <mutex_kernel.h>

namespace EPOS_Kernel {

Mutex::Mutex(): _locked(false)
{
    db<Synchronizer>(TRC) << "Mutex() => " << this << endl;
}


Mutex::~Mutex()
{
    db<Synchronizer>(TRC) << "~Mutex(this=" << this << ")" << endl;
}


void Mutex::lock()
{
    db<Synchronizer>(TRC) << "Mutex::lock(this=" << this << ")" << endl;

    begin_atomic();
    if(tsl(_locked))
        sleep(); // implicit end_atomic()
    else
        end_atomic();
}


void Mutex::unlock()
{
    db<Synchronizer>(TRC) << "Mutex::unlock(this=" << this << ")" << endl;

    begin_atomic();
    _locked = false;
    wakeup(); // implicit end_atomic()
}

} // namespace EPOS_Kernel
