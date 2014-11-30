// EPOS System Abstraction Initialization

#include <system.h>
#include <alarm_kernel.h>
#include <task_kernel.h>

namespace EPOS_Kernel {

void System::init()
{
    if(Traits<Alarm>::enabled)
        Alarm::init();

    if(Traits<Task>::enabled)
        Task::init();
}

} // namespace EPOS_Kernel
