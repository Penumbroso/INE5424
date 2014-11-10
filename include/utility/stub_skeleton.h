// Metaprogrammed stub/skeleton generation machinery
#ifndef __stub_skeleton_h
#define __stub_skeleton_h

#include "tuple.h"

namespace EPOS {

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

} // namespace EPOS

/* Macros to automate stub generation.
 * Define STUB_CLASS before starting; every stub/skeleton pair will be generated
 * with name STUB_CLASS referencing EPOS::STUB_CLASS. */
#define STUB_BEGIN                  \
    struct STUB_CLASS {             \
        EPOS::STUB_CLASS * object;  \
    public:

#define STUB_END };

#define METHOD_1( ret, name, t1, p1, cv )                                   \
        ret name( t1 p1 ) cv {                                              \
            EPOS::tuple< EPOS::tuple<t1>, cv EPOS::STUB_CLASS*, ret > tup;  \
            get<0>( tup ) = tuple<t1>( p1 );                                \
            get<1>( tup ) = this->object;                                   \
            syscall(                                                        \
                    Skeleton<cv EPOS::STUB_CLASS, ret, t1>                  \
                    ::method< &EPOS::STUB_CLASS::name >                     \
                    ::call,                                                 \
                    (void*) &tup                                            \
                );                                                          \
            return get<2>( tup );                                           \
        }

#define METHOD_2( ret, name, t1, p1, t2, p2, cv )                               \
        ret name( t1 p1, t2 p2 ) cv {                                           \
            EPOS::tuple< EPOS::tuple<t1, t2>, cv EPOS::STUB_CLASS*, ret > tup;  \
            get<0>( tup ) = tuple<t1, t2>( p1, p2 );                            \
            get<1>( tup ) = this->object;                                       \
            syscall(                                                            \
                    Skeleton<cv EPOS::STUB_CLASS, ret, t1, t2>                  \
                    ::method< &EPOS::STUB_CLASS::name >                         \
                    ::call,                                                     \
                    (void*) &tup                                                \
                );                                                              \
            return get<2>( tup );                                               \
        }

#define VOID_METHOD( name )                                             \
        void name() {                                                   \
            EPOS::tuple< EPOS::tuple<>, EPOS::STUB_CLASS* > tup;        \
            EPOS::get<1>(tup) = this->object;                           \
            EPOS::syscall(                                              \
                    Skeleton<EPOS::STUB_CLASS, void>                    \
                    ::method< &EPOS::STUB_CLASS::name >                 \
                    ::call,                                             \
                (void*) &tup                                            \
            );                                                          \
        }

#endif // __stub_skeleton_h
