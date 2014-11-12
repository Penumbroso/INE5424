// Unit test to EPOS_Kernel::tuple and EPOS_Kernel::get
#include <utility/tuple.h>
#include <utility/ostream.h>

#define TO_STRING( X ) REALLY_TO_STRING( X )
#define REALLY_TO_STRING( X ) #X
#define __LINE_STR__ TO_STRING( __LINE__ )

#define dynamic_assert( ... )                                       \
    do {                                                            \
        if( !(__VA_ARGS__) )                                        \
            cout << "Assertion " #__VA_ARGS__                       \
            " failed at " __FILE__ ":" __LINE_STR__ << EPOS_Kernel::endl;  \
    } while(false)
#define static_assert( ... ) static_assert( __VA_ARGS__ , #__VA_ARGS__ ) // ugly

using namespace EPOS_Kernel;

double f( int i, int j ) {
    return i + j;
}
long long g( int i, int j ) {
    return i - j;
}
static bool h_was_called;
void h( int, int ) {
    h_was_called = true;
}

struct S {
    int i() {
        return k;
    }
    float j( int y ) {
        return y + k;
    }
    int k;
};

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

    // tuple_call with functions
    tuple< int, int > pair( 2, 1 );
    static_assert( is_same<
            double,
            decltype( tuple_call( f, pair ) )
        >::value );
    static_assert( is_same<
            long long,
            decltype( tuple_call( g, pair ) )
        >::value );
    static_assert( is_same<
            void,
            decltype( tuple_call( h, pair ) )
        >::value );
    dynamic_assert( tuple_call( f, pair ) == 3.0 );
    dynamic_assert( tuple_call( g, pair ) == 1 );
    get<1>( pair ) = -get<1>( pair );
    dynamic_assert( tuple_call( f, pair ) == 1.0 );
    dynamic_assert( tuple_call( g, pair ) == 3 );
    h_was_called = false;
    dynamic_assert( !h_was_called );
    tuple_call( h, pair );
    dynamic_assert( h_was_called );

    // tuple_call with methods
    S s;
    s.k = 2;
    tuple< int > int_tuple( 7 );
    static_assert( is_same<
            int,
            decltype( tuple_call( &S::i, &s, null_tuple ) )
        >::value );
    static_assert( is_same<
            float,
            decltype( tuple_call( &S::j, &s, int_tuple ) )
        >::value );
    dynamic_assert( tuple_call( &S::i, &s, null_tuple ) == 2 );
    dynamic_assert( tuple_call( &S::j, &s,  int_tuple ) == 9.0f );
    s.k = 3;
    dynamic_assert( tuple_call( &S::i, &s, null_tuple ) == 3 );
    dynamic_assert( tuple_call( &S::j, &s,  int_tuple ) == 10.0f );
    get<0>(int_tuple)++;
    dynamic_assert( tuple_call( &S::j, &s,  int_tuple ) == 11.0f );

    return 0;
}
