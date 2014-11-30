// EPOS Compile-time Type Management System

typedef __SIZE_TYPE__ size_t;

#ifndef __types_h
#define __types_h

inline void * operator new(size_t s, void * a) { return a; }
inline void * operator new[](size_t s, void * a) { return a; }

__OPEN_UTILITY_NS

// Utilities
class Debug;
class Lists;
class Spin;
class Heap;

__CLOSE_UTILITY_NS

__OPEN_SYSTEM_NS

// System parts
class Build;
class Boot;
class Setup;
class Init;
class Init_First;
class Init_System;
class Init_Application;
class Framework;

__CLOSE_SYSTEM_NS

__OPEN_ARCHITECTURE_NS

// Dummy class for incomplete architectures and machines
template<int>
class Dummy;

// Hardware Mediators - CPU
class IA32;

// Hardware Mediators - Time-Stamp Counter
class IA32_TSC;

// Hardware Mediators - Memory Management Unit
class IA32_MMU;

// Hardware Mediators - Performance Monitoring Unit
class IA32_PMU;

__CLOSE_ARCHITECTURE_NS

__OPEN_MACHINE_NS

// Hardware Mediators - Machine
class PC;

// Hardware Mediators - Bus
class PC_PCI;

// Hardware Mediators - Interrupt Controller
class PC_IC;

// Hardware Mediators - Timer
class PC_Timer;

// Hardware Mediators - Real-time Clock
class PC_RTC;

// Hardware Mediators - EEPROM
class PC_EEPROM;

// Hardware Mediators - Scratchpad
class PC_Scratchpad;

// Hardware Mediators - UART
class PC_UART;

// Hardware Mediators - Display
class Serial_Display;
class PC_Display;

// Hardware Mediators - NIC
class PC_Ethernet;
class PCNet32;
class C905;
class E100;

__CLOSE_MACHINE_NS

__OPEN_ABSTRACTION_NS

// Abstractions - Domains
class System;
class Application;

// Abstractions	- Process Management
class Task;
class Thread;
class Active;
class Periodic_Thread;
class RT_Thread;

// Abstractions - Scheduling
template <typename> class Scheduler;

// Abstractions	- Memory Management
class Segment;
class Address_Space;

// Abstractions	- Synchronization
class Synchronizer;
class Mutex;
class Semaphore;
class Condition;

// Abstractions	- Timing
class Clock;
class Chronometer;
class Alarm;
class Delay;

// Abstractions - Communication
class Ethernet;

__CLOSE_ABSTRACTION_NS

__OPEN_SYSTEM_NS

namespace Scheduling_Criteria
{
    class Priority;
    class FCFS;
    class RR;
    class RM;
    class DM;
    class EDF;
    class CPU_Affinity;
    class GEDF;
    class PEDF;
    class CEDF;
};

__CLOSE_SYSTEM_NS

#ifndef __FRAMEWORK

#include <task.h>
#include <thread.h>
#include <address_space.h>
#include <segment.h>
#include <mutex.h>
#include <semaphore.h>
#include <condition.h>
#include <alarm.h>

#include <system/handle.h>

__OPEN_SYSTEM_NS

typedef Handle::<Core::Task> Task;
typedef Handle::<Core::Thread> Thread;
typedef Handle::<Core::Address_Space> Address_Space;
typedef Handle::<Core::Segment> Segment;
typedef Handle::<Core::Mutex> Mutex;
typedef Handle::<Core::Semaphore> Semaphore;
typedef Handle::<Core::Condition> Condition;
typedef Handle::<Core::Alarm> Alarm;
typedef Handle::<Core::Delay> Delay;

__CLOSE_SYSTEM_NS

#else

__OPEN_SYSTEM_NS

typedef Core::System System;
typedef Core::Application Application;

typedef Core::Task Task;
typedef Core::Thread Thread;
typedef Core::Active Active;
typedef Core::Periodic_Thread Periodic_Thread;
typedef Core::RT_Thread RT_Thread;

typedef Core::Address_Space Address_Space;
typedef Core::Segment Segment;

typedef Core::Synchronizer Synchronizer;
typedef Core::Mutex Mutex;
typedef Core::Semaphore Semaphore;
typedef Core::Condition Condition;

typedef Core::Clock Clock;
typedef Core::Chronometer Chronometer;
typedef Core::Alarm Alarm;
typedef Core::Delay Delay;

__CLOSE_SYSTEM_NS

#endif

__OPEN_SYSTEM_NS

// System Components IDs
// The order in this enumeration defines many things in the system (e.g. init)
typedef unsigned int Type_Id;
enum
{
    CPU_ID = 0,
    TSC_ID,
    MMU_ID,

    MACHINE_ID = 10,
    PCI_ID,
    IC_ID,
    TIMER_ID,
    RTC_ID,
    EEPROM_ID,
    SCRATCHPAD_ID,
    UART_ID,
    DISPLAY_ID,

    THREAD_ID = 20,
    TASK_ID,
    ACTIVE_ID,

    ADDRESS_SPACE_ID,
    SEGMENT_ID,

    MUTEX_ID,
    SEMAPHORE_ID,
    CONDITION_ID,

    CLOCK_ID,
    ALARM_ID,
    CHRONOMETER_ID,

    UNKNOWN_TYPE_ID,
    LAST_TYPE_ID = UNKNOWN_TYPE_ID - 1
};

// Type IDs for system components
template<typename T> struct Type { static const Type_Id ID = UNKNOWN_TYPE_ID; };

template<> struct Type<IA32> { static const Type_Id ID = CPU_ID; };
template<> struct Type<IA32_TSC> { static const Type_Id ID = TSC_ID; };
template<> struct Type<IA32_MMU> { static const Type_Id ID = MMU_ID; };

template<> struct Type<PC> { static const Type_Id ID = MACHINE_ID; };
template<> struct Type<PC_IC> { static const Type_Id ID = IC_ID; };
template<> struct Type<PC_Timer> { static const Type_Id ID = TIMER_ID; };
template<> struct Type<PC_UART> { static const Type_Id ID = UART_ID; };
template<> struct Type<PC_RTC> { static const Type_Id ID = RTC_ID; };
template<> struct Type<PC_PCI> { static const Type_Id ID = PCI_ID; };
template<> struct Type<PC_Display> { static const Type_Id ID = DISPLAY_ID; };

template<> struct Type<Thread> { static const Type_Id ID = THREAD_ID; };
template<> struct Type<Task> { static const Type_Id ID = TASK_ID; };
template<> struct Type<Address_Space> { static const Type_Id ID = ADDRESS_SPACE_ID; };
template<> struct Type<Segment> { static const Type_Id ID = SEGMENT_ID; };

__CLOSE_SYSTEM_NS

#endif
