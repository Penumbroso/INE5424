// join_test2.cc
#include <thread.h>
#include <utility/ostream.h>
#include <mutex.h>
#include <alarm.h>

#define SECS 1000000


Mutex table;
OStream cout;

void t_wake() {
    cout << "Resuming...\n";
    Thread::self()->resume();
    cout << "Resumed.\n";
}

int main (int argc, char *argv[])
{
    cout << "Creating alarm\n";
/*    Alarm resume_thread(1*SECS, t_wake);
    cout << "suspend()\n";*/
    Thread::self()->suspend();
    cout << "Continue\n";

    return 0;
}
