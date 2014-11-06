// Stub and Skeleton mechanism unit test.
#include <system/types.h>
#include <utility/tuple.h>
#include <utility/ostream.h>
#include <utility/stub_skeleton.h>

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
OStream cout;

static int f_int;
void f( void * ptr ) {
    int * integer = (int *) ptr;
    int f_tmp = f_int;
    f_int = *integer;
    *integer = f_tmp;
}
void g( void * ptr ) {
    tuple<const int, char> * tup = (tuple<const int, char>*) ptr;
    get<1>( *tup ) = get<0>( *tup ) + 'A';
}

namespace EPOS {
struct S {
    int i;
    void f() {
        i = 5;
    }
    int f( int j ) {
        int k = i;
        i = j;
        return k;
    }
    int f( char ) const {
        return i;
    }
};
}

int main() {
    // syscall test
    int local_int = 2;
    f_int = 6;
    dynamic_assert( local_int == 2 );
    dynamic_assert( f_int == 6 );
    syscall( f, (void *) &local_int );
    dynamic_assert( local_int == 6 );
    dynamic_assert( f_int == 2 );
    local_int = 4;
    syscall( f, (void *) &local_int );
    dynamic_assert( local_int == 2 );
    dynamic_assert( f_int == 4 );

    tuple<int, char> tup( 5, 'A' );
    syscall( g, (void *) &tup );
    dynamic_assert( get<1>(tup) == 'F' );
    get<0>( tup ) = 2;
    syscall( g, (void *) &tup );
    dynamic_assert( get<1>(tup) == 'C' );

    S s;
    s.i = 9;
    tuple< tuple<char>, S *, int > data1;
    get<0>(data1) = tuple<char>('2');
    get<1>(data1) = & s;
    syscall( Skeleton<S>::method< static_cast< int (S::*)( char ) const >(f) >::call, (void*) &data1 );
    dynamic_assert( s.i == 9 );
    dynamic_assert( get<2>(data1) == 9 );
    s.i = 4;
    syscall( Skeleton<S>::method< static_cast< int (S::*)( char ) const >(f) >::call, (void*) &data1 );
    dynamic_assert( s.i == 4 );
    dynamic_assert( get<2>(data1) == 4 );
}
