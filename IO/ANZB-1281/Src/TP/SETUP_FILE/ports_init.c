/*******************************************************
I/O Ports initialization created by the
CodeWizardAVR V3.49 Automatic Program Generator
© Copyright 1998-2022 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

Project : 
*******************************************************/

// I/O Registers definitions
#include <avr64db64.h>

// Ports initialization
void ports_init(void)
{
// PORTA initialization
// OUT register
PORTA.OUT=0x10;
// Pin0: Input
// Pin1: Input
// Pin2: Output
// Pin3: Input
// Pin4: Output
// Pin5: Input
// Pin6: Input
// Pin7: Output
PORTA.DIR=0x94;
// Pin0 Inverted: Off
// Pin0 Pullup on input: Off
// Pin0 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin0 Input level: Schmitt Tg.
PORTA.PIN0CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin1 Inverted: Off
// Pin1 Pullup on input: Off
// Pin1 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin1 Input level: Schmitt Tg.
PORTA.PIN1CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin2 Inverted: Off
// Pin2 Pullup on input: Off
// Pin2 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin2 Input level: Schmitt Tg.
PORTA.PIN2CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin3 Inverted: Off
// Pin3 Pullup on input: On
// Pin3 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin3 Input level: Schmitt Tg.
PORTA.PIN3CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin4 Inverted: Off
// Pin4 Pullup on input: Off
// Pin4 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin4 Input level: Schmitt Tg.
PORTA.PIN4CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin5 Inverted: Off
// Pin5 Pullup on input: On
// Pin5 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin5 Input level: Schmitt Tg.
PORTA.PIN5CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin6 Inverted: Off
// Pin6 Pullup on input: On
// Pin6 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin6 Input level: Schmitt Tg.
PORTA.PIN6CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin7 Inverted: Off
// Pin7 Pullup on input: Off
// Pin7 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin7 Input level: Schmitt Tg.
PORTA.PIN7CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);

// PORTB initialization
// OUT register
PORTB.OUT=0x00;
// Pin0: Output
// Pin1: Output
// Pin2: Output
// Pin3: Output
// Pin4: Output
// Pin5: Output
// Pin6: Output
// Pin7: Output
PORTB.DIR=0xFF;
// Pin0 Inverted: Off
// Pin0 Pullup on input: Off
// Pin0 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin0 Input level: Schmitt Tg.
PORTB.PIN0CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin1 Inverted: Off
// Pin1 Pullup on input: Off
// Pin1 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin1 Input level: Schmitt Tg.
PORTB.PIN1CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin2 Inverted: Off
// Pin2 Pullup on input: Off
// Pin2 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin2 Input level: Schmitt Tg.
PORTB.PIN2CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin3 Inverted: Off
// Pin3 Pullup on input: Off
// Pin3 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin3 Input level: Schmitt Tg.
PORTB.PIN3CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin4 Inverted: Off
// Pin4 Pullup on input: Off
// Pin4 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin4 Input level: Schmitt Tg.
PORTB.PIN4CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin5 Inverted: Off
// Pin5 Pullup on input: Off
// Pin5 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin5 Input level: Schmitt Tg.
PORTB.PIN5CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin6 Inverted: Off
// Pin6 Pullup on input: On
// Pin6 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin6 Input level: Schmitt Tg.
PORTB.PIN6CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin7 Inverted: Off
// Pin7 Pullup on input: On
// Pin7 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin7 Input level: Schmitt Tg.
PORTB.PIN7CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);

// PORTC initialization
// OUT register
PORTC.OUT=0x08;
// Pin0: Output
// Pin1: Input
// Pin2: Output
// Pin3: Output
// Pin4: Input
// Pin5: Output
// Pin6: Output
// Pin7: Output
PORTC.DIR=0xED;
// Pin0 Inverted: Off
// Pin0 Pullup on input: Off
// Pin0 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin0 Input level: Schmitt Tg.
PORTC.PIN0CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin1 Inverted: Off
// Pin1 Pullup on input: On
// Pin1 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin1 Input level: Schmitt Tg.
PORTC.PIN1CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin2 Inverted: Off
// Pin2 Pullup on input: Off
// Pin2 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin2 Input level: Schmitt Tg.
PORTC.PIN2CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin3 Inverted: Off
// Pin3 Pullup on input: Off
// Pin3 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin3 Input level: Schmitt Tg.
PORTC.PIN3CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin4 Inverted: Off
// Pin4 Pullup on input: On
// Pin4 Input/Sense configuration: Int. enabled, Sense falling edge
// Pin4 Input level: Schmitt Tg.
PORTC.PIN4CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
// Pin5 Inverted: Off
// Pin5 Pullup on input: Off
// Pin5 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin5 Input level: Schmitt Tg.
PORTC.PIN5CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin6 Inverted: Off
// Pin6 Pullup on input: Off
// Pin6 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin6 Input level: Schmitt Tg.
PORTC.PIN6CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin7 Inverted: Off
// Pin7 Pullup on input: Off
// Pin7 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin7 Input level: Schmitt Tg.
PORTC.PIN7CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);

// PORTD initialization
// OUT register
PORTD.OUT=0x00;
// Pin0: Input
// Pin1: Input
// Pin2: Input
// Pin3: Input
// Pin4: Input
// Pin5: Input
// Pin6: Input
// Pin7: Input
PORTD.DIR=0x00;
// Pin0 Inverted: Off
// Pin0 Pullup on input: On
// Pin0 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin0 Input level: Schmitt Tg.
PORTD.PIN0CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin1 Inverted: Off
// Pin1 Pullup on input: On
// Pin1 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin1 Input level: Schmitt Tg.
PORTD.PIN1CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin2 Inverted: Off
// Pin2 Pullup on input: On
// Pin2 Input/Sense configuration: Int. enabled, Sense falling edge
// Pin2 Input level: Schmitt Tg.
PORTD.PIN2CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
// Pin3 Inverted: Off
// Pin3 Pullup on input: On
// Pin3 Input/Sense configuration: Int. enabled, Sense falling edge
// Pin3 Input level: Schmitt Tg.
PORTD.PIN3CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
// Pin4 Inverted: Off
// Pin4 Pullup on input: On
// Pin4 Input/Sense configuration: Int. enabled, Sense falling edge
// Pin4 Input level: Schmitt Tg.
PORTD.PIN4CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
// Pin5 Inverted: Off
// Pin5 Pullup on input: On
// Pin5 Input/Sense configuration: Int. enabled, Sense falling edge
// Pin5 Input level: Schmitt Tg.
PORTD.PIN5CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
// Pin6 Inverted: Off
// Pin6 Pullup on input: On
// Pin6 Input/Sense configuration: Int. enabled, Sense falling edge
// Pin6 Input level: Schmitt Tg.
PORTD.PIN6CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
// Pin7 Inverted: Off
// Pin7 Pullup on input: On
// Pin7 Input/Sense configuration: Int. enabled, Sense falling edge
// Pin7 Input level: Schmitt Tg.
PORTD.PIN7CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);

// PORTE initialization
// OUT register
PORTE.OUT=0x00;
// Pin0: Input
// Pin1: Input
// Pin2: Input
// Pin3: Input
// Pin4: Input
// Pin5: Input
// Pin6: Input
// Pin7: Input
PORTE.DIR=0x00;
// Pin0 Inverted: Off
// Pin0 Pullup on input: On
// Pin0 Input/Sense configuration: Int. enabled, Sense falling edge
// Pin0 Input level: Schmitt Tg.
PORTE.PIN0CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
// Pin1 Inverted: Off
// Pin1 Pullup on input: On
// Pin1 Input/Sense configuration: Int. enabled, Sense falling edge
// Pin1 Input level: Schmitt Tg.
PORTE.PIN1CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
// Pin2 Inverted: Off
// Pin2 Pullup on input: On
// Pin2 Input/Sense configuration: Int. enabled, Sense falling edge
// Pin2 Input level: Schmitt Tg.
PORTE.PIN2CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
// Pin3 Inverted: Off
// Pin3 Pullup on input: On
// Pin3 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin3 Input level: Schmitt Tg.
PORTE.PIN3CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin4 Inverted: Off
// Pin4 Pullup on input: On
// Pin4 Input/Sense configuration: Int. enabled, Sense falling edge
// Pin4 Input level: Schmitt Tg.
PORTE.PIN4CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
// Pin5 Inverted: Off
// Pin5 Pullup on input: On
// Pin5 Input/Sense configuration: Int. enabled, Sense falling edge
// Pin5 Input level: Schmitt Tg.
PORTE.PIN5CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
// Pin6 Inverted: Off
// Pin6 Pullup on input: On
// Pin6 Input/Sense configuration: Int. enabled, Sense falling edge
// Pin6 Input level: Schmitt Tg.
PORTE.PIN6CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);
// Pin7 Inverted: Off
// Pin7 Pullup on input: On
// Pin7 Input/Sense configuration: Int. enabled, Sense falling edge
// Pin7 Input level: Schmitt Tg.
PORTE.PIN7CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_FALLING_gc | (0<<PORT_INLVL_bp);

// PORTF initialization
// OUT register
PORTF.OUT=0x00;
// Pin0: Input
// Pin1: Output
// Pin2: Output
// Pin3: Output
// Pin4: Output
// Pin5: Output
// Pin6: Input
PORTF.DIR=0x3E;
// Pin0 Inverted: Off
// Pin0 Pullup on input: On
// Pin0 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin0 Input level: Schmitt Tg.
PORTF.PIN0CTRL=(0<<PORT_INVEN_bp) | (1<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin1 Inverted: Off
// Pin1 Pullup on input: Off
// Pin1 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin1 Input level: Schmitt Tg.
PORTF.PIN1CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin2 Inverted: Off
// Pin2 Pullup on input: Off
// Pin2 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin2 Input level: Schmitt Tg.
PORTF.PIN2CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin3 Inverted: Off
// Pin3 Pullup on input: Off
// Pin3 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin3 Input level: Schmitt Tg.
PORTF.PIN3CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin4 Inverted: Off
// Pin4 Pullup on input: Off
// Pin4 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin4 Input level: Schmitt Tg.
PORTF.PIN4CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin5 Inverted: Off
// Pin5 Pullup on input: Off
// Pin5 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin5 Input level: Schmitt Tg.
PORTF.PIN5CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin6 Inverted: Off
// Pin6 Pullup on input: Off
// Pin6 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin6 Input level: Schmitt Tg.
PORTF.PIN6CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);

// PORTG initialization
// OUT register
PORTG.OUT=0x00;
// Pin0: Output
// Pin1: Output
// Pin2: Output
// Pin3: Output
// Pin4: Output
// Pin5: Output
// Pin6: Output
// Pin7: Output
PORTG.DIR=0xFF;
// Pin0 Inverted: Off
// Pin0 Pullup on input: Off
// Pin0 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin0 Input level: Schmitt Tg.
PORTG.PIN0CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin1 Inverted: Off
// Pin1 Pullup on input: Off
// Pin1 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin1 Input level: Schmitt Tg.
PORTG.PIN1CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin2 Inverted: Off
// Pin2 Pullup on input: Off
// Pin2 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin2 Input level: Schmitt Tg.
PORTG.PIN2CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin3 Inverted: Off
// Pin3 Pullup on input: Off
// Pin3 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin3 Input level: Schmitt Tg.
PORTG.PIN3CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin4 Inverted: Off
// Pin4 Pullup on input: Off
// Pin4 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin4 Input level: Schmitt Tg.
PORTG.PIN4CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin5 Inverted: Off
// Pin5 Pullup on input: Off
// Pin5 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin5 Input level: Schmitt Tg.
PORTG.PIN5CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin6 Inverted: Off
// Pin6 Pullup on input: Off
// Pin6 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin6 Input level: Schmitt Tg.
PORTG.PIN6CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
// Pin7 Inverted: Off
// Pin7 Pullup on input: Off
// Pin7 Input/Sense configuration: Int. disabled, Inp. buffer enabled
// Pin7 Input level: Schmitt Tg.
PORTG.PIN7CTRL=(0<<PORT_INVEN_bp) | (0<<PORT_PULLUPEN_bp) | PORT_ISC_INTDISABLE_gc | (0<<PORT_INLVL_bp);
}

// PORTC interrupt service routine
interrupt [PORTC_PORT_vect] void portc_int_isr(void)
{
// Clear the PORTC interrupt flags
PORTC.INTFLAGS=PORTC.INTFLAGS;

// Write your code here

}

// PORTD interrupt service routine
interrupt [PORTD_PORT_vect] void portd_int_isr(void)
{
// Clear the PORTD interrupt flags
PORTD.INTFLAGS=PORTD.INTFLAGS;

// Write your code here

}

// PORTE interrupt service routine
interrupt [PORTE_PORT_vect] void porte_int_isr(void)
{
// Clear the PORTE interrupt flags
PORTE.INTFLAGS=PORTE.INTFLAGS;

// Write your code here

}

