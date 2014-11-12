/* Metaprogramming library.
 *
 * All functions in this file are either value metafunctions or
 * type metafunctions; that is, consists of a struct with either
 * a static integer or boolean constant value named 'value',
 * or a nested typedef named 'type', that correspond to the return
 * value of the respective function.
 *
 * The naming conventions was chosen to resemble Boost.MPL.
 */
#ifndef __meta_h
#define __meta_h

namespace EPOS_Kernel {

/* True if both types are the same, false if they are different.
 * This template is sensible to cv-qualifications. */
template< typename T, typename U >
struct is_same {
    static const bool value = false;
};
template< typename T >
struct is_same<T, T> {
    static const bool value = true;
};

/* Returns the Nth element of the list.
 * The indexing is 0 based; that is,
 * type_at_index< 1, int, double >::value is double. */
template< int N, typename ... List >
struct type_at_index;

template< typename Head, typename ... Tail >
struct type_at_index< 0, Head, Tail... > {
    typedef Head type;
};
template< int N, typename Head, typename ... Tail >
struct type_at_index< N, Head, Tail... > {
    typedef typename type_at_index<N-1, Tail...>::type type;
};

/* If first parameter is true, returns the first type;
 * otherwise, returns the second type. */
template< bool, typename True, typename False >
struct conditional {
    typedef False type;
};
template< typename True, typename False >
struct conditional<true, True, False> {
    typedef True type;
};

/* Template class used to implement tuple_call-like functions. */
template< typename T, T... >
struct integer_sequence {};

/* Type metafunction that returns an integer_sequence of type T
 * whose values are 0, 1, 2, ..., N-1.
 *
 * In C++14, a very similar metafunction named make_integer_sequence
 * will be avaliable in standard headers; we cannot implement it here
 * due to the lack of template alias in this ancient compiler, so
 * we gave a different name to avoid mental name clashes. */
template< typename T, T N >
struct index_sequence_sized;

// Implementation of index_sequence_sized
template< bool b, typename T, T ... Ns >
struct boolean_index_sequence_helper;
template< typename T, T ... Ns >
struct index_sequence_helper;

template< bool b, typename T, T N, T ... Ns >
struct boolean_index_sequence_helper< b, T, N, Ns... > {
    typedef integer_sequence< T, Ns... > type;
};
template< typename T, T N, T ... Ns >
struct boolean_index_sequence_helper< false, T, N, Ns... > {
    typedef typename index_sequence_helper< T, N-1, N-1, Ns... >::type type;
};
template< typename T, T N, T ... Ns >
struct index_sequence_helper< T, N, Ns... > {
    typedef typename boolean_index_sequence_helper< N==0, T, N, Ns... >::type type;
};

template< typename T, T N >
struct index_sequence_sized {
    typedef typename index_sequence_helper<T, N>::type type;
};

} // namespace EPOS_Kernel

#endif // __meta_h
