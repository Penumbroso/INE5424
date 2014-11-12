// Metaprogrammed stub/skeleton generation machinery
#ifndef __stub_skeleton_h
#define __stub_skeleton_h

#include "tuple.h"
#include <system/config.h> // operator new

namespace EPOS_Kernel {

/* Automation of parameter marshalling.
 * Call convention:
 * A call to T::m, with parameters Args... and return type R,
 * is done via a tuple of three elements. The first two contains,
 * respectively, the arguments (in a tuple, suited for calling
 * tuple_call) and a pointer to the object that will call the
 * function. The last element will be modified to the return value
 * of the function call.
 *
 * The function, with syscall-compatible signature, that does this
 * invocation, is found in Skeleton<T>::method<m>::call.
 */
template< typename T, typename R, typename ... Args > // non-void, non-const
struct Skeleton {
    template< R (T::* M)( Args... ) >
    struct method {
        static void call( void * data ) {
            tuple< tuple<Args...>, T *, R >* tup = (tuple< tuple<Args...>, T *, R >*) data;
            get<2>( *tup ) = tuple_call( M, get<1>(*tup), get<0>(*tup) );
        }
    };
};
template< typename T, typename ... Args > // void, non-const
struct Skeleton< T, void, Args... > {
    template< void (T::* M)( Args... ) >
    struct method {
        static void call( void * data ) {
            tuple< tuple<Args...>, T * >* tup = (tuple< tuple<Args...>, T * >*) data;
            tuple_call( M, get<1>(*tup), get<0>(*tup) );
        }
    };
    static T* constructor( Args... args ) {
        return new(SYSTEM) T( args... );
    }
    static void construct( void * data ) {
        tuple< tuple<Args...>, T * >* tup = (tuple< tuple<Args...>, T * >*) data;
        get<1>( *tup ) = tuple_call( constructor, get<0>(*tup) );
    }
};
template< typename T, typename R, typename ... Args > // non-void, const
struct Skeleton< const T, R, Args... > {
    template< R (T::* M)( Args... ) const >
    struct method {
        static void call( void * data ) {
            tuple< tuple<Args...>, const T *, R >* tup = (tuple< tuple<Args...>, const T *, R >*) data;
            get<2>( *tup ) = tuple_call( M, get<1>(*tup), get<0>(*tup) );
        }
    };
};
template< typename T, typename ... Args > // void, const
struct Skeleton< const T, void, Args... > {
    template< void (T::* m)( Args... ) const >
    struct method { // void, const
        static void call( void * data ) {
            tuple< tuple<Args...>, const T * >* tup = (tuple< tuple<Args...>, const T * >*) data;
            tuple_call( m, get<1>(*tup), get<0>(*tup) );
        }
    };
};
template< typename T >
struct DestructorSkeleton {
    static void destructor( void * data ) {
        T * t = (T*) data;
        delete t;
    }
};

} // namespace EPOS_Kernel

/* Macros to automate stub generation.
 * skeleton is the fully-qualified name of the existing skeleton class,
 * stub is the unqualified name of the generated stub class. */
#define STUB_BEGIN( stub_name, skeleton_class )                     \
    class stub_name {                                               \
        typedef skeleton_class skeleton_type;                       \
        skeleton_type * object;                                     \
    public:                                                         \
        ~stub_name() {                                              \
            syscall( EPOS_Kernel::DestructorSkeleton<skeleton_type> \
                    ::destructor, (void*) object );                 \
        }

#define STUB_END };

#define STUB_CONSTRUCTOR_0( stub_name )                                                 \
    stub_name() {                                                                       \
        EPOS_Kernel::tuple< EPOS_Kernel::tuple<>, skeleton_type* > tup;                 \
        syscall( EPOS_Kernel::Skeleton<skeleton_type, void>::construct, (void*)&tup );  \
        object = get<1>( tup );                                                         \
    }

#define STUB_CONSTRUCTOR_1( stub_name, t1, p1 )                                 \
    stub_name( t1 p1 ) {                                                        \
        EPOS_Kernel::tuple< EPOS_Kernel::tuple<t1>, skeleton_type* > tup;       \
        get<0>( tup ) = EPOS_Kernel::tuple<t1>( p1 );                           \
        syscall( Skeleton<skeleton_type, void, t1>::construct, (void*)&tup );   \
        object = get<1>( tup );                                                 \
    }

#define STUB_CONSTRUCTOR_2( stub_name, t1, p1, t2, p2 )                         \
    stub_name( t1 p1, t2 p2 ) {                                                 \
        EPOS_Kernel::tuple< EPOS_Kernel::tuple<t1, t2>, skeleton_type* > tup;   \
        get<0>( tup ) = EPOS_Kernel::tuple<t1>( p1, p2 );                       \
        syscall( Skeleton<skeleton_type, void, t1>::construct, (void*)&tup );   \
        object = get<1>( tup );                                                 \
    }

#define STUB_METHOD_0( ret, name, cv )                                              \
        ret name() cv {                                                             \
            EPOS_Kernel::tuple< EPOS_Kernel::tuple<>, cv skeleton_type*, ret > tup; \
            get<1>( tup ) = this->object;                                           \
            syscall(                                                                \
                    Skeleton<cv skeleton_type, ret>                                 \
                    ::method< &skeleton_type::name >                                \
                    ::call,                                                         \
                    (void*) &tup                                                    \
                );                                                                  \
            return get<2>( tup );                                                   \
        }

#define STUB_METHOD_0_VOID( name, cv )                                          \
        void name() cv {                                                        \
            EPOS_Kernel::tuple< EPOS_Kernel::tuple<>, cv skeleton_type* > tup;  \
            get<1>( tup ) = this->object;                                       \
            syscall(                                                            \
                    Skeleton<cv skeleton_type, void>                            \
                    ::method< &skeleton_type::name >                            \
                    ::call,                                                     \
                    (void*) &tup                                                \
                );                                                              \
        }                                                                       

#define STUB_METHOD_1( ret, name, t1, p1, cv )                                          \
        ret name( t1 p1 ) cv {                                                          \
            EPOS_Kernel::tuple< EPOS_Kernel::tuple<t1>, cv skeleton_type*, ret > tup;   \
            get<0>( tup ) = tuple<t1>( p1 );                                            \
            get<1>( tup ) = this->object;                                               \
            syscall(                                                                    \
                    Skeleton<cv skeleton_type, ret, t1>                                 \
                    ::method< &skeleton_type::name >                                    \
                    ::call,                                                             \
                    (void*) &tup                                                        \
                );                                                                      \
            return get<2>( tup );                                                       \
        }

#define STUB_METHOD_1_VOID( name, t1, p1, cv )                                      \
        void name( t1 p1 ) cv {                                                     \
            EPOS_Kernel::tuple< EPOS_Kernel::tuple<t1>, cv skeleton_type* > tup;    \
            get<0>( tup ) = tuple<t1>( p1 );                                        \
            get<1>( tup ) = this->object;                                           \
            syscall(                                                                \
                    Skeleton<cv skeleton_type, void, t1>                            \
                    ::method< &skeleton_type::name >                                \
                    ::call,                                                         \
                    (void*) &tup                                                    \
                );                                                                  \
        }

#define STUB_METHOD_2( ret, name, t1, p1, t2, p2, cv )                                      \
        ret name( t1 p1, t2 p2 ) cv {                                                       \
            EPOS_Kernel::tuple< EPOS_Kernel::tuple<t1, t2>, cv skeleton_type*, ret > tup;   \
            get<0>( tup ) = tuple<t1, t2>( p1, p2 );                                        \
            get<1>( tup ) = this->object;                                                   \
            syscall(                                                                        \
                    Skeleton<cv skeleton_type, ret, t1, t2>                                 \
                    ::method< &skeleton_type::name >                                        \
                    ::call,                                                                 \
                    (void*) &tup                                                            \
                );                                                                          \
            return get<2>( tup );                                                           \
        }

#define STUB_METHOD_2_VOID( name, t1, p1, t2, p2, cv )                              \
        void name( t1 p1, t2 p2 ) cv {                                              \
            EPOS_Kernel::tuple< EPOS_Kernel::tuple<t1, t2>, cv skeleton_type* > tup;\
            get<0>( tup ) = tuple<t1, t2>( p1, p2 );                                \
            get<1>( tup ) = this->object;                                           \
            syscall(                                                                \
                    Skeleton<cv skeleton_type, void, t1, t2>                        \
                    ::method< &skeleton_type::name >                                \
                    ::call,                                                         \
                    (void*) &tup                                                    \
                );                                                                  \
        }

#define STUB_METHOD_3( ret, name, t1, p1, t2, p2, t3, p3, cv )                                  \
        ret name( t1 p1, t2 p2, t3 p3 ) cv {                                                    \
            EPOS_Kernel::tuple< EPOS_Kernel::tuple<t1, t2, t3>, cv skeleton_type*, ret > tup;   \
            get<0>( tup ) = tuple<t1, t2, t3>( p1, p2, p3 );                                    \
            get<1>( tup ) = this->object;                                                       \
            syscall(                                                                            \
                    Skeleton<cv skeleton_type, ret, t1, t2, t3>                                 \
                    ::method< &skeleton_type::name >                                            \
                    ::call,                                                                     \
                    (void*) &tup                                                                \
                );                                                                              \
            return get<2>( tup );                                                               \
        }

#define STUB_METHOD_3_VOID( name, t1, p1, t2, p2, t3, p3, cv )                          \
        void name( t1 p1, t2 p2, t3 p3 ) cv {                                           \
            EPOS_Kernel::tuple< EPOS_Kernel::tuple<t1, t2, t3>, cv skeleton_type* > tup;\
            get<0>( tup ) = tuple<t1, t2, t3>( p1, p2, p3 );                            \
            get<1>( tup ) = this->object;                                               \
            syscall(                                                                    \
                    Skeleton<cv skeleton_type, void, t1, t2, t3>                        \
                    ::method< &skeleton_type::name >                                    \
                    ::call,                                                             \
                    (void*) &tup                                                        \
                );                                                                      \
        }

#endif // __stub_skeleton_h
