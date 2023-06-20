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

    DDRB    =  0x00 ;      // Port B data direction, bit 0, 4-7 out
//    PORTB   =  0xc;
    UnitID  = (PINB >> 2)& 0x03;       //get the unit ID
#if (OS_UART == 0)
    UnitID = 0x01;            //AStmark  for test Evalkort use ZBANA
#endif

    Init_CPU();                         // init all processes
    Init_IO();
    Init_TMR() ;
    Init_USART(0, 38400) ;              //
    Init_USART(1, 38400) ;              //
    Init_AD();
    Init_Values();                      // init the values in the system

    ADCSR |= 0x40 ;                     //start the AD convertion
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
    case AN_ZB485:                  // AN-ZB485
        EIMSK = 0x00 ;        // External interrupt mask register, all off
        EICRA = 0xAf ;        // External interrupt control register, 0,1 raising, rest faling
        EICRB = 0xAA ;        // External interrupt control register
        EIMSK = 0x03 ;        // External interrupt mask register, int 0 and 1 on
        break;
    case AN_ZBANA:                  // AN-ZBANA
        EIMSK = 0x00 ;        // External interrupt mask register , all off
        EICRA = 0xAA ;        // External interrupt control register, o on faling edge
        EICRB = 0xAA ;        // External interrupt control register
        EIMSK = 0x01 ;        // External interrupt mask register, int 0 on
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
    WDTCR = 0x0f;
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
    case AN_ZB485:                  // AN-ZB485
        DDRA   =  0xff ;      // Port A data direction (out), external bus
        PORTA  =  0x00 ;      // Port A data
        DDRB   =  0x10 ;      // Port B data direction, bit 0, 4-7 out
        PORTB  =  0x00 ;      // Port B data
        DDRC   =  0xff ;      // Port C data direction, all out
        PORTC  =  0x00 ;      // Port C data
        DDRD   =  0x00 ;      // Port D data direction, all in except output to osc and txd
        PORTD  =  0xff ;      // Port D data pullup on int fro AD
        DDRE   =  0xFE ;      // Port E data direction, all out except rxd
        PORTE  =  0xf0 ;      // Port E data
        DDRF   =  0x00 ;      // Port F data direction, used for ADC
        PORTF  =  0x00 ;      // Port F data
        DDRG   =  0x07 ;      // Port G data direction, port 1,2,3 out
        PORTG  =  0x03 ;      // Port G data
        break;
    case AN_ZBANA:                  // AN-ZBANA
        DDRA   =  0x00 ;      // Port A data direction in (not used)
        PORTA  =  0x00 ;      // Port A data
        DDRB   =  0xF1 ;      // Port B data direction, bit 0, 4-7 out
        PORTB  =  0x00 ;      // Port B data
        DDRC   =  0xFF ;      // Port C data direction, all out
        PORTC  =  0x00 ;      // Port C data
        DDRD   =  0x02 ;      // Port D data direction, all in except output to osc and txd
        PORTD  =  0xf1 ;      // Port D data pullup on int fro AD
        DDRE   =  0xFE ;      // Port E data direction, all out except rxd
        PORTE  =  0x00 ;      // Port E data
        DDRF   =  0x00 ;      // Port F data direction, used for ADC
        PORTF  =  0x00 ;      // Port F data
        DDRG   =  0x10 ;      // Port G data direction, bit 5 out
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
    case AN_ZB485:                  // AN-ZB485
        TCCR0   =  0x99 ;      // Timer control register 0
        OCR0    =  3;         // Timer output compare register 0, 2MHZ //16MHz xtal
        break;
    case AN_ZBANA:                  // AN-ZBANA
        TCCR0   =  0x99 ;      // Timer control register 0
        OCR0    =  7 ;         // Timer output compare register 0, 1MHZ //16MHz xtal
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
    case 0x01 :
        UART[channel].RxTimeout = RX_TO_TIME ;   // reset timeout
        UART[channel].pTxBuffer = TxBufferCh1;
        UART[channel].pRxBuffer = RxBufferCh1;
        UCSR1A  = 0x00;
        UBRR1L  = ((XTAL_CPU / 16 / baud )-1) & 0xff;
        UBRR1H  = (((XTAL_CPU / 16 / baud )-1)>> 8) & 0xff;
        UCSR1B  = 0xb8;       /* tx/ rx enable, int udre/rxon */
        UCSR1C  = 0x06;       /* n,8,1 */
        break;
    default:
        break ;
    }
}


/*
**===========================================================================
** Init the AD converter registers
**===========================================================================
*/
void Init_AD( void ) {

    char i;
    for (i = 0; i<8; i++) {                 // Init variables
        ADInt.Result[i] = 0;                   // convertion resluts
    }
    ADChannel = 0x00 ;                      // AD channel to be converted
    ADMUX   = 0xc0 ;                        // Ref = 2,56V, right adjust
    ADCSR   = 0x8f ;                        // AD enabled, int enabled, xtal / 128
}

/*
**===========================================================================
** Init values  in the system
**===========================================================================
*/
void Init_Values(void) {


}
