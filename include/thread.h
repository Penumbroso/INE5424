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

        STUB_METHOD_0( void, suspend, )
        STUB_METHOD_0( void, resume, )
        STUB_METHOD_0( void, pass, )
        STUB_METHOD_0( int, join, )
        static STUB_FUNCTION_0( void, yield, skeleton_type::yield )

    private:
        // Auxiliar methods and functions to Thread::self()
        static STUB_FUNCTION_0( skeleton_type * volatile, _self, skeleton_type::self )
        STUB_METHOD_1( Thread *, stub, Thread**, stub_ptr, )
        static Thread * aux; // automate a function call to EPOS_Kernel::Thread::stub
    public:
        static Thread * self() {
            /* The idea is to put a pointer to the stub in the skeleton, but to
             * make the linking on demand.
             *
             * When this function is executed, if aux is null, we allocate a new
             * stub in user heap, and assign the return of Thread::self() as the
             * skeleton of this struct. If aux was not null, this means that we
             * already had a spare stub, so we will use this object.
             *
             * We then execute aux->stub. This redirects to Thread::stub. If the
             * skeleton did not had a stub assigned to it, it will use the given
             * Thread* as its stub and assign null to our pointer. Otherwise,
             * it will just return the pointer to us.
             *
             * It should be noted that this solution works well only in a
             * single-task environment.*/
            if( aux == 0 ) aux = new Thread;
            aux->object = _self();
            return aux->stub( &aux );
        }

    STUB_END
}
