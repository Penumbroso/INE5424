// Unit test to std::tuple and std::get
#include <tuple>
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

int main() {
    EPOS::OStream cout;

    std::tuple<> null_tuple; // must compile

    std::tuple< int, char, double > tuple( 1, 'C', 3.5 );
    dynamic_assert( std::get<0>(tuple) == 1 );
    dynamic_assert( std::get<1>(tuple) == 'C' );
    dynamic_assert( std::get<2>(tuple) == 3.5 );
    std::get<0>(tuple) = 2;
    std::get<1>(tuple) = '+';
    std::get<2>(tuple) = 2.5;
    dynamic_assert( std::get<0>(tuple) == 2 );
    dynamic_assert( std::get<1>(tuple) == '+' );
    dynamic_assert( std::get<2>(tuple) == 2.5 );

    static_assert( std::is_same< int &,    decltype(std::get<0>(tuple)) >::value );
    static_assert( std::is_same< char &,   decltype(std::get<1>(tuple)) >::value );
    static_assert( std::is_same< double &, decltype(std::get<2>(tuple)) >::value );

    const std::tuple< int, char, double > & ctuple = tuple;

    dynamic_assert( std::get<0>(ctuple) == 2 );
    dynamic_assert( std::get<1>(ctuple) == '+' );
    dynamic_assert( std::get<2>(ctuple) == 2.5 );

    static_assert( std::is_same< const int &,    decltype(std::get<0>(ctuple)) >::value );
    static_assert( std::is_same< const char &,   decltype(std::get<1>(ctuple)) >::value );
    static_assert( std::is_same< const double &, decltype(std::get<2>(ctuple)) >::value );

    std::tuple< int, char, double > other( tuple );
    dynamic_assert( tuple == other );
    dynamic_assert( !(tuple != other) );
    std::get<1>( other ) = '1';
    dynamic_assert( tuple != other );
    dynamic_assert( !(tuple == other) );

    static_assert( std::is_same<
            decltype( tuple ),
            decltype( std::make_tuple( 2, '1', 2.5 ) )
        >::value );

    tuple = std::make_tuple( 2, '1', 2.5 );
    dynamic_assert( tuple == other );
    dynamic_assert( !(tuple != other) );
    tuple = std::make_tuple( 2, '4', 2.5 );
    dynamic_assert( tuple != other );
    dynamic_assert( !(tuple == other) );
    return 0;
}
