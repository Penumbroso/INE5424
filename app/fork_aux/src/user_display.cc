// #include "../include/user_display.hh"

#include <display.h>

typedef _SYS::Serial_Display User_Serial_Display;

// Class attributes copied from src/mach/common/serial_display.cc
_SYS::UART User_Serial_Display::_uart;
int User_Serial_Display::_line;
int User_Serial_Display::_column;

extern "C" 
{ 
    void user_display_puts(const char * s)
    {
        User_Serial_Display::puts(s);
    }    
}
