// EPOS Alarm Abstraction Implementation

#include <semaphore.h>
#include <alarm.h>
#include <display.h>

__BEGIN_SYS

// Class attributes
Alarm_Timer * Alarm::_timer;
volatile Alarm::Tick Alarm::_elapsed;
Alarm::Queue Alarm::_request;


// Methods
Alarm::~Alarm()
{
    lock();

    db<Alarm>(TRC) << "~Alarm(this=" << this << ")" << endl;

    _request.remove(this);

    unlock();

    delete _handler;
}

namespace detail {
    struct lambda0 {
        Thread * target;
        void operator ()(){
            target->resume();
        }
    };
}

// Class methods
void Alarm::delay(const Microsecond & time)
{
    db<Alarm>(TRC) << "Alarm::delay(time=" << time << ")" << endl;
    detail::lambda0 awaker;
    awaker.target = Thread::self();
    Alarm resumer( time, awaker );
    Thread::self()->suspend();
}


void Alarm::handler()
{
    static Tick next_tick;
    static Handler * next_handler;

    lock();

    _elapsed++;

    if(Traits<Alarm>::visible) {
        Display display;
        int lin, col;
        display.position(&lin, &col);
        display.position(0, 79);
        display.putc(_elapsed);
        display.position(lin, col);
    }

    if(next_tick)
        next_tick--;
    if(!next_tick) {
        if(next_handler) {
            db<Alarm>(TRC) << "Alarm::handler(h=" << next_handler << ")" << endl;
            (*next_handler)();
        }
        if(_request.empty())
            next_handler = 0;
        else {
            Queue::Element * e = _request.remove();
            Alarm * alarm = e->object();
            next_tick = alarm->_ticks;
            next_handler = alarm->_handler;
            if(alarm->_times != -1)
                alarm->_times--;
            if(alarm->_times) {
                e->rank(alarm->_ticks);
                _request.insert(e);
            }
        }
    }

    unlock();
}

__END_SYS
