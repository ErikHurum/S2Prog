#include <stdio.h>
#include "iom1280.h"
#include "RTOS.h"
#include "constants.h"

#include "hart_gpio.h"

////////////////////////////////////////////////////////////////////////////////
//
// Channel Power Control
//
////////////////////////////////////////////////////////////////////////////////
/*
 * power control for each channel
 *
 * CHP0     : PA0
 * CHP1     : PA1
 * CHP2     : PA2
 * CHP3     : PA3
 * CHP4     : PA4
 * CHP5     : PA5
 * CHP6     : PA6
 * CHP7     : PA7
 * CHP8     : PJ4
 * CHP9     : PJ5
 * CHP10    : PJ6
 * CHP11    : PJ7
 *
 * HIGH     : Power On
 * LOW      : Power Off
 *
 */
static void
hart_gpio_power_gpio_init(void) {
    My_SetBit(DDRA, 0xff);         // PA0-PA7 as output
    My_SetBit(DDRJ, 0xf0);         // PJ4-PJ7 as output

    //
    // power off everything just to make sure
    //
    My_ClrBit(PORTA, 0xff);        // PA0-PA7 LOW
    My_ClrBit(PORTJ, 0xf0);        // PJ4-PJ7 LOW
}

void
hart_gpio_power_on(hart_channel_t chnl) {
    switch ( chnl ) {
    case hart_channel_0:
    case hart_channel_1:
    case hart_channel_2:
    case hart_channel_3:
    case hart_channel_4:
    case hart_channel_5:
    case hart_channel_6:
    case hart_channel_7:
        My_SetBit(PORTA, __BIT_MASK(chnl));
        break;

    case hart_channel_8:
    case hart_channel_9:
    case hart_channel_10:
    case hart_channel_11:
        My_SetBit(PORTJ, __BIT_MASK(chnl - hart_channel_8 + 4));
        break;
    }
}

void
hart_gpio_power_off(hart_channel_t chnl) {
    switch ( chnl ) {
    case hart_channel_0:
    case hart_channel_1:
    case hart_channel_2:
    case hart_channel_3:
    case hart_channel_4:
    case hart_channel_5:
    case hart_channel_6:
    case hart_channel_7:
        My_ClrBit(PORTA, __BIT_MASK(chnl));
        break;

    case hart_channel_8:
    case hart_channel_9:
    case hart_channel_10:
    case hart_channel_11:
        My_ClrBit(PORTJ, __BIT_MASK((chnl - hart_channel_8 + 4)));
        break;
    }
}


////////////////////////////////////////////////////////////////////////////////
//
// Modem MUX control
//
////////////////////////////////////////////////////////////////////////////////
/*
 *    MUX0
 * ENABLE     : PD5
 * ADR0       : PK0
 * ADR1       : PK1
 *
 *    MUX1
 * ENABLE     : PH3
 * ADR0       : PK4
 * ADR1       : PK5
 *
 *    MUX2
 * ENABLE     : PJ3
 * ADR0       : PC0
 * ADR1       : PC1
 *
 */
static void
hart_gpio_mux_gpio_init(void) {
    //
    // MUX0
    //
    My_SetBit(DDRD, __BIT_MASK(5));    // ENABLE : PD5 as output
    My_SetBit(DDRK, __BIT_MASK(0));    // ADDR0  : PK0 as output
    My_SetBit(DDRK, __BIT_MASK(1));    // ADDR1  : PK1 as output

    //
    // MUX1
    //
    My_SetBit(DDRH, __BIT_MASK(3));    // ENABLE : PH3 as output
    My_SetBit(DDRK, __BIT_MASK(4));    // ADDR0  : PK4 as output
    My_SetBit(DDRK, __BIT_MASK(5));    // ADDR1  : PK5 as output

    //
    // MUX2
    //
    My_SetBit(DDRJ, __BIT_MASK(3));    // ENABLE : PJ3 as output
    My_SetBit(DDRC, __BIT_MASK(0));    // ADDR0  : PC0 as output
    My_SetBit(DDRC, __BIT_MASK(1));    // ADDR1  : PC1 as output
}

void
hart_gpio_mux_enable(hart_mux_t mux) {
    switch ( mux ) {
    case hart_mux_0:
        My_SetBit(PORTD, __BIT_MASK(5));     // PD5
        break;

    case hart_mux_1:
        My_SetBit(PORTH, __BIT_MASK(3));     // PH3
        break;

    case hart_mux_2:
        My_SetBit(PORTJ, __BIT_MASK(3));     // PJ3
        break;
    }
}

void
hart_gpio_mux_disable(hart_mux_t mux) {
    switch ( mux ) {
    case hart_mux_0:
        My_ClrBit(PORTD, __BIT_MASK(5));     // PD5
        break;

    case hart_mux_1:
        My_ClrBit(PORTH, __BIT_MASK(3));     // PH3
        break;

    case hart_mux_2:
        My_ClrBit(PORTJ, __BIT_MASK(3));     // PJ3
        break;
    }
}

/*
 * NOTE: XXX
 *
 * if you think disabling/enabling mux is not necessary during 
 * channel change, just remove it. I don't care.
 */
void
hart_gpio_channel_select(hart_channel_t chnl) {
    switch ( chnl ) {
    case hart_channel_0:
    case hart_channel_1:
    case hart_channel_2:
    case hart_channel_3:
        {
            uint8_t chnl_mask = (uint8_t)(chnl - hart_channel_0);
            OS_IncDI();
            uint8_t tmpPort =  PORTK;
            tmpPort &= ~(__BIT_MASK(0) | __BIT_MASK(1));
            tmpPort |= chnl_mask << 0;
            PORTK = tmpPort;
            OS_DecRI();

            //My_ClrBit(PORTK, 3/* (__BIT_MASK(0) | __BIT_MASK(1))*/);     // clear first
            //My_SetBit(PORTK, chnl_mask/*(chnl_mask << 0)*/);
        }
        break;

    case hart_channel_4:
    case hart_channel_5:
    case hart_channel_6:
    case hart_channel_7:
        {
            uint8_t chnl_mask = (uint8_t)(chnl - hart_channel_4);
            OS_IncDI();
            uint8_t tmpPort =  PORTK;
            tmpPort &= ~(__BIT_MASK(4) | __BIT_MASK(5));
            tmpPort |= chnl_mask << 4;
            PORTK = tmpPort;
            OS_DecRI();

            //My_ClrBit(PORTK, (__BIT_MASK(4) | __BIT_MASK(5)));     // clear first
            //My_SetBit(PORTK, (chnl_mask << 4));                    // PK4/PK5

        }
        break;

    case hart_channel_8:
    case hart_channel_9:
    case hart_channel_10:
    case hart_channel_11:
        {
            uint8_t chnl_mask = (uint8_t)(chnl - hart_channel_8);
            OS_IncDI();
            uint8_t tmpPort =  PORTC;
            tmpPort &= ~(__BIT_MASK(0) | __BIT_MASK(1));
            tmpPort |= chnl_mask << 0;
            PORTC = tmpPort;
            OS_DecRI();

            //My_ClrBit(PORTC, (__BIT_MASK(0) | __BIT_MASK(1)));     // clear first
            //My_SetBit(PORTC, (chnl_mask << 0));                    // PC0/PC1
        }
        break;
    }
}



/*
 * NOTE: XXX
 *
 * Enable all mux for HART
 *
 */
void hart_gpio_enable_all_mux(void) {

    hart_gpio_mux_enable(hart_mux_0);
    hart_gpio_mux_enable(hart_mux_1);
    hart_gpio_mux_enable(hart_mux_2);
}

////////////////////////////////////////////////////////////////////////////////
//
// ADC & ADC MUX
//
////////////////////////////////////////////////////////////////////////////////
/*
 *
 * ADC MUX
 * ADR0       : PF0
 * ADR1       : PF1
 * ADR2       : PF2
 * ADR3       : PF3
 *
 * ADC SPI
 *
 * SCLK       : PL0
 * MISO       : PL1
 * MOSI       : PL2
 * CS         : N/A. always selected
 * /RESET     : PL3
 * /DRDY      : PD0, PD0 is mapped to EINT0 when set up as input
 *
 */
static void
hart_gpio_adc_gpio_init(void) {
    My_SetBit(DDRF,  0x0f);              // PF0-PF3 as output
    // Port F data direction, used for ADC
    My_SetBit(DDRL,  AD7715_SCLK);       // SCLK   : PL0 as output
    My_ClrBit(DDRL,  AD7715_MISO);       // MISO   : PL1 as input
    My_SetBit(DDRL,  AD7715_MOSI);       // MOSI   : PL2 as output
    My_SetBit(DDRL,  __BIT_MASK(3));     // /RESET : PL3 as output
    My_ClrBit(DDRD,  __BIT_MASK(0));     // /DRDY  : PD0 as input

    //
    // setup clock high
    //
    My_SetBit(AD7715_PORT, AD7715_SCLK);

    //
    // put ADC in reset state
    //
    hart_gpio_adc_reset(0);
}

void hart_gpio_adc_channel_select(hart_channel_t chnl) {
    uint8_t   mask    = (uint8_t)(chnl - hart_channel_0);
    // No protection needed as exclusive use
    //OS_EnterRegion();
    //OS_IncDI();
    uint8_t tmpReg = PORTF;
    tmpReg &= ~0x0f;         // clear
    tmpReg |=  mask;         // set
    PORTF = tmpReg;
    //OS_LeaveRegion();
    //OS_DecRI();
}

void hart_gpio_adc_reset(uint8_t hi) {
    if ( hi ) {
        My_SetBit(AD7715_PORT, __BIT_MASK(3));
    } else {
        My_ClrBit(AD7715_PORT, __BIT_MASK(3));
    }
}

////////////////////////////////////////////////////////////////////////////////
//
// HART Modem Control
//
////////////////////////////////////////////////////////////////////////////////
/*
 *
 * MODEM0 /RTS : PD4
 * MODEM1 /RTS : PH2
 * MODEM2 /RTS : PJ2
 *
 */
static void hart_gpio_modem_gpio_init(void) {
    My_SetBit(DDRD,  __BIT_MASK(4));     // MODEM0 /RTS: PD4 as output
    My_SetBit(DDRH,  __BIT_MASK(2));     // MODEM1 /RTS: PH2 as output
    My_SetBit(DDRJ,  __BIT_MASK(2));     // MODEM2 /RTS: PJ2 as output

    hart_gpio_hart_carrier_off(hart_modem_0);
    hart_gpio_hart_carrier_off(hart_modem_1);
    hart_gpio_hart_carrier_off(hart_modem_2);
}

void hart_gpio_hart_carrier_off(hart_modem_t modem) {
    OS_IncDI();
    hart_gpio_hart_carrier_off_irq(modem);
    OS_DecRI();
}

void hart_gpio_hart_carrier_off_irq(hart_modem_t modem) {
    switch ( modem ) {
    case hart_modem_0:
        {
            uint8_t tmpReg = PORTD;
            tmpReg |= __BIT_MASK(4);
            PORTD = tmpReg;
        }
        break;

    case hart_modem_1:
        {
            uint8_t tmpReg = PORTH;
            tmpReg |= __BIT_MASK(2);
            PORTH = tmpReg;
        }
        break;

    case hart_modem_2:
        {
            uint8_t tmpReg = PORTJ;
            tmpReg |= __BIT_MASK(2);
            PORTJ = tmpReg;
        }
        break;
    }
}

void hart_gpio_hart_carrier_on(hart_modem_t modem) {
    OS_IncDI();
    hart_gpio_hart_carrier_on_irq(modem);
    OS_DecRI();
}

void hart_gpio_hart_carrier_on_irq(hart_modem_t modem) {
    switch ( modem ) {
    case hart_modem_0:
        {
            uint8_t tmpReg = PORTD;
            tmpReg &= ~__BIT_MASK(4);
            PORTD = tmpReg;
        }
        PORTD &= ~__BIT_MASK(4);
        break;
    case hart_modem_1:
        {
            uint8_t tmpReg = PORTH;
            tmpReg &= ~__BIT_MASK(2);
            PORTH = tmpReg;
        }
        break;
    case hart_modem_2:
        {
            uint8_t tmpReg = PORTJ;
            tmpReg &= ~__BIT_MASK(2);
            PORTJ = tmpReg;
        }
        break;
    }
}

////////////////////////////////////////////////////////////////////////////////
//
// Misc
//
////////////////////////////////////////////////////////////////////////////////
/*
 *
 * Debug LED: PG5
 * 
 * Address Rotary Switch 0 : PE4
 * Address Rotary Switch 1 : PE5
 * Address Rotary Switch 2 : PE6
 * Address Rotary Switch 3 : PE7 
 *
 * My485UART0 RS485 RX/TX Control : PE2
 *
 * ADC CLOCK, OSC, 1 MHz : PE3
 */
static void hart_gpio_misc_gpio_init(void) {

    My_SetBit(DDRG, __BIT_MASK(5));        // Debug LED: PG5 as output


    My_ClrBit(DDRE, (0xf0));               // PE4-PE7 as input

    My_SetBit(DDRE,  __BIT_MASK(2));       // PE2 : My485UART0 RS485 RX/TX Control
    My_ClrBit(PORTE, __BIT_MASK(2));

    My_SetBit(DDRE, __BIT_MASK(3));        // PE3 : 1 MHz ADC Clock
}

void hart_gpio_debug_led(uint8_t on) {
    // No protection needed as exclusive use
    //OS_EnterRegion();
    //OS_IncDI();
    if ( on ) {
        PORTG &= ~__BIT_MASK(5);
    } else {
        PORTG |=  __BIT_MASK(5);
    }
    //OS_LeaveRegion();
    //OS_DecRI();
}

////////////////////////////////////////////////////////////////////////////////
//
// GPIO init
//
////////////////////////////////////////////////////////////////////////////////
void
hart_gpio_init(void) {
    hart_gpio_power_gpio_init();
    hart_gpio_mux_gpio_init();
    hart_gpio_adc_gpio_init();
    hart_gpio_modem_gpio_init();
    hart_gpio_misc_gpio_init();
}
