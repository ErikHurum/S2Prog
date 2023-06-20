/****************************************************************************************
/ Init the project
/
***************************************************************************************/
#include "iom1280.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"
#include "inavr.h"
#include "string.h"

#include "hart_gpio.h"
#include "hart.h"

/*
**===========================================================================
** Init the system according to board type
**===========================================================================
*/
void InitSystem(void) {
    // UnitID = AN_ZBANA; //EHSMark AN_ZBHART;                   // 0x02: ZBHART

    UnitID  = (PINB >> 2) & 0x03;          //get the unit ID
    Init_CPU();                           // init all processes
    Init_IO();
    Init_TMR();
#if (OS_UART != 0)
    Init_USART(38400);                // only 1 My485UART to TCU on ZBHART
#endif
    //Init_AD();
    Init_Values();                        // init the values in the system

    //ADCSRA |= 0x40 ;                    //start the AD convertion
}

/*
**===========================================================================
** Init the CPU related registers
**===========================================================================
*/
void Init_CPU(void) {

    __disable_interrupt();

    MCUCR = 0x00;        // MCU control register wait state
    EIMSK = 0x00;        // External interrupt mask register , all off
    EICRA = 0xAA;        // External interrupt control register, o on faling edge
    EICRB = 0xAA;        // External interrupt control register
    EIMSK = 0x01;        // External interrupt mask register, int 0 on

    XMCRA = 0x00;        // maximum wait states
    XMCRB = 0x07;        // Full portC + bus keeper
    SREG  = 0x80;        // global interrupt
    //XDIV  = 0x00 ;      // Init valuse used 0x00v XXX

    RestartStatus = MCUCR;       // Remember reset source
    MCUCR = 0x00;              // and reset

    /*--- Initialize buffer ---*/
    WriteCount = 0;
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
    /*--- Initialize the data registers, output value and input pullup ---*/
    switch ( UnitID ) {
    case AN_ZB485:                  // AN-ZB485
    case AN_ZBANA:                  // AN-ZBANA
        break;
    case AN_ZBHART:
        DDRF      =  0x00;      // Port F data direction, used for ADC
        PORTF     =  0x00;      // Port F data
        // Port K initialization
        // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
        DDRK=(0<<DDK7) | (0<<DDK6) | (1<<DDK5) | (1<<DDK4) | (0<<DDK3) | (0<<DDK2) | (1<<DDK1) | (1<<DDK0);
        // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T Pullup
        PORTK=(1<<PORTK7) | (0<<PORTK6) | (0<<PORTK5) | (0<<PORTK4) | (1<<PORTK3) | (1<<PORTK2) | (0<<PORTK1) | (0<<PORTK0);
        // ADC initialization
        // ADC Clock frequency: 125,000 kHz
        // ADC Voltage Reference: AVCC pin
        // ADC Auto Trigger Source: ADC Stopped
        // Digital input buffers on ADC0: On, ADC1: On, ADC2: On, ADC3: On
        // ADC4: On, ADC5: On, ADC6: On, ADC7: On
        DIDR0=(0<<ADC7D) | (0<<ADC6D) | (0<<ADC5D) | (0<<ADC4D) | (0<<ADC3D) | (0<<ADC2D) | (0<<ADC1D) | (0<<ADC0D);
        // Digital input buffers on ADC8: On, ADC9: On, ADC10: On, ADC11: On
        // ADC12: On, ADC13: On, ADC14: Off, ADC15: On
        DIDR2=(0<<ADC15D) | (1<<ADC14D) | (0<<ADC13D) | (0<<ADC12D) | (0<<ADC11D) | (0<<ADC10D) | (0<<ADC9D) | (0<<ADC8D);
        //ADMUX=ADC_VREF_TYPE;
        ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
        ADCSRB=(0<<MUX5) | (0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);
        hart_gpio_init();
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
void Init_TMR(void) {
    /*--- Timer control (disable clock inputs) ---*/

    switch ( UnitID ) {
    case AN_ZB485:                  // AN-ZB485
    case AN_ZBANA:                  // AN-ZBANA
        break;
    case AN_ZBHART:
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
void Init_USART(unsigned long baud) {


    /*--- Configure My485UART data block ---*/
    My485UART.TxFirst   	    = 0x00;
    My485UART.TxLast    	    = 0x00;
    My485UART.TxCount   	    = 0x00;
    My485UART.TxId        	    = 0x00;
    My485UART.TxAddress   	    = 0x00;
    My485UART.RxCount   	    = 0x00;
    My485UART.TxStatus  	    = 0x00;
    My485UART.SequenceNumber    = 0x00;

    UCSR0A  = 0x00;
    UBRR0L  = ((XTAL_CPU / 16 / baud) - 1) & 0xff;
    UBRR0H  = (((XTAL_CPU / 16 / baud) - 1) >> 8) & 0xff;
    // why the fuck do you enalbe UDRE here you stupid fucktard!!! -hkim-
    //UCSR0B  = 0xb8;                                       /* tx/ rx enable, int udre/rxon */
    //UCSR0B  &= 0x07;  //  Disable Tx,TxE, Rx at startup 0x98;                                       /* tx/ rx enable, int udre/rxon */
    //UCSR0B  = 0x98;                                       /* tx/ rx enable, int udre/rxon */
    UCSR0C  = 0x06;                                       /* n,8,1 */
}


/*
**===========================================================================
** Init values  in the system
**===========================================================================
*/
void Init_Values(void) {
}
