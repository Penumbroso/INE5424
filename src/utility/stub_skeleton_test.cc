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
struct S { // Sample system class
    int i;
    void f() {
        i = 5;
    }
    int f( int j ) {
        int k = i;
        i = j;
        return k;
    }
    int f( char, double ) const {
        return i;
    }
};
}
namespace USER {
    struct S { // Stub class
        EPOS::S * object;
        void f() {
            tuple< tuple<>, EPOS::S* > tup;
            get<0>(tup) = tuple<>(); // unnecessary; just for consistency
            get<1>(tup) = object;
            syscall(Skeleton<EPOS::S, void>::method<
                    static_cast< int (EPOS::S::*)() >(EPOS::S::f) >::call, (void*)&tup);
        }
        int f( int p1 ) {
            tuple< tuple<int>, EPOS::S*, int > tup;
            get<0>( tup ) = tuple<int>( p1 );
            get<1>( tup ) = object;
            syscall(Skeleton<EPOS::S, int, int>::method< &EPOS::S::f >::call, (void*) &tup);
            return get<2>( tup );
        }
        int f( char p1, double p2 ) const {
            tuple< tuple<char, double>, const EPOS::S*, int > tup;
            get<0>( tup ) = tuple<char, double>( p1, p2 );
            get<1>( tup ) = object;
            syscall(Skeleton<const EPOS::S, int, char, double>::method< &EPOS::S::f >::call, (void*) &tup);
            return get<2>( tup );
        }
        // TODO: implement constructor in the same lines
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
    tuple< tuple<char, double>, S *, int > data1;
    get<0>(data1) = tuple<char, double>('2', 3.5 );
    get<1>(data1) = & s;
    syscall( Skeleton<S, int, char, double>::method< &S::f >::call, (void*) &data1 );
    dynamic_assert( s.i == 9 );
    dynamic_assert( get<2>(data1) == 9 );
    s.i = 4;
    syscall( Skeleton<S, int, char, double>::method< &S::f >::call, (void*) &data1 );
    dynamic_assert( s.i == 4 );
    dynamic_assert( get<2>(data1) == 4 );

    USER::S ss;
    ss.object = &s;
    ss.f();
    dynamic_assert( s.i == 5 );
    dynamic_assert( ss.f( 7 ) == 5 );
    dynamic_assert( s.i == 7 );
    dynamic_assert( ss.f( 'a', 3.5 ) == 5 );
    dynamic_assert( s.i == 7 );
}
