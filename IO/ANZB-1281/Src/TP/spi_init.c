/*******************************************************
SPI initialization created by the
CodeWizardAVR V3.49 Automatic Program Generator
© Copyright 1998-2022 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

Project : 
*******************************************************/

// I/O Registers definitions
#include <avr64db64.h>

// SPI1 initialization
void spi1_init(void)
{
// The SPI1 signals are not remapped: 
// MOSI: PORTC.0, MISO: PORTC.1, SCK: PORTC.2, /SS: PORTC.3
PORTMUX.SPIROUTEA&= ~PORTMUX_SPI1_gm;
// Note: The MOSI (PORTC, Pin 0), SCK (PORTC, Pin 2) and /SS (PORTC, Pin 3)
// signals are configured as outputs in the ports_init function.

// SPI1 is enabled
// SPI mode: 3
// Operating as: Master
// Data order: MSB First
// SCK clock prescaler: 128
// SCK clock doubled: Off
// SCK clock frequency: 31,257 kHz
SPI1.CTRLA=SPI_ENABLE_bm | (1<<SPI_MASTER_bp) | (0<<SPI_DORD_bp) |
	SPI_PRESC_DIV128_gc | (0<<SPI_CLK2X_bp);

// SPI mode: 3
// /SS signal used as chip select: On
SPI1.CTRLB=SPI_MODE_3_gc | (0<<SPI_SSD_bp);

// SPI1 interrupt: Off
SPI1.INTCTRL=(0<<SPI_IE_bp);
}

// SPI1 transmit/receive function in Master mode
// c - data to be transmitted
// Returns the received data
#pragma used+
unsigned char spi1_master_tx_rx(unsigned char c)
{
// Transmit data in Master mode
SPI1.DATA=c;
// Wait for the data to be transmitted/received
while ((SPI1.INTFLAGS & SPI_IF_bm)==0);
// Return the received data
return SPI1.DATA;
}
#pragma used-

