/****************************************************************************************
/  Misc. routines
/
***************************************************************************************/
#ifdef __ATMEGA_1280__
#include	"iom1280.h"
#endif

#ifdef __AVR_ATmega1281__
#include	"iom1281.h"
#endif
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "inavr.h"
#include "string.h"

void WDT_Prescaler_Change(void)
{
    __disable_interrupt();
    __watchdog_reset();
    /* Start timed equence */
    WDTCSR |= (1<<WDCE) | (1<<WDE);
    /* Set new prescaler(time-out) value = 64K cycles (~0.5 s) */
    //WDTCSR = (1<<WDE) | (1<<WDP2) | (1<<WDP0);
    /* Set new prescaler(time-out) value = 256K cycles (~2.0 s) */
   // WDTCSR = (1<<WDE) | (1<<WDP2) | (1<<WDP1) | (1<<WDP0);
    /* Set new prescaler(time-out) value = 256K cycles (~2.0 s) */
    WDTCSR = (1<<WDE) | (1<<WDP3)| (1<<WDP2) | (1<<WDP1) | (1<<WDP0);


__enable_interrupt();
}

// ***************************************************************
void EEPROM_writeByte(unsigned int uiAddress, unsigned char ucData)
{
  // Wait for completion of previous write 
  while(EECR & (1<< EEPE));
  // Set up address and Data Registers 
  EEAR = uiAddress;
  EEDR = ucData;
  //  Write logical one to EEMPE (master write enable)
  EECR |= (1<< EEMPE);
  //  Start eeprom write by setting EEPE (write enable)
  EECR |= (1<< EEPE);
}
// ***************************************************************************************************
unsigned char EEPROM_readByte(unsigned int uiAddress)
{
  // Wait for completion of previous write */
  while(EECR & (1<< EEPE));
  // Set up address register */
  EEAR = uiAddress;
  // Start eeprom read by writing EERE */
  EECR |= (1<< EERE);
  // Return data from Data Register */
  return EEDR;
}

/*************************************************************************
*
*  Get my address
*
*************************************************************************/
char MyAddress(void) {
    //return 0;
    char Address = (~(PIND>>4) & 0x0f) ;
    return Address;
}
