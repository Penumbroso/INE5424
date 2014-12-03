// EPOS EEPROM Mediator Common Package

#ifndef __eeprom_h
#define __eeprom_h

#include <system/config.h>

namespace EPOS_Kernel {

class EEPROM_Common
{
protected:
    EEPROM_Common() {}

public:
    typedef unsigned int Address;
};

} // namespace EPOS_Kernel

#ifdef __EEPROM_H
#include __EEPROM_H
#endif

#endif
