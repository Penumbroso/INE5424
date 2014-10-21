// EPOS Task Test Program

#include <utility/ostream.h>
#include <alarm.h>
#include <thread.h>
#include <task.h>

using namespace EPOS;

const int iterations = 10;

#define REALLY_TO_STRING( str ) #str
#define TO_STRING( str ) REALLY_TO_STRING(str)
#define __LINE_STR__ "(line " TO_STRING(__LINE__) ")"

int func_a(void);
int func_b(void);

Thread * a;
Thread * b;
Thread * m;

OStream cout;

int main()
{
    cout << "Task test\n";

    m = Thread::self();

    cout << "I'll try to clone myself:\n";

    Task * task0 = Task::self();
    Address_Space * as0 = task0->address_space();
    cout << "My address space's page directory is located at " << as0 << " " __LINE_STR__ "\n";

    const Segment * cs0 = &task0->code_segment();
    CPU::Log_Addr code0 = cs0;
    cout << "My code segment is located at "
         << static_cast<void *>(code0)
         << " and it is " << cs0->size() << " bytes long " __LINE_STR__ "\n";

    const Segment * ds0 = &task0->data_segment();
    CPU::Log_Addr data0 = ds0;
    cout << "My data segment is located at "
         << static_cast<void *>(data0)
         << " and it is " << ds0->size() << " bytes long " __LINE_STR__ "\n";

    cout << "Creating and attaching segments: " __LINE_STR__ "\n";
    Segment cs1(cs0->size());
    CPU::Log_Addr code1 = as0->attach(cs1);
    cout << "  code => " << code1 << " done! " __LINE_STR__ << endl;
    Segment ds1(ds0->size());
    CPU::Log_Addr data1 = as0->attach(ds1);
    cout << "  data => " << data1 << " done! " __LINE_STR__  << endl;

    cout << "Copying segments: " __LINE_STR__ ;
    memcpy(code1, code0, cs1.size());
    cout << " code => done! " __LINE_STR__  << endl;
    memcpy(data1, data0, ds1.size());
    cout << " data => done! " __LINE_STR__  << endl;

    cout << "Detaching segments: " __LINE_STR__ ;
    as0->detach(cs1);
    as0->detach(ds1);
    cout << " done! " __LINE_STR__  << endl;

    Task * task1 = new (SYSTEM) Task(cs1, ds1);
    a = task1->create_thread(&func_a);
    b = new (SYSTEM) Thread(&func_b);

    m->suspend();

    cout << "Both threads are now done and have suspended themselves. I'll now wait for 1 second and then wake them up so they can exit ... " __LINE_STR__ "\n";

    Alarm::delay(1000000);

    a->resume();
    b->resume();

    int status_a = a->join();
    int status_b = b->join();

    cout << "Thread A exited with status " << status_a 
         << " and thread B exited with status " << status_b << " " __LINE_STR__ "\n";

    delete a;
    delete b;
    delete task1;

    cout << "I'm also done, bye! " __LINE_STR__ << endl;

    return 0;
}

int func_a(void)
{
    for(int i = iterations; i > 0; i--) {
        for(int i = 0; i < 79; i++)
            cout << "a";
        cout << " " __LINE_STR__ "\n";
        Thread::yield();
    }

    Thread::self()->suspend();

    return 'A';   
}

int func_b(void)
{
    for(int i = iterations; i > 0; i--) {
        for(int i = 0; i < 79; i++)
            cout << "b";
        cout << " " __LINE_STR__ "\n";
        Thread::yield();
    }

    m->resume();

    Thread::self()->suspend();

    return 'B';   
}
