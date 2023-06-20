/*******************************************************
SPI initialization created by the
CodeWizardAVR V3.49 Automatic Program Generator
© Copyright 1998-2022 Pavel Haiduc, HP InfoTech S.R.L.
http://www.hpinfotech.ro

Project : 
*******************************************************/

#ifndef _SPI_INIT_INCLUDED_
#define _SPI_INIT_INCLUDED_

// SPI1 initialization
void spi1_init(void);
// Macro used to drive the SPI1 /SS signal low in order to select the slave
#define SET_SPI1_SS_LOW {PORT.OUTCLR=SPI_SS_bm;}
// Macro used to drive the SPI1 /SS signal high in order to deselect the slave
#define SET_SPI1_SS_HIGH {PORT.OUTSET=SPI_SS_bm;}
// SPI1 transmit/receive function in Master mode
// c - data to be transmitted
// Returns the received data
unsigned char spi1_master_tx_rx(unsigned char c);

#endif
