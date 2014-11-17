// EPOS Task Abstraction Implementation

#include <task_kernel.h>
#include <task.h>

namespace EPOS {
    Task * Task::aux = 0;
}

namespace EPOS_Kernel {

// Class attributes
Task * Task::_master;

// Constructor/destructor
Task::Task(const Segment* c, const Segment* d )
    : _stub(0)
    , _as(new (SYSTEM) Address_Space)
    , _cs(c)
    , _ds(d)
    , _code(_as->attach(*c))
    , _data(_as->attach(*d))
{
    db<Task>(TRC) << "Task(cs=" << _cs << ",ds=" << _ds << ") => " << this << endl;
}

Task::~Task()
{
    db<Task>(TRC) << "~Task(this=" << this << ")" << endl;

    while(!_threads.empty())
        delete _threads.remove()->object();
}

EPOS::Task * Task::stub( EPOS::Task ** ptr_stub ) {
    if( _stub == 0 ) {
        _stub = *ptr_stub;
        *ptr_stub = 0;
    }
    return _stub;
}

} // namespace EPOS_Kernel
