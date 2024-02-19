/****************************************************************************************
/ Init the project
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
#include "constants.h"
#include "externals.h"
#include "inavr.h"
#include "string.h"

/*
**===========================================================================
** Init the system according to board type
**===========================================================================
*/
void InitSystem(void) {


    Init_CPU();                         // init all processes
    Init_IO();
    Init_TMR();
    Init_USART( SPEED) ;              // Init uarts
}

/*
**===========================================================================
** Init the CPU related registers
**===========================================================================
*/
void Init_CPU(void) {
    __disable_interrupt();

    EIMSK = 0x00;        // External interrupt mask register
    EICRA = 0x00;       // External interrupt control register Int 0/1 on low level
    EICRB = 0x00;        // External interrupt control register Int 0/1 enabled
    EIMSK = 0x00;        // External interrupt mask register
    MCUCR = 0x00;        // MCU control register  External Ram + wait state
    XMCRA = 0x00;       // maximum wait states
    XMCRB = 0x00;       // Full 16 bit bus + bus keeper
    SREG  = 0x00;        // glabal interrupt

    ResetStatus = MCUCR;       // Remember reset source
    MCUCR = 0x00;              // and reset
    /*--- Initialize buffer ---*/
    // enable bootloader interrupt HKim code
    char temp = MCUCR;
    MCUCR = temp | (1 << IVCE);       // enable change of interrupt vectors
    MCUCR = temp | (1 << IVSEL);      // move inerrupt vectors to boot flash section

}

/*
**===========================================================================
** Init the watchdog registers
**===========================================================================
*/
__monitor void Init_Watchdog(void) {

    asm("WDR");                             // kick the dog!!
    WDTCSR = 0x0f;
    asm("WDR");                             // kick the dog!!

}

/*
**===========================================================================
** Init the IO related registers
**===========================================================================
*/
void Init_IO(void) {
#if ANZBANA_V8 == 1
    DDRA    =  0x00 ;      // Port A data direction, bit 0, 4-7 out
    PORTA   =  0x3;
    UnitID  = PINA & 0x03;       //get the unit ID
#else
    DDRB    =  0x00 ;      // Port B data direction, bit 0, 4-7 out
//    PORTB   =  0xc;
    UnitID  = (PINB >> 2)& 0x03;       //get the unit ID
#endif
    DDRA   =  0x00;      // Port A data
    PORTA  =  0x00;      // Port A data
    DDRB   =  0x00;      // Port B data
    PORTB  =  0xC0;      // Port B data
    DDRC   =  0x00;      // Port C data
    PORTC  =  0x00;      // Port C data
    DDRD   =  0x00;      // Port D data
    PORTD  =  0xf0;      // Port D data  //pullup addr
    DDRE   =  0x0E;      // Port E data bit 7-4 Address in, Bit 3 -1 out, bit 0 rxd in
    PORTE  =  0x00;      // Port E data
    DDRF   =  0x00;      // Port F data
    PORTF  =  0x00;      // Port F data
    DDRG   =  0x00;      // Port G data
    PORTG  =  0x00;      // Port G data
}

/*
**===========================================================================
** Init the timer related registers
**===========================================================================
*/
void Init_TMR(void) {
    switch (UnitID) {
    case AN_ZB485:                  // AN-ZB485
        // 128 -> 1281
        // TIM0 and TIM2 are swapped in 1281.
        // Registers are completely changed.
        // TCCR0   =  0x99 ;      // Timer control register 0
        // OCR0    =  3;         // Timer output compare register 0, 2MHZ //16MHz xtal
        //
        // TCCR2A : 0 1 0 0 - - 1 0
        // TCCR2B : 1 0 - - 0 0 0 1
        //
        // COM2A1 COM2A0 : 0 1
        // COM2B1 COM2B0 : 0 0
        // WGM21 WGM20   : 1 0
        // FOC2A : 1, FOR2B : 0, WGM22 : 0, CS2/1/0 : 0 0 1
        //
        // COM2A : Toggle
        // WGM : CTC
        // Clock Scale: 1

        TCCR2A = 0x42;
        TCCR2B = 0x81;
        OCR2A = 3;
        break;
    case AN_ZBANA:                  // AN-ZBANA
        // 128 -> 1281
        // TCCR0   =  0x99 ;      // Timer control register 0
        // OCR0    =  7 ;         // Timer output compare register 0, 1MHZ //16MHz xtal
        TCCR2A = 0x42;
        TCCR2B = 0x81;
        OCR2A = 7;
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
void Init_USART( unsigned long baud ) {

    /*--- Configure UART data block ---*/
    myUART.TxFirst   = 0x00;
    myUART.TxLast    = 0x00;
    myUART.TxCount   = 0x00;
    myUART.RxFirst   = 0x00;
    myUART.RxLast    = 0x00;
    myUART.RxCount   = 0x00;
    myUART.RxState   = SYNC;
    myUART.SyncCnt   = 0 ;
    myUART.TxStatus  = 0x00;

    myUART.RxTimeout = RX_TO_TIME ;   // reset timeout
    UCSR0A  = 0x00; 
    UBRR0L  = ((XTAL_CPU / 16 / baud )-1) & 0xff;
    UBRR0H  = (((XTAL_CPU / 16 / baud )-1)>> 8) & 0xff;
    UCSR0B  = (1<<RXEN0) | (1<<TXEN0);        // Enable recieve and transmit
    UCSR0C  = 0x06;       /* n,8,1 */
}

