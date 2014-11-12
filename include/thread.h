// User stub to EPOS_Kernel::Thread
#include <utility/stub_skeleton.h>
#include <thread_kernel.h>
#include <task.h>

namespace EPOS {

    STUB_BEGIN( Thread, ::EPOS_Kernel::Thread )
    protected:
        Thread() {}
    public:

        typedef skeleton_type::State State;
        typedef skeleton_type::Criterion Criterion;
        static const unsigned int STACK_SIZE = skeleton_type::STACK_SIZE;

        Thread(int (* entry)(),
                State state = EPOS_Kernel::Thread::READY, Criterion criterion = EPOS_Kernel::Thread::NORMAL, unsigned int stack_size = STACK_SIZE) {
            EPOS_Kernel::tuple< EPOS_Kernel::tuple< int(*)(), State, Criterion, unsigned >,
                    skeleton_type * > tup;
            EPOS_Kernel::get<0>(tup) = EPOS_Kernel::tuple< int(*)(), State, Criterion, unsigned >(
                    entry, state, criterion, stack_size );
            EPOS_Kernel::syscall( EPOS_Kernel::
                    Skeleton<skeleton_type, void, int (*)(), State, Criterion, unsigned>
                    ::construct, (void*) &tup );
            object = EPOS_Kernel::get<1>( tup );
        }
        Thread(const Task & task, int (* entry)(),
                State state = EPOS_Kernel::Thread::READY, Criterion criterion = EPOS_Kernel::Thread::NORMAL, unsigned int stack_size = STACK_SIZE) {
            EPOS_Kernel::tuple< EPOS_Kernel::tuple< const EPOS_Kernel::Task *, int(*)(), State, Criterion, unsigned >,
                    skeleton_type * > tup;
            EPOS_Kernel::get<0>(tup) = EPOS_Kernel::tuple< const EPOS_Kernel::Task *, int(*)(), State, Criterion, unsigned >(
                    task.object, entry, state, criterion, stack_size );
            EPOS_Kernel::syscall( EPOS_Kernel::
                    Skeleton<skeleton_type, void, const EPOS_Kernel::Task *, int (*)(), State, Criterion, unsigned>
                    ::construct, (void*) &tup );
            object = EPOS_Kernel::get<1>( tup );
        }

        STUB_METHOD_0_VOID( suspend, )
        STUB_METHOD_0_VOID( resume, )
        STUB_METHOD_0_VOID( pass, )
        STUB_METHOD_0( int, join, )
        static STUB_FUNCTION_0_VOID( yield, skeleton_type::yield )
        

        static Thread * self() {
            EPOS_Kernel::tuple< EPOS_Kernel::tuple<>, skeleton_type * > tup;
            EPOS_Kernel::syscall( EPOS_Kernel::FunctionSkeleton<skeleton_type * volatile>
                        ::function< skeleton_type::self >::call,
                        (void*) &tup );
            Thread * ret = new Thread;
            ret->object = EPOS_Kernel::get<1>( tup );
            return ret;
        }

    STUB_END
}
