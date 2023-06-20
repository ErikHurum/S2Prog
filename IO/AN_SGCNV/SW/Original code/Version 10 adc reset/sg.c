/***** SG.C *************************************************************
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

#include "math.h"
#include "float.h"
#include "stdio.h"
#include "ioh8325.h"
#include "inth8325.h"

#include "sg.h"
#include "sgext.h"

unsigned char		tx_buff[TX_SIZE] ;
unsigned char		rx_buff[RX_SIZE] ;
unsigned char		tx_indx ;
unsigned char		tx_bytes ;
unsigned char		tx_tail;
unsigned char		wait_for_pc ;
unsigned char		rx_indx ;
unsigned char		rx_hndx ;
unsigned char		rx_start ;
unsigned char		rx_counter ;
unsigned char		rx_packlen ;
unsigned char		rx_timeout ;
unsigned char		sync_cnt ;

short				sens_data[UNPACKED_DATA_SIZE] ; 	/*  unpacked data */
signed char			sens_nl1 ;							/* none linearity 1*/
signed char			sens_nl2 ;							/* none linearity 2*/

unsigned char		packed_data[NOPSD][PACKED_DATA_SIZE] ; /* packed sensor data */

/* and the on board eep*/
unsigned char		eep_status;							/* status byte of the eep*/
unsigned char		time_b_temp;						/* time between temp read */
unsigned char		time_b_cnt;							/* time between temp cnt */
unsigned char		time_e_cnt;						   /* time between eep check */
unsigned short		ad_timeout_cnt ;				   /* timeout ad conv */
unsigned short		sec_cnt ;						   /* seconds sounter */

short		        curr_sens_data ;		/* sensor data from ad conv. */

short		        cal_data[NOIOCH] ;	    /* calibration data */
short	            raw_data[NOIOCH] ;	    /* raw data from senors */
float				mes_data[NOIOCH];		/* measured data result */
float				gain[NOIOCH] ;			/* gain for sensors */
short				offset[NOIOCH] ;		/* offset for sensors */

float				cal_gain;				/* gain for the 1 ohm resistor */
short				cal_zero;				/* zero for the 1 ohm resistor */

unsigned char		not_mes_data ;			/* number of tx of measured data */
unsigned char		not_raw_data ;			/* number of tx of raw data */
unsigned char		not_cal_data ;			/* number of tx of calib. data */

signed char		   curr_ad_ch ; 			/* current ad ch */

unsigned char		ad_state	;				/* status for ad conversion */
unsigned char		ad_mode ;				/* modus */
/*Bit 7 = test mode
  Bit 6 = next cal conv.
  Bit 5 =
  Bit 4 = Start new channel
  Bit 3 = Read temperature
  Bit 2 = Read other
  Bit 1 = Read Pressure
  Bit 0 =		*/
unsigned long		ms_delay_cnt ;				/* increased each millisecond */
unsigned short		ad_settling ;				/* ad settling timer */

unsigned char		ad_gain ;					/* ad com register, keep gain */

unsigned char		ch_stat[NOIOCH] ;				/* sensor status */
/*Bit  765
  x00 = Unknown
  x01 = temp
  x10 = inclinometer
  x11 = Press
  1xx = Mark new sensor
  Bit	432
  000 = Unused
  001 = temp
  010 = inclinometer
  011 = Press
  1xx = Setup from PC
  Bit 1  cal status 0=OK 1=Fail
  Bit 0  conv. status 0=OK 1=Fail */

unsigned char		eep_type[NOPSD] ;			/* eeprom status*/
/* Bit 7654
   0000	= None
   0001 = Ok from sensor
   0010 = Error from sensor
   0011 =
   Bit 3210
   x000 = None
   x001 = Ok from PC
   x010 = Error from PC
   1xxx = Use data from PC */

unsigned char		p_filter ;				/* pressure filter */
unsigned char		t_filter ;				/* temperature filter */
unsigned char		o_filter ;				/* "other" filter */
unsigned char		my_address ;			/* my address */
unsigned char		rx_state ;				/* rx state */
unsigned char		tx_complete ;			/* tx state */

unsigned char		sendtail ;
unsigned char	  display[NO_OF_DISP] ; 		/* display mode */

const crc[] =		      /*Dallas Semiconductor one-wire CRC table */
{
  0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65,
  157, 195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220,
  35, 125, 159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98,
  190, 224, 2, 92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255,
  70, 24, 250, 164, 39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7,
  219, 133, 103, 57, 186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154,
  101, 59, 217, 135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36,
  248, 166, 68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185,
  140, 210, 48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205,
  17, 79, 173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236, 14, 80,
  175, 241, 19, 77, 206, 144, 114, 44, 109, 51, 209, 143, 12, 82, 176, 238,
  50, 108, 142, 208, 83, 13, 239, 177, 240, 174, 76, 18, 145, 207, 45, 115,
  202, 148, 118, 40, 171, 245, 23, 73, 8, 86, 180, 234, 105, 55, 213, 139,
  87, 9, 235, 181, 54, 104, 138, 212, 149, 203, 41, 119, 244, 170, 72, 22,
  233, 183, 85, 11, 136, 214, 52, 106, 43, 117, 151, 201, 74, 20, 246, 168,
  116, 42, 200, 150, 21, 75, 169, 247, 182, 232, 10, 84, 215, 137, 107, 53
} ;



static void
ResetADCBySW(void)
{
  WriteAdByte(0xff) ;				/* Reset the ad */
  WriteAdByte(0xff) ;				/* with */
  WriteAdByte(0xff) ;				/* 32 (8*4)*/
  WriteAdByte(0xff) ;				/* write pulses*/
}

/*************************************************************************
 *
 *  Initialize I/O ports
 *
 *  Set RS232 parametres
 *  Initialize interrupt system
 *
 *************************************************************************/
void InitRegs(void)
{

  /* Internal timer 1 ms */
  TMR1_TCR   =	0x4a;		/* int a, clear reg a, 1/64 clock (38600 Hz)*/
  TMR1_TCSR  = 0x00;		/* No invert p44 */
  TMR1_TCORA =	37 ;		/* Set 38600/(37+1) = 1 msec compare */

  P7DDR = 0x00 ;			/* Port 7, all input */
  P7DR = 0xff ; 		/* All pull-ups on */

  P6DDR = 0x07	;			/* Port 6, P60,1,2 out, P6 3,4,5,6 input */
  P6DR = 0xf8 ; 		/* Pull ups on P6 3-6 */

  P5DDR = 0x2d ;			/* Serial line I/O, may be not neccessary */
  P5DR = 0x12 ; 			/* internal pull up on input pins */

  SCI0_SMR = SMR_0;		/* uart 0 mode */
  SCI0_BRR = BRR_0;		/* uart0 baudrate */

  P4DDR = 0xd0 ;			/* Port 4, P4 4,6,7 out, rest in */

  P3DDR = 0xff ;			/* All output */

  P2DDR = 0x00 ;			/* All input */
  P2DR = 0xff ; 		/* All pull-ups on */

  P1DDR = 0xff ;			/* All output */

  ISCR	= 0x8f; 			/* IRQ0, 1 and 2 on falling edge */
  IER	= 0xfe; 				/* enable int 1, 2, Disable 0 */

  // hkim set_interrupt_mask(0);	/* Enable interrupt */

}

/*************************************************************************
 *
 *	Initialize variables
 *
 *************************************************************************/
void InitVar(void)
{

  short i;
  /*
   **	Init the the com cannal variables
   */
  tx_indx = 0 ;
  tx_complete = TRUE ;
  tx_bytes = 0 ;
  tx_tail = 0 ;
  wait_for_pc = 0 ;
  rx_indx = 1 ;
  rx_hndx = 1 ;
  rx_start = 0 ;
  rx_buff[0] = 0 ;
  rx_counter = 0 ;
  rx_state = SYNC ;
  rx_timeout = 0 ;

  /*
   **	Init channel variables
   */
  for (i = 0; i< NOIOCH; i += 2) {
    ch_stat[i] = 0x0c ;			/*channel setup, try pressure */
  }
  for (i = 1; i< NOIOCH; i += 2) {
    ch_stat[i] = 0x04 ;			/*channel setup, try temp */
  }
  for (i = 0; i< NOPSD; i++) {
    eep_type[i] = 0 ;				/*eeprom status */
  }
  for (i = 0; i< NOIOCH; i++) {
    offset[i] = 0 ; 						/*channel setup, offest */
    gain[i] = 1.0;
  }

  /*
   **	Init other variables
   */

  cal_gain = 1.0 ;
  cal_zero = 0 ;
  p_filter = 5 ;
  t_filter = 2 ;
  o_filter = 2 ;
  sec_cnt = SEC_CNT_INIT; 				/* initvalue for 1 sec counter */
  ad_state = IDLE ;							/* no convertion */
  curr_ad_ch = NOIOCH  ;
  ad_mode = 0x88 ;							/* test mode on and start with press.*/
  ad_mode |= 0x10 ;							/* mark restart of card */
  ad_gain = 0 ;								/* gain 1 */
  time_b_temp = 15 ;						/* temp readings in sec */
  time_b_cnt = 0 ;
  time_e_cnt = TIME_BETWEEN_EEP ;
  not_mes_data = 0 ;
  not_raw_data = 0 ;
  not_cal_data = 0 ;
}

/*************************************************************************
 *
 *	Startup
 *
 *************************************************************************/
void InitStartup(void)
{

  P5DR |= ADCLK ; 							/*	set AD clock line high */

  Led(1, OFF) ;								/* switch leds off */
  Led(2, OFF) ;

  TxDriver(OFF) ; 							/* tx enable off */
  SetEepromChannel(EEPCHOFF) ;			/* set eeprom channel off */
  SetMuxChannel(MUXCHOFF) ;				/* set mux channel off */
  SetSupplyChannel(SUPPCHOFF) ;		/* set supply channel off */
  SetSupplyCurrent(1);						/* set 1 mA supply */

  GetMyAddress() ;							/* get my address */

}


/*************************************************************************
 *
 *  Get my address from address switch
 *
 *************************************************************************/
unsigned char GetMyAddress(void)
{

  my_address  = ((P4DR & 0x0f) + 10) ;	/* Bit 0-3 */
  /* add 10 due to protocole */
  return my_address;
}

/*************************************************************************
 *
 *  Kick watch dog
 *
 *************************************************************************/
void KickDog(void)
{
  P6DR &= ~WATCH_DOG;
  P6DR |=  WATCH_DOG;
}

/*************************************************************************
 *
 *  Write to the leds
 *
 *************************************************************************/
void Led(short no, short state)
{
  switch (no) {
    case	1:										/* LED 1 */
      switch (state) {
        case ON :
          P6DR &= ~LED1;
          break ;
        case OFF :
        default :
          P6DR |= LED1;
          break ;
      }
      break ;
    case	2:										/* LED 2 */
      switch (state) {
        case ON :
          P6DR &= ~LED2;
          break ;
        case OFF :
        default :
          P6DR |= LED2;
          break ;
      }
      break ;
    default :
      break ;
  }
}


/*************************************************************************
 *
 *  Enable / disable RS485 driver on SCI0
 *
 *************************************************************************/
void TxDriver(short state)
{

  switch (state) {
    case ON :							/* driver on */
      P5DR |= TXE;
      break;
    case OFF :							/* driver off */
      P5DR &= ~TXE;
      break;
    default :
      break;
  }
}


/*************************************************************************
 *
 *  Return from this function after  time * 1ms
 *
 *************************************************************************/
void OneMsecDelay(unsigned long time)
{
  ms_delay_cnt = time ;
  while (ms_delay_cnt) {					/* wait for time * 1ms */
    KickDog() ;
  }
}


/*************************************************************************
 *
 *  Set com channel to a eeprom DS2430
 *
 *************************************************************************/
void SetEepromChannel(unsigned char channel)
{
  if (channel == EEPCHOFF) {
    P1DR &= ~0x3C ; 							/* switch off any channel */
  } else {
    P1DR &= ~0x3C ; 							/* switch off any output */
    P1DR |= ((channel & 0x7) << 2) | 0x20 ;  /* set channel and enable bit */
  }
}


/*************************************************************************
 *
 *  Set supply channel to a sensor
 *
 *************************************************************************/
void SetSupplyChannel(unsigned char channel)
{

  if (channel == SUPPCHOFF) {
    P1DR &= ~0x03 ; 								/* switch off any channel */
    P3DR &= ~0xe0 ;
  } else {
    P1DR &= ~0x03 ; 								/* switch off any channel */
    P3DR &= ~0xe0 ;
    P3DR |= ((channel & 0x07) << 5) ;
    P1DR |= ((channel & 0x08) >> 3) | 0x02 ; /* set channel and enable bit */
  }
}

/*************************************************************************
 *
 *  Set mux channel to a sensor
 *
 *************************************************************************/
void SetMuxChannel(unsigned char channel)
{

  if (channel == MUXCHOFF) {
    P3DR &= ~0x1f ; 							/* switch off any channel */
  } else {
    P3DR &= ~0x1f ; 							/* switch off any channel */
    P3DR |= (channel & 0x07) ;
    if (channel < 8 ) {							/* set E1 or E2 */
      P3DR |= 0x08 ;							/* set enable bit 1 */
    } else {
      P3DR |= 0x10 ;							/* set enable bit 2 */
    }
  }
}

/*************************************************************************
 *
 *  Set 1 / 10 mA sypply current
 *
 *************************************************************************/
void SetSupplyCurrent(unsigned char current)
{
  if (current == 10 ) {
    P4DR &= (~SELMA & 0xf0);					/* set 10 mA */
  } else {
    P4DR |= SELMA ; 								/* set 1 mA */
  }
}

/*************************************************************************
 *
 *  Select calibration resistance
 *
 *************************************************************************/
void SetCalResistance(unsigned char value)
{
  switch (value) {
    case OHM_1R :										/* 1 ohm resistor */
      P1DR |= OHM_1R ;
      P1DR &= ~OHM_1K ;
      break ;
    case OHM_1K :										/* 1000 ohm resistor */
      P1DR |= OHM_1K ;
      P1DR &= ~OHM_1R ;
      break ;
    default :											/* both off */
      P1DR &= ~(OHM_1R | OHM_1K) ;
      break ;
  }
}

/*************************************************************************
 *
 *  Check new convertion*
 *************************************************************************/
void CheckConvert(void)
{

  if (ad_state == IDLE ) {			/* New channel? */
    ad_state = START_NEW_POINT ;
    if (curr_ad_ch < (NOIOCH-1)) {
      curr_ad_ch++ ;
    } else {
      curr_ad_ch = 0 ;
      if (!time_e_cnt) {
        if (ad_mode & 0x80) {				/* test */
          ad_mode &= ~0x80 ;				/* test mode off */
        }
        CheckEepChannel()	;					/* Check the sensordata */
        time_e_cnt = TIME_BETWEEN_EEP ;
      }
      if (not_mes_data && (ad_mode & 0x02)) { 	/* autosend? */
        BuildHeader() ; 					/* Build send packet header */
        BuildMPData();						/* Build data p. for pressure */
        BuildMTData();						/* Build data p. for temp */
        BuildMOData();						/* Build data p. for other */
        BuildTail(NO_MORE_DATA, 0) ;	/* Build tail */
        not_mes_data-- ;
      } else if (not_raw_data && (ad_mode & 0x02)) {	/* autosend? */
        BuildHeader() ; 					/* Build send packet header */
        BuildRPData();						/* Build data p. for pressure */
        BuildRTData();						/* Build data p. for temp */
        BuildROData();						/* Build data p. for other */
        BuildTail(NO_MORE_DATA, 0) ;	/* Build tail */
        not_raw_data-- ;
      } else if (not_cal_data && (ad_mode & 0x02)) {	/* autosend? */
        BuildHeader() ; 					/* Build send packet header */
        BuildCalData(); 					/* Build data p. for calib */
        BuildTail(NO_MORE_DATA, 0) ;	/* Build tail */
        not_cal_data-- ;
      }
      if (ad_mode & 0x08) {			/* temp readings */
        ad_mode &= ~0x0e ;
        ad_mode |= 0x02 ;
        ad_state = START_CALIBRATION ;
      } else if (ad_mode & 0x04) {	/* "other" */
        ad_mode &= ~0x0e ;
        ad_mode |= 0x08 ;
        ad_state = START_CALIBRATION ;
      } else if (ad_mode & 0x02) {			/* pressure */
        if (!time_b_cnt) {
          ad_mode &= ~0x0e ;
          ad_mode |= 0x04 ;					/* convert temp */
          ad_state = START_CALIBRATION ;
          time_b_cnt = time_b_temp ;		/* reload counter */
        }
      } else {
        ad_mode &= ~0x0e ;
        ad_mode |= 0x04 ;						/* next pressure */
      }
    }
  }
  if (tx_complete) {
    ADConvert() ;									/* convert data */
  }
}

/*************************************************************************
 *
 *  Convert sensor data
 *
 *************************************************************************/
void ADConvert(void)
{
  unsigned short ad_data ;

  switch (ad_state) {
    case	START_NEW_POINT :
      ad_mode &= ~0x01 ;							/* reset tx check marker */
      ad_timeout_cnt = AD_TIMEOUT ;					/* timeout ad cnv */
      switch ((ch_stat[curr_ad_ch]>> 2) & 0x03) {
        case 0x03 :				 /* pressure */
          if (ad_mode & 0x02) {						/* pressure readings */
            SetCalResistance(OHM_1R);
            SetSupplyChannel(curr_ad_ch) ;
            SetSupplyCurrent(10) ;
            SetMuxChannel(curr_ad_ch) ;
            ad_gain = 3 ;
            WriteAdByte(ad_gain | 0x10) ;			/* Next write data */
            WriteAdByte(0x2a) ;						/* Ad setup data, bipolar*/
            ad_settling = AD_SET_TIME ;			/* wait 67 ms */
            ad_state = WAIT_FOR_INTERRUPT ; 		/* next state */
          } else {
            ad_state = IDLE ;
          }
          break;
        case 0x02 :				  /* "OTHER " */
          if (ad_mode & 0x04) {						/* other readings */
            SetCalResistance(OHM_1K);
            SetSupplyChannel(curr_ad_ch) ;
            SetSupplyCurrent(1) ;
            SetMuxChannel(curr_ad_ch) ;
            ad_gain = 0 ;
            WriteAdByte(ad_gain | 0x10) ;			 /* Next write data */
            WriteAdByte(0x2a) ;						 /* Ad setup data */
            ad_settling = AD_SET_TIME ;			 /* wait 67 ms */
            ad_state = WAIT_FOR_INTERRUPT ; 		 /* next state */
          } else {
            ad_state = IDLE ;
          }
          break;
        case 0x01 :				  /* temp */
          if (ad_mode & 0x08) {						/* convert temp? */
            SetCalResistance(OHM_1K);
            SetSupplyChannel(curr_ad_ch) ;
            SetSupplyCurrent(1) ;
            SetMuxChannel(curr_ad_ch) ;
            ad_gain = 0 ;
            WriteAdByte(ad_gain | 0x10) ;			 /* Next write data */
            WriteAdByte(0x2a) ;						/* Ad setup data, bipolar*/
            ad_settling = AD_SET_TIME ;			 /* wait 67 ms */
            ad_state = WAIT_FOR_INTERRUPT ; 		 /* next state */
          } else {
            ad_state = IDLE ;
          }
          break;
        default :
          ad_state = IDLE ;
          break ;
      }
      break ;
    case	WAIT_FOR_INTERRUPT :
      break ;
    case	CONV_COMPLETE :
      WriteAdByte(ad_gain | 0x38) ;					/* Next read data */
      ad_data = ReadAdByte()* 256 ;			   /* read data 16 bit data from ad */
      ad_data += ReadAdByte() ;
      if (ad_mode & 0x40) {							/* cal point ? */
        ad_mode &= ~0x40 ;
        SetSupplyCurrent(1) ;
        SetMuxChannel(MUXCHOFF) ;
        SetSupplyChannel(SUPPCHOFF) ;
        SetCalResistance(OFF);
        ad_state = IDLE ;
        ad_timeout_cnt = 0 ;							/* timeout off */
        if (!(ad_mode & 0x01)) {					/* tx during conv? */
          cal_data[curr_ad_ch] = (short)(ad_data - 32767) ;    /* no, use data  */

          switch ((ch_stat[curr_ad_ch]>> 2) & 0x03) {
            case 0x03 :				   /* pressure */
              cal_data[curr_ad_ch] = (short)((float) cal_data[curr_ad_ch]* cal_gain) ;	 /* adjust for resistor errors */
              if ((cal_data[curr_ad_ch] > MAX_PRE_CAL) ||
                  (cal_data[curr_ad_ch] < MIN_PRE_CAL)) {
                ch_stat[curr_ad_ch] |= 0x02 ; 		/* Calibration fail */
              } else {
                ch_stat[curr_ad_ch] &= ~0x02 ;	/* Calibration OK */
              }
              if ((cal_data[curr_ad_ch] > FMAX_PRE_CAL)||
                  (cal_data[curr_ad_ch] < FMIN_PRE_CAL)) {
                ch_stat[curr_ad_ch] |= 0x01 ;		/* Reading fail */
                eep_type[curr_ad_ch >> 1] = 0 ; 	/* clear read status */
                mes_data[curr_ad_ch] = 0.0 ;	   /* ASt mark ?? */
                raw_data[curr_ad_ch] = curr_sens_data ; /* sen raw raw */
                if (ad_mode & 0x80) {				/* test */
                  ch_stat[curr_ad_ch] &= ~0x60 ;	/* no sensor */
                }
              } else {
                if (ad_mode & 0x80) {				/* test */
                  ch_stat[curr_ad_ch] |= 0x6c ;	/* pr. sensor  OK*/
                }
                ch_stat[curr_ad_ch] &= ~0x01 ;	/* Reading OK */
                curr_sens_data -= cal_zero ;
                raw_data[curr_ad_ch] = ( short)((float)curr_sens_data * 20000.0
                    / (float)cal_data[curr_ad_ch]) ;
                CalcPress(curr_ad_ch) ; 			/* calculate pressure */
              }
              break;
            case 0x02 :									/* "other" */
              break;
            case 0x01 :									/* temp */
              if ((cal_data[curr_ad_ch] > MAX_TMP_CAL ) ||
                  (cal_data[curr_ad_ch] < MIN_TMP_CAL )) {
                ch_stat[curr_ad_ch] |= 0x02 ; 		/* Calibration fail */
              } else {
                ch_stat[curr_ad_ch] &= ~0x02 ;		/* Calibration OK */
              }
              if ((cal_data[curr_ad_ch] > FMAX_TMP_CAL) ||
                  (cal_data[curr_ad_ch] < FMIN_TMP_CAL)) {
                ch_stat[curr_ad_ch] |= 0x01 ;		/* Reading fail */
                mes_data[curr_ad_ch] = 0.0 ;	     /* ASt mark ?? */
                raw_data[curr_ad_ch] = curr_sens_data ; /* sen raw raw */
                if (ad_mode & 0x80) {				/* test */
                  ch_stat[curr_ad_ch] &= ~0x60 ;	/* no sensor */
                }
              } else {
                if (ad_mode & 0x80) {
                  ch_stat[curr_ad_ch] |= 0x24 ;	/* tmp sensor  OK*/
                }
                ch_stat[curr_ad_ch] &= ~0x01 ;	/* Reading OK */
                raw_data[curr_ad_ch] = (short)(((float)curr_sens_data * 1000.0
                      / (float)cal_data[curr_ad_ch] ) * 10.0);
                CalcTemp(curr_ad_ch) ;				/* calculate temperature */
              }
              break;
            default :
              break ;
          }
        } else {
          curr_ad_ch-- ;                                 // remeasure the chanell if skipped due to UART TX
        }
      } else {												/* normal conv enter point */
        curr_sens_data = (short)(ad_data - 32767) ;	       /* use ad data */

        switch ((ch_stat[curr_ad_ch]>> 2) & 0x03) {
          case 0x03 :				  /* pressure */
            SetMuxChannel(PRE_CAL_CH) ;			/* cal channel */
            ad_mode |= 0x40 ;							/* next cal */
            ad_settling = AD_SET_TIME ;			/* wait 67 ms */
            ad_state = WAIT_FOR_INTERRUPT ; 		/* wait for cal int */
            UnpackSensData(curr_ad_ch) ;			/* Unpack data */
            break;
          case 0x02 :				   /* other */
            SetSupplyCurrent(1) ;					/* no cal on this */
            SetMuxChannel(MUXCHOFF) ;
            SetSupplyChannel(SUPPCHOFF) ;
            SetCalResistance(OFF);
            ad_state = IDLE ;
            raw_data[curr_ad_ch] = curr_sens_data ;
            cal_data[curr_ad_ch] = 0 ;		   /* do no use caldata  */
            ch_stat[curr_ad_ch] &= ~0x03 ;		/* Cal. and readings set to OK */
            ad_timeout_cnt = 0 ;						/* timeout off */
            if (ad_mode & 0x80) {					/* test */
              ch_stat[curr_ad_ch] |= 0x48 ;		/* other sensor  OK*/
            }
            CalcOther(curr_ad_ch) ; 				/* calculate "other" */
            break;
          case 0x01 :				  /* temp */
            SetMuxChannel(TMP_CAL_CH) ;			/* cal channel */
            ad_mode |= 0x40 ;							/* next cal */
            ad_settling = AD_SET_TIME ;			/* wait 67 ms */
            ad_state = WAIT_FOR_INTERRUPT ; 		/* wait for cal int */
            break;
          default :
            ad_state = IDLE ;							/* Start new point */
            break ;
        }
      }
      break ;
    case	START_CALIBRATION :
      Led(2, ON) ;										/* Led 2 on */
      ad_timeout_cnt = AD_TIMEOUT ;					/* timeout ad cnv */
      ad_settling = 20 ;								/* wait >mclock/128  */
      if (tx_complete == TRUE) {
        if (ad_mode & 0x02) {						/* pressure readings */
          ad_gain = 3;
        } else {
          ad_gain = 0;
        }
        ad_state = WAIT_FOR_CAL_INT ;				/* next state */
        WriteAdByte(ad_gain | 0x10) ;				/* Next write setup reg */
        WriteAdByte(0x6a) ;						/*  Ad setup data, bipolar */
      }
      break ;
    case	WAIT_FOR_CAL_INT :
      break ;
    case	CAL_COMPLETE :
      ad_timeout_cnt = 0 ;								/* timeout off */
      curr_ad_ch -= 1 ;									/* To start with ch 0 !! */
      ad_state = IDLE ;
      Led(2, OFF) ;										/* Led 2 off */
      break ;
    case	IDLE :
      break ;
    default :
      ad_state = IDLE ;
      break ;
  }
}

/*************************************************************************
 *
 *  Calculate and filter pressure
 *
 *************************************************************************/
void CalcPress(signed char ch)
{

  float temp_data ;

  Led(2, ON)	;								/* Led 2 on */

  if ((sens_data[0]>0) && (raw_data[ch] < sens_data[0])) {
    temp_data = CalcPercent((sens_data[1]-sens_data[0]), sens_data[0],
        raw_data[ch], 0.0) ;
    temp_data *= 40.0 ;				/* caluclate %, using 0-40% cal data*/

  } else if (raw_data[ch] <  sens_data[1]) {
    temp_data = CalcPercent((sens_data[1]-sens_data[0]), sens_data[0],
        raw_data[ch], (float)sens_nl1) ;
    temp_data *= 40.0 ;				/* caluclate % */

  } else if (raw_data[ch] < sens_data[2]) {
    temp_data = CalcPercent((sens_data[2]-sens_data[1]), sens_data[1],
        raw_data[ch], (float)(sens_nl2 / 3)) ;
    temp_data = temp_data*(60.0 - 40.0)+40.0 ;				/* caluclate % */

  } else if (raw_data[ch] < sens_data[3]) {
    temp_data = CalcPercent((sens_data[3]-sens_data[2]), sens_data[2],
        raw_data[ch], (float)sens_nl2 ) ;
    temp_data = temp_data*(100.0 - 60.0)+60.0 ;				/* caluclate % */

  } else {
    temp_data = CalcPercent((sens_data[3]-sens_data[2]), sens_data[2],
        raw_data[ch], 0.0) ;
    temp_data = temp_data*(100.0 - 60.0)+60.0 ;				/* caluclate % */
  }

  temp_data *= ((((float)packed_data[ch >> 1][6]/10.0) -
        (float) packed_data[ch >> 1][5] / 100.0) /100.0 ) * 10.197162;
  temp_data -= ((float) offset[ch] / 1000.0) ;
  temp_data *=  gain[ch] ;
  temp_data += ((float) packed_data[ch >> 1][5] / 100.0)	* 10.197162 ;
  mes_data[ch] += (temp_data - mes_data[ch])/ ((float)p_filter + 1.0) ;
  if ((mes_data[ch] > 500.0) || (mes_data[ch] < -50.0)) {
    mes_data[ch] = 0.0 ;
  }
  Led(2, OFF) ;								    /* Led 2 off */

}

/*************************************************************************
 *
 *  Calculate precentage for pressure
 *
 *************************************************************************/
float	CalcPercent( unsigned short span, short low_span, short raw_data,
    float nl)
{

  float x, yy, fspan, range ;

  range = (float)raw_data - (float)low_span ;
  fspan = (float)span ;

  x = range/fspan ;
  yy = (fspan - fspan*x)*fspan*x*nl/(fspan * fspan / 4.0) ;
  return (range - yy)/fspan ;

}

/*************************************************************************
 *
 *  Calculate and filter temperature
 *
 *************************************************************************/
void CalcTemp(signed char ch)
{

  float temp_data, resist, temp_resist ;

  resist = (float) raw_data[ch] ;
  resist /= 10.0 ;
  if (resist > 500.0 ) {								/* Pt 1000 ?*/
    resist /= 10.0 ;							    /* Yes */
  }

  temp_resist = resist - 100.0 ;
  temp_data = (temp_resist / 0.390802) +
    ((temp_resist * temp_resist)/1000.0) ;

  temp_data -= (float) offset[ch] / 10.0 ;
  temp_data *= gain[ch] ;
  mes_data[ch] += (temp_data - mes_data[ch])/ ((float)t_filter + 1.0) ;
}

/*************************************************************************
 *
 *  Calculate and filter "other"
 *
 *************************************************************************/
void CalcOther(signed char ch)
{

  float temp_data ;

  temp_data = (float)(raw_data[ch]) * 2.5 / 32767.0 ;
  /*input * 2.5 volt / +-15 bit*/
  temp_data -= (float) offset[ch]/ 10000.0 ;
  temp_data *= gain[ch] ;
  mes_data[ch] += (temp_data - mes_data[ch])/ ((float)o_filter + 1.0) ;

}

/*************************************************************************
 *
 *  Unpack sensor data
 *
 *************************************************************************/
void UnpackSensData(signed char ch)
{

  short knst, d_knst, g1, g2, g3 ;
  float temp_data ;
  unsigned char  temp_byte ;
  signed char c_ch ;

  temp_byte = FindTemp(ch);
  if (temp_byte >= NOIOCH ) {					/* no temp. found */
    temp_data = 0 ; 								/* 25. 0 - 25.0  */
  } else {
    temp_data = mes_data[temp_byte] - 25.0 ;
  }
  temp_data /= 100.0 ;			  /* use 1/100 deg C in calc. */

  c_ch = ch >>1 ; 						/* start calculate data for 0 % FRO */
  if ((eep_type[c_ch] & 0x01) || (eep_type[c_ch] & 0x10)) { /* OK data */
    knst =	((short) packed_data[c_ch][8] +
        packed_data[c_ch][9] * 256) & 0x1fff ;

    if (knst & 0x1000) {				/* negative */
      knst |= 0xe000 ;
    }
    g1 =  ((short) ((packed_data[c_ch][9] >> 5) & 0x07) +
        (packed_data[c_ch][10] * 8)	+
        ((packed_data[c_ch][11] & 0x03) * 2048)) & 0x1fff ;
    if (g1 & 0x1000) {			      /* negative */
      g1 |= 0xe000 ;
    }
    g2 =  ((short) ((packed_data[c_ch][11] >> 2) & 0x3f) +
        ((packed_data[c_ch][12] & 0x7f)* 64 )) & 0x1fff ;
    if (g2 & 0x1000) {			      /* negative */
      g2 |= 0xe000 ;
    }
    g3 =  ((short) ((packed_data[c_ch][12] >> 7) & 0x01) +
        (packed_data[c_ch][13] * 2)	+
        ((packed_data[c_ch][14] & 0x0f) * 512)) & 0x1fff ;
    if (g3 & 0x1000) {			      /* negative */
      g3 |= 0xe000 ;
    }
    sens_data[0] = CalcSensData(knst*2, g1*2, g2*2, g3*2, temp_data) ;
    /* sens value 0%FRO @ temp */

    /* start calculate data for 40 % FRO */
    d_knst =  ((short) ((packed_data[c_ch][14] >> 4) & 0x0f) +
        (packed_data[c_ch][15] * 16) +
        ((packed_data[c_ch][16] & 0x01) * 4096))& 0x1fff ;

    g1 =  ((short) ((packed_data[c_ch][16] >> 1) & 0x7f) +
        ((packed_data[c_ch][17] & 0x3f) * 128)) & 0x1fff ;
    if (g1 & 0x1000) {			      /* negative */
      g1 |= 0xe000 ;
    }
    g2 =  ((short) ((packed_data[c_ch][17] >> 6) & 0x03) +
        (packed_data[c_ch][18] * 4)	+
        ((packed_data[c_ch][19]& 0x07) * 1024)) & 0x1fff ;
    if (g2 & 0x1000) {			      /* negative */
      g2 |= 0xe000 ;
    }
    g3 =  ((short) ((packed_data[c_ch][19] >> 3) & 0x1f) +
        (packed_data[c_ch][20] * 32)) & 0x1fff ;
    if (g3 & 0x1000) {			      /* negative */
      g3 |= 0xe000 ;
    }
    knst += d_knst; 								/* remember new value */
    sens_data[1] = CalcSensData(knst*2, g1*2, g2*2, g3*2, temp_data) ;
    /* sens value 40%FRO @ temp */

    /* start calculate data for 60 % FRO */
    d_knst =  ((short) packed_data[c_ch][21] +
        packed_data[c_ch][22] * 256) & 0x1fff ;

    g1 =  ((short) ((packed_data[c_ch][22] >> 5) & 0x07) +
        (packed_data[c_ch][23] * 8)	+
        ((packed_data[c_ch][24] & 0x03) * 2048)) & 0x1fff ;
    if (g1 & 0x1000) {			      /* negative */
      g1 |= 0xe000 ;
    }
    g2 =  ((short) ((packed_data[c_ch][24] >> 2) & 0x3f) +
        ((packed_data[c_ch][25] & 0x7f)* 64 )) & 0x1fff ;
    if (g2 & 0x1000) {			      /* negative */
      g2 |= 0xe000 ;
    }
    g3 =  ((short)((packed_data[c_ch][25] >> 7) & 0x01) +
        (packed_data[c_ch][26] * 2)	+
        ((packed_data[c_ch][27] & 0x0f) * 512)) & 0x1fff ;
    if (g3 & 0x1000) {			      /* negative */
      g3 |= 0xe000 ;
    }
    knst += d_knst; 								/* remember new value */
    sens_data[2] = CalcSensData(knst*2, g1*2, g2*2, g3*2, temp_data) ;
    /* sens value 60%FRO @ temp */

    /* start calculate data for 100 % FRO */
    d_knst = ((short)((packed_data[c_ch][27] >> 4) & 0x0f) +
        (packed_data[c_ch][28] * 16) +
        ((packed_data[c_ch][29] & 0x01)) * 4096)& 0x1fff ;

    g1 =  ((short) ((packed_data[c_ch][29] >> 1) & 0x7f) +
        ((packed_data[c_ch][30] & 0x3f) * 128)) & 0x1fff ;
    if (g1 & 0x1000) {			      /* negative */
      g1 |= 0xe000 ;
    }
    g2 =  ((short) ((packed_data[c_ch][30] >> 6) & 0x03) +
        (packed_data[c_ch][31] * 4)	+
        ((packed_data[c_ch][32]& 0x07) * 1024)) & 0x1fff ;
    if (g2 & 0x1000) {			      /* negative */
      g2 |= 0xe000 ;
    }
    g3 =  ((short) ((packed_data[c_ch][32] >> 3) & 0x1f) +
        (packed_data[c_ch][33] * 32)) & 0x1fff ;
    if (g3 & 0x1000) {			      /* negative */
      g3 |= 0xe000 ;
    }
    knst += d_knst; 								/* remember new value */
    sens_data[3] = CalcSensData(knst*2, g1*2, g2*2, g3*2, temp_data) ;
    /* sens value 100%FRO @ temp */

    sens_nl1 = (signed char)((packed_data[c_ch][34] >> 3) & 0x0f) ; /*  NL1 */
    if ((packed_data[c_ch][34]) & 0x80) {
      sens_nl1 |= 0xf0 ;
    }
    sens_nl1 *= 3 ;

    sens_nl2 = (signed char) (packed_data[c_ch][34] & 0x07) ;		  /* NL2 */
    if ((packed_data[c_ch][34]) & 0x04) {
      sens_nl2 |= 0xf8 ;
    }
    sens_nl2 *= 3 ;

    offset[ch] =  (short) (packed_data[c_ch][35] +
        (packed_data[c_ch][36] * 256)) ;			/*offset*/

    gain[ch] =  1.0 + (float)((packed_data[c_ch][37] +
          packed_data[c_ch][38] * 256)/100000.0) ;	/*gain*/
    /* 256 can not be 256.0 !!!*/
  } else {
    sens_data[0] =	   0 ;					/* dummy values to prevent */
    sens_data[1] =	4000 ;		       /* divide by zero */
    sens_data[2] =	8000 ;
    sens_data[3] = 12000 ;
    sens_nl1 = 0 ;
    sens_nl2 = 0 ;
    offset[ch] =  0 ;						/*offset*/
    gain[ch] =  1.0 ;						/* gain */
  }
  if ((eep_type[7] & 0x01) || (eep_type[7] & 0x10)){     /* ok data */
    cal_zero = (short) packed_data[7][35] + packed_data[7][36] * 256 ;
    cal_gain =  1.0 + (float)((packed_data[7][37] +
          packed_data[7][38] * 256)/100000.0) ; /*gain*/
    /* 256 can not be 256.0 !!!*/
  } else {
    cal_zero = 0 ;
    cal_gain = 1.0 ;
  }
}

/*************************************************************************
 *
 *  Calculate sensordata
 *
 *************************************************************************/
short CalcSensData(short knst, short g1, short g2, short g3, float temp)
{

  return (knst + (g1 * temp) +
      (g2 * temp * temp) +
      (g3 * temp * temp * temp)) ;	/* sens value ?%FRO @ temp */

}

/*************************************************************************
 *
 *  Find temperature for a channel
 *
 *************************************************************************/
short FindTemp(signed char ch)
{

  short temp_ch, i ;

  temp_ch = (short) ch + 1 ;
  if (((ch_stat[temp_ch] & 0xc) == 0x4) &&
      (mes_data[temp_ch] < 150.0) && 					/* to high or */
      (mes_data[temp_ch] > -80.0) && 					/* to low temp or */
      (!(ch_stat[temp_ch] & 0x01))) {					/* convertion error */
  } else {
    temp_ch = NOIOCH ;							/* used if no temp */
    for (i = 0; i < NOIOCH; i++) {
      if ((ch_stat[i] & 0x0c) == 0x04) {  /* temp ? */
        if ((mes_data[i] < 150.0) &&	     /* to high or */
            (mes_data[i] > -80.0) &&	  /* to low temp or */
            !(ch_stat[i] & 0x01)) {	     /* convertion error */
          temp_ch = i ;
          i = NOIOCH ;								/* exit */
        }
      }
    }
  }

  return temp_ch ;
}

/*************************************************************************
 *
 *  Read from AD-converter
 *
 *************************************************************************/
unsigned char ReadAdByte(void)
{

  unsigned char i, read_byte ;

  for (i = 0; i <  8; i++) {
    read_byte <<= 1 ;						  /* shift to next bit */
    P5DR &= ~ADCLK ;								/*	set clock line low */
    P5DR |= ADCLK ; 								/*	set clock line high */
    if (P5DR & ADDO) {							/* data  = 1? */
      read_byte |= 0x01 ;						/* set bit high */
    } else {
      read_byte &= ~0x01 ;						/* set bit low */
    }
  }
  return read_byte ;
}

/*************************************************************************
 *
 *  Write to AD-converter
 *
 *************************************************************************/
void WriteAdByte(unsigned char data)
{

  short i;

  for (i = 0; i <  8; i++) {
    P5DR &= ~ADCLK ;								/*	set clock line low */
    if (data & 0x80) {							/* data bit = 1? */
      P5DR |= ADDI ;								/* set data high */
    } else {
      P5DR &= ~ADDI ;								/* set data low */
    }
    data <<= 1 ;							 /* shift to next bit */
    P5DR |= ADCLK ; 								/*	set clock line high */
  }
}



/*************************************************************************
 *
 *  Reset pointer to RX received data on RS485
 *
 *************************************************************************/
void ResetRxPointer(void) {

  rx_indx = 1 ;
  rx_hndx = 0 ;
  rx_start = 0 ;
  rx_buff[0] = 0 ;
  rx_buff[1] = 0 ;
  rx_buff[2] = 0 ;
  rx_state = SYNC ;					/* error in pack len */
  rx_timeout = OFF ;				   /* timeout on channel */
}

/*************************************************************************
 *
 * Calculate rx checksum
 *
 *************************************************************************/
int CalcRxChecksum(void)
{

  int				cnt ;
  unsigned char	csum ;

  csum = 0 ;
  for (cnt=rx_start ; cnt < (rx_start+rx_packlen-2) ; cnt++) {
    csum = crc[csum ^ rx_buff[cnt]] ;
  }
  if (csum == (rx_buff[rx_start + rx_packlen - 2])) {
    return TRUE ;
  } else {
    return FALSE ;
  }
}



/*************************************************************************
 *
 *  Handle rx data on RS485
 *
 *************************************************************************/
void HandleRxPacket(void)
{
  short	  pointer, ndb, more ;

  Led(1, ON) ;
  sendtail = FALSE ;
  more	= TRUE ;
  pointer = 0 ;
  ndb	= 2 ;											/* point to first command */
  pointer = rx_start;								/* Point to  command */
  while (more && (pointer < (rx_packlen + rx_start))) {
    pointer = pointer + ndb + 2;				/* Point to  command */
    ndb = rx_buff[pointer+1]	;				/* Save pointer to next command */
    if (!CheckAction(pointer)){
      more = FALSE ;								/* terminate while  */
    }
  }
  Led(1, OFF) ;
}

/*************************************************************************
 *
 *  Receive data on RS485
 *
 *************************************************************************/
int ReceiveRxPacket(void)
{
  int	  ret_val, cnt, new_sync ;

  ret_val = FALSE ;
  rx_timeout = RX_TO_TIME ;				/* timeout on channel */
  while (rx_indx > rx_hndx) {						/* more char to check */
    switch (rx_state) {						/* check state */
      case SYNC :
        // all functionallity moved to inerrupt routine for receive
        // on version 10
        break ;
      case HEADER :
        if ((rx_hndx-rx_start) >= 3) { 			/* rec. header */
          rx_packlen = ((rx_buff[rx_start+2] * 256) +
              rx_buff[rx_start+3] ) ; 			/* calc. pack.len */
          if ((rx_packlen < ((short) RX_SIZE-rx_hndx)) &&    /* chk. header */
              (rx_packlen >= MIN_PACK_LEN) &&
              (rx_buff[rx_start+1] != 0xff)) {
            rx_state = RECEIVE ;					/* header ok */
            rx_counter = rx_hndx - rx_start + 1 ;
          } else {
            ResetRxPointer() ;
          }
        }
        break ;
      case RECEIVE :
        if (++rx_counter >= rx_packlen) {
          if ((rx_buff[rx_packlen + rx_start-1]) == ETX) {
            if (CalcRxChecksum()) {
              if (rx_buff[rx_start + 1] < PC_START_ADDRESS) {
              }
              if ((rx_buff[rx_start] == GetMyAddress())||
                  (rx_buff[rx_start] == 0)){	       /* don't use address*/
                ret_val = TRUE ;
              }
            } else {
              ResetRxPointer() ;			    /* reset pointer */
            }
          }
        }
        break ;
      default :
        ResetRxPointer() ;							/* reset pointer */
        break ;
    }														/* end switch */
    if (++rx_hndx >= RX_SIZE) {					/* check pointer */
      ResetRxPointer() ;							/* reset pointer */
    }
  }															/* end while.. */
  return ret_val ;
}




/*************************************************************************
 *
 *      IRQ 0	(Not used)
 *
 *************************************************************************/
interrupt [IRQ_0] void Irq0Int(void)
{

}


/*************************************************************************
 *
 *      IRQ 1 , interrupt from AD converter
 *
 *************************************************************************/
interrupt [IRQ_1] void Irq1Int(void)
{

  if (ad_mode & 0x20) {						/* ok for int */
    ad_state++ ;								/* Go to next state */
    ad_mode &= ~0x20;							/* int ok, reset flag */
  }

}


/*************************************************************************
 *
 *      IRQ 2 , external int from display connector
 *
 *************************************************************************/
interrupt [IRQ_2] void Irq2Int(void)
{

}


/*************************************************************************
 *
 *  Free running timer capture interrupt routine
 *
 *************************************************************************/
interrupt [FRT_ICI] void FrtcInt(void)
{

  unsigned temp_icr;

  temp_icr = FRT_ICR ;
  FRT_TCSR &= ~TCSRF_ICF; 	/* clear input capt flag */
}

/*************************************************************************
 *
 *  Free running timer overflow interrupt routine
 *
 *************************************************************************/
interrupt [FRT_FOVI] void FrtoInt(void)
{

  FRT_TCSR &= ~TCSRF_OVF; 	/* clear overflow flag */
}

/*************************************************************************
 *
 *  Timer interrupt routine
 *
 *  This routine is called each msec
 *
 *************************************************************************/
interrupt [TMR_CMI1A] void TimInt(void)
{

  TMR1_TCSR &= ~(TCSR_CMFB | TCSR_CMFA | TCSR_OVF);
  /* Clear match to reenable interrupt */

  if (ms_delay_cnt) {							/* count down 1 ms delay */
    ms_delay_cnt-- ;
  }

  if (!--sec_cnt) {				/* counter for 1 sec. */
    sec_cnt = SEC_CNT_INIT;
    if (time_b_cnt) {			/* timer for temperature readings */
      time_b_cnt-- ;
    }
    if (time_e_cnt) {			/* timer for eed check*/
      time_e_cnt-- ;
    }
  }

  if (ad_settling) {							/* count down ad setling time */
    if (!--ad_settling) {
      ad_mode |= 0x20;						/* Ok for int 1 */
    }
  }
  /* timeout ad converter */
  if (ad_timeout_cnt) {
    if (!--ad_timeout_cnt) {
      ad_state = IDLE ;
      ResetADCBySW();
    }
  }

  if (rx_timeout) {								/* check timeout on tx0  */
    if (!--rx_timeout) {
      ResetRxPointer();
    }
  }


  if (tx_tail) {									/* check tx0 driver */
    if (!--tx_tail) {
      TxDriver(OFF);
      tx_complete = TRUE;
      ResetRxPointer() ;			/* reset pointer */
      Led(1, OFF) ;
    }
  }

  if (wait_for_pc) {							/* delay before sending ch0 */
    ad_mode |= 0x01 ;				 /* mark that byte aresent */
    if (!--wait_for_pc) {
      SCI0_TDR = tx_buff[tx_indx++];
      SCI0_SSR &= ~SSR_TDRE;				/* clear TDRE-flag */
      SCI0_SCR |= SCR_TIE;					/*  enable  tx int */
      Led(1, ON) ;
    }
  }
}


/*************************************************************************
 *
 *  Transmit interrupt routine  TX0
 *
 *  This routine is called on transmition on serial line 0 (RS485)
 *
 ****************************************************************************/
interrupt [SCI_TXI0] void Tx0Int(void)
{

  char status;

  status = SCI0_SSR;
  if (tx_indx < tx_bytes) {	       /* More to send ? */
    SCI0_TDR = tx_buff[tx_indx++];
    SCI0_SSR = status & ~SSR_TDRE;        /* clear TDRE-flag */
    ad_mode |= 0x01 ;				 /* mark that byte are sent */
  } else {
    SCI0_SCR &= ~SCR_TIE;		       /* Disable tx int */
    tx_tail = TXTAIL ;		       /* driver on for last char */
  }
}


/*************************************************************************
 *
 *  Error interrupt routine
 *
 *  Error on RS485 port 0 goes here.
 *
 *************************************************************************/
interrupt [SCI_ERI0] void Err0Int(void)
{

  char status;

  status = SCI0_SSR;
  SCI0_SSR = status & ~(SSR_ORER | SSR_FER | SSR_PER);

}


/*************************************************************************
 *
 *  Receive interrupt routine  RX0
 *
 *  Char received on serial port 0
 *
 *************************************************************************/
interrupt [SCI_RXI0] void Rx0Int(void)
{

  char status, bufch;

  status = SCI0_SSR;
  bufch = SCI0_RDR;


  if (tx_complete) {						/* ok to receive? */
    switch (rx_state) {                     /* check state */
      case SYNC :
        if (bufch == STX) {
          sync_cnt ++ ;               // cont sync
        } else if (sync_cnt >= 2) {
          sync_cnt = 0 ;              // reset counter
          rx_state = HEADER ;
          rx_indx = 0 ;
          rx_hndx = 0 ;
          rx_start = rx_hndx ;            /* start after the two STX */
          rx_buff[rx_indx++] = bufch;
        } else {
          sync_cnt = 0 ;                  // start over once more
        }
        break;
      default:
        rx_buff[rx_indx++] = bufch;
        break;
    }
    if (rx_indx >= RX_SIZE) {           /* check rx pointer */
      ResetRxPointer() ;              // reset pointer
    }
  }
  SCI0_SSR = status & ~SSR_RDRF;			/* Reset RDRF */
}


/*************************************************************************
 *
 *  Transmit interrupt routine  TX1
 *
 *  This routine is called on transmition on serial line 1
 *
 ****************************************************************************/
interrupt [SCI_TXI1] void Tx1Int(void)
{

  char status;

  status = SCI1_SSR;
  SCI1_TDR = 0;
  SCI1_SSR = status & ~SSR_TDRE;	/* clear TDRE-flag */
  SCI1_SCR &= ~SCR_TIE;					/* Disable tx int */
}


/*************************************************************************
 *
 *  Error interrupt routine
 *
 *  Error on port 1 goes here.
 *
 *************************************************************************/
interrupt [SCI_ERI1] void Err1Int(void)
{

  char status;

  status = SCI1_SSR;
  SCI1_SSR = status & ~(SSR_ORER | SSR_FER | SSR_PER);

}


/*************************************************************************
 *
 *  Receive interrupt routine  RX1
 *
 *  Char received on serial port 1
 *
 *************************************************************************/
interrupt [SCI_RXI1] void Rx1Int(void)
{

  char status, bufch;

  status = SCI1_SSR;
  bufch  = SCI1_RDR;
  SCI1_SSR = status & ~SSR_RDRF;	/* Reset RDRF */
}


/*************************************************************************
 *
 *  MAIN ROUTINE
 *
 *************************************************************************/
int main(void)
{
  int		cnt ;

  InitRegs();
  InitVar();
  InitStartup();

  ResetADCBySW();

  set_interrupt_mask(0);	/* Enable interrupt */
  SCI0_SCR = 0x7c;			/* enable rx0/tx0 + rx0 interrupt */

  CheckEepChannel()	;

  while (TRUE) {
    KickDog();
    /* communication starts here */
    if (rx_indx > rx_hndx) {			/* new char in buffer ? */
      if (ReceiveRxPacket()) {
        HandleRxPacket() ;			/* Handle here */
        ResetRxPointer() ;			/* reset pointer */
      }
    }
    /* AD convert starts here */
    CheckConvert();
  }												/* end while.. */

  return 0 ;
}

/* end program ******************************************************/

