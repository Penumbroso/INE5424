#include <mmu.h>
#include <task.h>

__BEGIN_SYS

void Task::init() {
    db<Task>(TRC) << "Task::init()" << endl;

    System_Info<Machine> * si = System::info();

    Task::_main_task = new (SYSTEM) Task (
            new (SYSTEM) Address_Space(MMU::current()),
            new (SYSTEM) Segment(Log_Addr(si->lm.app_code), si->lm.app_code_size),
            new (SYSTEM) Segment(Log_Addr(si->lm.app_data), si->lm.app_data_size),
            Log_Addr(Memory_Map<Machine>::APP_CODE),
            Log_Addr(Memory_Map<Machine>::APP_DATA)
        );
}

__END_SYS
