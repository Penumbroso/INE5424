// EPOS PC EEPROM Mediator Common Declarations

#ifndef __pc_eeprom_h
#define __pc_eeprom_h

#include <eeprom.h>
#include "rtc.h"

namespace EPOS_Kernel {

class PC_EEPROM: public EEPROM_Common, private MC146818
{
public:
    typedef EEPROM_Common::Address Address;

public:
    PC_EEPROM() {};

    unsigned char read(const Address & a) { return cmos_read(a); }
    void write(const Address & a, unsigned char d) { cmos_write(a, d); }

    int size() const { return cmos_size(); }
};

} // namespace EPOS_Kernel

#endif
