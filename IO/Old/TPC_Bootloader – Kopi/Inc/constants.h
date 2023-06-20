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

#define PROGTYPE_BOOT   128                // Boot program offset to Prog version to detect bootloader

#define WATCHDOGTIME      15      // seconds before timeout (max. 255 seconds)

#define TPC140_LOC      0x00            // Unit ID for TPC140
#define TPC140          0x10            // Old ID for TPC140
#define TPC350_LOC      0x01            // Unit ID for TPC350
#define TPC350          0x00            // Old ID for TPC350
#define TPC196_LOC      0x02            // Unit ID for TPC196
#define TPC196          0x01            // Old ID for TPC196

#define TPC140_DEF_ADDR  31            // Default address for TPC140
#define TPC350_DEF_ADDR  30            // UDefault address for TPC350
#define TPC196_DEF_ADDR  32            // Default address for TPC196

// UART buffer size
#define TXSIZE_UART       350       /* TX buffer size */
#define RXSIZE_UART       350       /* RX buffer size */

//ANPRO10 definitions for internal use, other moved to ..\..\Shared\Inc\Anpro10Const.h
#define SYNC		    0		/* rx mode syncing */
#define HEADER		    1		/* rx mode check header */
#define RECEIVE 	    2		/* rx mode receiving */
#define HANDLE   	   10		/* rx mode handling */
#define RX_TO_TIME	   250      	// Timeout on uart

#define MIN_PACK_LEN	    7           // Min lengt of Uart package  

#define EEPROM_OK           0xFF
#define EEPROM_RESET        0xdb         // used for checking the EEPROM reset 
#define EEPROM_ID           0xbd        // marker for EEPROM, First byte in EEPROM
    // EEPROM addresses and packages length
#define EEPROM_ID_START     0                                  // Start pos for Key + version id of data
#define EEPROM_1ST_DATA     EEPROM_ID_START                    // 1.st data in EEPROM //AStmark
#define EEPROM_PRI_ADDR     EEPROM_1ST_DATA + 1                 // Primary address ( normal 31)
#define EEPROM_SEC_ADDR     EEPROM_PRI_ADDR + 1                 // Secondary address
#define EEPROM_EEPROMDATA   EEPROM_SEC_ADDR + 1                 // EEpromdata old type
#define EEPROM_NEXTBYTE     EEPROM_EEPROMDATA + PACKED_DATA_SIZE
#define EEPROM_STOP         EEPROM_NEXTBYTE + 1                 // Stop of data in EEPROM 

// FLASH programming failure
#define FLASH_ERASE_OK      0                                  // Flash earse ok
#define FLASH_PROG_OK       0                                  // Flash programmed ok
#define FLASH_PROG_PAGEF    1                                  // Flash programmed page fault
#define FLASH_PROG_ERROR    2                                  // Flash compare error
#define FLASH_COPYL_OK      5                                   // Flash copy Low oart of block OK
