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

   // DDRB    =  0x00 ;      // Port B data direction, bit 0, 4-7 out
    UnitID = AN_SGCNV;  // EHSMark, just for testing
    Init_IO();
//    PORTB   =  0xc;
   // UnitID  = (PINB >> 2)& 0x03;       //get the unit ID
#if (OS_UART == 0)
    UnitID = AN_SGCNV; //EHSMark for test
#endif

    Init_CPU();                         // init all processes
    //Init_IO();
    Init_TMR() ;
#if (OS_UART != 0)
    //Init_USART(0, 38400) ;              // 
#endif
   // Init_USART(1, 38400) ;              //    
    //Init_AD();
    Init_Values();                      // init the values in the system

    //ADCSR |= 0x40 ;                     //start the AD convertion
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
    case AN_SGCNV:                  // AN-ZBANA
        MCUCR = 0x00 ;        // MCU control register wait state
        EIMSK = 0x00 ;        // External interrupt mask register , all off
        EICRA = 0xAA ;        // External interrupt control register, o on faling edge
        EICRB = 0xAA ;        // External interrupt control register 
        //EIMSK = 0x01 ;        // External interrupt mask register, int 0 on EHSMark set later to 3 Tank cleaning
        EIMSK = 0x02 ;        // External interrupt mask register , all off
        break;
    }
    //XMCRA = 0x00 ;       // maximum wait states
    //XMCRB = 0x07 ;       // Full portC + bus keeper
    SREG  = 0x80 ;        // global interrupt
    // From page 372, ATMega128.pdf
    //asm("CLI");
    //XDIV  = 0x00 ;     // Init valuse used 0x00
    //asm("NOP");
    //asm("NOP");
    //asm("NOP");
    //asm("NOP");
    //asm("NOP");
    //asm("NOP");
    //asm("NOP");
    //asm("NOP");
    //asm("NOP");
    //asm("SEI");
    __no_operation();
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
    case AN_SGCNV:                  // AN-ZB485  
        DDRA   =  0x00 ;      // Port A data direction (in)
        PORTA  =  0xff ;      // Port A data, Pull up on all inputs
        DDRB   =  0xff ;      // Port B data direction, all bits output
        PORTB  =  0x10 ;      // Port B data set all outputs low except OC0, Bit 4 
        DDRC   =  0x00 ;      // Port C data direction, all out
        PORTC  =  0x00 ;      // Port C data, Pull up on all inputs
        DDRD   =  0xf8 ;      // Port D data direction, bit 0-2 is inputs, bit 1 : INT1
        PORTD  =  0x07 ;      // Port D data pullup on bit 0 - 2
        DDRE   =  0xDE ;      // Port E data direction, all out except rxd (0) and bit 5 (TCL)
        PORTE  =  0x21 ;      // Port E data pullup on bit 0 and 5
        DDRF   =  0x05 ;      // Port F data direction, bit  1 for LED, bit 4 - 7 for JTAG
        PORTF  =  0x00 ;      // Port F data 
        DDRG   =  0x1f ;      // Port G data direction, port 0,1,2,3, 4 out
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
    case AN_SGCNV:                  // AN-ZB485
        TCCR0   =  0x99 ;      // Timer control register 0 
        OCR0    =  1;         // Timer output compare register 0, 2MHZ //16MHz xtal
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
