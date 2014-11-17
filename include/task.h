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

    private:
        // Auxiliar methods and functions to Thread::self()
        static STUB_FUNCTION_0( skeleton_type *, _self, skeleton_type::self )
        STUB_METHOD_1( Task *, stub, Task**, stub_ptr, )
        static Task * aux; // automate a function call to EPOS_Kernel::Thread::stub
    public:
        static Task * self() {
            if( aux == 0 ) aux = new Task;
            aux->object = _self();
            return aux->stub( &aux );
        }

    STUB_END
}
#endif // TASK_H
