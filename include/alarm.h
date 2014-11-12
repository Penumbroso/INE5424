// User stub to EPOS_Kernel::Alarm
#include <utility/stub_skeleton.h>
#include <alarm_kernel.h>

namespace EPOS {
    STUB_BEGIN( Alarm, ::EPOS_Kernel::Alarm )
        typedef skeleton_type::Microsecond Microsecond;
        typedef skeleton_type::Hertz Hertz;
        enum { INFINITE = skeleton_type::INFINITE };

        STUB_CONSTRUCTOR_2( Alarm, Microsecond, time, EPOS_Kernel::Handler *, handler );
        STUB_CONSTRUCTOR_3( Alarm, Microsecond, time, EPOS_Kernel::Handler *, handler, int, times );

        static STUB_FUNCTION_0( Hertz, frequency, skeleton_type::frequency )
        static STUB_FUNCTION_1_VOID( delay, Microsecond, time, skeleton_type::delay )
    STUB_END
}
