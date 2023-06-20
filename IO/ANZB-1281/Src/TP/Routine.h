/*******************************************************

*
*     Program for signal convertion card, AN-SGCNV
*
*     Company: ARISTON Norway as
*
*     Author: Thierry Pottier
*
*    * @file     routine.h
	 * @brief    Routine Header File
	 * @version  V0.00
	 * @date     18. October 2022
	 * @note
*

*******************************************************/


#ifndef ___ROUTINE_H_
#define ___ROUTINE_H_

#define TRUE				1
#define FALSE				0
#define ON					1
#define OFF					0
#define ALL_OFF             0
#define AD_CAL				1
#define AD_NORM 			0

#define MAKE			0x01
#define TX_ERR	        0x02

#define STX				0x02
#define ETX				0x03

#define SYNC				0			/* rx mode syncing */
#define HEADER                1            /* rx mode check header */
#define RECEIVE             2            /* rx mode receiving */

//#define TX_SIZE        118            /* No. of byte in send buffer */
//#define RX_SIZE        104            /* No. of byte to receive */
#define TX_SIZE        200            /* No. of byte in send buffer */
#define RX_SIZE        200            /* No. of byte to receive */

#define RX_PACK_LEN    (RX_SIZE - 7)    /* Max rx pack length for me */
#define MIN_PACK_LEN      5            /* Min rx pack length  */

#define PC_START_ADDRESS 0xf0        /* address space to pc */

#define NOIOCH                14        /* number of IO channels */
#define NOPSD                8        /* number of packed sensor data */
                                            /* and one on board eeprom */
#define NOWT                4        // number of washtrec channels
#define PACKED_DATA_SIZE    40    /* length of packed data */
#define UNPACKED_DATA_SIZE  4        /* length of unpacked data */

#define TXTAIL                2        /* 2 chr delay    (9600Bd)    */
#define PC_SLOW             20        /* delay 20ms before send to PC */
#define RX_TO_TIME            1000    /* Timeout on rx channels */
#define SEC_CNT_INIT            1000    /* Second timer init value */
#define TIME_BETWEEN_EEP    15        /* 15 sec between check of eeprom */
#define AD_TIMEOUT            2000    /* timeout ad-cnv 2 sec. */

#define AD_SET_TIME            67    /* Settling time for ad, 67ms */

#define SUPPCHOFF            16            /* Switch off the supply shannel */
#define  MUXCHOFF            16            /* Switch off the mux shannel */
#define  EEPCHOFF            9            /* Switch off the eeprom shannel */
#define GNDCHOFF             9            /* mux to GND */     

// all min / max divided by 2 due to binary convertion (1/2 resolution)   
//#define MIN_PRE_CAL        25000 /2      /* minimum value for pressure cal */
//#define MAX_PRE_CAL        35000 /2        /* maximum value for pressure cal */
#define MIN_PRE_CAL        25000 /2      /* minimum value for pressure cal */
#define MAX_PRE_CAL        35000         /* maximum value for pressure cal */


#define FMIN_PRE_CAL    15000/2        /* fail min limit for pressure reading */
//#define FMAX_PRE_CAL    45000 /2        /* fail max limit for pressure reading */
//#define FMAX_PRE_CAL    45000         /* fail max limit for pressure reading */
#define FMAX_PRE_CAL    55000         /* fail max limit for pressure reading */



#define MIN_TMP_CAL        20000 /2        /* minimum value for temp. cal */
#define MAX_TMP_CAL        51000 /2        /* maximum value for temp cal (25000@1K / 42000@100R)*/
                                    // changed to 51000 due to removal of diode
#define FMIN_TMP_CAL	10000 /2		/* fail min limit for temp reading */
#define FMAX_TMP_CAL	55000 /2		/* fail max limit for temp reading */
                                        // chaned to 55000
#define 	PRE_CAL_CH		15			/* channel for pressure calibration */
#define 	TMP_CAL_CH		14			/* channel for temp calibration */

/************************************************************************/
/*      AD states                        */
/*                NB::: the value must be in incremental order !!! */

#define START_NEW_POINT         0x01        /* Start convertion of new point */
#define WAIT_FOR_INTERRUPT        0x02     /* Wait for settling/int of AD*/
#define CONV_COMPLETE            0x03        /* Convertion complete */
#define START_CALIBRATION        0x04        /* Start cal. of ad converter */
#define WAIT_FOR_CAL_INT        0x05        /* Wait for calibration int */
#define CAL_COMPLETE                0x06        /* Cal. conv. complete */
#define IDLE                        0x07        /* Idle */


/************************************************************************/
/*      AN-PRO1 actions                        */

#define NO_MORE_DATA        0            /* No more data */
#define  SEND_ACK            1            /* Send acknowlage on packet */

#define  TX_ACK             5            /* Replay with errorcode */

                        /* 10 - 29 = PC to SGCNV */
#define SEND_M_DATA        10            /* Send measured data */
#define SEND_R_DATA       13        /* Send raw data */
#define SEND_C_DATA        16            /* Send calibration data */
#define SEND_CONFIG       17            /* Send configuration */
#define REC_EEP_DATA        18           /* Receive ID-REG andsensor data for ch no. */
#define REC_OFF_GAIN        19           /* Receive offset and gain */
#define REC_SET_UP        20            /* Receive setudata */
#define REC_TBTR            21            /* Receive time between temp. readings */
#define CMD_WRITE_EEP    22            /* Write eep-data for a channel to eeprom */
#define CMD_WRITE_ADR    23            /* Write AD-REG for a channel to eeprom */
#define SEND_EEP_DATA	24			/* Send AD-REG and data for a channel */
#define CMD_READ_EEP		25			/* Read AD-REG and sensor data from channel */
#define REC_FILTER		26			/* Receive filters */
#define SEND_CARD_STAT	27			/* Send card status */
#define SEND_SER_NO		28			/* Send serial no of eeprom */

						/* 30 - 49 =  SGCNV to PC */
#define TX_MP_DATA		30			/* Sending measured pressure data */
#define TX_MT_DATA		31			/* Sending measured temperature data */
#define TX_MO_DATA		32			/* Sending measured "other" data */
#define TX_RP_DATA	   33	    /* Sending raw pressure data */
#define TX_RT_DATA	   34	    /* Sending raw temperature	data */
#define TX_RO_DATA	   35	    /* Sending raw "other" data */
#define TX_CAL_DATA		36			/* Sending calibration data */
#define TX_CONFIG		37			/* Sending configuration */
#define ASK_EEP_DATA		38		   /* Ask for ID-REG andsensor data for ch no. */
#define ASK_OFF_GAIN		39		   /* Ask for offset and gain */
#define ASK_SET_UP		40			/* Ask for setudata */
#define TX_WRITE_EEP		42			/* Ack. for writing snsdata to a eeprom */
#define TX_WRITE_ADR		43			/* Ack. for writing ID-REG  to eeprom */
#define TX_EEP_DATA		44			/* Sending ID-REG and data for a channel */
#define TX_CARD_STAT		47			/* Sending card status */
#define TX_SER_NO			48			/* Serial no for eeprom */
#define TX_WH_DATA	        49			/* Send highlevel and washtrack */

/************************************************************************/
/*	  Free running timer						*/

#define TCSRF_ICF			0x80
#define TCSRF_OCFB		0x40
#define TCSRF_OCFA		0x20
#define TCSRF_OVF			0x10

/************************************************************************/
/*	  Timer 							*/

#define TCSR_CMFB		0x80
#define TCSR_CMFA		0x40
#define TCSR_OVF		0x20


/************************************************************************/
/*	  Serial Comm. Interface					*/

#define SMR_0		   0x0		    /* UART0 (..,8,n,1), ù clock */
#define BRR_0			7		       /* UART0 4.9152MHz / 2 / 7 =9600 */
#define SMR_1			0x0		    /* UART1 (..,8,n,1), ù clock */
#define BRR_1			7		       /* UART1 4.9152MHz / 2 / 7 =9600 */

#define SCR_TIE 		0x80
#define SCR_RIE 		0x40
#define SCR_TE			0x20
#define SCR_RE			0x10

#define SSR_TDRE		0x80
#define SSR_RDRF		0x40
#define SSR_ORER		0x20
#define SSR_FER 		0x10
#define SSR_PER 		0x08

/************************************************************************/
///*	  Port bit def. 						*/
//
//#define P65				0x20		/* port 6 bit 5 */
//#define P64				0x10		/* port 6 bit 4 */
//#define P63				0x08		/* port 6 bit 3 */
//#define LED2			0x04		/* port 6 bit 2, STATUSLED2 0 = ON */
//#define LED1			0x02		/* port 6 bit 1, STATUSLED1 0=ON */
//#define WATCH_DOG		0x01		/* port 6 bit 0, WATCHDOG OUTPUT */
//
//#define ADCLK			0x20		/* port 5 bit 5, AD CLK */
//#define ADDO			0x10		/* port 5 bit 4, AD DATA OUT */
//#define ADDI			0x08		/* port 5 bit 3, AD DATA IN */
//#define TXE				0x04		/* port 5 bit 2, TX ON */
//
//#define SELMA			0x80		/* port 4 bit 7, SELECT 1 MA */
//
//#define EEPIN			0x20		/* port 4, pin 5 EEPORT */
//#define EPORTI			0xd0		/* port 4, EEPROM DATA IN  bit 4, 6, 7 out rest in  */
//#define EPORTO			0xf0		/* port 4, EEPROM DATA OUT bit 4, 5 , 6 7, out rest in*/
//
#define OHM_1K			0x80		/* port 1 bit 7, 1 K OHM RESISTOR */
#define OHM_1R			0x40		/* port 1 bit 6, 1 OHM RESISTOR */

#define short   unsigned int

//static     uint16_t adcreadout;
extern unsigned char       tx_buff[TX_SIZE] ;
extern unsigned char       rx_buff[RX_SIZE] ;
extern unsigned char       tx_indx ;
//extern unsigned int       tx_indx ;

extern unsigned char       tx_bytes ;
extern unsigned char       tx_tail;
extern unsigned char       wait_for_pc ;
extern unsigned char       rx_indx ;
extern unsigned char       rx_hndx ;
extern unsigned char       rx_start ;
extern unsigned char       rx_counter ;
extern unsigned char       rx_packlen ;
extern unsigned char       rx_timeout ;
extern unsigned char       sync_cnt ;

//extern short               sens_data[UNPACKED_DATA_SIZE] ;     /*  unpacked data */
extern unsigned int       sens_data[UNPACKED_DATA_SIZE] ;     /*  unpacked data */
extern signed char         sens_nl1 ;                          /* none linearity 1*/
extern signed char         sens_nl2 ;                          /* none linearity 2*/

//extern unsigned int       packed_data[NOPSD][PACKED_DATA_SIZE] ; /* packed sensor data */
extern unsigned char       packed_data[NOPSD][PACKED_DATA_SIZE] ; /* packed sensor data */

/* and the on board eep*/
extern unsigned char       eep_status;                /* status byte of the eep*/
extern unsigned char       time_b_temp;               /* time between temp read */
extern unsigned char       time_b_cnt;                /* time between temp cnt */
extern unsigned char       time_e_cnt;               /* time between eep check */
extern unsigned int      ad_timeout_cnt ;          /* timeout ad conv */
extern unsigned int      sec_cnt ;                 /* seconds sounter */
extern unsigned int      ms_cnt;                 /* seconds sounter */

extern short               curr_sens_data ;        /* sensor data from ad conv. */

extern short               cal_data[NOIOCH] ;      /* calibration data */
extern short               raw_data[NOIOCH] ;      /* raw data from senors */
extern float               mes_data[NOIOCH];       /* measured data result */
extern volatile unsigned char       highlevel;              // high level result
extern unsigned int      washtrac[NOWT];          // Whashtrec result
extern volatile unsigned char       washtrac_prev;          // Whashtrec previous port state

extern float               gain[NOIOCH] ;          /* gain for sensors */
extern short               offset[NOIOCH] ;        /* offset for sensors */

extern float               cal_gain;               /* gain for the 1 ohm resistor */
extern short               cal_zero;               /* zero for the 1 ohm resistor */

extern unsigned char       not_mes_data ;          /* number of tx of measured data */
extern unsigned char       not_raw_data ;          /* number of tx of raw data */
extern unsigned char       not_cal_data ;          /* number of tx of calib. data */

extern signed char        curr_ad_ch ;             /* current ad ch */
extern unsigned char       old_curr_ad_ch;
extern unsigned char       ad_state    ;               /* status for ad conversion */
extern unsigned char       ad_mode ;               /* modus */
/*Bit 7 = test mode
   Bit 6 = next cal conv.
   Bit 5 =
   Bit 4 = Start new channel
   Bit 3 = Read temperature
   Bit 2 = Read other
   Bit 1 = Read Pressure
   Bit 0 =        */
extern unsigned short      ms_delay_cnt ;              /* increased each millisecond */
extern unsigned short      ad_settling ;               /* ad settling timer */

extern unsigned char       ad_gain ;                   /* ad com register, keep gain */

extern unsigned char       ch_stat[NOIOCH] ;               /* sensor status */
/*Bit  765
          x00 = Unknown
          x01 = temp
          x10 = inclinometer
          x11 = Press
          1xx = Mark new sensor
  Bit    432
          000 = Unused
          001 = temp
          010 = inclinometer
          011 = Press
          1xx = Setup from PC
Bit 1  cal status 0=OK 1=Fail
Bit 0  conv. status 0=OK 1=Fail */

extern unsigned char       eep_type[NOPSD] ;           /* eeprom status*/
/* Bit 7654
         0000    = None
         0001 = Ok from sensor
         0010 = Error from sensor
         0011 =
    Bit 3210
         x000 = None
         x001 = Ok from PC
         x010 = Error from PC
         1xxx = Use data from PC */

extern unsigned char       p_filter ;              /* pressure filter */
extern unsigned char       t_filter ;              /* temperature filter */
extern unsigned char       o_filter ;              /* "other" filter */
extern unsigned char       my_address ;            /* my address */
extern volatile unsigned char       rx_state ;              /* rx state */
extern volatile unsigned char       tx_complete ;           /* tx state */

extern unsigned char       sendtail ;

extern unsigned char ZeroCountTemp;
extern unsigned char ZeroCountPress;
//extern unsigned char ZeroCountOther;
#define ZEROCOUNT 3

//extern flash unsigned char crc[];
extern const unsigned char crc[];

//extern unsigned char BuffCRC_Index;
//extern unsigned char BuffCRC[];


void    InitVar(void);
void    InitStartup(void);
void Led(unsigned char no, unsigned char state);
void TxDriver(unsigned char state);
void SetEepromChannel(unsigned char channel);
void SetSupplyChannel(unsigned char channel);
void SetGNDChannel(unsigned char channel);
void SetMuxChannel(unsigned char channel);
void SetSupplyCurrent(unsigned char current);
void SetCalResistance(unsigned char value);
void CheckConvert(void);



void ADConvert(void);
void CalcPress(signed char ch);
float CalcPercent( unsigned short span, short low_span, short raw_data,float nl);
float GetTempFromR(float R);
void CalcTemp(signed char ch);
void UnpackSensData(signed char ch);
void CalcOther(signed char ch);
short CalcSensData(short knst, short g1, short g2, short g3, float temp);
short FindTemp(signed char ch);

void ResetRxPointer(void);
int CalcRxChecksum(void);
void RecEepData(short) ;

void     ResetADCBySW(void);
void     ResetADCByHW(void);
int ReceiveRxPacket(void);
void HandleRxPacket(void);
#endif 
