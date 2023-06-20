/*******************************************************

*
*     Program for signal convertion card, AN-SGCNV
*
*     Company: ARISTON Norway as
*
*     Author: Thierry Pottier
*
*    * @file     SGcom.c
	 * @brief    SGcom Header File
	 * @version  V0.00
	 * @date     18. October 2022
	 * @note
*

*******************************************************/

#include "SGcom.h"
#include <string.h>
#include "PinName.h"
#include "Routine.h"
#include "SGeep.h"
#include "LocalEEprom.h"


// I/O Registers definitions
#include <avr64db64.h>
#include <stdio.h>
#include "delay.h"
#include <iobits.h>
#include "math.h"
#include "float.h"


// Standard definitions
#include <stddef.h>

/*************************************************************************
*
*  Check action on received data
*
*************************************************************************/
unsigned int CheckAction(unsigned int data)
{
    short i, test, ret_val = TRUE ;
    unsigned char d_buff[PACKED_DATA_SIZE] ;
    unsigned int pointer=data;
    switch ( rx_buff[pointer] ) {                      /* check action */
        case SEND_M_DATA :
        not_mes_data = rx_buff[pointer+2] ;     /* number of transmissions */
        not_raw_data = 0 ;
        not_cal_data = 0 ;
        if ( not_mes_data ) {                         /* check if not 0 and send one */
            not_mes_data-- ;
        }
        //if ( !sendtail )
        if ( sendtail==0 ) 
        {                            /* make header ? */
            BuildHeader() ;                             /* Build send packet header */
            sendtail |= MAKE ;              /* build tail*/
        }
        if ( (sendtail & TX_ERR) || ((TX_SIZE - tx_indx) < 10 ) ) {
            sendtail |= TX_ERR ;
        } else {
            BuildMTData() ;                     /* Build data p. for temp. */
        }
        if ( (sendtail & TX_ERR) || ((TX_SIZE - tx_indx) < 10 ) ) {
            sendtail |= TX_ERR ;
        } else {
            BuildMPData();                          /* Build data p. for pressure */
        }
        if ( (sendtail & TX_ERR) || ((TX_SIZE - tx_indx) < 10 ) ) {
            sendtail |= TX_ERR ;
        } else {
            BuildMOData() ;                         /* Build data p. for other */
        }
        if ( (sendtail & TX_ERR) || ((TX_SIZE - tx_indx) < 10 ) ) {
            sendtail |= TX_ERR ;
        } else {
            BuildWHData();                        // Send high level and washtrac
        }
        break ; 
        
        case SEND_R_DATA :      // Commande 13 Ask SGCNV to send raw data
        not_raw_data = rx_buff[pointer+2] ;     /* number of transmissions */   
        not_raw_data=4; // debugg 01-02-23
        not_mes_data = 0 ;
        not_cal_data = 0 ;
        if ( not_raw_data ) 
        {                         /* check if not 0 and send one */
            not_raw_data-- ;
        }
        //if ( !sendtail ) 
        if ( sendtail==0 ) 
        {                            /* make header ? */
            BuildHeader() ;                             /* Build send packet header */
            sendtail |= MAKE ;              /* build tail*/
        }
        if ( (sendtail & TX_ERR) ||
             ((TX_SIZE - tx_indx) < 56 ) ) 
        {
            sendtail |= TX_ERR ;
        } 
        else 
        {
            BuildRTData() ;                         /* Build data p. for temp. */
        }
        if ( (sendtail & TX_ERR) ||
             ((TX_SIZE - tx_indx) < 28 ) ) 
        {
            sendtail |= TX_ERR ;
        } 
        else 
        {
            BuildRPData() ;                             /* Build data p. for pressure */
        }
        if ( (sendtail & TX_ERR) ||
             ((TX_SIZE - tx_indx) < 28 ) ) 
        {
            sendtail |= TX_ERR ;
        } 
        else 
        {
            BuildROData() ;                     /* Build data p. for other */
        }
        break ;
    case SEND_C_DATA :
        not_cal_data = rx_buff[pointer+2] ;     /* number of transmissions */
        not_raw_data = 0 ;
        not_mes_data = 0 ;
        if ( not_cal_data ) {                         /* check if not 0 and send one */
            not_cal_data-- ;
        }
        //if ( !sendtail )
        if ( sendtail==0 )  
        {                            /* make header ? */
            BuildHeader() ;                             /* Build send packet header */
            sendtail |= MAKE ;              /* build tail*/
        }
        if ( (sendtail & TX_ERR) ||
             ((TX_SIZE - tx_indx) < 56 ) ) {
            sendtail |= TX_ERR ;
        } else {
            BuildCalData() ;                        /* Build calibration data */
        }
        break ;
    case SEND_CONFIG :
        //if ( !sendtail )
        if ( sendtail==0 ) 
        {                            /* make header ? */
            BuildHeader() ;                             /* Build send packet header */
            sendtail |= MAKE ;              /* build tail*/
        }
        if ( (sendtail & TX_ERR) ||
             ((TX_SIZE - tx_indx) < 42 ) ) {
            sendtail |= TX_ERR ;
        } else {
            BuildConfData() ;                           /* Build config data */
        }
        break ;
    case REC_EEP_DATA :
        RecEepData(pointer+2) ;                     /* new eeprom data for a channel*/
        break ;
    case REC_OFF_GAIN :
        RecOGData(pointer) ;                            /* offset and gain from PC */
        break ;
    case REC_SET_UP :
        RecSetupData(pointer + 2) ;             /* setup for channels */
        break ;
    case REC_TBTR :
        time_b_temp = rx_buff[pointer+2]  ;     /* seconds between temp reading*/
        time_b_cnt = time_b_temp ;                  /* reload counter */
        break ;
    case CMD_WRITE_EEP :
        test = TRUE ;
        if ( eep_type[rx_buff[pointer+2]>>1] & 0x09 ) {
            for ( i = 0; i < PACKED_DATA_SIZE; i++ ) {
                d_buff[i] = packed_data[rx_buff[pointer+2]>>1][i] ; /*copy buffer */
            }
            //if ( !Eeprom(rx_buff[pointer+2]>>1, WRITE_SP) ) 
            if ( Eeprom(rx_buff[pointer+2]>>1, WRITE_SP)==0 ) 
            {
                test= FALSE ;                               /* write data to scratchpad */
            }
            //if ( !Eeprom(rx_buff[pointer+2]>>1, READ_SP) )
            if ( Eeprom(rx_buff[pointer+2]>>1, READ_SP)==0 ) 
            {
                test = FALSE ;                          /* Read data from scratchpad */
            }
            for ( i = 0; i < PACKED_DATA_SIZE; i++ ) {
                if ( d_buff[i] != packed_data[rx_buff[pointer+2]>>1][i] ) {
                    test = FALSE;                                  /*compare buffer */
                }
            }
        } else {
            test = FALSE ;
        }
        //if ( !sendtail )   
        if ( sendtail==0 ) 
        {                                /* make header ? */
            BuildHeader() ;                             /* Build send packet header */
            sendtail |= MAKE ;                      /* build tail*/
        }
        //if ( !(sendtail & TX_ERR) )
        if ( (sendtail & TX_ERR)==0 ) 
        {
            tx_buff[tx_indx++] = TX_WRITE_EEP ;     /* Command  */
            tx_buff[tx_indx++] = 1 ;                    /* One byte data  */
            tx_buff[tx_indx] = 1 ;              /* Write status code FAIL */
            if ( test == TRUE ) {                             /* write to eep OK */
                if ( Eeprom(rx_buff[pointer+2]>>1, COPY_SP_NV) ) {    /* copy data to NV-ram */
                    tx_buff[tx_indx] = 0 ;              /* Write status code OK*/
                }
            }
            tx_indx++ ;                                     /* Write status code FAIL */
        }
        break ;
    case CMD_WRITE_ADR :
        test = TRUE ;
        if ( eep_type[rx_buff[pointer+2]>>1] & 0x09 ) {
            for ( i = 0; i < PACKED_DATA_SIZE; i++ ) {
                d_buff[i] = packed_data[rx_buff[pointer+2]>>1][i] ; /*copy buffer */
            }
            //if ( !Eeprom(rx_buff[pointer+2]>>1, WRITE_APPREG) )   
            if ( Eeprom(rx_buff[pointer+2]>>1, WRITE_APPREG)==0 ) 
            {
                test = FALSE ;                      /* write data to adreg */
            }
            //if ( !Eeprom(rx_buff[pointer+2]>>1, READ_APPREG) ) 
            if ( Eeprom(rx_buff[pointer+2]>>1, READ_APPREG)==0 ) 
            {
                test = FALSE ;                          /* Read data from adreg */
            }
            for ( i = 0; i < PACKED_DATA_SIZE; i++ ) {
                if ( d_buff[i] != packed_data[rx_buff[pointer+2]>>1][i] ) {
                    test = FALSE;                                  /*compare buffer */
                }
            }
        } else {
            test = FALSE ;
        }
        //if ( !sendtail )  
        if ( sendtail==0 ) 
        {                                /* make header ? */
            BuildHeader() ;                             /* Build send packet header */
            sendtail |= MAKE ;                      /* build tail*/
        }
            //if ( !(sendtail & TX_ERR) ) 
            if ( (sendtail & TX_ERR)==0 ) 
            {
                tx_buff[tx_indx++] = TX_WRITE_ADR ;     /* Command  */
                tx_buff[tx_indx++] = 1 ;                    /* One data byte  */
                if ( test == TRUE ) 
                {
                        if (    (rx_buff[pointer+3] == 'L')
                             && (rx_buff[pointer+4] == 'O')
                             && (rx_buff[pointer+5] == 'C')
                             && (rx_buff[pointer+6] == 'K') ) 
                        {     /* LOCK AP? */
                                test = FALSE ;
                                if ( Eeprom(rx_buff[pointer+2]>>1, LOCK_APP) )
                                {   /* LOCK APP REG. */                                   
                                    test = TRUE ;
                                    
                                }
                                if ( test == TRUE ) {
								tx_buff[tx_indx++] = 0 ;                /* Write status code OK*/
                                } 
                                else {
                                    tx_buff[tx_indx++] = 1 ;                /* Write status code FAIL*/
                                } 
                                
                        }             
                        else if (  (rx_buff[pointer+3] == 'U')
                                && (rx_buff[pointer+4] == 'N')
                                && (rx_buff[pointer+5] == 'L')
                                && (rx_buff[pointer+6] == 'O')
                                && (rx_buff[pointer+7] == 'C')
                                && (rx_buff[pointer+8] == 'K') ) 
                        {     /* UNLOCK AP? */
                                test = TRUE ;
                                SerielNummerLock= UNLOCK_BYTE;
                                EEpromStatusByte=DEFAULT_EEPROM_STATUS;  
                                if ( test == TRUE ) {
                                    tx_buff[tx_indx++] = 0 ;                /* Write status code OK*/
                                } 
                                else {
                                    tx_buff[tx_indx++] = 1 ;                /* Write status code FAIL*/
                                } 
                        }
                        else 
                        {
                            tx_buff[tx_indx++] = 1 ;                /* Write status code FAIL */
                        }
                        
                        if ( test == TRUE ) {
                            tx_buff[tx_indx++] = 0 ;                /* Write status code OK*/
                        } else {
                            tx_buff[tx_indx++] = 1 ;                /* Write status code FAIL*/
                        }
                } 
                else 
                {   tx_buff[tx_indx++] = 1 ;                /* Write status code FAIL */
                }
        }
        break ;
    case SEND_EEP_DATA :
        //if ( !sendtail ) 
        if ( sendtail==0 ) 
        {                                /* make header ? */
            BuildHeader() ;                             /* Build send packet header */
            sendtail |= MAKE ;                      /* build tail*/
        }
        if ( (sendtail & TX_ERR) ||
             ((TX_SIZE - tx_indx) < PACKED_DATA_SIZE ) ) {
            sendtail |= TX_ERR ;
        } else {
            BuildEepData(rx_buff[pointer+2]) ;  /* Build eeprom data for a channel*/
        }
        break ;
    case CMD_READ_EEP :
        eep_type[rx_buff[pointer+2]>>1] |= 0x20 ;     /* Error before read */
        eep_type[rx_buff[pointer+2]>>1] &= ~0x10 ;
        if ( Eeprom(rx_buff[pointer+2]>>1, COPY_NV_SP) ) {
            if ( Eeprom(rx_buff[pointer+2]>>1, READ_SP) ) {
                if ( Eeprom(rx_buff[pointer+2]>>1, READ_APPREG) ) {
                    if ( CheckADData(&packed_data[rx_buff[pointer+2]>>1][0]) &&
                         CheckEepData(&packed_data[rx_buff[pointer+2]>>1][8]) ) { /*check checksum */
                        eep_type[rx_buff[pointer+2]>>1] |= 0x10 ;     /* OK from eeprom */
                        eep_type[rx_buff[pointer+2]>>1] &= ~0x20 ;     /* Error from eeprom */
                    }
                }
            }
        }
        break ;
    case REC_FILTER :
        p_filter = rx_buff[pointer+2] ;
        t_filter = rx_buff[pointer+3] ;
        o_filter = rx_buff[pointer+4] ;                     /* set new filter */
        break ;                    /* press, temp, other */
    case SEND_CARD_STAT :
        //if ( !sendtail ) 
        if ( sendtail==0 ) 
        {                                /* make header ? */
            BuildHeader() ;                             /* Build send packet header */
            sendtail |= MAKE ;                      /* build tail*/
        }
        //if ( !(sendtail & TX_ERR) ) 
        if ( (sendtail & TX_ERR)==0 ) 
        {
            BuildCSData() ;                             /* Build datablock for status */
        }
        break ;
    case SEND_SER_NO :                              /* Serial no from eeprom */
        //if ( !sendtail ) 
        if ( sendtail==0 ) 
        {                                /* make header ? */
            BuildHeader() ;                             /* Build send packet header */
            sendtail |= MAKE ;                      /* build tail*/
        }
        //if ( !(sendtail & TX_ERR) ) 
        if ( (sendtail & TX_ERR)==0 ) 
        {
            tx_buff[tx_indx++] = TX_SER_NO ;
            tx_buff[tx_indx++] = 10 ;
            tx_buff[tx_indx++] = rx_buff[pointer+2] ; /*channel no */
            if ( Eeprom(rx_buff[pointer+2]>>1, READ_ROM) ) 
            {  /* EEP serial number */
                tx_indx += 8 ;
                if ( Eeprom(rx_buff[pointer+2]>>1, READ_STATUS) ) { /* EEP status register */
                    tx_buff[tx_indx++] = eep_status ;    /* status */
                } else {
                    tx_buff[tx_indx++] = 0x0f ;          /* status */
                }
            } 
            else 
            {
                for ( i = 0; i < 9; i++ ) 
                {
                    tx_buff[tx_indx++] = 0x00 ;             /*  send 0's when error */
                }
            }
        }
        break ;
    case SEND_ACK :                                     /* No more data, send ack. */
    case NO_MORE_DATA :                             /* No more data */
        if ( sendtail ) 
        {
            if ( rx_buff[pointer] == SEND_ACK ) 
            {
                BuildTail(TX_ACK, sendtail & TX_ERR) ;  /* Build t. w/ err code */
            } 
            else 
            {
                BuildTail(NO_MORE_DATA,  sendtail & TX_ERR) ;/* Build tail */
            }
        }
        ret_val = FALSE ;
        break ;
    default:                                                /* I don't understand this */
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

    tx_buff[tx_indx++] = STX ;                  /* STX */
    tx_buff[tx_indx++] = STX ;                  /* STX */
    tx_buff[tx_indx++] = rx_buff[rx_start+1] ; /* Rx address */
    tx_buff[tx_indx++] = MYADRESS_LOCAL ;           /* Tx address */
    tx_buff[tx_indx++] = 0 ;                          /* packlen HB, dont know yet */
    tx_buff[tx_indx++] = 0 ;                     /* packlen LB, dont know yet */
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

    tx_buff[tx_indx++] = TX_MP_DATA ;           /* action */
    ntna = tx_indx++ ;                                  /* remember index */
    for ( i = 0; i < NOIOCH; i++ ) {
        if ( (ch_stat[i] & 0x0c) == 0x0c ) {    /* find pressure sensors */
            *((float*)&senddata[0]) = mes_data[i] ;       /* data */
            tx_buff[tx_indx++] = i ;                /* channel number */
            tx_buff[tx_indx++] = (ch_stat[i]   ) ;     /* cal/conv status */
//            tx_buff[tx_indx++] = senddata[3] ;
//            tx_buff[tx_indx++] = senddata[2] ;
//            tx_buff[tx_indx++] = senddata[1] ;
//            tx_buff[tx_indx++] = senddata[0] ;   
            tx_buff[tx_indx++] = senddata[0] ;
            tx_buff[tx_indx++] = senddata[1] ;
            tx_buff[tx_indx++] = senddata[2] ;
            tx_buff[tx_indx++] = senddata[3] ;
        }
    }
    tx_buff[ntna] = tx_indx - ntna - 1  ;                /* length of data block */
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

    tx_buff[tx_indx++] = TX_MT_DATA ;           /* action */
    ntna = tx_indx++ ;                                  /* remember index */
    for ( i = 0; i < NOIOCH; i++ ) {
        if ( (ch_stat[i] & 0x0c)  == 0x04 ) {    /* find temperature sensors */
            *((float*)&senddata[0]) = mes_data[i] ;      /* data */
            tx_buff[tx_indx++] = i ;                /* channel number */
            tx_buff[tx_indx++] = ( ch_stat[i]  ) ;     /* cal/conv status */
//            tx_buff[tx_indx++] = senddata[3] ;
//            tx_buff[tx_indx++] = senddata[2] ;
//            tx_buff[tx_indx++] = senddata[1] ;
//            tx_buff[tx_indx++] = senddata[0] ;     
            
            tx_buff[tx_indx++] = senddata[0] ;
            tx_buff[tx_indx++] = senddata[1] ;
            tx_buff[tx_indx++] = senddata[2] ;
            tx_buff[tx_indx++] = senddata[3] ;
        }
    }
    tx_buff[ntna] = tx_indx - ntna - 1 ;                /* length of data block */
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

    tx_buff[tx_indx++] = TX_MO_DATA ;           /* action */
    ntna = tx_indx++ ;                                  /* remember index */
    for ( i = 0; i < NOIOCH; i++ ) {
        if ( (ch_stat[i] & 0x0c)  == 0x08 ) {    /* find other sensors */
            *((float*)&senddata[0]) = mes_data[i] ;                               /* data */
            tx_buff[tx_indx++] = i ;                /* channel number */
            tx_buff[tx_indx++] = ch_stat[i] ;     /* cal/conv status */
//            tx_buff[tx_indx++] = senddata[3] ;
//            tx_buff[tx_indx++] = senddata[2] ;
//            tx_buff[tx_indx++] = senddata[1] ;
//            tx_buff[tx_indx++] = senddata[0] ;
            tx_buff[tx_indx++] = senddata[0] ;
            tx_buff[tx_indx++] = senddata[1] ;
            tx_buff[tx_indx++] = senddata[2] ;
            tx_buff[tx_indx++] = senddata[3] ;
        }
    }
    tx_buff[ntna] = tx_indx - ntna - 1  ;               /* length of data block */
}

/*************************************************************************
*
* Build datablock for highlevel and washtrac
*
*************************************************************************/
//#define SELECT_EXTBOARD_1   TSTBIT (PORTD.IN,0)
//#define SELECT_EXTBOARD_2   TSTBIT (PORTD.IN,1)

void BuildWHData(void)
{
    short ntna, i ; 
    /*  // AN-SGCNV_EXT not connected
        if ( P7DR & 0x80 )
    {
        return;
    } 
    */
    if (SELECT_EXTBOARD_1 ==1)  // AN-SGCNV_EXT not connected
    {    return; 
    }
    else {
        tx_buff[tx_indx++] = TX_WH_DATA ;               // action
        ntna = tx_indx++ ;                              // remember index
        for ( i = 0; i< NOWT; i++ ) {
            unsigned short WTCnt = washtrac[i];
            washtrac[i] = 0;
            tx_buff[tx_indx++] = WTCnt & 0xff;         // add washtrack
            tx_buff[tx_indx++] = (WTCnt >> 8) & 0xff;         // add washtrack
        }
        tx_buff[tx_indx++] = highlevel;                 // add highlevel
        {
            unsigned short TNow = ms_cnt;
            ms_cnt = 0;
            tx_buff[tx_indx++] = TNow & 0xff;               // add washtrack
            tx_buff[tx_indx++] = (TNow >> 8) & 0xff;        // add washtrack
        }
        tx_buff[ntna] = tx_indx - ntna - 1 ;            // length of data block
    }
}

/*************************************************************************
*
* Build datablock for raw pressure data
*
*************************************************************************/
void BuildRPData(void)
{

    short i, ntna ;
//    char senddata[2];

    tx_buff[tx_indx++] = TX_RP_DATA ;           /* action */
    ntna = tx_indx++ ;                                  /* remember index */
    for ( i = 0; i < NOIOCH; i++ ) {
        if ( (ch_stat[i] & 0x0c) == 0x0c ) 
        {    /* find pressure sensors */
//            char *senddata = (char*)&raw_data[i] ;                           /* data */
            tx_buff[tx_indx++] = i ;                /* channel number */
            tx_buff[tx_indx++] = ch_stat[i] ;     /* cal/conv status */
//            tx_buff[tx_indx++] = senddata[1] ;            /* data  LB */
//            tx_buff[tx_indx++] = senddata[0] ;            /* data  HB */ 
			 tx_buff[tx_indx++] = raw_data[i]&0x00ff ;            /* data  LB */  
            tx_buff[tx_indx++] = raw_data[i] >>8 ;            /* data  HB */
        }
    }
    tx_buff[ntna] = tx_indx - ntna - 1  ;               /* length of data block */
}

/*************************************************************************
*
* Build datablock for raw temperature data
*
*************************************************************************/
void BuildRTData(void)
{

    short i, ntna ;
//    char senddata[2];

    tx_buff[tx_indx++] = TX_RT_DATA ;           /* action */
    ntna = tx_indx++ ;                                  /* remember index */
    for ( i = 0; i < NOIOCH; i++ ) {
        if ( (ch_stat[i] & 0x0c)  == 0x04 ) {    /* find temperature sensors */
//            *((short*)&senddata[0]) = raw_data[i] ;                           /* data */
            tx_buff[tx_indx++] = i ;                /* channel number */
            tx_buff[tx_indx++] = ch_stat[i] ;     /* cal/conv status */
			 tx_buff[tx_indx++] = raw_data[i]&0x00ff ;            /* data  LB */  
            tx_buff[tx_indx++] = raw_data[i] >>8 ;            /* data  HB */

//            tx_buff[tx_indx++] = senddata[0] ;            /* data  HB */
//            tx_buff[tx_indx++] = senddata[1] ;            /* data  LB */
        }
    }
    tx_buff[ntna] = tx_indx - ntna - 1  ;               /* length of data block */
}

/*************************************************************************
*
* Build datablock for other raw data
*
*************************************************************************/
void BuildROData(void)
{

    short i, ntna ;
//    char senddata[2];

    tx_buff[tx_indx++] = TX_RO_DATA ;           /* action */
    ntna = tx_indx++ ;                                  /* remember index */
    for ( i = 0; i < NOIOCH; i++ ) {
        if ( (ch_stat[i] & 0x0c)  == 0x08 ) {    /* find other sensors */
//            *((short*)&senddata[0]) = raw_data[i] ;                           /* data */
            tx_buff[tx_indx++] = i ;                /* channel number */
            tx_buff[tx_indx++] = ch_stat[i] ;     /* cal/conv status */
//            tx_buff[tx_indx++] = senddata[1] ;            /* data  LB */
//            tx_buff[tx_indx++] = senddata[0] ;            /* data  HB */
			 tx_buff[tx_indx++] = raw_data[i]&0x00ff ;            /* data  LB */  
            tx_buff[tx_indx++] = raw_data[i] >>8 ;            /* data  HB */

        }
    }
    tx_buff[ntna] = tx_indx - ntna - 1  ;               /* length of data block */
}

/*************************************************************************
*
* Build datablock for calibration data
*
*************************************************************************/
void BuildCalData(void)
{

    short i, ntna ;
//    char  senddata[2];

    tx_buff[tx_indx++] = TX_CAL_DATA ;              /* action */
    ntna = tx_indx++ ;                                  /* remember index */
    for ( i = 0; i < NOIOCH; i++ ) {
 //       *((short*)&senddata[0]) = cal_data[i] ;   /* data */
        tx_buff[tx_indx++] = i ;                        /* channel number */
        tx_buff[tx_indx++] = ch_stat[i] ;             /* cal status */
		tx_buff[tx_indx++] = cal_data[i]&0x00ff ;            /* data  LB */  
        tx_buff[tx_indx++] = cal_data[i] >>8 ;            /* data  HB */

    }
    tx_buff[ntna] = tx_indx - ntna - 1  ;             /* length of data block */
}

/*************************************************************************
*
* Build datablock for configuration data
*
*************************************************************************/
void BuildConfData(void)
{

    short i, ntna ;

    tx_buff[tx_indx++] = TX_CONFIG ;                  /* action */
    ntna = tx_indx++ ;                                /* remember index */
    for ( i = 0; i < NOIOCH; i++ ) {
        tx_buff[tx_indx++] = i ;                      /* channel number */
        tx_buff[tx_indx++] = ch_stat[i] ;             /* channel setup */
        tx_buff[tx_indx++] = eep_type[i >> 1] ;           /* eeprom setup */
    }
    tx_buff[ntna] = tx_indx - ntna - 1  ;               /* length of data block */
}

/*************************************************************************
*
* Build datablock for eeprom data
*
*************************************************************************/
void BuildEepData(unsigned char channel)
{

    short i, ntna;
    tx_buff[tx_indx++] = TX_EEP_DATA ;              /* action */
    ntna = tx_indx++ ;                                  /* remember index */
    tx_buff[tx_indx++] = channel ;          /* channel number */
    channel >>= 1 ;
    for ( i = 0; i < PACKED_DATA_SIZE; i++ ) {
        tx_buff[tx_indx++] = packed_data[channel][i]; /* data */
    }
    tx_buff[ntna] = tx_indx - ntna - 1  ;      /* length of data block */
    ch_stat[channel << 1]  &= ~0x80 ;                  /* Release new sensor flag */
}

/*************************************************************************
*
* Build datablock for card status
*
*************************************************************************/
void BuildCSData(void)
{

    short ntna ;
    char senddata[4] ;

    tx_buff[tx_indx++] = TX_CARD_STAT ;         /* action */
    ntna = tx_indx++ ;                                  /* remember index */
    tx_buff[tx_indx++] = (unsigned char) VERSION; /* software version */
//    tx_buff[tx_indx] = GetMyAddress();        /* get the address */
        tx_buff[tx_indx] = MYADRESS_LOCAL;        /* get the address */

    if ( ad_mode & 0x10 ) {
        tx_buff[tx_indx] |= 0x80 ;                   /* restart flag */
    }
    tx_indx++  ;
    ad_mode &= ~0x10 ;                                   /* reset restart flag */
    tx_buff[tx_indx++] = (unsigned char) RX_SIZE; /* rx buffer size */
    tx_buff[tx_indx++] = (unsigned char) TX_SIZE; /* tx buffer size */
    tx_buff[tx_indx++] = (unsigned char) cal_zero ;     /* cal zero */
    tx_buff[tx_indx++] = (unsigned char) cal_zero >> 8 ;    
    
    *((float*)&senddata[0]) = cal_gain ;              /* calibration gain */
//    tx_buff[tx_indx++] = senddata[3] ;
//    tx_buff[tx_indx++] = senddata[2] ;
//    tx_buff[tx_indx++] = senddata[1] ;
//    tx_buff[tx_indx++] = senddata[0] ; 
    tx_buff[tx_indx++] = senddata[0] ;
    tx_buff[tx_indx++] = senddata[1] ;
    tx_buff[tx_indx++] = senddata[2] ;
    tx_buff[tx_indx++] = senddata[3] ;   
    
    tx_buff[ntna] = tx_indx - ntna - 1 ;                /* length of data block */
}

/*************************************************************************
*
* Build  packet tail
*
*************************************************************************/
void BuildTail(unsigned char type, unsigned char error)
{  unsigned char tmp_crc;

    tx_buff[tx_indx++] = type ;                 /* action end */
    tx_buff[tx_indx++] = error ;                /* error code */

    tx_buff[4] = tx_indx >> 8 ;                /* packet len high */
    tx_buff[5] = tx_indx ;                          /* correct length because stx's*/
    tmp_crc=CalcTxChecksum(tx_indx);
//    BuffCRC[BuffCRC_Index]=tmp_crc;
//    BuffCRC_Index++;
//    tx_buff[tx_indx++] = CalcTxChecksum(tx_indx) ; /* Get checksum */
    tx_buff[tx_indx++] = tmp_crc ; /* Get checksum */

    tx_buff[tx_indx++] = ETX ;                  /* ETX */

    tx_bytes = tx_indx;                         /*bytes to send */
    tx_indx = 0;                                    /* reset cunter */
    tx_complete = FALSE;
    wait_for_pc = PC_SLOW;                      /* delay before send */
    TxDriver(ON);                                   /* driver on */
    Led(1, ON) ;
}

/*************************************************************************
*
* Receive eeprom data
*
*************************************************************************/
void RecEepData(unsigned int pointer)
{

    short i, ch ;
//    unsigned char temp_data[PACKED_DATA_SIZE];
    unsigned char   *e_data, *a_data ;

    ch = (rx_buff[pointer++] >> 1 ) ;                               /* get channel */
    a_data = &rx_buff[pointer] ;
    e_data = &rx_buff[pointer + 8] ;

    if ( CheckEepData(e_data) && CheckADData(a_data) &&
         (rx_buff[pointer + PACKED_DATA_SIZE] & 0x01) ) { /* check legale packet */
        for ( i = 0; i < PACKED_DATA_SIZE; i++ ) {
            packed_data[ch][i] = rx_buff[pointer++];            /* copy data */
        }
        eep_type[ch] &= ~0x0f ;
        eep_type[ch] |= 0x09 ;               /* use PC data */
    } else {
        eep_type[ch] &= ~0x0f ;
        eep_type[ch] |= 0x02 ;                          /* fail from pc */
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
    float gai;

    number = rx_buff[++pointer] / 5 ;   /* number of channels (5 bytes each ch) */
    for ( i = 0; i < number; i++ ) {
        channel = rx_buff[++pointer] ;         /* Remember channel */
        /* Must be like this due to error in compiler, compiles from right to left!!! */
        offset[channel] = (rx_buff[++pointer] * 256) ;
        offset[channel] += rx_buff[++pointer] ;
        /* Must be like this due to error in compiler, compiles from right to left!!! */
        gai = (float)(rx_buff[++pointer]) * 256.0 ;
        gai += (float)(rx_buff[++pointer]) ;
        gain[channel] = 1.0 + (gai / 100000.0) ;   /*gain*/
    }
}


/*************************************************************************
*
* Receive setup
*
*************************************************************************/
void RecSetupData(unsigned char pointer)
{
    unsigned char temp;
    short i, test ;
    unsigned char d_buff[PACKED_DATA_SIZE] ;

    for ( i = 0; i < NOIOCH; i++ ) 
    {
        ch_stat[i] &= ~0x1c ;
//        ch_stat[i] |= (rx_buff[pointer++] & 0x1c);  /* Setup for channel */
        temp= rx_buff[pointer] & 0x1c;
        ch_stat[i] |= temp;  /* Setup for channel */
        pointer++;
    }
    if ( rx_buff[pointer] ) 
    {
        for ( i = 0; i < NOIOCH; i++ ) {
            packed_data[7][i+8] = (ch_stat[i] & 0x0c) ; /* copy setup to eeprom */
        }
        MakeEepChksum(&packed_data[7][8]) ;

        for ( i = 0; i < PACKED_DATA_SIZE; i++ ) {
            d_buff[i] = packed_data[7][i] ;                 /*copy buffer */
        }
        test = TRUE ;
        // Intern EEprom 
        //if ( !Eeprom(7, WRITE_SP) ) 
        if ( Eeprom(7, WRITE_SP)==0 ) 
        {
            test= FALSE ;                               /* write data to scratchpad */
        }
        //if ( !Eeprom(7, READ_SP) ) 
        if ( Eeprom(7, READ_SP)==0 ) 
        {
            test = FALSE ;                          /* Read data from scratchpad */
        }
        for ( i = 0; i < PACKED_DATA_SIZE; i++ ) {
            if ( d_buff[i] != packed_data[7][i] ) {
                test = FALSE;                                  /*compare buffer */
            }
        }
        if ( test == TRUE ) {                             /* write to eep OK */
            if ( Eeprom(7, COPY_SP_NV) ) {    /* copy data to NV-ram */
            }
        }
    }
    ad_state = IDLE ;                               /* Restart convertion */
    curr_ad_ch = NOIOCH  ;
    ad_mode = 0x04 ;                            /* start with press.*/

}

/*************************************************************************
*
* Calculate tx checksum
*
*************************************************************************/
unsigned char CalcTxChecksum(unsigned int pack_len)
{

    unsigned int             cnt ;
    unsigned char   csum ; 
 
    csum = 0 ;
    for ( cnt = 2 ; cnt < (pack_len) ; cnt++ ) 
    {  
        csum = crc[csum ^ tx_buff[cnt]] ;
    }
    return csum ;
}
