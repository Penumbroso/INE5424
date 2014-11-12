/* tuple
 * Partial implementation of std::tuple.
 *
 * This implementation is just complete enough to be usable by the
 * automatic stub/skeleton generator machinery.
 */
#ifndef __tuple_h
#define __tuple_h
#include <utility/meta.h>

namespace EPOS_Kernel {

/* Tuple class.
 * The member access is done via std::get functions.
 */
template< typename ... Ts >
struct tuple {};

template< typename Head, typename ... Tail >
struct tuple< Head, Tail... > {
    tuple() {}
    Head head;
    tuple<Tail...> tail;

    tuple( Head h, Tail... ts ) :
        head( h ),
        tail( ts... )
    {}
};

// Equivalence operators
template< typename ... Args >
bool operator==( const tuple<Args...>& lhs, const tuple<Args...>& rhs ) {
    return lhs.head == rhs.head && lhs.tail == rhs.tail;
}
bool operator==( const tuple<> &, const tuple<> & ) {
    return true;
}
template< typename ... Args >
bool operator!=( const tuple<Args...>& lhs, const tuple<Args...>& rhs ) {
    return !( lhs == rhs );
}

/* get<N>
 * Returns a reference to the N-th element in the tuple.
 * This function treats the tuple as 0-indexed.
 */
template< int N, typename ... Args >
typename type_at_index<N, Args...>::type       & get( tuple<Args...>       & t );
template< int N, typename ... Args >
typename type_at_index<N, Args...>::type const & get( tuple<Args...> const & t );

/* make_tuple
 * Constructs a tuple type with given arguments.
 *
 * This function is most useful to force parameter type deduction.
 */
template< typename ... Args >
tuple< Args... > make_tuple( const Args& ... args ) {
    return tuple<Args...>( args... );
}

/* tuple_call
 * Call the function (or member function) with the values of the tuple. */
template< typename R, typename ... Args >
R tuple_call( R (*)( Args... ), tuple<Args...> );
template< typename R, typename T, typename ... Args >
R tuple_call( R (T::*)( Args... ), T*, tuple<Args...> );
template< typename R, typename T, typename ... Args >
R tuple_call( R (T::*)( Args... ) const, const T*, tuple<Args...> );


/* Implementation of get<N>
 * Workaround to the inexistence of partial function overloading in C++ */
template< int N, typename ... Args >
struct get_t {
    typedef typename type_at_index<N, Args...>::type type;
    static type & get( tuple<Args...>& t ) {
        return EPOS_Kernel::template get<N-1>( t.tail );
    }
    static const type & get( const tuple<Args...>& t ) {
        return EPOS_Kernel::template get<N-1>( t.tail );
    }
};
template< typename ... Args >
struct get_t<0, Args...> {
    typedef typename type_at_index<0, Args...>::type type;
    static type & get( tuple<Args...>& t ) {
        return t.head;
    }
    static const type & get( const tuple<Args...>& t ) {
        return t.head;
    }
};
template< int N, typename ... Args >
typename type_at_index<N, Args...>::type       & get( tuple<Args...>       & t ) {
    return get_t<N, Args...>::get( t );
}
template< int N, typename ... Args >
typename type_at_index<N, Args...>::type const & get( tuple<Args...> const & t ) {
    return get_t<N, Args...>::get( t );
}

// Implementation of tuple_call
template< typename R, typename ... Args, int ... Indexes >
R tuple_call( R (*fun)( Args... ), tuple< Args... > t, integer_sequence< int, Indexes... > ) {
    return fun( get<Indexes>(t)... );
}
template< typename R, typename T, typename ... Args, int ... Indexes >
R tuple_call( R (T::*fun)( Args... ), T* obj, tuple< Args... > t, integer_sequence< int, Indexes... > ) {
    return (obj->*fun)( get<Indexes>(t)... );
}
template< typename R, typename T, typename ... Args, int ... Indexes >
R tuple_call( R (T::*fun)( Args... ) const, const T* obj, tuple< Args... > t, integer_sequence< int, Indexes... > ) {
    return (obj->*fun)( get<Indexes>(t)... );
}
template< typename R, typename ... Args >
R tuple_call( R (*fun)( Args... ), tuple<Args...> t ) {
    return tuple_call( fun, t, typename index_sequence_sized< int, sizeof...(Args) >::type() );
}
template< typename R, typename T, typename ... Args >
R tuple_call( R (T::* fun)( Args... ), T* obj, tuple<Args...> t ) {
    return tuple_call( fun, obj, t, typename index_sequence_sized< int, sizeof...(Args) >::type() );
}
template< typename R, typename T, typename ... Args >
R tuple_call( R (T::* fun)( Args... ) const, const T* obj, tuple<Args...> t ) {
    return tuple_call( fun, obj, t, typename index_sequence_sized< int, sizeof...(Args) >::type() );
}

} // namespace EPOS_Kernel

#endif // __tuple_h
