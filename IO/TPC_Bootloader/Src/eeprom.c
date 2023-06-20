/****************************************************************************************
/ Read and write the eeprom
/
***************************************************************************************/
#include "iom128.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"
#include "inavr.h"


/*---------------------------------------------------------------------------
**
**  Reads an address in the eeprom
**
**--------------------------------------------------------------------------*/
char ReadEEPROMByte( unsigned int Address ) {

    unsigned char Data;

    while (EECR & (1<<EEWE))     // Wait until ready
        ;
    EEAR = Address;
    EECR |= (1 << EERE) ;       // Don't use SetBit macrod due to timing

    Data = EEDR;
    return Data;

}

/*---------------------------------------------------------------------------
**
**  Write a caracther to the eeprom
**
**--------------------------------------------------------------------------*/
void WriteEEPROMByte( unsigned int Address, char Data ) {   

    while (EECR & (1<<EEWE))     // Wait until ready
        ;
    EEAR = Address;
    EEDR = Data;
    EECR |= (1 << EEMWE) ;       // Don't use SetBit macrod due to timing
    EECR |= (1 << EEWE) ;        // Don't use SetBit macrod due to timing
}

