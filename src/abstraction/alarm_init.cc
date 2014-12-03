// EPOS Alarm Abstraction Initialization

#include <system.h>
#include <alarm_kernel.h>

namespace EPOS_Kernel {

void Alarm::init()
{
    db<Init, Alarm>(TRC) << "Alarm::init()" << endl;

    _timer = new (SYSTEM) Alarm_Timer(handler);
}

} // namespace EPOS_Kernel
