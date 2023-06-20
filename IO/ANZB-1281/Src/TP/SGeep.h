/*******************************************************

*
*     Program for signal convertion card, AN-SGCNV
*
*     Company: ARISTON Norway as
*
*     Author: Thierry Pottier
*
*    * @file     SGeep.h
	 * @brief    SGeep Header File
	 * @version  V0.00
	 * @date     18. October 2022
	 * @note
*

*******************************************************/


#ifndef ___SGEEP_H_
#define ___SGEEP_H_

/************************************************************************/
/*      DS2430 commands                        */

#define READ_ROM            0x33        /* Read ROM */
#define MATCH_ROM            0x55        /* Match ROM  */
#define SKIP_ROM            0xcc        /* Skip ROM  */
#define SEARCH_ROM        0xf0        /* Search ROM  */
#define READ_SP             0xaa        /* Read scratch pad register from adr... */
#define WRITE_SP		   0x0f     /* Write scratch pad register from adr... */
#define COPY_SP_NV		0x55		/* Copy scratch pad to NV */
#define COPY_NV_SP		0xf0		/* Copy NV to scratch pad */
#define READ_STATUS		0x66		/* Read status register */
#define READ_APPREG		0xc3		/* Read AD-REG from address.. */
#define WRITE_APPREG		0x99		/* Write AD-REG from address... */
#define LOCK_APP			0x5a		/* Copies and write protects AD-REG */

/************************************************************************/
/*	  Port bit def. 						*/


#define ADCLK			0x20		/* port 5 bit 5, AD CLK */
#define ADDO			0x10		/* port 5 bit 4, AD DATA OUT */
#define ADDI			0x08		/* port 5 bit 3, AD DATA IN */
#define TXE				0x04		/* port 5 bit 2, TX ON */


#define EEPIN			0x20		/* port 4, pin 5 EEPORT */
#define EPORTI			0xd0		/* port 4, EEPROM DATA IN  bit 4, 6, 7 out rest in  */
#define EPORTO			0xf0		/* port 4, EEPROM DATA OUT bit 4, 5 , 6 7, out rest in*/


/************************************************************************/


/* sgeep.c */
short Eeprom(unsigned char, unsigned char) ;
char SendEepromCommand(unsigned char command, unsigned char cmd_byte, unsigned char number);
void ReadEepromData(unsigned char*, char);
void WriteEepromData(unsigned char*, char);
//unsigned char ReadEepromByte(void) ;
//void WriteEepromByte(unsigned char) ;
//short ResetEeprom(void);
short CheckEepChannel(void);
unsigned char CheckEepData(unsigned char *) ;
unsigned char CheckADData(unsigned char *) ;
void MakeEepChksum(unsigned char *) ;

void set_interrupt_mask (unsigned char data);



#endif 
