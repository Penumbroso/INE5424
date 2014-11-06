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

#endif // __stub_skeleton_h
