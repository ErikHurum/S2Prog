/****************************************************************************************
/ Init the project
/
***************************************************************************************/
#include "iom128.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "inavr.h"
#include "string.h"

/*
**===========================================================================
** Init the system according to board type
**===========================================================================
*/ 
void InitSystem(void) {

    char UnitIDtemp;
    DDRB   =  0x00 ;      // Port B data direction, bit 0, 4-7 out
    UnitIDtemp  = (PINB >> 2)& 0x03;       //get the unit ID
   
    Init_CPU();                         // init all processes
    Init_IO();
    Init_TMR() ;
    Init_USART(0, SPEED) ;              // Init uarts
    Init_USART(1, SPEED) ;              
     if (((ReadEEPROMByte(EEPROM_PRI_ADDR)) < 30) || ((ReadEEPROMByte(EEPROM_PRI_ADDR) > 45))) {
      switch (UnitIDtemp) {
        case TPC140_LOC:
          WriteEEPROMByte(EEPROM_PRI_ADDR, TPC140_DEF_ADDR);
          WriteEEPROMByte(EEPROM_SEC_ADDR, 0);
          break;
        case TPC350_LOC:
          WriteEEPROMByte(EEPROM_PRI_ADDR, TPC350_DEF_ADDR);
          WriteEEPROMByte(EEPROM_SEC_ADDR, 0);
          break;
        case TPC196_LOC:
          WriteEEPROMByte(EEPROM_PRI_ADDR, TPC196_DEF_ADDR);
          WriteEEPROMByte(EEPROM_SEC_ADDR, 0);
          break;
      }
    }
   
    switch (UnitIDtemp) {
      case TPC140_LOC:
        UnitID = TPC140;
        MyPriAddress = TPC140_DEF_ADDR;
        break;
      case TPC350_LOC:
        UnitID = TPC350;
        MyPriAddress = TPC350_DEF_ADDR;
        break;
      case TPC196_LOC:
        UnitID = TPC196;
        MyPriAddress = TPC196_DEF_ADDR;
        break;
    }
    MySecAddress = MyAddress() ;    // Get my address
}

/*
**===========================================================================
** Init the CPU related registers
**===========================================================================
*/ 
void Init_CPU( void ) {

    __disable_interrupt();

    EIMSK = 0x00 ;        // External interrupt mask register 
    EICRA = 0x00 ;       // External interrupt control register Int 0/1 on low level
    EICRB = 0x00 ;        // External interrupt control register Int 0/1 enabled
    EIMSK = 0x00 ;        // External interrupt mask register 
    MCUCR = 0x00 ;        // MCU control register  External Ram + wait state
    XMCRA = 0x00 ;       // maximum wait states
    XMCRB = 0x00 ;       // Full 16 bit bus + bus keeper
    SREG  = 0x00 ;        // glabal interrupt

    RestartStatus = MCUCSR;       // Remember reset source
    MCUCSR = 0x00;              // and reset
    /*--- Initialize buffer ---*/

}

/*
**===========================================================================
** Init the watchdog registers
**===========================================================================
*/ 
__monitor void Init_Watchdog( void ) {

    asm("WDR");                             // kick the dog!!
    WDTCR = 0x1f;
    WDTCR = 0x1f;
    asm("WDR");                             // kick the dog!!

}

/*
**===========================================================================
** Init the IO related registers
**===========================================================================
*/ 
void Init_IO( void ) {

    DDRA   =  0x00 ;      // Port A data 
    PORTA  =  0x00 ;      // Port A data
    DDRB   =  0x00 ;      // Port B data 
    PORTB  =  0x00 ;      // Port B data   
    DDRC   =  0x00 ;      // Port C data 
    PORTC  =  0x00 ;      // Port C data
    DDRD   =  0xff ;      // Port D data direction, all out
    PORTD  =  0xff ;      // Port D data 1-7 high, 0 low
    DDRE   =  0xFE ;      // Port E data direction, all out except rxd
    PORTE  =  0x00 ;      // Port E data 
    DDRF   =  0x00 ;      // Port F data 
    PORTF  =  0x00 ;      // Port F data 
    DDRG   =  0x10 ;      // Port G data 4 out, Alarm LED
    PORTG  =  0x00 ;      // Port G data 
}

/*
**===========================================================================
** Init the timer related registers
**===========================================================================
*/ 
void Init_TMR( void ) {
    /*--- Timer control (disable clock inputs) ---*/
    
    TCCR0   =  0x00 ;      // Timer control register 0 
    OCR0    =  57 ;        // Timer output compare register 0, 1000HZ //7.37MHz xtal
    TCCR1A  =  0x00 ;      // Timer control register 1A 
    TCCR1B  =  0x00 ;      // Timer control register 1B , divide by 256
    TCCR1C  =  0x00 ;      // Timer control register 1c , force outp. comp
    OCR1A   =  288 ;       // Timer output compare register 1A, 100 Hz //7.37MHz xtal
    TCCR2   =  0x00 ;      // Timer control register 2 
    OCR2    =  0x00 ;      // Timer output compare register 2 
    TCCR3A  =  0x00 ;      // Timer control register 3A 
    TCCR3B  =  0x00 ;      // Timer control register 3B , divide by 256
    TCCR3C  =  0x00 ;      // Timer control register 3c , force outp. comp
    OCR3AH  =  0x00 ;      // Timer output compare register 3C, 1 Hz //7.37MHz xtal
    OCR3AL  =  0x00 ;      // Timer output compare register 3C, 1 Hz
    ASSR    =  0x00 ;      // Asynchronous status register 
    TIMSK   =  0x00 ;      // Timer interrupt mask register, enable 16 bit 1A, 8Bit73
    ETIMSK  =  0x00 ;      // Timer interrupt mask register, enable 16 bit 3A
} 

/*
**===========================================================================
** Init the USARTs registers
**===========================================================================
*/ 
void Init_USART( char channel, unsigned long baud ) {

    /*--- Configure UART data block ---*/
    UART[channel].TxFirst   = 0x00;
    UART[channel].TxLast    = 0x00;
    UART[channel].TxCount   = 0x00;
    UART[channel].RxFirst   = 0x00;
    UART[channel].RxLast    = 0x00;
    UART[channel].RxCount   = 0x00;
    UART[channel].RxState   = SYNC;
    UART[channel].SyncCnt   = 0 ;
    UART[channel].TxStatus  = 0x00;

    switch (channel) {
    case 0x00 :          
        UART[channel].RxTimeout = RX_TO_TIME ;   // reset timeout
        UART[channel].pTxBuffer = TxBufferCh0;        
        UART[channel].pRxBuffer = RxBufferCh0;        
        UCSR0A  = 0x00; 
        UBRR0L  = ((XTAL_CPU / 16 / baud )-1) & 0xff;
        UBRR0H  = (((XTAL_CPU / 16 / baud )-1)>> 8) & 0xff;
        UCSR0B  = (1<<RXEN0) | (1<<TXEN0);        // Enable recieve and transmit
        UCSR0C  = 0x06;       /* n,8,1 */
        break;
    case 0x01 :
        UART[channel].RxTimeout = RX_TO_TIME ;   // reset timeout
        UART[channel].pTxBuffer = TxBufferCh1;
        UART[channel].pRxBuffer = RxBufferCh1;
        UCSR1A  = 0x00; 
        UBRR1L  = ((XTAL_CPU / 16 / baud )-1) & 0xff;
        UBRR1H  = (((XTAL_CPU / 16 / baud )-1)>> 8) & 0xff;
        UCSR1B  = (1<<RXEN1) | (1<<TXEN1);        // Enable recieve and transmit
        UCSR1C  = 0x06;       /* n,8,1 */
        break;
    default:
        break ;
    }    
}

