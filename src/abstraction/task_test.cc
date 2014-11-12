// EPOS EPOS::Task Test Program

#include <utility/ostream_kernel.h>
#include <alarm.h>
#include <thread.h>
#include <task.h>

using namespace EPOS_Kernel;

const int iterations = 10;

int func_a(void);
int func_b(void);

EPOS::Thread * a;
EPOS::Thread * b;
EPOS::Thread * m;

OStream cout;

int main()
{
    cout << "EPOS::Task test\n";

    m = EPOS::Thread::self();

    cout << "I'll try to clone myself:\n";

    const EPOS::Task * task0 = EPOS::Task::self();
    Address_Space * as0 = task0->address_space();
    cout << "My address space's page directory is located at " << as0 << "\n";

    const Segment * cs0 = task0->code_segment();
    CPU::Log_Addr code0 = task0->code();
    cout << "My code segment is located at "
         << static_cast<void *>(code0)
         << " and it is " << cs0->size() << " bytes long" << "\n";

    const Segment * ds0 = task0->data_segment();
    CPU::Log_Addr data0 = task0->data();
    cout << "My data segment is located at "
         << static_cast<void *>(data0)
         << " and it is " << ds0->size() << " bytes long" << "\n";

    cout << "Creating and attaching segments:\n";
    Segment cs1(cs0->size());
    CPU::Log_Addr code1 = as0->attach(cs1);
    cout << "  code => " << code1 << " done!" << endl;
    Segment ds1(ds0->size());
    CPU::Log_Addr data1 = as0->attach(ds1);
    cout << "  data => " << data1 << " done!" << endl;

    cout << "Copying segments:";
    memcpy(code1, code0, cs1.size());
    cout << " code => done!" << endl;
    memcpy(data1, data0, ds1.size());
    cout << " data => done!" << endl;

    cout << "Detaching segments:";
    as0->detach(cs1);
    as0->detach(ds1);
    cout << " done!" << endl;

    EPOS::Task * task1 = new (SYSTEM) EPOS::Task(cs1, ds1);
    a = new (SYSTEM) EPOS::Thread(*task1, &func_a);
    b = new (SYSTEM) EPOS::Thread(&func_b);

    m->suspend();

    cout << "Both threads are now done and have suspended themselves. I'll now wait for 1 second and then wake them up so they can exit ...\n";

    EPOS::Alarm::delay(1000000);

    a->resume();
    b->resume();

    int status_a = a->join();
    int status_b = b->join();

    cout << "EPOS::Thread A exited with status " << status_a 
         << " and thread B exited with status " << status_b << "\n";

    delete a;
    delete b;
    delete task1;

    cout << "I'm also done, bye!" << endl;

    return 0;
}

int func_a(void)
{
    for(int i = iterations; i > 0; i--) {
        for(int i = 0; i < 79; i++)
            cout << "a";
        cout << "\n";
        EPOS::Thread::yield();
    }

    EPOS::Thread::self()->suspend();

    return 'A';   
}

int func_b(void)
{
    for(int i = iterations; i > 0; i--) {
        for(int i = 0; i < 79; i++)
            cout << "b";
        cout << "\n";
        EPOS::Thread::yield();
    }

    m->resume();

    EPOS::Thread::self()->suspend();

    return 'B';   
}
