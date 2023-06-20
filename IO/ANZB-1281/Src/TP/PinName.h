/*******************************************************

*
*     Program for signal convertion card, AN-SGCNV
*
*     Company: ARISTON Norway as
*
*     Author: Thierry Pottier
*
*    * @file     PinName.h
	 * @brief    Pin macro for HW ver17-10-2022 Header File
	 * @version  V0.00
	 * @date     18. October 2022
     * @note
*

*******************************************************/

#ifndef _PINNAME_INIT_INCLUDED_
#define _PINNAME_INIT_INCLUDED_

// RS485
//#define SENT_RS485 SETBIT( PORTA.OUT,7);
//#define READ_RS485 delay_ms(5);CLRBIT ( PORTA.OUT,7);

#define OPEN_RS485  SETBIT( PORTA.OUT,7);

#define CLOSE_RS485 CLRBIT ( PORTA.OUT,7);


// AD7715

// SCLK      PORTC pin2,
// Data OUT  PORTC pin1
// Data In   PORTC pin0 
// DRDY in  PORTC pin4

// Chip Select
#define ADC_CS_LOW      CLRBIT ( PORTC.OUT,3);  
//#define ADC_CS_HIGH     SETBIT ( PORTC.OUT,3);  
#define ADC_CS_HIGH     CLRBIT ( PORTC.OUT,3);  //force CS low   
#define ADC_CLOCK_HIGH  SETBIT ( PORTC.OUT,2);
#define ADC_CLOCK_LOW  CLRBIT ( PORTC.OUT,2);

// Reset pin
#define ADC_RST_LOW     CLRBIT ( PORTF.OUT,5);
#define ADC_RST_HIGH    SETBIT ( PORTF.OUT,5);      
// ADC clock 
// PORTA pin 2, frequency 1MHz from TCA1 
#define DRDY_state  TSTBIT (PORTC.IN,4)
#define DRDY_INTERRUPT_FLAG 0x10    // 0b00010000
// define AD7715 message
#define COM_REG_R   0b00111000  // Read reg 1


// MUX PIN
// MUX POWER CS1 - CS14 (IC6)
// 406A3-0 == portb 0 -3 &406E1  PortC,7

#define SET_406A3       SETBIT ( PORTB.OUT,0); 
#define CLR_406A3       CLRBIT ( PORTB.OUT,0);

#define SET_406A2       SETBIT ( PORTB.OUT,1); 
#define CLR_406A2       CLRBIT ( PORTB.OUT,1);

#define SET_406A1       SETBIT ( PORTB.OUT,2); 
#define CLR_406A1       CLRBIT ( PORTB.OUT,2);

#define SET_406A0       SETBIT ( PORTB.OUT,3); 
#define CLR_406A0       CLRBIT ( PORTB.OUT,3);

#define SET_406E1       SETBIT ( PORTC.OUT,7); 
#define CLR_406E1       CLRBIT ( PORTC.OUT,7);

// CURRENT GENERATOR

#define CUR_10MA        CLRBIT ( PORTF.OUT,2);            
#define CUR_1MA         SETBIT ( PORTF.OUT,2);

// mux diff
#define SET_407A2       SETBIT ( PORTG.OUT,7); 
#define CLR_407A2       CLRBIT ( PORTG.OUT,7);

#define SET_407A1       SETBIT ( PORTG.OUT,6); 
#define CLR_407A1       CLRBIT ( PORTG.OUT,6);

#define SET_407A0       SETBIT ( PORTG.OUT,5); 
#define CLR_407A0       CLRBIT ( PORTG.OUT,5);

#define SET_407E1       SETBIT ( PORTC.OUT,5); 
#define CLR_407E1       CLRBIT ( PORTC.OUT,5);

#define SET_407E2       SETBIT ( PORTC.OUT,6); 
#define CLR_407E2       CLRBIT ( PORTC.OUT,6);

// "GND" MUX or VS- on the schema
// Mux use 408E1 to access
#define SET_408A2       SETBIT ( PORTG.OUT,2); 
#define CLR_408A2       CLRBIT ( PORTG.OUT,2);

#define SET_408A1       SETBIT ( PORTG.OUT,1); 
#define CLR_408A1       CLRBIT ( PORTG.OUT,1);

#define SET_408A0       SETBIT ( PORTG.OUT,0); 
#define CLR_408A0       CLRBIT ( PORTG.OUT,0);

#define SET_408E1       SETBIT ( PORTG.OUT,4); 
#define CLR_408E1       CLRBIT ( PORTG.OUT,4);

// Mux EEPROM use 408E2 to access
// use same line 408Ax to eeprom than GND 

#define SET_408E2       SETBIT ( PORTG.OUT,3); 
#define CLR_408E2       CLRBIT ( PORTG.OUT,3);

// connect resistor

#define SET_RES1R       SETBIT ( PORTF.OUT,4); 
#define CLR_RES1R       CLRBIT ( PORTF.OUT,4);

#define SET_RES1K       SETBIT ( PORTF.OUT,3); 
#define CLR_RES1K       CLRBIT ( PORTF.OUT,3);

#define LED1_OFF     SETBIT (PORTB.OUT,4);
#define LED1_ON    CLRBIT (PORTB.OUT,4);

#define LED2_OFF     SETBIT (PORTB.OUT,5);
#define LED2_ON    CLRBIT (PORTB.OUT,5);

#define LED3_OFF     SETBIT (PORTB.OUT,6);
#define LED3_ON    CLRBIT (PORTB.OUT,6);

#define LED4_OFF     SETBIT (PORTB.OUT,7);
#define LED4_ON    CLRBIT (PORTB.OUT,7);

// EXTENSION BOARD:
#define SELECT_EXTBOARD_1   TSTBIT (PORTD.IN,0)
#define SELECT_EXTBOARD_2   TSTBIT (PORTD.IN,1)
#define AN-SGCNV_EXT    0x01    // SELECT_EXTBOARD_1 GND, SELECT_EXTBOARD_2 OPEN 

// Extension board  J12 4 to 7 port D
#define WASHTRAC4   TSTBIT (PORTD.IN,4)
#define WASHTRAC3   TSTBIT (PORTD.IN,5)
#define WASHTRAC2   TSTBIT (PORTD.IN,6)
#define WASHTRAC1   TSTBIT (PORTD.IN,7)
#define WASHTRAC_DELAY  5   // us

// Extension board  J12 0 to 7 port E
#define HIGHLEVEL1  TSTBIT ( PORTE.IN,7)
#define HIGHLEVEL2  TSTBIT ( PORTE.IN,6)
#define HIGHLEVEL3  TSTBIT ( PORTE.IN,5)
#define HIGHLEVEL4  TSTBIT ( PORTE.IN,4)
#define HIGHLEVEL5  TSTBIT ( PORTE.IN,3)
#define HIGHLEVEL6  TSTBIT ( PORTE.IN,2)
#define HIGHLEVEL7  TSTBIT ( PORTE.IN,1)
#define HIGHLEVEL8  TSTBIT ( PORTE.IN,0)




#endif
