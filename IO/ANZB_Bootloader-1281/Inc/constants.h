/****************************************************************************
 **             - constants.h -
 **
 **
 ***************************************************************************/

#define __BIT_MASK(A) (1<<(A))
#define SetBit( SFR, MASK ) (SFR) |=  (MASK)
#define ClrBit( SFR, MASK ) (SFR) &= ~(MASK) 

#define true              1 
#define false             0 

#define XTAL_CPU      16000000L     // Frequency of CPU Xtal
//#define XTAL_CPU       3686400L     // Frequency of CPU Xtal (Eval. board)
#define TIMER_TICK_COUNT_FOR_1MS        250


#define PROGTYPE_BOOT   0                // Boot program
#define PROGTYPE_APP    1                // Application program

#define WATCHDOGTIME      15      // seconds before timeout (max. 255 seconds)

// myUART buffer size
#define TXSIZE_UART       350       /* TX buffer size */
#define RXSIZE_UART       350       /* RX buffer size */

//ANPRO10 definitions for internal use, other moved to ..\..\Shared\Inc\Anpro10Const.h
#define SYNC		    0		/* rx mode syncing */
#define HEADER		    1		/* rx mode check header */
#define RECEIVE 	    2		/* rx mode receiving */
#define HANDLE   	   10		/* rx mode handling */
#define RX_TO_TIME	   250      	// Timeout on myUART

#define MIN_PACK_LEN	    7           // Min lengt of myUART package  

#define EEPROM_OK           0xFF
#define EEPROM_RESET        0xdb         // used for checking the EEPROM reset 
#define EEPROM_ID           0xbd        // marker for EEPROM, First byte in EEPROM
    // EEPROM addresses and packages length
#define EEPROM_ID_START     0                                  // Start pos for Key + version id of data
#define EEPROM_1ST_DATA     EEPROM_ID_START                    // 1.st data in EEPROM //AStmark
#define EEPROM_STOP         EEPROM_1ST_DATA + 1                 // Stop of data in EEPROM 

// FLASH programming failure
#define FLASH_ERASE_OK      0                                  // Flash earse ok
#define FLASH_PROG_OK       0                                  // Flash programmed ok
#define FLASH_PROG_PAGEF    1                                  // Flash programmed page fault
#define FLASH_PROG_ERROR    2                                  // Flash compare error

#define AN_ZB485        0x00            // Unit ID for AN-ZB485
#define AN_ZBANA        0x01            // Unit ID for AN-ZBANA
#define AN_ZBHART       0x03            // XXX : FIXE IT WHATEVER YOU WANT


