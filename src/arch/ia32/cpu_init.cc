// EPOS IA32 CPU Mediator Initialization

#include <cpu.h>
#include <tsc.h>
#include <mmu.h>
#include <system.h>
#include <system/info.h>

namespace EPOS_Kernel {

void IA32::init()
{
    db<Init, CPU>(TRC) << "CPU::init()" << endl;

    _cpu_clock = System::info()->tm.cpu_clock;
    _bus_clock = System::info()->tm.bus_clock;

    // Initialize the MMU
    if(Traits<MMU>::enabled)
        MMU::init();
    else
        db<Init, MMU>(WRN) << "MMU is disabled!" << endl;
}

} // namespace EPOS_Kernel
