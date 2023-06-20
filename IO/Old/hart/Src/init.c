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
	Init_USART(0, 38400);                // only 1 UART to TCU on ZBHART
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
	switch (UnitID) {
	case AN_ZB485:                  // AN-ZB485
		DDRA   =  0xff;      // Port A data direction (out), external bus
		PORTA  =  0x00;      // Port A data
		DDRB   =  0x10;      // Port B data direction, bit 0, 4-7 out
		PORTB  =  0x00;      // Port B data
		DDRC   =  0xff;      // Port C data direction, all out
		PORTC  =  0x00;      // Port C data
		DDRD   =  0x00;      // Port D data direction, all in except output to osc and txd
		PORTD  =  0xff;      // Port D data pullup on int fro AD
		DDRE   =  0xFE;      // Port E data direction, all out except rxd
		PORTE  =  0xf0;      // Port E data
		DDRF   =  0x00;      // Port F data direction, used for ADC
		PORTF  =  0x00;      // Port F data
		DDRG   =  0x07;      // Port G data direction, port 1,2,3 out
		PORTG  =  0x03;      // Port G data
		break;

	case AN_ZBANA:                  // AN-ZBANA
		DDRA   =  0x00;      // Port A data direction in (not used)
		PORTA  =  0x00;      // Port A data
		DDRB   =  0xF1;      // Port B data direction, bit 0, 4-7 out
		PORTB  =  0x00;      // Port B data
		DDRC   =  0xFF;      // Port C data direction, all out
		PORTC  =  0x00;      // Port C data
		DDRD   =  0x02;      // Port D data direction, all in except output to osc and txd
		PORTD  =  0xf1;      // Port D data pullup on int fro AD
		DDRE   =  0xFE;      // Port E data direction, all out except rxd
		PORTE  =  0x00;      // Port E data
		DDRF   =  0x00;      // Port F data direction, used for ADC
		PORTF  =  0x00;      // Port F data
		DDRG   =  0x10;      // Port G data direction, bit 5 out
		PORTG  =  0x00;      // Port G data
		break;

	case AN_ZBHART:
        DDRF      =  0x00 ;      // Port F data direction, used for ADC
		PORTF     =  0x00 ;      // Port F data 
		//DDRK      =  0xC0;     // Port K data direction, port 6,7 out
		PORTK     =  0x00;       // Port K data
		// Set up AD converter
		ADChannel = 0x0e;
		ADMUX     &= 0xe0 ;                           // set the channel
		ADMUX     |= ADChannel ;
        //as ADC0 is being used we can leave the ADMUX register as default (i.e. 0)
        ADCSRA    |= (1 << ADATE);  // this starts the conversion which is auto triggered
        ADCSRB    &= 0xF8;          // (1 << ADTS2) | (0 << ADTS1) | (0 << ADTS0); // triggered using timer/counter0 overflow
        ADCSRA    |= (1 << ADEN);   // this enables the ADC
        ADCSRA    |= (1 << ADIE);   // enables completion interrupt
		TIFR1 = 1;
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

	switch (UnitID) {
	case AN_ZB485:                  // AN-ZB485
		TCCR0A  =  0x99;             // Timer control register 0
		OCR0A   =  3;                 // Timer output compare register 0, 2MHZ //16MHz xtal
		break;

	case AN_ZBANA:                  // AN-ZBANA
		TCCR0A  =  0x99;             // Timer control register 0
		OCR0A    =  7;               // Timer output compare register 0, 1MHZ //16MHz xtal
		break;

	case AN_ZBHART:
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
void Init_USART(char channel, unsigned long baud) {


	/*--- Configure UART data block ---*/
	UART[channel].TxFirst   	= 0x00;
	UART[channel].TxLast    	= 0x00;
	UART[channel].TxCount   	= 0x00;
	UART[channel].TxId        	= 0x00;
	UART[channel].TxAddress   	= 0x00;
	UART[channel].RxCount   	= 0x00;
	UART[channel].TxStatus  	= 0x00;
	UART[channel].SequenceNumber= 0x00;
	
	UART[channel].Channel   = channel;

	switch (channel) {
	case 0x00 :
		OS_CreateMB( &UART[channel].RxMailBox, 1, MBUF_SIZE, MailBufCh0);
		UART[channel].pTxBuffer = TxBufferCh0;
		UART[channel].pRxBuffer = RxBufferCh0;
		UCSR0A  = 0x00;
		UBRR0L  = ((XTAL_CPU / 16 / baud) - 1) & 0xff;
		UBRR0H  = (((XTAL_CPU / 16 / baud) - 1) >> 8) & 0xff;
		// why the fuck do you enalbe UDRE here you stupid fucktard!!! -hkim-
		//UCSR0B  = 0xb8;                                       /* tx/ rx enable, int udre/rxon */
		UCSR0B  = 0x98;                                       /* tx/ rx enable, int udre/rxon */
		UCSR0C  = 0x06;                                       /* n,8,1 */
		break;
	case 0x01 :
	default:
		break;
	}
}


/*
**===========================================================================
** Init values  in the system
**===========================================================================
*/
void Init_Values(void) {
}
