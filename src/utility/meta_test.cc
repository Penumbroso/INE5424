// Metaprogram library unit test
#include <utility/meta.h>

#define static_assert( ... ) static_assert( __VA_ARGS__ , #__VA_ARGS__ ) // ugly

using namespace EPOS_Kernel;

int main() {
    static_assert( is_same<int, int>::value );
    static_assert( is_same<signed, int>::value );
    static_assert( is_same<const int, const int>::value );
    static_assert( is_same<volatile char, volatile char>::value );
    static_assert( !is_same<int, const int>::value );
    static_assert( !is_same<volatile char, char>::value );
    static_assert( !is_same<char, signed char>::value );
    static_assert( !is_same<int, double>::value );

    static_assert( is_same<
            type_at_index<0, int, char, const char, double>::type,
            int
        >::value );
    static_assert( is_same<
            type_at_index<1, int, char, const char, double>::type,
            char
        >::value );
    static_assert( is_same<
            type_at_index<2, int, char, const char, double>::type,
            const char
        >::value );
    static_assert( is_same<
            type_at_index<3, int, char, const char, double>::type,
            double
        >::value );
    static_assert( is_same< type_at_index<0, int>::type, int >::value );
    static_assert( !is_same< type_at_index<0, unsigned>::type, int>::value );
    return 0;
}
