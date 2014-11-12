// User stub to EPOS_Kernel::Task
#ifndef TASK_H
#define TASK_H
#include <utility/stub_skeleton.h>
#include <task_kernel.h>

namespace EPOS {

    typedef EPOS_Kernel::Address_Space Address_Space;
    typedef EPOS_Kernel::Segment Segment;
    typedef EPOS_Kernel::CPU CPU;

    class Thread;

    STUB_BEGIN( Task, ::EPOS_Kernel::Task )
        friend class Thread;
    protected:
        Task() {}
    public:

        typedef skeleton_type::Log_Addr Log_Addr;

        Task( const Segment & cs, const Segment & ds ) {
            EPOS_Kernel::tuple< EPOS_Kernel::tuple< const Segment*, const Segment* >, skeleton_type* > tup;
            EPOS_Kernel::get<0>( tup ) = EPOS_Kernel::tuple< const Segment *, const Segment * >(&cs, &ds);
            EPOS_Kernel::syscall( EPOS_Kernel::
                    Skeleton<skeleton_type, void, const Segment*, const Segment*>
                    ::construct, (void*) &tup );
            object = EPOS_Kernel::get<1>( tup );
        }

        STUB_METHOD_0( Address_Space *, address_space, const )
        STUB_METHOD_0( const Segment *, code_segment, const )
        STUB_METHOD_0( const Segment *, data_segment, const )
        STUB_METHOD_0( Log_Addr, code, const )
        STUB_METHOD_0( Log_Addr, data, const )

        static Task * self() {
            EPOS_Kernel::tuple< EPOS_Kernel::tuple<>, skeleton_type * > tup;
            EPOS_Kernel::syscall( EPOS_Kernel::FunctionSkeleton<const skeleton_type *>
                        ::function< skeleton_type::self >::call,
                        (void*) &tup );
            Task * ret = new Task;
            ret->object = EPOS_Kernel::get<1>( tup );
            return ret;
        }

    STUB_END
}
#endif // TASK_H
