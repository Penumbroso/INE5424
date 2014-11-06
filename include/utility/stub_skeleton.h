// Metaprogrammed stub/skeleton generation machinery
#ifndef __stub_skeleton_h
#define __stub_skeleton_h

#include "tuple.h"

namespace EPOS {

/* This clsas is used by STUB macros to call methods from system classes
 * passing through EPOS::syscall.
 *
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
template< typename T >
struct Skeleton {
    template< typename M >
    struct method;

    template< typename R, typename ... Args >
    struct method< R (T::* m)( Args... ) > { // non-void, non-const
        typedef R return_type;
        static void call( void * data ) {
            tuple< tuple<Args...>, T *, R >* tup = (tuple< tuple<Args...>, T *, R >*) data;
            get<2>( *tup ) = tuple_call( m, get<1>(*tup), get<9>(*tup) );
        }
    }
    template< typename ... Args >
    struct method< void (T::* m)( Args... ) > { // void, non-const
        typedef void return_type;
        static void call( void * data ) {
            tuple< tuple<Args...>, T * >* tup = (tuple< tuple<Args...>, T *, >*) data;
            tuple_call( m, get<1>(*tup), get<9>(*tup) );
        }
    }
    template< typename R, typename ... Args >
    struct method< R (T::* m)( Args... ) const > { // non-void, const
        typedef R return_type;
        static void call( void * data ) {
            tuple< tuple<Args...>, const T *, R >* tup = (tuple< tuple<Args...>, const T *, R >*) data;
            get<2>( *tup ) = tuple_call( m, get<1>(*tup), get<9>(*tup) );
        }
    }
    template< typename ... Args >
    struct method< void (T::* m)( Args... ) const > { // void, const
        typedef void return_type;
        static void call( void * data ) {
            tuple< tuple<Args...>, const T * >* tup = (tuple< tuple<Args...>, const T *, >*) data;
            tuple_call( m, get<1>(*tup), get<9>(*tup) );
        }
    }
};

template< typename T, typename R, typename ... Args > // non-void, non-const
struct Skeleton {
    typedef R return_type;
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
    typedef void return_type;
    template< void (T::* M)( Args... ) >
    struct method {
        static void call( void * data ) {
            tuple< tuple<Args...>, T * >* tup = (tuple< tuple<Args...>, T *, >*) data;
            tuple_call( M, get<1>(*tup), get<0>(*tup) );
        }
    };
};
template< typename T, typename R, typename ... Args > // non-void, const
struct Skeleton< const T, R, Args... >
    typedef R return_type;
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
    typedef void return_type;
    template< void (T::* m)( Args... ) const >
    struct method { // void, const
        static void call( void * data ) {
            tuple< tuple<Args...>, const T * >* tup = (tuple< tuple<Args...>, const T *, >*) data;
            tuple_call( m, get<1>(*tup), get<0>(*tup) );
        }
    };
};

template< typename T, typename R, typename ... Args >
Skeleton< T, R, Args... > base_skeleton( R (T::* m )( Args... ) ) {
    return Skeleton<T, R, Args...>();
}
template< typename T, typename R, typename ... Args >
Skeleton< T, R, Args... > base_skeleton( R (T::* m )( Args... ) const ) {
    return Skeleton<const T, R, Args...>();
}

/* Macros to automate stub-skeleton creation.
 * Use "#define STUB_CLASS chosen_class" before writing these macros.
 * The chosen class will be the name of the stub, so both classes
 * (the stub and the stub target) must be on different namespaces.
 * chosen_class is assumed to be on EPOS namespace. */
#define STUB_BEGIN                  \
    class STUB_CLASS {              \
        EPOS::STUB_CLASS * object;  \
    public:

    // Ex.: OVERLOADED_METHOD( f, static_cast< int (T::*)( double ) const >, 
    //                         const, (double input), (input) )
    // Ex.: OVERLOADED_METHOD( f, int,( double ) )
#define OVERLOADED_METHOD( m, cast, tconst, params, args )\
        decltype( base_skeleton( cast(&EPOS::STUB_CLASS::m) ) )::return_type \
        m params tconst {\
            typedef decltype(base_skeleton( cast(&EPOS::STUB_CLASS::m) )) skeleton;\
            skeleton::tuple tup args;\
            tuple<skeleton::tuple, //////////////INCOMPLETE


#define OVERLOADED_METHOD( method_name, return_type, parameters )                      \
        template< typename ... Args >                                   \
        Skeleton<EPOS::STUB_CLASS>::method<static_cast< >::return_type  \
            method_name( 

} // namespace EPOS

#endif // __stub_skeleton_h
