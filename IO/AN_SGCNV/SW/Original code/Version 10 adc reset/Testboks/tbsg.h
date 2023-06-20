/***** SG.H **************************************************************
*
*     Headerfile for SG*.C, signal convertion card
*
*     Company: ARISTON Norway as
*
*     Author: Asle Straume
*
*     Date: 1-aug-96.
*
*************************************************************************/

#define VERSION 1									/* Software version*/
/************************************************************************/
/*				Version overview */
/**/
/*		Version 01 :		Test version	*/
/************************************************************************/


#define TRUE				1
#define FALSE				0
#define ON					1
#define OFF					0
#define AD_CAL				1
#define AD_NORM			0

#define	MAKE				0x01
#define	TX_ERR         0x02

#define STX	     			0x02
#define ETX	     			0x03

#define SYNC				0			/* rx mode syncing */
#define HEADER				1			/* rx mode check header */
#define RECEIVE 		  	2			/* rx mode receiving */

#define TX_SIZE        120			/* No. of byte in send buffer */
#define RX_SIZE        110			/* No. of byte to receive */
#define RX_PACK_LEN    (RX_SIZE - 10)		/* Max rx pack length for me */
#define MIN_PACK_LEN	  5			/* Min rx pack length  */

#define PC_START_ADDRESS 0xf0		/* address space to pc */

#define NOIOCH				  14		/* number of IO channels */
#define NOPSD				  8		/* number of packed sensor data */
											/* and one on board eeprom */
#define PACKED_DATA_SIZE  	40 	/* length of packed data */
#define UNPACKED_DATA_SIZE 4		/* length of unpacked data */

#define TXTAIL					2		/* 2 chr delay  (9600Bd)	*/
#define PC_SLOW        		20 	/* delay 20ms before send to PC */
#define RX_TO_TIME   		1000 	/* Timeout on rx channels */
#define SEC_CNT_INIT	  		1000 	/* Second timer init value */
#define TIME_BETWEEN_CAL 	300	/* 5 minuts between cal */
#define TIME_BETWEEN_EEP 	15		/* 15 sec between check of eeprom */
#define AD_TIMEOUT			2000 	/* timeout ad-cnv 2 sec. */

#define AD_SET_TIME		 67 		/* Settling time for ad, 67ms */

#define	SUPPCHOFF		16			/* Switch off the supply shannel */
#define  MUXCHOFF			16			/* Switch off the mux shannel */
#define  EEPCHOFF			9			/* Switch off the eeprom shannel */

#define	MIN_PRE_CAL	  25000	 	/* minimum value for pressure cal */
#define	MAX_PRE_CAL	  35000	 	/* maximum value for pressure cal */
#define	FMIN_PRE_CAL  2000		/* fail min limit for pressure reading */
#define	FMAX_PRE_CAL  60000		/* fail max limit for pressure reading */

#define	MIN_TMP_CAL	  20000	 	/* minimum value for temp. cal */
#define	MAX_TMP_CAL	  30000	 	/* maximum value for temp cal */
#define	FMIN_TMP_CAL  2000		/* fail min limit for temp reading */
#define	FMAX_TMP_CAL  60000		/* fail max limit for temp reading */

#define 	PRE_CAL_CH		15			/* channel for pressure calibration */
#define 	TMP_CAL_CH		14			/* channel for temp calibration */


/************************************************************************/
/*	  DS2430 commands						*/

#define	READ_ROM			0x33		/* Read ROM */
#define	MATCH_ROM		0x55		/* Match ROM  */
#define	SKIP_ROM			0xcc		/* Skip ROM  */
#define	SEARCH_ROM		0xf0		/* Search ROM  */
#define	READ_SP			0xaa		/* Read scratch pad register from adr... */
#define	WRITE_SP		   0x0f     /* Write scratch pad register from adr... */
#define	COPY_SP_NV		0x55		/* Copy scratch pad to NV */
#define	COPY_NV_SP		0xf0		/* Copy NV to scratch pad */
#define	READ_STATUS		0x66		/* Read status register */
#define	READ_APPREG		0xc3		/* Read AD-REG from address.. */
#define	WRITE_APPREG  	0x99		/* Write AD-REG from address... */
#define	LOCK_APP			0x5a		/* Copies and write protects AD-REG */


/************************************************************************/
/*	  AD commands						*/



/************************************************************************/
/*	  AD states						*/
/*				NB::: the value must be in incremental order !!! */

#define	START_NEW_POINT	  	0x01		/* Start convertion of new point */
#define	WAIT_FOR_INTERRUPT   0x02     /* Wait for settling/int of AD*/
#define	CONV_COMPLETE			0x03     /* Convertion complete */
#define	START_CALIBRATION	  	0x04		/* Start cal. of ad converter */
#define	WAIT_FOR_CAL_INT	  	0x05		/* Wait for calibration int */
#define	CAL_COMPLETE		  	0x06		/* Cal. conv. complete */
#define	IDLE					  	0x07		/* Idle */


/************************************************************************/
/*	  AN-PRO1 actions						*/

#define	NO_MORE_DATA	0			/* No more data */
#define  SEND_ACK			1			/* Send acknowlage on packet */

#define  TX_ACK			5			/* Replay with errorcode */

						/* 10 - 29 = PC to SGCNV */
#define	SEND_M_DATA		10			/* Send measured data */
#define	SEND_R_DATA	   13       /* Send raw data */
#define	SEND_C_DATA		16			/* Send calibration data */
#define	SEND_CONFIG	   17			/* Send configuration */
#define	REC_EEP_DATA	18		   /* Receive ID-REG andsensor data for ch no. */
#define	REC_OFF_GAIN  	19		   /* Receive offset and gain */
#define	REC_SET_UP		20			/* Receive setudata */
#define	REC_TBTR			21			/* Receive time between temp. readings */
#define	CMD_WRITE_EEP	22			/* Write eep-data for a channel to eeprom */
#define	CMD_WRITE_ADR 	23			/* Write AD-REG for a channel to eeprom */
#define	SEND_EEP_DATA	24			/* Send AD-REG and data for a channel */
#define	CMD_READ_EEP	25			/* Read AD-REG and sensor data from channel */
#define	REC_FILTER		26			/* Receive filters */
#define	SEND_CARD_STAT	27			/* Send card status */
#define	SEND_SER_NO		28			/* Send serial no of eeprom */
#define	REC_DISP_DATA	29			/* Receive data for display */

						/* 30 - 49 =  SGCNV to PC */
#define	TX_MP_DATA		30			/* Sending measured pressure data */
#define	TX_MT_DATA		31			/* Sending measured temperature data */
#define	TX_MO_DATA		32			/* Sending measured "other" data */
#define	TX_RP_DATA	   33       /* Sending raw pressure data */
#define	TX_RT_DATA	   34       /* Sending raw temperature  data */
#define	TX_RO_DATA	   35       /* Sending raw "other" data */
#define	TX_CAL_DATA		36			/* Sending calibration data */
#define	TX_CONFIG	   37			/* Sending configuration */
#define	ASK_EEP_DATA	38		   /* Ask for ID-REG andsensor data for ch no. */
#define	ASK_OFF_GAIN  	39		   /* Ask for offset and gain */
#define	ASK_SET_UP		40			/* Ask for setudata */
#define	TX_WRITE_EEP	42			/* Ack. for writing snsdata to a eeprom */
#define	TX_WRITE_ADR 	43			/* Ack. for writing ID-REG  to eeprom */
#define	TX_EEP_DATA		44			/* Sending ID-REG and data for a channel */
#define	TX_CARD_STAT	47			/* Sending card status */
#define	TX_SER_NO		48			/* Serial no for eeprom */
#define	SEND_DISP_DATA	49			/* Receive data for display */

/************************************************************************/
/*	  Free running timer						*/

#define TCSRF_ICF   		0x80
#define TCSRF_OCFB  		0x40
#define TCSRF_OCFA  		0x20
#define TCSRF_OVF   		0x10

/************************************************************************/
/*	  Timer 							*/

#define TCSR_CMFB  		0x80
#define TCSR_CMFA  		0x40
#define TCSR_OVF   		0x20


/************************************************************************/
/*	  Serial Comm. Interface					*/

#define SMR_0	   	   0x0		    /* UART0 (..,8,n,1), � clock */
#define BRR_0	   		7		       /* UART0 4.9152MHz / 2 / 7 =9600 */
#define SMR_1	   		0x0		    /* UART1 (..,8,n,1), � clock */
#define BRR_1	   		7		       /* UART1 4.9152MHz / 2 / 7 =9600 */

#define SCR_TIE    		0x80
#define SCR_RIE    		0x40
#define SCR_TE	   		0x20
#define SCR_RE	   		0x10

#define SSR_TDRE   		0x80
#define SSR_RDRF   		0x40
#define SSR_ORER   		0x20
#define SSR_FER    		0x10
#define SSR_PER    		0x08

/************************************************************************/
/*	  Port bit def. 						*/

#define P65 		 		0x20 		/* port 6 bit 5 */
#define P64 	   		0x10 		/* port 6 bit 4 */
#define P63	   			0x08 		/* port 6 bit 3 */
#define LED1	   		0x02 		/* port 6 bit 1, STATUSLED1 0=ON */
#define WATCH_DOG	 		0x01 		/* port 6 bit 0, WATCHDOG OUTPUT */

#define ADCLK		     	0x20 		/* port 5 bit 5, AD CLK */
#define ADDO		     	0x10 		/* port 5 bit 4, AD DATA OUT */
#define ADDI		     	0x08 		/* port 5 bit 3, AD DATA IN */
#define TXE		   		0x04 		/* port 5 bit 2, TX ON */

#define SELMA	   		0x80 		/* port 4 bit 7, SELECT 1 MA */
#define EEPIN	   		0x20 		/* port 4 bit 5, EEPROM DATA IN */
#define LED2   			0x10 		/* port 6 bit 2, STATUSLED2 0 = ON */

#define OHM_1K	   		0x80 		/* port 1 bit 7, 1 K OHM RESISTOR */
#define OHM_1R	   		0x40 		/* port 1 bit 6, 1 OHM RESISTOR */

/************************************************************************/
/*	  Protyotypes  (functions)					*/

/* sg.c */
void InitRegs(void) ;
void InitVar(void) ;
void InitStartup(void) ;
unsigned char GetMyAddress(void) ;
void KickDog(void) ;
void Led(short, short) ;
void TxDriver(short) ;
void OneMsecDelay(unsigned long) ;
void SetEepromChannel(unsigned char);
void SetSupplyChannel(unsigned char) ;
void SetMuxChannel(unsigned char) ;
void SetSupplyCurrent(unsigned char) ;
void SetCalResistance(unsigned char) ;
void ADConvert(void) ;
void CalcPress(signed char) ;
float	CalcPercent(float, float, float, float) ;
void CalcTemp(signed char) ;
void CalcOther(signed char) ;
void UnpackSensData(signed char) ;
short CalcSensData(short, short, short, short, float) ;
short FindTemp(short) ;
unsigned char ReadAdByte(void) ;
void WriteAdByte(unsigned char) ;
int CalcRxChecksum(void) ;
void ResetRxPointer(void) ;
void HandleRxPacket(void) ;
int ReceiveRxPacket(void) ;
int main(void) ;

/* sgcom.c */
short CheckAction(short) ;
void BuildHeader(void) ;
void BuildMPData(void) ;
void BuildMTData(void) ;
void BuildMOData(void) ;
void BuildRPData(void) ;
void BuildRTData(void) ;
void BuildROData(void) ;
void BuildCalData(void) ;
void BuildConfData(void) ;
void BuildEepData(short) ;
void BuildCSData(void) ;
void BuildDisplay(void) ;
void BuildTail(unsigned char, unsigned char) ;
void RecOGData(unsigned char) ;
void RecSetupData(unsigned char) ;
void RecEepData(short) ;
void RecDispData(unsigned char) ;
unsigned char CalcTxChecksum(short) ;

/* sgeep.c */
short Eeprom(unsigned char, unsigned char) ;
short SendEepromCommand(unsigned char, short, short);
void ReadEepromData(unsigned char*, char);
void WriteEepromData(unsigned char*, char);
unsigned char ReadEepromByte(void) ;
void WriteEepromByte(unsigned char) ;
short ResetEeprom(void);
short CheckEepChannel(void);
unsigned char CheckEepData(unsigned char *) ;
unsigned char CheckADData(unsigned char *) ;
