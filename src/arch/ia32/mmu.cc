// EPOS IA32 MMU Mediator Implementation

#include <arch/ia32/mmu.h>

namespace EPOS_Kernel {

// Class attributes
IA32_MMU::List IA32_MMU::_free;
IA32_MMU::Page_Directory * IA32_MMU::_master;

} // namespace EPOS_Kernel
