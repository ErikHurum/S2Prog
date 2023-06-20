/***** SGEEP.C *************************************************************
*
*     Program for signal convertion card, AN-SGCNV
*
*     Company: Scanjet Ariston as
*
*     Author: Asle Straume
*
*     Date: 1-aug-96.
*
*************************************************************************/

#include "math.h"
#include "float.h"
#include "stdio.h"
#include "ioh8325.h"
#include "inth8325.h"

#include "sg.h"
#include "sgext.h"

/*************************************************************************
*
*  Operate eeprom DS2430
*
*			channel: 0 - 6 on sensors, 7 on PCB
*			type	 : IP_REG or EEPROM
*
*************************************************************************/
short Eeprom(unsigned char channel, unsigned char command)
{

char				ret_val = FALSE;
unsigned char	*data ;

	SetCalResistance(OHM_1R) ;						/* use 1 ohm res. on return. */
	SetEepromChannel(channel) ;					/* connect to the right eeprom */
	SetMuxChannel(MUXCHOFF) ;						/* mux channel off */
	SetSupplyChannel(SUPPCHOFF) ;					/* set channel off */
	SetSupplyCurrent(1);								/* set 1mA supply */
	OneMsecDelay(5) ;						/* supply the unit before read */
	set_interrupt_mask(1);							/* Disable interrupt */
	KickDog() ;										/* kick dog due to long read time*/

	switch (command) {			/* find command */
	case READ_SP :			/* read scratchpad */
		if (SendEepromCommand(command, 0, 1)) { /* Start at adderss 0 */
			data = &packed_data[channel][8] ;	/* nvram block */
			ReadEepromData(data, 32)	;			/* Read 32 bytes */
			ret_val = TRUE ;
		}
		break ;
	case WRITE_SP : 		/* write scratchpad */
		if (SendEepromCommand(command, 0, 1)){ /* Start at adderss 0 */
			data = &packed_data[channel][8] ;	/* nvram block */
			WriteEepromData(data, 32)	;			/* Write 32 bytes */
			ret_val = TRUE ;
		}
		break ;
	case READ_STATUS :			/* Read status register */
		if (SendEepromCommand(command, 0, 1)){	/* Command 0 */
			data = &eep_status ;						/* status */
			ReadEepromData(data, 1) ;				/* Read 1 bytes */
			ret_val = TRUE ;
		}
		break ;
	case COPY_SP_NV :									/* Copy scrpad to eeprom */
		if (SendEepromCommand(command, 0xa5, 1)) {
			set_interrupt_mask(0);					/* Enable interrupt due to*/
			OneMsecDelay(100) ;					/* the 100 ms delay */
			ret_val = TRUE ;
		}
		break ;
	case COPY_NV_SP :									/* Copy eeprom to scrpad */
		if (SendEepromCommand(command, 0, 1)) {
			ret_val = TRUE ;
		}
		break ;
	case READ_APPREG :							/* Read APP-REG */
		if (SendEepromCommand(command, 0, 1)) { 	/* Start at addrss 0 */
			data = &packed_data[channel][0] ;	/* ID-REG block */
			ReadEepromData(data, 8) ;				/* Read 8 bytes */
			ret_val = TRUE ;
		}
		break ;
	case WRITE_APPREG :			 /* Write ID-REG */
		if (SendEepromCommand(command, 0, 1)) {  /* Start at addrss 0 */
			data = &packed_data[channel][0] ;	 /* ID-REG block */
			WriteEepromData(data, 8)	;			 /* Write 8 bytes */
			ret_val = TRUE ;
		}
		break ;
	case LOCK_APP : 			 /* Lock data in ID-Reg */
		if (SendEepromCommand(command, 0xa5, 1)) { /* Command importent */
			ret_val = TRUE ;
		}
		break ;
	case READ_ROM : 		 /* Read id from eeprom */
		if (SendEepromCommand(command, 0, -1)) {	 /* No skip rom command!! */
			data = &tx_buff[tx_indx] ;					/* Tx buffer */
			ReadEepromData(data, 8) ;			 /* Read 8 bytes */
			ret_val = TRUE ;
		}
		break ;
	default :
		break ;
	}
	set_interrupt_mask(0);							/* Enable interrupt */
	SetSupplyCurrent(1);								/* set 1mA supply */
	SetEepromChannel(EEPCHOFF) ;					/* 9 = off */
	SetSupplyChannel(SUPPCHOFF) ;					/* 16 = off */
	SetCalResistance(OFF) ; 						/* Switch off cal. res. */
	KickDog() ;											/* kick dog due to long read time*/

	return ret_val ;
}

/*************************************************************************
*
*  Send a command to eeprom DS2430
*
*************************************************************************/
short SendEepromCommand(unsigned char command, short cmd_byte, short number)
{


	if (ResetEeprom()) {				/* Reset the chip */
		if (number != -1){
			WriteEepromByte(SKIP_ROM) ;	      /* skip rom */
		}
		WriteEepromByte(command) ;					/* Write command */
		if (number == 1) {							/* one cmd */
			WriteEepromByte(cmd_byte) ;			/* Write 2. command */
		}
		return TRUE ;
	} else {
	  return FALSE ;
	}
}


/*************************************************************************
*
*  Read data from eeprom DS2430
*
*************************************************************************/
void ReadEepromData(unsigned char *data, char NofBytes)
{
	short		i;

	for (i = 0; i < NofBytes; i++) {
		*data++ = ReadEepromByte() ;
	}
}

/*************************************************************************
*
*  Write data to eeprom DS2430
*
*************************************************************************/
void WriteEepromData(unsigned char* data, char NofBytes)
{
	short		i;


	for (i = 0; i < NofBytes; i++) {
		WriteEepromByte(*data++) ;
	}

}

/*************************************************************************
*
*  Read one byte from eeprom DS2430
*
*************************************************************************/
unsigned char ReadEepromByte(void)
{

	unsigned char read_byte ;
	short i, j ;


	read_byte = 0 ;
	P4DR &= (~EEPIN  & 0xf0);							/*	set data line low */
	if ((MDCR & 0x03) == 3){								/* mode 3, single chip	*/
		for (i = 0; i < 8; i++) {
			read_byte >>= 1 ;								/* shift bits  */
/*			P6DR &= ~LED1;	   */		   /*AStmark set led on */
			P4DDR = EPORTO ;								/* Port 4, 5 out (low)*/
			P4DDR = EPORTI ;								/* Port 4, 5 in  (tri-state)*/
			P4DDR = EPORTI ;								/* Repeat	    */
			P4DDR = EPORTI ;								/* this instruction */
			P4DDR = EPORTI ;								/* 6 times to delay */
			P4DDR = EPORTI ;								/* data reading     */
			P4DDR = EPORTI ;								/* about 14.6 us    */

/*			P6DR |= LED1;	   */		   /*AStmark set led off */
			if (P4DR & EEPIN) {
				read_byte |= 0x80 ;						/* set lsb */
			} else {
				read_byte &= ~0x80 ;						/* reset lsb */
			}
			for (j = 0; j < 15; j++ ){				/*Wait app. 50 us*/
			}
		}
	} else {					/* mode 1, prom */
		for (i = 0; i < 8; i++) {
			read_byte >>= 1 ;								/* shift bits  */
/*			P6DR &= ~LED1;		 */	 /*AStmark set led on */
			P4DDR = EPORTO ;								/* Port 4, 5 out (low)*/
			P4DDR = EPORTI ;								/* Port 4, 5 in  (tri-state)*/
			P4DDR = EPORTI ;      							/* delay data	 */

/*			P6DR |= LED1;		  */	 /*AStmark set led off */
			if (P4DR & EEPIN) {
				read_byte |= 0x80 ;						/* set lsb */
			} else {
				read_byte &= ~0x80 ;						/* reset lsb */
			}
			for (j = 0; j < 5; j++ ){				/*Wait 50 us*/
			}
	}
	}
	return read_byte ;
}


/*************************************************************************
*
*  Write one byte to eeprom DS2430
*
*************************************************************************/
void WriteEepromByte(unsigned char data)
{

	short i, j, delay ;


	if ((MDCR & 0x03) == 3){							/* mode 3 */
		delay = 12 ;
	} else {
		delay = 4 ;
	}

	P4DR &= (~EEPIN & 0xf0);									/*	set data line low */
	for (i = 0; i < 8; i++) {
		if (data & 0x01) {							/* lsb = "1" ? */
			P4DDR = EPORTO ;								/* Port 4, 5 out, Due to timing */
			P4DDR = EPORTI ;							/* Port 4, 5 in */
		} else {
			P4DDR = EPORTO ;							/* Port 4, 5 out,Due to timing */
		}
		for (j = 0; j < delay; j++ ){	    /*Wait 60 us*/
		}
		P4DDR = EPORTI ;								/* Port 4, 5 in */
		data >>= 1 ;										/* shift in next bit */
		for (j = 0; j < delay; j++ ){	    /*Wait 60 us*/
		}
	}
}

/*************************************************************************
*
*  Reset the eeprom DS2430
*
*************************************************************************/
short ResetEeprom(void)
{

	short i, delay ;
	unsigned char ret_val;

	Led(2, ON) ;								/* Led 2 on */

	if ((MDCR & 0x03) == 3){							/* mode 3 */
		delay = 100 ;
	} else {
		delay = 33 ;
	}

	ret_val = FALSE ;
	P4DR &= (~EEPIN & 0xf0) ;							/*	set data line low */
	P4DDR = EPORTO ;						/* Port 4, 5 out */
	for (i = 0; i < delay; i++ ){	    /*Wait 600 us */
	}
	P4DDR = EPORTI ;							/* Port 4, 5 in */
	for (i = 0; i < 20; i++ ){
		if (~P4DR & EEPIN){
			 ret_val = TRUE ;					/* set true if confirmed reset */
		Led(2, OFF) ;						   /* Led 2 off */
		}
	}
	for (i = 0; i < delay; i++ ){	    /*Wait 600 us */
	}
	return ret_val ;
}



/*************************************************************************
*
*  Chech the eeprom data for all channels
*
*************************************************************************/
short CheckEepChannel(void)
{

	short ch, i  ;

								/* read the on board eeprom */
	if (!(eep_type[7] & 0x10 ) && !(eep_type[7] & 0x09)){	/* ok sens || ok pc*/
		eep_type[7] |= 0x20 ;				/* Error before OK proved */
		eep_type[7] &= ~0x10 ;
		if (Eeprom(7, COPY_NV_SP)) {
			if (Eeprom(7, READ_SP)) {
				if (Eeprom(7, READ_APPREG)) {
					if (CheckADData(&packed_data[7][0]) &&
					CheckEepData(&packed_data[7][8])){			/*check checksum */
						eep_type[7] &= ~0x20 ;
						eep_type[7] |= 0x10 ;			/* OK from eeprom */
						for (i=0; i < NOIOCH; i++) {
							ch_stat[i] = packed_data[7][i+8] ;    /* copy setup */
						}
					}
				 }
			 }
		}
	}
	for (ch=0; ch < NOPSD-1; ch++) {
		if (!(eep_type[ch] & 0x10 ) && !(eep_type[ch]& 0x09) &&    /* ok sens || ok pc*/
				((ch_stat[ch<<1] & 0x1c) || (ch_stat[ch<<1] & 0x60))){ /* && pressure */
			eep_type[ch] |= 0x20 ;				/* Error before OK proved */
			eep_type[ch] &= ~0x10 ;
			if (Eeprom(ch, COPY_NV_SP)) {
				if (Eeprom(ch, READ_SP)) {
					if (Eeprom(ch, READ_APPREG)) {
						if (CheckADData(&packed_data[ch][0]) &&
							 CheckEepData(&packed_data[ch][8])){ /*check checksum */
							eep_type[ch] &= ~0x20 ;
							eep_type[ch] |= 0x10 ;		     /* OK from eeprom */
						   ch_stat[ch << 1] |= 0x80 ;			 /* New sensor flagged */
						 }
					}
				}
			}
		}
	}
}

/*************************************************************************
*
* Check AppData checksum
*
*************************************************************************/
unsigned char CheckADData(unsigned char *data)
{

	int				cnt ;
	unsigned char	csum, ok ;

	ok = FALSE ;
	csum = 0 ;
	for (cnt = 0 ; cnt < 7 ; cnt++) {
		if (*data != 0x00) {
			ok = TRUE ;
		}
		csum = crc[csum ^ *data++] ;
	}
	if ((csum == *data) && (ok == TRUE)) {
		return TRUE ;
	} else {
		return FALSE ;

	}
}


/*************************************************************************
*
* Check Eepdata checksum
*
*************************************************************************/
unsigned char CheckEepData(unsigned char *data)
{

	int				cnt ;
	unsigned char	csum, ok ;

	csum = 0 ;
	for (cnt = 8 ; cnt < (PACKED_DATA_SIZE -1) ; cnt++) {
		csum = crc[csum ^ *data++] ;
	}
	if (csum == *data) {
		return TRUE ;
	} else {
		return FALSE ;
	}
}

/*************************************************************************
*
* Make Eepdata checksum
*
*************************************************************************/
void MakeEepChksum(unsigned char *data)
{

	int				cnt ;
	unsigned char	csum ;

	csum = 0 ;
	for (cnt = 8 ; cnt < (PACKED_DATA_SIZE -1) ; cnt++) {
		csum = crc[csum ^ *data++] ;
	}
	*data = csum ;
}


