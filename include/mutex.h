// User stub to EPOS_Kernel::mutex
#include <utility/stub_skeleton.h>
#include <mutex_kernel.h>

namespace EPOS {
    STUB_BEGIN( Mutex, ::EPOS_Kernel::Mutex )
        STUB_CONSTRUCTOR_0( Mutex )

        STUB_CONSTRUCTOR_0( lock, )
        STUB_METHOD_0_VOID( unlock, )
    STUB_END
} // namespace EPOS
