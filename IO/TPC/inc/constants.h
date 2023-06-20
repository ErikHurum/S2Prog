/****************************************************************************
 **             - constants.h -
 **
 **
 ***************************************************************************/

#define __BIT_MASK(A) (1<<(A))
//#define SetBit( SFR, MASK ) OS_IncDI(); (SFR) |=  (MASK); OS_DecRI() 
//#define ClrBit( SFR, MASK ) OS_IncDI(); (SFR) &= ~(MASK); OS_DecRI() 
#define SetBit( SFR, MASK ) (SFR) |=  (MASK)
#define ClrBit( SFR, MASK ) (SFR) &= ~(MASK)

#define true              1 
#define false             0 

//  XTal frequences
#if (OS_UART != 0)                  // AStmark Use Eval board for test!
#define XTAL_CPU      16000000L     // Frequency of CPU Xtal
#else
#define XTAL_CPU       3686400L     // Frequency of CPU Xtal (Eval. board)
#endif

#define PROGTYPE_BOOT   0                // Boot program
#define PROGTYPE_APP    1                // Application program

#define TPC140_LOC      0x00            // Unit ID for TPC140
#define TPC140          0x10            // Old ID for TPC140
#define TPC350_LOC      0x01            // Unit ID for TPC350
#define TPC350          0x00            // Old ID for TPC350
#define TPC196_LOC      0x02            // Unit ID for TPC196
#define TPC196          0x01            // Old ID for TPC196

#define TPC140_DEF_ADDR  31            // Default address for TPC140
#define TPC350_DEF_ADDR  30            // UDefault address for TPC350
#define TPC196_DEF_ADDR  32            // Default address for TPC196

#define PI              3.141592654
#define RAD_FACTOR      (180/PI)       // 57.29577951

#define WATCHDOGTIME      15            // seconds before timeout (max. 255 seconds)
#define WD_USART0          0x01          // Task USART0
#define WD_Disp_Handler    0x02           // Task DisplayHandler
#define WD_Disp_Blink      0x04           // Task DisplayBlink
#define WD_Disp_Info       0x08           // Task Info

#define PACKED_DATA_SIZE	40		// length of packed data

// display constants
#define WIDE_CHAR			  0		    // wide character definition
#define TINY_CHAR			  1		    // tiny character definition
#define NO_OF_VT			  100	  // number of value set
#define ALARM_VT			  0		    // alarm value set
#define NO_OF_LOCH			7		    // number of char in low disp
#define NO_OF_LOGR			21		  // number of char in lo graph disp
#define SEVEN_SEG			2		      // 7-seg character definition
#define NO_OF_XDISP			5		    // number of x displays
#define NO_OF_XCH			5		      // number of char in x disp
#define NO_OF_HICH			4		    // number of char in high disp
#define SECBARUSED			0x10	  // Second bar used 


//Alarm Status 

#define ALARM_LED     0x10      // Bit 4 on PortG
#define	ALARM_OFF		  0x00
#define	ALARM_ON		  0x01
#define	ALARM_FLASH		0x02

#define TX_SENDOK			0x01
#define ALARM_SEND		0x02 
#define ALARM_TO_TX		0x04


// UART buffer size
#define TXSIZE_UART       150       /* TX buffer size */
#define RXSIZE_UART       255       /* RX buffer size */


//AN_PRO1 definitions
//See ANPRO1Const.h

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


