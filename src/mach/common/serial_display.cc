// EPOS Serial Display Mediator Implementation

#include <display.h>

namespace EPOS_Kernel {

// Class attributes
UART Serial_Display::_uart;
int Serial_Display::_line;
int Serial_Display::_column;

} // namespace EPOS_Kernel
