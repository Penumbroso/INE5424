// EPOS Task Abstraction Declarations

#ifndef __task_h
#define __task_h

#include <utility/malloc.h>
#include <address_space.h>
#include <segment.h>
#include <thread.h>

__BEGIN_SYS

class Task {
public:
    // Public type definitions
    typedef CPU::Log_Addr Log_Addr;


    // Constructor/destructor

    /* Constructs a task with the given code and data segments. */
    Task(const Segment & code, const Segment & data);
    ~Task();

    // Getters
    const Address_Space * address_space() const { return _as;   }
          Address_Space * address_space()       { return _as;   }
    const Segment       * code_segment()  const { return _code_segment; }
    const Segment       * data_segment()  const { return _data_segment; }
          Log_Addr        code()                { return _code_address; }
          Log_Addr        data()                { return _data_address; }

    // Instance methods
    Thread * create_thread(int (* entry)(), 
        const Thread::State & state = Thread::READY,
        const Thread::Criterion & criterion = Thread::NORMAL,
        unsigned int stack_size = STACK_SIZE);

    void destroy_thread(Thread * t);

    // Class methods
    static Task * volatile self() { return _running; }

    static void init();

private:
    // Type definitions
    typedef CPU::Context Context;
    typedef class Queue<Thread> Queue;

    // Constant definitions
    static const unsigned int STACK_SIZE = Traits<Application>::STACK_SIZE;

    // Instance atributes
    Address_Space * _as;
    const Segment * _code_segment;
    const Segment * _data_segment;
    Log_Addr _code_address;
    Log_Addr _data_address; // These will contain the address of the segments
    Queue _threads;

    // Class attributes
    static Task * volatile _running;

    // Constructor used in initialization
    Task(Address_Space *, const Segment *, const Segment *, Log_Addr, Log_Addr);
};

__END_SYS

#endif
