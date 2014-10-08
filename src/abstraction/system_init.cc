// EPOS System Abstraction Initialization

#include <system.h>
#include <alarm.h>
#include <address_space.h>

__BEGIN_SYS

void System::init()
{
    if(Traits<Alarm>::enabled)
        Alarm::init();

    if(Traits<Address_Space>::enabled)
        Address_Space::init();
}

__END_SYS
