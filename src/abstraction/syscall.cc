/* syscall function implementation.
 * The intention of the function to be implemented here is to
 * have a single memory address in which all system calls are
 * redirected.
 *
 * This is the same reason for why the syscall must not be inlined.
 */
#include <system/config.h>

namespace EPOS_Kernel {

void syscall( void (* function )( void * ), void * parameter ) {
    function( parameter );
}

}
