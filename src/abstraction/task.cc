// EPOS Task Abstraction Implementation

#include <task_kernel.h>

__BEGIN_SYS

// Class attributes
Task * Task::_master;

// Constructor/destructor
Task::Task(const Segment* c, const Segment* d )
    : _as(new (SYSTEM) Address_Space)
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

__END_SYS
