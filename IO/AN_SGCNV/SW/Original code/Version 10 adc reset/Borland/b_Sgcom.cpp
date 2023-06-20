/***** SGCOM.C *************************************************************
*
*     Program for signal convertion card, AN-SGCNV
*
*     Company: ARISTON Norway as
*
*     Author: Asle Straume
*
*     Date: 1-aug-96.
*
*************************************************************************/


#include <math.h>
#include <stdio.h>
/*#include "ioh8325.h"
#include "inth8325.h"
*/

#include "b_sg.h"
#include "b_sgext.h"


/*************************************************************************
*
*  Check action on received data
*
*************************************************************************/
short CheckAction(short pointer)
{
	short i, test, ret_val = TRUE ;
	unsigned char d_buff[PACKED_DATA_SIZE] ;

	switch (rx_buff[pointer]){						/* check action */
	case SEND_M_DATA :
		not_mes_data = rx_buff[pointer+2] ;		/* number of transmissions */
		not_raw_data = 0 ;
		not_cal_data = 0 ;
		if (not_mes_data) {							/* check if not 0 and send one */
			not_mes_data-- ;
		}
		if (!sendtail) {							/* make header ? */
			BuildHeader() ; 							/* Build send packet header */
			sendtail |= MAKE ; 				/* build tail*/
		}
		if ((sendtail & TX_ERR) ||
				((TX_SIZE - tx_indx) < 84 )){
			sendtail |= TX_ERR ;
		 } else {
			BuildMTData() ;						/* Build data p. for temp. */
		}
		if ((sendtail & TX_ERR) ||
				((TX_SIZE - tx_indx) < 42 )){
			sendtail |= TX_ERR ;
		 } else {
			BuildMPData();							/* Build data p. for pressure */
		}
		if ((sendtail & TX_ERR) ||
				((TX_SIZE - tx_indx) < 42 )){
			sendtail |= TX_ERR ;
		 } else {
			BuildMOData() ; 						/* Build data p. for other */
		}
		break ;
	case SEND_R_DATA :
		not_raw_data = rx_buff[pointer+2] ;		/* number of transmissions */
		not_mes_data = 0 ;
		not_cal_data = 0 ;
		if (not_raw_data) {							/* check if not 0 and send one */
			not_raw_data-- ;
		}
		if (!sendtail) {							/* make header ? */
			BuildHeader() ; 							/* Build send packet header */
			sendtail |= MAKE ; 				/* build tail*/
		}
		if ((sendtail & TX_ERR) ||
				((TX_SIZE - tx_indx) < 56 )){
			sendtail |= TX_ERR ;
		 } else {
			BuildRTData() ; 						/* Build data p. for temp. */
		}
		if ((sendtail & TX_ERR) ||
				((TX_SIZE - tx_indx) < 28 )){
			sendtail |= TX_ERR ;
		 } else {
			BuildRPData() ; 							/* Build data p. for pressure */
		}
		if ((sendtail & TX_ERR) ||
				((TX_SIZE - tx_indx) < 28 )){
			sendtail |= TX_ERR ;
		 } else {
			BuildROData() ; 					/* Build data p. for other */
		}
		break ;
	case SEND_C_DATA :
		not_cal_data = rx_buff[pointer+2] ;		/* number of transmissions */
		not_raw_data = 0 ;
		not_mes_data = 0 ;
		if (not_cal_data) {							/* check if not 0 and send one */
			not_cal_data-- ;
		}
		if (!sendtail) {							/* make header ? */
			BuildHeader() ; 							/* Build send packet header */
			sendtail |= MAKE ; 				/* build tail*/
		}
		if ((sendtail & TX_ERR) ||
				((TX_SIZE - tx_indx) < 56 )){
			sendtail |= TX_ERR ;
		 } else {
			BuildCalData() ;						/* Build calibration data */
		}
		break ;
	case SEND_CONFIG :
		if (!sendtail) {							/* make header ? */
			BuildHeader() ; 							/* Build send packet header */
			sendtail |= MAKE ; 				/* build tail*/
		}
		if ((sendtail & TX_ERR) ||
				((TX_SIZE - tx_indx) < 42 )){
			sendtail |= TX_ERR ;
		 } else {
			BuildConfData() ;							/* Build config data */
		}
		break ;
	case REC_EEP_DATA :
		RecEepData(pointer+2) ; 					/* new eeprom data for a channel*/
		break ;
	case REC_OFF_GAIN :
		RecOGData(pointer) ;							/* offset and gain from PC */
		break ;
	case REC_SET_UP :
		RecSetupData(pointer + 2) ;				/* setup for channels */
		break ;
	case REC_TBTR :
		time_b_temp = rx_buff[pointer+2]  ;		/* seconds between temp reading*/
		break ;
	case CMD_WRITE_EEP :
		for (i = 0; i < PACKED_DATA_SIZE; i++) {
			d_buff[i] = packed_data[rx_buff[pointer+2]][i] ; /*copy buffer */
		}
		Eeprom(rx_buff[pointer+2], WRITE_SP); 	/* write data to scratchpad */
		Eeprom(rx_buff[pointer+2], READ_SP);	/* Read data from scratchpad */
		test = TRUE ;
		for (i = 0; i < PACKED_DATA_SIZE; i++) {
			if (d_buff[i] != packed_data[rx_buff[pointer+2]][i]) {
				 test = FALSE; 									/*compare buffer */
			}
		}
		if (!sendtail) {								/* make header ? */
			BuildHeader() ; 							/* Build send packet header */
			sendtail |= MAKE ; 						/* build tail*/
		}
		if (!(sendtail & TX_ERR)){
			tx_buff[tx_indx++] = TX_WRITE_EEP ;		/* Command  */
			tx_buff[tx_indx++] = 1 ;					/* One byte data  */
			if (test == TRUE) {								/* write to eep OK */
				Eeprom(rx_buff[pointer+2], COPY_SP_NV);	/* copy data to NV-ram */
				tx_buff[tx_indx++] = 0 ;				/* Write status code OK*/
			} else {
				tx_buff[tx_indx++] = 1 ;				/* Write status code FAIL */
			}
		}
		break ;
	case CMD_WRITE_ADR :
		for (i = 0; i < PACKED_DATA_SIZE; i++) {
			d_buff[i] = packed_data[rx_buff[pointer+2]][i] ; /*copy buffer */
		}
		Eeprom(rx_buff[pointer+2], WRITE_APPREG); 	/* write data to adreg */
		Eeprom(rx_buff[pointer+2], READ_APPREG);		/* Read data from adreg */
		test = TRUE ;
		for (i = 0; i < PACKED_DATA_SIZE; i++) {
			if (d_buff[i] != packed_data[rx_buff[pointer+2]][i]) {
				 test = FALSE; 									/*compare buffer */
			}
		}
		if (!sendtail) {								/* make header ? */
			BuildHeader() ; 							/* Build send packet header */
			sendtail |= MAKE ; 						/* build tail*/
		}
		if (!(sendtail & TX_ERR)){
			tx_buff[tx_indx++] = TX_WRITE_ADR ;		/* Command  */
			tx_buff[tx_indx++] = 1 ;					/* One data byte  */
			if (test == TRUE){
				if (	  (rx_buff[pointer+3] == 'L')
					  && (rx_buff[pointer+4] == 'O')
					  && (rx_buff[pointer+5] == 'C')
					  && (rx_buff[pointer+6] == 'K')) { 	/* LOCK AP? */
					Eeprom(rx_buff[pointer+2], LOCK_APP);	/* LOCK APP REG. */
					test = FALSE ;
					for (i = 0; i < 100; i++) {
						Eeprom(rx_buff[pointer+2], READ_STATUS) ;	/* read status register */
						if (!(eep_status & 0x03)) {
							test = TRUE ;
							i = 100 ;									/* exit loop */
						}
					}
					if (test == TRUE ) {
						tx_buff[tx_indx++] = 0 ;				/* Write status code OK*/
					} else {
						tx_buff[tx_indx++] = 1 ;				/* Write status code FAIL*/
					}
				} else {
					tx_buff[tx_indx++] = 1 ;				/* Write status code FAIL */
				}
			} else {
				tx_buff[tx_indx++] = 1 ;				/* Write status code FAIL */
			}
		}
		break ;
	case SEND_EEP_DATA :
		if (!sendtail) {								/* make header ? */
			BuildHeader() ; 							/* Build send packet header */
			sendtail |= MAKE ; 						/* build tail*/
		}
		if ((sendtail & TX_ERR) ||
				((TX_SIZE - tx_indx) < PACKED_DATA_SIZE )){
			sendtail |= TX_ERR ;
		 } else {
			BuildEepData(rx_buff[pointer+2]) ;	/* Build eeprom data for a channel*/
		}
		break ;
	case CMD_READ_EEP :
		if (Eeprom(rx_buff[pointer+2], COPY_NV_SP)) {
			Eeprom(rx_buff[pointer+2], READ_SP) ;
			Eeprom(rx_buff[pointer+2], READ_APPREG) ;
			if (CheckADData(&packed_data[rx_buff[pointer+2]][0]) &&
				 CheckEepData(&packed_data[rx_buff[pointer+2]][8])){ /*check checksum */
				eep_type[rx_buff[pointer+2]] = 0x10 ;         /* OK from eeprom */
			} else {
				eep_type[rx_buff[pointer+2]] = 0x20 ;         /* Error from eeprom */
			}
		}
		break ;
	case REC_FILTER :
		p_filter = rx_buff[pointer+2] ;
		t_filter = rx_buff[pointer+3] ;
		o_filter = rx_buff[pointer+4] ; 					/* set new filter */
		break ;                                /* press, temp, other */
	case SEND_CARD_STAT :
		if (!sendtail) {								/* make header ? */
			BuildHeader() ; 							/* Build send packet header */
			sendtail |= MAKE ; 						/* build tail*/
		}
		if (!(sendtail & TX_ERR)){
			BuildCSData() ; 							/* Build datablock for status */
		}
		break ;
	case SEND_SER_NO :								/* Serial no from eeprom */
		if (!sendtail) {								/* make header ? */
			BuildHeader() ; 							/* Build send packet header */
			sendtail |= MAKE ; 						/* build tail*/
		}
		if (!(sendtail & TX_ERR)){
			tx_buff[tx_indx++] = TX_SER_NO ;
			tx_buff[tx_indx++] = 10 ;
			tx_buff[tx_indx++] = rx_buff[pointer+2] ; /*channel no */
			Eeprom(rx_buff[pointer+2], READ_ROM) ;		/* EEP serial number */
			tx_indx += 8 ;
			Eeprom(rx_buff[pointer+2], READ_STATUS) ;		/* EEP status register */
			tx_buff[tx_indx++] = eep_status ;        /* status */
		}
		break ;
	case SEND_ACK : 									/* No more data, send ack. */
		if (sendtail) {
			 BuildTail(TX_ACK, sendtail & TX_ERR) ;	/* Build t. w/ err code */
		}
		ret_val = FALSE ;
		break ;
	case NO_MORE_DATA :								/* No more data */
		if (sendtail) {
			 BuildTail(NO_MORE_DATA,  sendtail & TX_ERR) ;/* Build tail */
		}
		ret_val = FALSE ;
		break ;
	case 255 :								/* ASt mark TEST ONLY read from eeprom*/
		Eeprom(rx_buff[pointer+2], COPY_NV_SP);	/* Copy data to scratchpad */
		break ;
	case 254 :								/* ASt mark TEST ONLY Store in eeprom*/
		Eeprom(rx_buff[pointer+2], COPY_SP_NV) ; 	/* Copy data to eeprom*/
		break ;
	default:												/* I don't understand this */
		break ;
	}
	return ret_val ;
}


/*************************************************************************
*
* Build send packet header
*
*************************************************************************/
void BuildHeader(void)
{
	tx_indx = 0;

	tx_buff[tx_indx++] = STX ;					/* STX */
	tx_buff[tx_indx++] = STX ;					/* STX */
	tx_buff[tx_indx++] = rx_buff[rx_start+1] ; /* Rx address */
	tx_buff[tx_indx++] = my_address ;		    /* Tx address */
	tx_buff[tx_indx++] = 0 ;						  /* packlen HB, dont know yet */
	tx_buff[tx_indx++] = 0 ;					 /* packlen LB, dont know yet */
}

/*************************************************************************
*
* Build datablock for measured pressure data
*
*************************************************************************/
void BuildMPData(void)
{

	short i, ntna;
	char senddata[4] ;

	tx_buff[tx_indx++] = TX_MP_DATA ;			/* action */
	ntna = tx_indx++ ;									/* remember index */
	for (i = 0; i < NOIOCH; i++) {
		if ((ch_stat[i] & 0x0c) == 0x0c) {        /* find pressure sensors */
			*((float*)&senddata[0]) = mes_data[i] ; 	  /* data */
			tx_buff[tx_indx++] = i ;				/* channel number */
			tx_buff[tx_indx++] = senddata[0] ; 			  /* data  LB */
			tx_buff[tx_indx++] = senddata[1] ;			  /* data   */
			tx_buff[tx_indx++] = senddata[2] ; 			  /* data   */
			tx_buff[tx_indx++] = senddata[3] ; 			  /* data  HB */
			tx_buff[tx_indx++] = ch_stat[i] ;	  /* cal/conv status */
		}
	}
	tx_buff[ntna] = tx_indx - ntna - 1  ;			     /* length of data block */
}

/*************************************************************************
*
* Build datablock for measured temperature data
*
*************************************************************************/
void BuildMTData(void)
{

	short i, ntna;
	char senddata[4];

	tx_buff[tx_indx++] = TX_MT_DATA ;			/* action */
	ntna = tx_indx++ ;									/* remember index */
	for (i = 0; i < NOIOCH; i++) {
		if ((ch_stat[i] & 0x0c)  == 0x04) {        /* find temperature sensors */
			*((float*)&senddata[0]) = mes_data[i] ; 							  /* data */
			tx_buff[tx_indx++] = i ;				/* channel number */
			tx_buff[tx_indx++] = senddata[0] ; 			  /* data  LB */
			tx_buff[tx_indx++] = senddata[1] ;			  /* data   */
			tx_buff[tx_indx++] = senddata[2] ; 			  /* data   */
			tx_buff[tx_indx++] = senddata[3] ; 			  /* data  HB */
			tx_buff[tx_indx++] = ch_stat[i] ;	  /* cal/conv status */
		}
	}
	tx_buff[ntna] = tx_indx - ntna - 1 ;			    /* length of data block */
}

/*************************************************************************
*
* Build datablock for other measured data
*
*************************************************************************/
void BuildMOData(void)
{

	short i, ntna;
	char senddata[4] ;

	tx_buff[tx_indx++] = TX_MO_DATA ;			/* action */
	ntna = tx_indx++ ;									/* remember index */
	for (i = 0; i < NOIOCH; i++) {
		if ((ch_stat[i] & 0x0c)  == 0x08) {        /* find other sensors */
			*((float*)&senddata[0]) = mes_data[i] ; 							  /* data */
			tx_buff[tx_indx++] = i ;				/* channel number */
			tx_buff[tx_indx++] = senddata[0] ; 			  /* data  LB */
			tx_buff[tx_indx++] = senddata[1] ;			  /* data   */
			tx_buff[tx_indx++] = senddata[2] ; 			  /* data   */
			tx_buff[tx_indx++] = senddata[3] ; 			  /* data  HB */
			tx_buff[tx_indx++] = ch_stat[i] ;	  /* cal/conv status */
		}
	}
	tx_buff[ntna] = tx_indx - ntna - 1  ;			    /* length of data block */
}

/*************************************************************************
*
* Build datablock for raw pressure data
*
*************************************************************************/
void BuildRPData(void)
{

	short i, ntna ;
	char senddata[2];

	tx_buff[tx_indx++] = TX_RP_DATA ;			/* action */
	ntna = tx_indx++ ;									/* remember index */
	for (i = 0; i < NOIOCH; i++) {
		if ((ch_stat[i] & 0x0c) == 0x0c) {        /* find pressure sensors */
			*((unsigned short*)&senddata[0]) = raw_data[i] ; 							  /* data */
			tx_buff[tx_indx++] = i ;				/* channel number */
			tx_buff[tx_indx++] = senddata[0] ; 			  /* data  LB */
			tx_buff[tx_indx++] = senddata[1] ;			  /* data  HB */
			tx_buff[tx_indx++] = ch_stat[i] ;	  /* cal/conv status */
		}
	}
	tx_buff[ntna] = tx_indx - ntna - 1  ;			    /* length of data block */
}

/*************************************************************************
*
* Build datablock for raw temperature data
*
*************************************************************************/
void BuildRTData(void)
{

	short i, ntna ;
	char senddata[2];

	tx_buff[tx_indx++] = TX_RT_DATA ;			/* action */
	ntna = tx_indx++ ;									/* remember index */
	for (i = 0; i < NOIOCH; i++) {
		if ((ch_stat[i] & 0x0c)  == 0x04) {        /* find temperature sensors */
			*((unsigned short*)&senddata[0]) = raw_data[i] ; 							  /* data */
			tx_buff[tx_indx++] = i ;				/* channel number */
			tx_buff[tx_indx++] = senddata[0] ; 			  /* data  LB */
			tx_buff[tx_indx++] = senddata[1] ;			  /* data  HB */
			tx_buff[tx_indx++] = ch_stat[i] ;	  /* cal/conv status */
		}
	}
	tx_buff[ntna] = tx_indx - ntna - 1  ;			    /* length of data block */
}

/*************************************************************************
*
* Build datablock for other raw data
*
*************************************************************************/
void BuildROData(void)
{

	short i, ntna ;
	char senddata[2];

	tx_buff[tx_indx++] = TX_RO_DATA ;			/* action */
	ntna = tx_indx++ ;									/* remember index */
	for (i = 0; i < NOIOCH; i++) {
		if ((ch_stat[i] & 0x0c)  == 0x08) {        /* find other sensors */
			*((unsigned short*)&senddata[0]) = raw_data[i] ; 							  /* data */
			tx_buff[tx_indx++] = i ;				/* channel number */
			tx_buff[tx_indx++] = senddata[0] ; 			  /* data  LB */
			tx_buff[tx_indx++] = senddata[1] ;			  /* data  HB */
			tx_buff[tx_indx++] = ch_stat[i] ;	  /* cal/conv status */
		}
	}
	tx_buff[ntna] = tx_indx - ntna - 1  ;			    /* length of data block */
}

/*************************************************************************
*
* Build datablock for calibration data
*
*************************************************************************/
void BuildCalData(void)
{

	short i, ntna ;
	char  senddata[2];

	tx_buff[tx_indx++] = TX_CAL_DATA ;				/* action */
	ntna = tx_indx++ ;									/* remember index */
	for (i = 0; i < NOIOCH; i++) {
		*((unsigned short*)&senddata[0]) = cal_data[i] ;   /* data */
		tx_buff[tx_indx++] = i ;						/* channel number */
		tx_buff[tx_indx++] = senddata[0] ; 			  /* data  LB */
		tx_buff[tx_indx++] = senddata[1] ;			  /* data  HB */
		tx_buff[tx_indx++] = ch_stat[i] ;			  /* cal status */
	}
	tx_buff[ntna] = tx_indx - ntna - 1  ;			  /* length of data block */
}

/*************************************************************************
*
* Build datablock for configuration data
*
*************************************************************************/
void BuildConfData(void)
{

	short i, ntna ;

	tx_buff[tx_indx++] = TX_CONFIG ;				  /* action */
	ntna = tx_indx++ ;								  /* remember index */
	for (i = 0; i < NOIOCH; i++) {
		tx_buff[tx_indx++] = i ;					  /* channel number */
		tx_buff[tx_indx++] = ch_stat[i] ; 			  /* channel setup */
		if (i < 8 ){
			tx_buff[tx_indx++] = eep_type[i] ;			  /* eeprom setup */
		} else {
			tx_buff[tx_indx++] = 0 ;						  /* dummy */
		}
	}
	tx_buff[ntna] = tx_indx - ntna - 1  ;			    /* length of data block */
}

/*************************************************************************
*
* Build datablock for eeprom data
*
*************************************************************************/
void BuildEepData(short channel)
{

	short i, ntna;

	tx_buff[tx_indx++] = TX_EEP_DATA ;			/* action */
	ntna = tx_indx++ ;									/* remember index */
	tx_buff[tx_indx++] = channel;					/* channel number */
	for (i = 0; i < PACKED_DATA_SIZE; i++) {
		tx_buff[tx_indx++] = packed_data[channel][i]; /* data */
	}
	tx_buff[ntna] = tx_indx - ntna - 1  ;	  /* length of data block */
}

/*************************************************************************
*
* Build datablock for card status
*
*************************************************************************/
void BuildCSData(void)
{

	short ntna ;

	tx_buff[tx_indx++] = TX_CARD_STAT ;			/* action */
	ntna = tx_indx++ ;									/* remember index */
	tx_buff[tx_indx++] = (unsigned char) VERSION; /* software version */
	tx_buff[tx_indx++] = (unsigned char) my_address; /* my address */
	tx_buff[tx_indx++] = (unsigned char) RX_SIZE; /* rx buffer size */
	tx_buff[tx_indx++] = (unsigned char) TX_SIZE; /* tx buffer size */
	tx_buff[ntna] = tx_indx - ntna - 1 ;			    /* length of data block */
}


/*************************************************************************
*
* Build  packet tail
*
*************************************************************************/
void BuildTail(unsigned char type, unsigned char error)
{

	tx_buff[tx_indx++] = type ;					/* action end */
	tx_buff[tx_indx++] = error ;				/* error code */

	tx_buff[4] = tx_indx >> 8 ;				   /* packet len high */
	tx_buff[5] = tx_indx ;							/* correct length because stx's*/

	tx_buff[tx_indx++] = CalcTxChecksum(tx_indx) ; /* Get checksum */

	tx_buff[tx_indx++] = ETX ;					/* ETX */

	tx_bytes = tx_indx;							/*bytes to send */
	tx_indx = 0;									/* reset cunter */
	tx_complete = FALSE;
	wait_for_pc = PC_SLOW;						/* delay before send */
	TxDriver(ON);									/* driver on */
}

/*************************************************************************
*
* Receive eeprom data
*
*************************************************************************/
void RecEepData(short pointer)
{

	short i, ch ;
	unsigned char temp_data[PACKED_DATA_SIZE] ;
	unsigned char	*e_data, *a_data ;

	ch = rx_buff[pointer++] ;								/* get channel */
	a_data = &rx_buff[pointer] ;
	e_data = &rx_buff[pointer + 8] ;

	if (CheckEepData(e_data) && CheckADData(a_data) &&
			(rx_buff[pointer + PACKED_DATA_SIZE] & 0x01)) { /* check legale packet */
		for (i = 0; i < PACKED_DATA_SIZE; i++) {
			packed_data[ch][i] = rx_buff[pointer++]; 			/* copy data */
		}
		eep_type[ch] &= ~0x0f ;
		eep_type[ch] |= 0x09 ;                       /* use PC data */
	} else {
		eep_type[ch] &= ~0x0f ;
		eep_type[ch] &= ~0x02 ;								/* fail from pc */
	}
}


/*************************************************************************
*
* Receive offset and gain
*
*************************************************************************/
void RecOGData(unsigned char pointer)
{

	short i, number, channel ;

	number = rx_buff[++pointer] / 5 ; 	/* number of channels (5 bytes each ch) */
	for (i = 0; i < number; i++) {
	  channel = rx_buff[++pointer] ;                 /* Remember channel */
	  offset[channel] = rx_buff[++pointer] * 256 + rx_buff[++pointer] ;
	  gain[channel] = 1.0 + (float)((rx_buff[++pointer]* 256 +
							  rx_buff[++pointer])/100000.0) ;   /*gain*/
	}
}


/*************************************************************************
*
* Receive setup
*
*************************************************************************/
void RecSetupData(unsigned char pointer)
{

	short i ;

	for (i = 0; i < NOIOCH; i++) {
	  ch_stat[i] &= ~0x1c ;
	  ch_stat[i] |= (rx_buff[pointer++] & 0x1c);  /* Setup for channel */
	}
}


/*************************************************************************
*
* Calculate tx checksum
*
*************************************************************************/
unsigned char CalcTxChecksum(short pack_len)
{

	int				cnt ;
	unsigned char	csum ;

	csum = 0 ;
	for (cnt = 2 ; cnt < (pack_len) ; cnt++) {
		csum = crc[csum ^ tx_buff[cnt]] ;
	}
	return csum ;
}

