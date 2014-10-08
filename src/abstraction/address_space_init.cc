// EPOS Address_Space Abstraction Initialization

#include <system.h>
#include <address_space.h>

__BEGIN_SYS

void Address_Space::init()
{
    db<Init, Address_Space>(TRC) << "Address_Space::init()" << endl;

    _master = new (SYSTEM) Address_Space(MMU::current());
}

__END_SYS
