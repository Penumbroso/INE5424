// User OStream class
#include <utility/ostream_kernel.h>
#include <utility/tuple.h>

namespace EPOS {

using EPOS_Kernel::begl;
using EPOS_Kernel::endl;
using EPOS_Kernel::hex;
using EPOS_Kernel::dec;
using EPOS_Kernel::oct;
using EPOS_Kernel::bin;

class OStream {
    EPOS_Kernel::OStream os;
public:

    template< typename T >
    OStream& operator<<( T t ) {
        EPOS_Kernel::tuple< T, EPOS_Kernel::OStream * > tup( t, &os );
        EPOS_Kernel::syscall( &system_call<T>, (void*) &tup );
        return *this;
    }

private:
    template< typename T >
    static void system_call( void * data ) {
        EPOS_Kernel::tuple< T, EPOS_Kernel::OStream * >* tup =
            (EPOS_Kernel::tuple< T, EPOS_Kernel::OStream * >*) data;
        *EPOS_Kernel::get<1>(*tup) << EPOS_Kernel::get<0>(*tup);
    }
};

} // namespace EPOS
