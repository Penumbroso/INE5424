// User stub to EPOS_Kernel::semaphore
#include <utility/stub_skeleton.h>
#include <semaphore_kernel.h>

namespace EPOS {
    STUB_BEGIN( Semaphore, ::EPOS_Kernel::Semaphore )
        STUB_CONSTRUCTOR_0( Semaphore )
        STUB_CONSTRUCTOR_1( Semaphore, int, v )

        STUB_METHOD_0_VOID( p, )
        STUB_METHOD_0_VOID( v, )
    STUB_END
} // namespace EPOS
