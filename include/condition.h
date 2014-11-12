// User stub to EPOS_Kernel::condition
#include <utility/stub_skeleton.h>
#include <condition_kernel.h>

namespace EPOS {
    STUB_BEGIN( Condition, ::EPOS_Kernel::Condition )
        STUB_CONSTRUCTOR_0( Condition )

        STUB_METHOD_0_VOID( wait, )
        STUB_METHOD_0_VOID( signal, )
        STUB_METHOD_0_VOID( broadcast, )
    STUB_END
} // namespace EPOS
