/****************************************************************************************
/ Init the project
/
***************************************************************************************/
#include "iom128.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"
#include "inavr.h"
#include "string.h"

/*
**===========================================================================
** Init the system according to board type
**===========================================================================
*/ 
void InitSystem(void) {

    char UnitIDtemp;

    DDRB    =  0x00 ;      // Port B data direction, bit 0, 4-7 out
//    PORTB   =  0xc;
#if (OS_UART == 0)
    UnitIDtemp = TPC140_LOC; //AStmark  for test
#else
    UnitIDtemp  = (PINB >> 2)& 0x03;       //get the unit ID
#endif
 
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


//#if (OS_UART == 0)
//    UnitID = TPC140; //AStmark  for test
//#endif

    Init_CPU();                         // init all processes
    Init_IO();
    Init_TMR() ;
#if (OS_UART != 0)
    Init_USART(0, 9600) ;              // 
#endif
    Init_Values();                      // init the values in the system

}

/*
**===========================================================================
** Init the CPU related registers
**===========================================================================
*/ 
void Init_CPU( void ) {

    __disable_interrupt();

    /*--- Configure CPU and interrupts ---*/
    switch (UnitID) {
    case TPC140:                  // TPC140
    case TPC196:                  // TPC196
        EIMSK = 0x00 ;        // External interrupt mask register, all off
        EICRA = 0xAA ;        // External interrupt control register, faling
        EICRB = 0xAA ;        // External interrupt control register, falling edge 
        EIMSK = 0xF0 ;        // External interrupt mask register, int 4 - 7 on 
        break;
    }
    MCUCR = 0x00 ;        // MCU control register  External Ram + wait state
    XMCRA = 0x00 ;       // maximum wait states
    XMCRB = 0x07 ;       // Full portC + bus keeper
    SREG  = 0x80 ;        // global interrupt
    XDIV  = 0x00 ;     // Init valuse used 0x00


    RestartStatus = MCUCSR;       // Remember reset source
    MCUCSR = 0x00;              // and reset
    /*--- Initialize buffer ---*/
    WriteCount = 0;

}

/*
**===========================================================================
** Init the watchdog registers
**===========================================================================
*/ 
__monitor void Init_Watchdog( void ) {

    asm("WDR");                             // kick the dog!!
    WDTCR = 0x0f;                           // 2.1 sec
    asm("WDR");                             // kick the dog!!

}

/*
**===========================================================================
** Init the IO related registers
**===========================================================================
*/ 
void Init_IO( void ) {

    /*--- Initialize the data registers, output value and input pullup ---*/
    switch (UnitID) {
    case TPC140:                  // TPC140  
        DDRA   =  0xff ;      // Port A data direction, all out
        PORTA  =  0x00 ;      // Port A data
        DDRB   =  0x00 ;      // Port B data direction, all in
        PORTB  =  0x06 ;      // Port B data pullup on bit 2 and 3   
        DDRC   =  0xff ;      // Port C data direction, all out
        PORTC  =  0x00 ;      // Port C data
        DDRD   =  0xff ;      // Port D data direction, all out
        PORTD  =  0xfe ;      // Port D data 1-7 high, 0 low
        DDRE   =  0x04 ;      // Port E data direction, PE2out
        PORTE  =  0xfb ;      // Port E data pullup
        DDRF   =  0x00 ;      // Port F data direction, all in
        PORTF  =  0xff ;      // Port F data pullup
        DDRG   =  0xff ;      // Port G data direction, all out
        PORTG  =  0x00 ;      // Port G data 
        break;
    case TPC196:                  // TPC196 
        DDRA   =  0xff ;      // Port A data direction, all out
        PORTA  =  0x00 ;      // Port A data
        DDRB   =  0x80 ;      // Port B data direction, 0-6 inm 7 out
        PORTB  =  0x06 ;      // Port B data pullup on bit 2 and 3   
        DDRC   =  0xff ;      // Port C data direction, all out
        PORTC  =  0x00 ;      // Port C data
        DDRD   =  0xff ;      // Port D data direction, all out
        PORTD  =  0xfe ;      // Port D data 1-7 high, 0 low
        DDRE   =  0x04 ;      // Port E data direction, PE2out
        PORTE  =  0xfb ;      // Port E data pullup
        DDRF   =  0x00 ;      // Port F data direction, all in
        PORTF  =  0xff ;      // Port F data pullup
        DDRG   =  0xff ;      // Port G data direction, all out
        PORTG  =  0x00 ;      // Port G data 
        break;
    default:
        break;
    }    
}

/*
**===========================================================================
** Init the timer related registers
**===========================================================================
*/ 
void Init_TMR( void ) {
    /*--- Timer control (disable clock inputs) ---*/

    switch (UnitID) {
    case TPC140:                  // TPC140
    case TPC196:                  // TPC196
        TCCR0   =  0x89 ;      // Timer control register 0 
        OCR0    =  3;         // Timer output compare register 0, 2MHZ //16MHz xtal
        break;
    default:
        break;
    }

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
        UCSR0B  = 0xb8;       /* tx/ rx enable, int udre/rxon */
        UCSR0C  = 0x06;       /* n,8,1 */
        break;
    default:
        break ;
    }    
}

/*
**===========================================================================
** Init values  in the system
**===========================================================================
*/ 
void Init_Values(void) {

    int i;
    
    for (i = 0; i < PACKED_DATA_SIZE; i++) {  //copy data from eeprom to ram
      packed_data[i] = ReadEEPROMByte(EEPROM_EEPROMDATA +i);
    }
 /* AStmark unused so far
    CharToAscii(MyPriAddress, &Disp.lo_data[0][0]);
    CharToAscii(MySecAddress, &Disp.lo_data[0][3]);
    Disp.lo_data[0][0] = 5 ;                         // four char to disp

    CharToAscii((char) PROG_VERSION, &Disp.x_data[0][0]);
    Disp.x_data[0][0] = 2 ;                          // four char to disp

    Disp.hi_data[0][0] = 4 ;                         // four char to disp
    Disp.hi_data[0][1] = 'V' ;                       // version
    CharToAscii((char) PROG_VERSION, &Disp.hi_data[0][2]) ;
*/

}
