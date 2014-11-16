// Stub and Skeleton mechanism unit test.
#include <system/types.h>
#include <utility/tuple.h>
#include <utility/ostream_kernel.h>
#include <utility/stub_skeleton.h>

// We will do only a small modification to allow for easier testing
#undef STUB_BEGIN
#define STUB_BEGIN( stub_name, skeleton_class )                                       \
    struct stub_name {                                                                \
        typedef skeleton_class skeleton_type;                                         \
        skeleton_type * object;                                                       \
    public:                                                                           \
        ~stub_name() {                                                                \
            syscall( DestructorSkeleton<skeleton_type>::destructor, (void*) object ); \
        }

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

namespace EPOS_Kernel {
struct S { // Sample system class
    S() {}
    S( double d ) : i(d+0.5) {}
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

    static int val;
    static int f( char ) {
        return 5+val;
    }
    static void f( float j ) {
        val = j;
    }
};
} // namespace EPOS_Kernel

namespace EPOS {
    STUB_BEGIN( S, ::EPOS_Kernel::S )
        STUB_CONSTRUCTOR_0( S )
        STUB_CONSTRUCTOR_1( S, double, d )
        STUB_METHOD_0( void, f, )
        STUB_METHOD_1( int, f, int, p1, )
        STUB_METHOD_2( int, f, char, p1, double, p2, const )

        static STUB_FUNCTION_1( int, f, char, dummy, ::EPOS_Kernel::S::f )
        static STUB_FUNCTION_1( void, f, float, j, ::EPOS_Kernel::S::f )
    STUB_END
} // namespace EPOS

int EPOS_Kernel::S::val;

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

    EPOS_Kernel::S s;
    s.i = 9;
    tuple< tuple<char, double>, EPOS_Kernel::S *, int > data1;
    get<0>(data1) = tuple<char, double>('2', 3.5 );
    get<1>(data1) = & s;
    syscall( Skeleton<const EPOS_Kernel::S, int, char, double>
                ::method< &EPOS_Kernel::S::f >::call, (void*) &data1 );
    dynamic_assert( s.i == 9 );
    dynamic_assert( get<2>(data1) == 9 );
    s.i = 4;//           |
    // Note o const aqui v 
    syscall( Skeleton<const EPOS_Kernel::S, int, char, double>
                ::method< &EPOS_Kernel::S::f >::call, (void*) &data1 );
    dynamic_assert( s.i == 4 );
    dynamic_assert( get<2>(data1) == 4 );

    EPOS::S ss;
    ss.f();
    dynamic_assert( ss.object->i == 5 );
    dynamic_assert( ss.f( 7 ) == 5 );
    dynamic_assert( ss.object->i == 7 );
    dynamic_assert( ss.f( 'a', 3.5 ) == 7 );
    dynamic_assert( ss.object->i == 7 );

    EPOS::S st( 14 );
    dynamic_assert( st.object->i == 14 );

    EPOS_Kernel::S::val = 9;
    dynamic_assert( EPOS::S::f( 'a' ) == 14 );
    EPOS_Kernel::S::val = 8;
    dynamic_assert( EPOS::S::f( 'a' ) == 13 );
    EPOS::S::f( 3.5f );
    dynamic_assert( EPOS_Kernel::S::val == 3 );
    dynamic_assert( EPOS::S::f( 'a' ) == 8 );
}
