/* ostream_test.cc
 * Compilation (and run) test to see wether the stub is working. */
#include <utility/ostream.h>

int main() {
    EPOS::OStream cout;
    cout << 5 << EPOS::endl;
    cout << 10 << EPOS::endl;
    cout << 6.75f << EPOS::endl;
    cout << EPOS::oct << 10 << EPOS::endl;
    return 0;
}
