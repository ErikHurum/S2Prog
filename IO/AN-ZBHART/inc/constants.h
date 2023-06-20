/****************************************************************************
 **             - constants.h -
 **
 **
 ***************************************************************************/

#define __BIT_MASK(A) (1<<(A))
#define My_SetBitsOr( SFR, MASK ) OS_IncDI(); (SFR) |=  (MASK); OS_DecRI()                                     

#define My_ClrsBit( SFR, MASK ) OS_IncDI(); (SFR) &= ~(MASK); OS_DecRI() 

#define My_SetBitsAnd( SFR, MASK ) OS_IncDI(); (SFR) &= (MASK); OS_DecRI() 

#define My_SetBit( SFR, MASK ) OS_IncDI(); (SFR) |=  (MASK); OS_DecRI()                                     
#define My_ClrBit( SFR, MASK ) OS_IncDI(); (SFR) &= ~(MASK); OS_DecRI() 

#define true              1 
#define false             0 

//  XTal frequences
#if (OS_UART != 0)                  // AStmark Use Eval board for test!
#define XTAL_CPU      16000000L     // Frequency of CPU Xtal
#else
#define XTAL_CPU       3686400L     // Frequency of CPU Xtal (Eval. board)
#endif

#define RS485My485UART0  (0x2200 + 0x08)         // Address to My485UART0
#define RS485My485UART1  0x2200                  // Address to My485UART1

#define PROGTYPE_BOOT   0                // Boot program
#define PROGTYPE_APP    1                // Application program

#define AN_ZB485        0x00            // Unit ID for AN-ZB485
#define AN_ZBANA        0x01            // Unit ID for AN-ZBANA
#define AN_ZBHART       0x03            // XXX : FIXE IT WHATEVER YOU WANT
 
#define PI              3.141592654
#define RAD_FACTOR      (180/PI)       // 57.29577951

#define ADCLK             __BIT_MASK(0)   // PORTL bit 0 for AD clock
#define ADDO              __BIT_MASK(1)   // PORTL bit 1 for AD out
#define ADDI              __BIT_MASK(2)   // PORTL bit 2 for AD in

// My485UART buffer size
#define TXSIZE_UART       400       /* TX buffer size must be larger than HART_MAX_TX_BUFFER_SIZE */
#define RXSIZE_UART       150       /* RX buffer size */
#define MBUF_SIZE		  100

#define POWER_ON_CNT      5         // 0.5 * POWER_ON_CNT = 2.5 Sec off time on power
#define UART_START_DELAY 6000       // delay before starting com to target after power on


//ANPRO10 definitions for internal use, other moved to ..\..\Shared\Inc\Anpro10Const.h
#define SYNC		    0		/* rx mode syncing */
#define HEADER		    1		/* rx mode check header */
#define RECEIVE 	    2		/* rx mode receiving */
#define HANDLE   	   10		/* rx mode handling */
#define RX_TO_TIME	   250      	// Timeout on My485UART

#define MIN_PACK_LEN	    7           // Min lengt of My485UART package  

#define FAILCNT_ERROR   5         // No of failcount before error
#define COMFAIL_BIT     1         // Bit in CardStatus for com failure

#define EEPROM_OK           0xFF
#define EEPROM_RESET        0xdb         // used for checking the EEPROM reset 
#define EEPROM_ID           0xbd        // marker for EEPROM, First byte in EEPROM
    // EEPROM addresses and packages length
#define EEPROM_ID_START     0                                  // Start pos for Key + version id of data
#define EEPROM_1ST_DATA     EEPROM_ID_START                    // 1.st data in EEPROM //AStmark
#define EEPROM_PORTSETUP    EEPROM_1ST_DATA + 2                 // Port setup in EEPROM Two bytes see ZB485 and ZBANA
#define EEPROM_HART_SNS     EEPROM_PORTSETUP + 2                 // HART sensor setup in EEPROM Two bytes
#define EEPROM_OFFGAIN      EEPROM_HART_SNS  + 4                // Offset and gain
#define EEPROM_NEXTBYTE     EEPROM_OFFGAIN  + 2048
#define EEPROM_STOP         EEPROM_NEXTBYTE + 1                 // Stop of data in EEPROM 

#define UART0_EVENT_TX_COMPLETE 1
#define ZB_ERR_MODEM_0      1
#define ZB_ERR_MODEM_1      2
#define ZB_ERR_MODEM_2      3
#define ZB_ERR_UART         4
#define ZB_ERR_EXT_ADC      5
#define ZB_ERR_INT_ADC      6
#define ZB_REBOOT           7

#define NELEMENTS(array)		/* number of elements in an array */ \
		(sizeof (array) / sizeof ((array) [0]))

