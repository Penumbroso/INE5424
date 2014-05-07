// EPOS Thread Abstraction Initialization

#include <system/kmalloc.h>
#include <system.h>
#include <thread.h>
#include <alarm.h>

__BEGIN_SYS

void Thread::init()
{
    int (* entry)() = reinterpret_cast<int (*)()>(System::info()->lmm.app_entry);

    db<Init, Thread>(TRC) << "Thread::init(entry=" << (void *) entry << ")" << endl;

    // Create the application's main thread
    // This must precede idle, thus avoiding implicit rescheduling
    // For preemptive scheduling, reschedule() is called, but it will preserve MAIN as the RUNNING thread
    _running = new (kmalloc(sizeof(Thread))) Thread(entry, RUNNING, MAIN);
    new (kmalloc(sizeof(Thread))) Thread(&idle, READY, IDLE);

    if(preemptive)
        _timer = new (kmalloc(sizeof(Scheduler_Timer))) Scheduler_Timer(QUANTUM, reschedule);

    db<Init, Thread>(INF) << "Dispatching the first thread: " << _running << endl;

    This_Thread::not_booting();

    _running->_context->load();
}

__END_SYS
