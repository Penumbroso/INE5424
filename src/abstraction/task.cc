#include <task.h>
#include <system.h>

__BEGIN_SYS

Task * volatile Task::_running;


// Constructor/destructor
Task::Task(Address_Space * as, const Segment * cs, const Segment * ds, Log_Addr ca, Log_Addr da):
    _as(as),
    _code_segment(cs),
    _data_segment(ds),
    _code_address(ca),
    _data_address(da)
{}

Task::Task(const Segment& c, const Segment& d )
    : _as(new(SYSTEM) Address_Space)
    , _code_segment(&c)
    , _data_segment(&d)
    , _code_address(_as->attach(c))
    , _data_address(_as->attach(d))
{
    db<Task>(TRC) << "Task()\n";
}

Task::~Task() {
    db<Task>(TRC) << "~Task()\n";
    while(!_threads.empty())
        delete _threads.remove()->object();
}

Thread * Task::create_thread(int (* entry)(), 
    const Thread::State & state,
    const Thread::Criterion & criterion,
    unsigned int stack_size)
{
    _as->activate();
    Thread * t = new (SYSTEM) Thread(entry, state, criterion);
    Queue::Element * e = new (SYSTEM) Queue::Element(t);
    _threads.insert(e);
    return t;
}

void Task::destroy_thread(Thread * t) {
    Queue::Element * e = _threads.remove(t);
    if(e)
        delete e->object();
}

__END_SYS
