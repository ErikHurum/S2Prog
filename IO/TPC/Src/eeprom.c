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
**  See how many date i remining
**
**--------------------------------------------------------------------------*/
char TestEEPROM( void ) {

    return WriteCount;
}

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
    OS_IncDI();
    EECR |= (1 << EERE) ;       // Don't use SetBit macrod due to timing
    OS_DecRI();

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
    OS_IncDI();
    EEAR = Address;
    EEDR = Data;
    EECR |= (1 << EEMWE) ;       // Don't use SetBit macrod due to timing
    EECR |= (1 << EEWE) ;        // Don't use SetBit macrod due to timing
    OS_DecRI();
}

/*---------------------------------------------------------------------------
**
**  Read a tring from the eeprom
**
**--------------------------------------------------------------------------*/
void ReadEEPROMBuffer( unsigned int Address, char Size, char *pData ) {   
    unsigned int Index;

    for ( Index = 0; Index < Size; Index++ ) {
        *pData++ = ReadEEPROMByte( Address + Index );
    }
}

/*---------------------------------------------------------------------------
**
**  Writ buffer to eeprom
**
**--------------------------------------------------------------------------*/
void WriteEEPROMBuffer( unsigned int Address, char Size, char *pData ) {   

    while (EECR & (1<<EEWE))     // Wait until ready
        ;
    OS_IncDI();
    pWriteBuffer = pData;
    WriteCount = Size;
    EEAR = Address ;
    EEDR = *pData ;
    pWriteBuffer++;
    RestoreStat = true;
    EECR |= (1 << EEMWE) ;       // Don't use SetBit macrod due to timing
    EECR |= (1 << EEWE) ;        // Don't use SetBit macrod due to timing
    EECR |= (1 << EERIE) ;       // Don't use SetBit macrod due to timing
    OS_DecRI();
}

/*---------------------------------------------------------------------------
**
**  Interrupt on EEPROM write
**
**--------------------------------------------------------------------------*/
#pragma vector=EE_RDY_vect
__interrupt void IntHandler_EEPROM( void ){

    if ( --WriteCount ) {                        // More to write? 
        EEAR++;                                  // Define address and data 
        EEDR = *pWriteBuffer++;
        EECR |= (1 << EEMWE) ;       // Don't use SetBit macrod due to timing
        EECR |= (1 << EEWE) ;        // Don't use SetBit macrod due to timing
    } else {
        EECR &= ~(1 << EERIE) ;       // Don't use ClrBit macrod due to timing
        RestoreStat = false;
    }
}


/**===========================================================================
** Get the stored version in EEPROM
**==========================================================================*/ 
char EEPROMVersion(void) {
    char val ;
    char retval = false;

    ReadEEPROMBuffer(EEPROM_ID_START, 1, (char*)&val) ;
    if (val == EEPROM_ID) {                                     //correct EEPROM ID
        ReadEEPROMBuffer(EEPROM_ID_START+1, 1, (char*)&val) ;
        if (val == STORE_VERSION) {                             // and version
            ReadEEPROMBuffer(0xffe, 1, (char*)&val) ;
            if (val == EEPROM_OK) {                             // and no reset from user
                retval = true ;                                 // then everything is OK
            }
        }
    }
    return retval;
}

/**===========================================================================
** Reset the EEPROM
**==========================================================================*/ 
void EEPROMReset(void) {
    EEARL = (0x0ffe & 0xff);
    EEARH = (0x0ffe >> 8);
    EEDR = EEPROM_RESET;
    EECR |= (1<<EEMWE);
    EECR |= (1<<EEWE);
    while (EECR & (1<<EEWE))
        ;
    WDTCR = 0x18;               //Start watchdog to genetate restart
    WDTCR = 0x18;
}
