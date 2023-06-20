/****************************************************************************
 **             - constants.h -
 **
 **
 ***************************************************************************/

#define __BIT_MASK(A) (1<<(A))
#define SetBit( SFR, MASK ) OS_IncDI(); (SFR) |=  (MASK); OS_DecRI()                                     // en able int

#define ClrBit( SFR, MASK ) OS_IncDI(); (SFR) &= ~(MASK); OS_DecRI() 

#define true              1 
#define false             0 

//  XTal frequences
#if (OS_UART != 0)                  // AStmark Use Eval board for test!
#define XTAL_CPU      16000000L     // Frequency of CPU Xtal
#else
#define XTAL_CPU       3686400L     // Frequency of CPU Xtal (Eval. board)
#endif

#define RS485UART0  (0x2200 + 0x08)         // Address to uart0
#define RS485UART1  0x2200                  // Address to uart1

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

// UART buffer size
#define TXSIZE_UART       275       /* TX buffer size */
#define RXSIZE_UART       150       /* RX buffer size */
#define TXSIZE_UART_16552  60       /* TX buffer size PC16552  */
#define RXSIZE_UART_16552 120       /* RX buffer size PC16552  */

// PC16552 #0 register definition
// DLAB = 0
#define U0_RBR       (*(volatile char *) (RS485UART0 + 0))       // Reseive buffer
#define U0_THR       (*(volatile char *) (RS485UART0 + 0))       // Transmitt buffer
#define U0_IER       (*(volatile char *) (RS485UART0 + 1))       // Interrupt enable register
#define U0_IIR       (*(volatile char *) (RS485UART0 + 2))       // Interrupt ident. reg
#define U0_FCR       (*(volatile char *) (RS485UART0 + 2))       // FIFO control register
#define U0_LCR       (*(volatile char *) (RS485UART0 + 3))       // Line control register
#define U0_MCR       (*(volatile char *) (RS485UART0 + 4))       // Modem Control register
#define U0_LSR       (*(volatile char *) (RS485UART0 + 5))       // Line status register
#define U0_MSR       (*(volatile char *) (RS485UART0 + 6))       // Modem status register
#define U0_SCR       (*(volatile char *) (RS485UART0 + 7))       // Scratch register
// DLAB = 1
#define U0_DLL       (*(volatile char *) (RS485UART0 + 0))       // Divisor latch LS
#define U0_DLM       (*(volatile char *) (RS485UART0 + 1))       // Divisor latch MS
#define U0_AFR       (*(volatile char *) (RS485UART0 + 2))       // Alternative function register

// PC16552 #1 register definition
// DLAB = 0
#define U1_RBR      (*(volatile char *)(RS485UART1 +0))       // Reseive buffer
#define U1_THR      (*(volatile char *)(RS485UART1 +0))       // Transmitt buffer
#define U1_IER      (*(volatile char *)(RS485UART1 +1))       // Interrupt enable register
#define U1_IIR      (*(volatile char *)(RS485UART1 +2))       // Interrupt ident. reg
#define U1_FCR      (*(volatile char *)(RS485UART1 +2))       // FIFO control register
#define U1_LCR      (*(volatile char *)(RS485UART1 +3))       // Line control register
#define U1_MCR      (*(volatile char *)(RS485UART1 +4))       // Modem Control register
#define U1_LSR      (*(volatile char *)(RS485UART1 +5))       // Line status register
#define U1_MSR      (*(volatile char *)(RS485UART1 +6))       // Modem status register
#define U1_SCR      (*(volatile char *)(RS485UART1 +7))       // Scratch register
// DLAB = 1
#define U1_DLL      (*(volatile char *)(RS485UART1 +0))       // Divisor latch LS
#define U1_DLM      (*(volatile char *)(RS485UART1 +1))       // Divisor latch MS
#define U1_AFR      (*(volatile char *)(RS485UART1 +2))       // Alternative function register

//UART PC16552 refister definition
#define DTR              0x01       // Data terminal ready bit
#define RTS              0x02       // request to send bit
#define OUT1             0x04       // Out 1 bit 

#define DATA_READY       0x01       // Data available in RX buffer

#define FIFO_TX_BUFSIZE   16        // TX buffer size
#define MAX_16552_FAIL    8         // two faults on all 4 channels
#define POWER_ON_CNT      5         // 0.5 * POWER_ON_CNT = 2.5 Sec off time on power
#define UART_START_DELAY 6000       // delay before starting com to target after power on

//AN_PRO1 definitions
#define MY_SGCNV_ADDR    253            // my address used for AN-SGCNV

//ANPRO10 definitions for internal use, other moved to ..\..\Shared\Inc\Anpro10Const.h
#define SYNC		    0		/* rx mode syncing */
#define HEADER		    1		/* rx mode check header */
#define RECEIVE 	    2		/* rx mode receiving */
#define HANDLE   	   10		/* rx mode handling */
#define RX_TO_TIME	   250      	// Timeout on uart

#define MIN_PACK_LEN	    7           // Min lengt of Uart package  

#define FAILCNT_ERROR   5         // No of failcount before error
#define COMFAIL_BIT     1         // Bit in CardStatus for com failure

#define EEPROM_OK           0xFF
#define EEPROM_RESET        0xdb         // used for checking the EEPROM reset 
#define EEPROM_ID           0xbd        // marker for EEPROM, First byte in EEPROM
    // EEPROM addresses and packages length
#define EEPROM_ID_START     0                                  // Start pos for Key + version id of data
#define EEPROM_1ST_DATA     EEPROM_ID_START                    // 1.st data in EEPROM //AStmark
#define EEPROM_PORTSETUP    EEPROM_1ST_DATA + 2                 // Port setup in EEPROM Two bytes see ZB485 and ZBANA
#define EEPROM_OFFGAIN      EEPROM_PORTSETUP + 3                // Offset and gain
#define EEPROM_NEXTBYTE     EEPROM_OFFGAIN + 2048
#define EEPROM_STOP         EEPROM_NEXTBYTE + 1                 // Stop of data in EEPROM 

