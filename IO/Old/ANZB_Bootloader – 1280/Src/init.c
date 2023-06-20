/****************************************************************************************
/ Init the project
/
***************************************************************************************/
//#include "iom1280.h"
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

    DDRB   =  0x00 ;      // Port B data direction, bit 0, 4-7 out
    UnitID  = (PINB >> 2) & 0x03;          //get the unit ID
   
    Init_CPU();                         // init all processes
    Init_IO();
    Init_TMR() ;
    Init_USART(38400) ;              // Init uarts
    //Init_USART(1, SPEED) ;              

}

/*
**===========================================================================
** Init the CPU related registers
**===========================================================================
*/ 
static void Init_CPU( void ) {
  unsigned char temp;
  __disable_interrupt();

    EIMSK = 0x00 ;        // External interrupt mask register 
    EICRA = 0x00 ;       // External interrupt control register Int 0/1 on low level
    EICRB = 0x00 ;        // External interrupt control register Int 0/1 enabled
    EIMSK = 0x00 ;        // External interrupt mask register 
    MCUCR = 0x00 ;        // MCU control register  External Ram + wait state
    XMCRA = 0x00 ;       // maximum wait states
    XMCRB = 0x00 ;       // Full 16 bit bus + bus keeper
    SREG  = 0x00 ;        // glabal interrupt

  // ResetStatus = MCUCR;       // Remember reset source
  MCUCR = 0x00;              // and reset
    /*--- Initialize buffer ---*/

  // enable bootloader interrupt
  temp = MCUCR;
  MCUCR = temp | (1 << IVCE);       // enable change of interrupt vectors
  MCUCR = temp | (1 << IVSEL);                             // move inerrupt vectors to boot flash section 
}

/*
**===========================================================================
** Init the watchdog registers
**===========================================================================
*/ 
/*
__monitor void
Init_Watchdog( void )
{
  asm("WDR");                             // kick the dog!!
  WDTCSR = 0x1f;
  WDTCSR = 0x1f;
  asm("WDR");                             // kick the dog!!

}
*/

/*
**===========================================================================
** Init the IO related registers
**===========================================================================
*/ 
static void Init_IO( void ) {

    DDRA   =  0x00 ;      // Port A data 
    PORTA  =  0x00 ;      // Port A data
    DDRB   =  0x00 ;      // Port B data 
    PORTB  =  0x00 ;      // Port B data   
    DDRC   =  0x00 ;      // Port C data 
    PORTC  =  0x00 ;      // Port C data
    DDRD   =  0x00 ;      // Port D data   
    PORTD  =  0xf0 ;      // Port D data  //pullup addr
    DDRE   =  0x0E ;      // Port E data direction, all out except rxd
    PORTE  =  0x00 ;      // Port E data 
    DDRF   =  0x00 ;      // Port F data 
    PORTF  =  0x00 ;      // Port F data 
    DDRG   =  0x00 ;      // Port G data 
    PORTG  =  0x00 ;      // Port G data 
}

/*
**===========================================================================
** Init the timer related registers
**===========================================================================
*/ 
void Init_TMR( void ) {
    /*--- Timer control (disable clock inputs) ---*/
    
    //TCCR0A  =  0x99;             // Timer control register 0
    //OCR0A    =  7;               // Timer output compare register 0, 1MHZ //16MHz xtal
    //
    // to provide ADC with 1 Mhz clock, OC3A (PE3) is connected to ADC clock
    //
    // we will use TC3 to generate 1 Mhz clock by setting
    //
    // 1) TCCR3A    : 01000000   = 0x40
    //    a) Bit 7:6,     COM3A1/COM3A0   :   01  - Toggle OC3A(PE3) on compare match
    //    b) Bit 5:2,     don't care. all zero
    //    c) Bit 1:0,     WGM31/WGM30     :   00 for CTC mode
    //
    // 2) TCCR3B    : 00001001 = 0x09
    //    a) Bit 7,       noise canceler. don't care. 0
    //    b) Bit 6,       edge select for input. don't care. 0
    //    c) Bit 5,       reserved, 0
    //    d) Bit 4:3,     WGM33/WGM32     : 01 for CTC mode with OCR3A as TOP
    //    e) Bit 2:0,     CS32/CS31/CS30  : Clock Select, 001 : 16 Mhz with no divider
    //
    // 3) OCR3A     : 7, compare match at 8 tick at 16 Mhz will generate 1 MHz Clock
    //
    //
    TCCR3A    = 0x40;
    TCCR3B    = 0x09;
    OCR3A     = 7;



} 

/*
**===========================================================================
** Init the USARTs registers
**===========================================================================
*/ 
void Init_USART(  unsigned long baud ) {
    UCSR0A  = 0x00; 
    UBRR0L  = ((XTAL_CPU / 16 / baud )-1) & 0xff;
    UBRR0H  = (((XTAL_CPU / 16 / baud )-1)>> 8) & 0xff;
    UCSR0B  = (1<<RXEN0) | (1<<TXEN0);        // Enable recieve and transmit
    UCSR0B  = 0x98;                                       /* tx/ rx enable, int udre/rxon */
    UCSR0C  = 0x06;       /* n,8,1 */


}


