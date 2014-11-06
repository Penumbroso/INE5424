// Unit test to EPOS::tuple and EPOS::get
#include <utility/tuple.h>
#include <utility/ostream.h>

#define TO_STRING( X ) REALLY_TO_STRING( X )
#define REALLY_TO_STRING( X ) #X
#define __LINE_STR__ TO_STRING( __LINE__ )

#define dynamic_assert( ... )                                       \
    do {                                                            \
        if( !(__VA_ARGS__) )                                        \
            cout << "Assertion " #__VA_ARGS__                       \
            " failed at " __FILE__ ":" __LINE_STR__ << EPOS::endl;  \
    } while(false)
#define static_assert( ... ) static_assert( __VA_ARGS__ , #__VA_ARGS__ ) // ugly

using namespace EPOS;

int main() {
    OStream cout;

    tuple<> null_tuple; // must compile

    // Tuple and get
    tuple< int, char, double > tup( 1, 'C', 3.5 );
    dynamic_assert( get<0>(tup) == 1 );
    dynamic_assert( get<1>(tup) == 'C' );
    dynamic_assert( get<2>(tup) == 3.5 );
    get<0>(tup) = 2;
    get<1>(tup) = '+';
    get<2>(tup) = 2.5;
    dynamic_assert( get<0>(tup) == 2 );
    dynamic_assert( get<1>(tup) == '+' );
    dynamic_assert( get<2>(tup) == 2.5 );

    static_assert( is_same< int &,    decltype(get<0>(tup)) >::value );
    static_assert( is_same< char &,   decltype(get<1>(tup)) >::value );
    static_assert( is_same< double &, decltype(get<2>(tup)) >::value );

    // const tuple and get
    const tuple< int, char, double > & ctuple = tup;

    dynamic_assert( get<0>(ctuple) == 2 );
    dynamic_assert( get<1>(ctuple) == '+' );
    dynamic_assert( get<2>(ctuple) == 2.5 );

    static_assert( is_same< const int &,    decltype(get<0>(ctuple)) >::value );
    static_assert( is_same< const char &,   decltype(get<1>(ctuple)) >::value );
    static_assert( is_same< const double &, decltype(get<2>(ctuple)) >::value );

    // Equality operator
    tuple< int, char, double > other( tup );
    dynamic_assert( tup == other );
    dynamic_assert( !(tup != other) );
    get<1>( other ) = '1';
    dynamic_assert( tup != other );
    dynamic_assert( !(tup == other) );

    // make_tuple
    static_assert( is_same<
            decltype( tup ),
            decltype( make_tuple( 2, '1', 2.5 ) )
        >::value );

    tup = make_tuple( 2, '1', 2.5 );
    dynamic_assert( tup == other );
    dynamic_assert( !(tup != other) );
    tup = make_tuple( 2, '4', 2.5 );
    dynamic_assert( tup != other );
    dynamic_assert( !(tup == other) );

    // nested tuples
    tuple< tuple< tuple<>, int > > nested_tuple(
            tuple< tuple<>, int>(tuple<>(), 2)
        );

    static_assert( is_same<
            tuple< tuple<>, int > &,
            decltype( get<0>(nested_tuple) )
        >::value );
    static_assert( is_same<
            tuple<> &,
            decltype( get<0>( get<0>(nested_tuple) ) )
        >::value );
    static_assert( is_same<
            int &,
            decltype( get<1>( get<0>(nested_tuple) ) )
        >::value);
    dynamic_assert( get<1>(get<0>(nested_tuple)) == 2 );

    return 0;
}
