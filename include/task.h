// EPOS Task Abstraction Declarations

#include <thread.h>

#ifndef __task_h
#define __task_h

#include <utility/malloc.h>
#include <address_space.h>
#include <segment.h>


__BEGIN_SYS
class Task
{
    // Type used in public methods
    typedef CPU::Log_Addr Log_Addr;

public:
    /* Constructs a task with the given code and data segments. */
    Task(const Segment & cs, const Segment & ds);
    ~Task();

    // Getters
          Address_Space * address_space() const { return _as;   }
    const Segment *       code_segment()  const { return _cs;   }
    const Segment *       data_segment()  const { return _ds;   }
          Log_Addr        code()          const { return _code; }
          Log_Addr        data()          const { return _data; }

    // Class methods
    static const Task * self() { return multitask ? Thread::self()->task() : _master; }
    static void init();

protected:
    // Constructor used in initialization
    Task(Address_Space * as, const Segment * cs, const Segment * ds, Log_Addr code, Log_Addr data)
    : _as(as), _cs(cs), _ds(ds), _code(code), _data(data) {}

private:
    friend class System;
    friend class Thread;

    // Type definitions (rememder Log_Addr is already defined)
    typedef CPU::Phy_Addr Phy_Addr;
    typedef CPU::Context Context;
    typedef class Queue<Thread> Queue;

    // Instance atributes
    Address_Space * _as; // Address Space
    const Segment * _cs; // Code Segment
    const Segment * _ds; // Data Segment
    Log_Addr _code; // Address of the code segment
    Log_Addr _data; // Address of the data segment
    Queue _threads;

    // Class attribute
    static Task * _master;

    // Traits alias
    static const bool multitask = Traits<System>::multitask;

    // Private instance method
    void activate() const { _as->activate(); }
};

__END_SYS

#endif
