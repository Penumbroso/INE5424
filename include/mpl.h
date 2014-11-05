/* mpl.h
 * Metaprogramming library.
 *
 * All functions in this file are either value metafunctions or
 * type metafunctions; that is, consists of a struct with either
 * a static integer or boolean constant value named 'value',
 * or a nested typedef named 'type', that correspond to the return
 * value of the respective function.
 *
 * The naming conventions was chosen to resemble Boost.MPL.
 *
 * All metafunctions are in namespace std, outside namespace EPOS;
 * this was done so the library could be reused with little or
 * no code change.
 */
#ifndef __mpl_h
#define __mpl_h

namespace std {

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

} // namespace std

#endif // __mpl_h
