/*******************************************************

*
*     Program for signal convertion card, AN-SGCNV
*
*     Company: ARISTON Norway as
*
*     Author: Thierry Pottier
*
*    * @file     routine.c
	 * @brief    Routine Header File
	 * @version  V0.00
	 * @date     18. October 2022
	 * @note
*

*******************************************************/

#include "Routine.h"
#include "PinName.h"
#include "SGcom.h"
#include "SGeep.h"

// I/O Registers definitions
#include <avr64db64.h>
#include <stdio.h>
#include "delay.h"
#include <iobits.h>
#include "math.h"
#include "float.h"
// Standard definitions
#include <stddef.h>
#include <string.h>
// SPI initialization functions
#include "spi_init.h"
#include "usarts_init.h"

///** Local variables */
//static     uint16_t adcreadout;
unsigned char       tx_buff[TX_SIZE] ;
unsigned char       rx_buff[RX_SIZE] ;
//unsigned int       tx_indx ;
unsigned char       tx_indx ;

unsigned char       tx_bytes ;
unsigned char       tx_tail;
unsigned char       wait_for_pc ;
unsigned char       rx_indx ;
unsigned char       rx_hndx ;
unsigned char       rx_start ;
unsigned char       rx_counter ;
unsigned char       rx_packlen ;
unsigned char       rx_timeout ;
unsigned char       sync_cnt ;

//short               sens_data[UNPACKED_DATA_SIZE] ;     /*  unpacked data */
unsigned int               sens_data[UNPACKED_DATA_SIZE] ;     /*  unpacked data */

signed char         sens_nl1 ;                          /* none linearity 1*/
signed char         sens_nl2 ;                          /* none linearity 2*/

//unsigned int       packed_data[NOPSD][PACKED_DATA_SIZE] ; /* packed sensor data */
unsigned char       packed_data[NOPSD][PACKED_DATA_SIZE] ; /* packed sensor data */

/* and the on board eep*/
unsigned char       eep_status;                /* status byte of the eep*/
unsigned char       time_b_temp;               /* time between temp read */
unsigned char       time_b_cnt;                /* time between temp cnt */
unsigned char       time_e_cnt;               /* time between eep check */
unsigned int      ad_timeout_cnt ;          /* timeout ad conv */
unsigned int      sec_cnt ;                 /* seconds sounter */
unsigned int  ms_cnt;                 /* seconds sounter */

unsigned int               curr_sens_data ;        /* sensor data from ad conv. */

unsigned int               cal_data[NOIOCH] ;      /* calibration data */
unsigned int               raw_data[NOIOCH] ;      /* raw data from senors */
float               mes_data[NOIOCH];       /* measured data result */
volatile unsigned char       highlevel;              // high level result
unsigned int     washtrac[NOWT];          // Whashtrec result
volatile char       washtrac_prev;          // Whashtrec previous port state

float               gain[NOIOCH] ;          /* gain for sensors */
unsigned int               offset[NOIOCH] ;        /* offset for sensors */

float               cal_gain;               /* gain for the 1 ohm resistor */
unsigned int               cal_zero;               /* zero for the 1 ohm resistor */

unsigned char       not_mes_data ;          /* number of tx of measured data */
unsigned char       not_raw_data ;          /* number of tx of raw data */
unsigned char       not_cal_data ;          /* number of tx of calib. data */

signed char        curr_ad_ch ;             /* current ad ch */
unsigned char       old_curr_ad_ch;
unsigned char       ad_state    ;               /* status for ad conversion */
unsigned char       ad_mode ;               /* modus */
/*Bit 7 = test mode
   Bit 6 = next cal conv.
   Bit 5 =
   Bit 4 = Start new channel
   Bit 3 = Read temperature
   Bit 2 = Read other
   Bit 1 = Read Pressure
   Bit 0 =        */
unsigned int      ms_delay_cnt ;              /* increased each millisecond */
unsigned int      ad_settling ;               /* ad settling timer */

unsigned char       ad_gain ;                   /* ad com register, keep gain */

unsigned char       ch_stat[NOIOCH] ;               /* sensor status */
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

unsigned char       eep_type[NOPSD] ;           /* eeprom status*/
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

unsigned char       p_filter ;              /* pressure filter */
unsigned char       t_filter ;              /* temperature filter */
unsigned char       o_filter ;              /* "other" filter */
unsigned char       my_address ;            /* my address */
volatile unsigned char       rx_state ;              /* rx state */
volatile unsigned char       tx_complete ;           /* tx state */

unsigned char       sendtail ;

// take away "zero value for Raw data ..
unsigned char ZeroCountTemp;
unsigned char ZeroCountPress;
//unsigned char ZeroCountOther;

//flash unsigned char crc[] =             /*Dallas Semiconductor one-wire CRC table */
const unsigned char crc[] =             /*Dallas Semiconductor one-wire CRC table */
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

//unsigned char BuffCRC_Index;
//unsigned char BuffCRC[32];


void    InitVar(void)
{
/*************************************************************************
*
*	Initialize variables
*
*************************************************************************/

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
        for ( i = 0; i< NOIOCH; i += 2 ) {
            ch_stat[i] = 0x0c ;         /*channel setup, try pressure */
        }
        for ( i = 1; i< NOIOCH; i += 2 ) {
            ch_stat[i] = 0x04 ;         /*channel setup, try temp */
        }
        for ( i = 0; i< NOPSD; i++ ) {
            eep_type[i] = 0 ;               /*eeprom status */
        }
        for ( i = 0; i< NOIOCH; i++ ) {
            offset[i] = 0 ;                         /*channel setup, offest */
            gain[i] = 1.0;
        }

    /*
    **	Init other variables
    */

        cal_gain = 1.0 ;
        cal_zero = 0 ;
        p_filter = 5 ;
        //t_filter = 2 ;
        t_filter = 4 ;  // filter for temperature
        o_filter = 2 ;
        sec_cnt = SEC_CNT_INIT;                 /* initvalue for 1 sec counter */
        ms_cnt   = 0;
        ad_state = IDLE ;                           /* no convertion */
        curr_ad_ch = NOIOCH  ;
        ad_mode = 0x88 ;                            /* test mode on and start with press.*/
        ad_mode |= 0x10 ;                           /* mark restart of card */
        ad_gain = 0 ;                               /* gain 1 */
        time_b_temp = 15 ;                      /* temp readings in sec */
        time_b_cnt = time_b_temp ;
        time_e_cnt = TIME_BETWEEN_EEP ;
        not_mes_data = 0 ;
        not_raw_data = 0 ;
        not_cal_data = 0 ;


    }

void    InitStartup(void)
    {
        
        ResetADCByHW();             // CS is low      
        //P5DR |= ADCLK ;                             /*	set AD clock line high */
        ADC_CLOCK_HIGH;                             /*	set AD clock line high */
        Led(1, OFF) ;                               /* switch leds off */
        Led(2, OFF) ;  
        Led(3, OFF) ;
        Led(4, OFF) ;

        TxDriver(OFF) ;                             /* tx enable off */
        SetEepromChannel(EEPCHOFF) ;            /* set eeprom channel off */
        SetMuxChannel(MUXCHOFF) ;               /* set mux channel off */
        SetSupplyChannel(SUPPCHOFF) ;            /* set supply channel off */
        SetGNDChannel (GNDCHOFF);
        SetSupplyCurrent(1);                        /* set 1 mA supply */

        //GetMyAddress() ;                            /* get my address */  
        my_address=MYADRESS_LOCAL;
    }
    
void Led(unsigned char no, unsigned char state)
{
    switch ( no ) 
    {
        case    1:                                      /* LED 1 */
            switch ( state ) {
            case ON :
                LED1_ON;
                break ;
            case OFF :
            default :
                LED1_OFF;
                break ;
            }
            break ;
            
        case    2:                                      /* LED 2 */
            switch ( state ) {
            case ON :
                LED2_ON;
                break ;
            case OFF :
            default :
                LED2_OFF;
                break ;
            }
            break ;
             
        case 3:
            switch ( state ) {
            case ON :
                LED3_ON;
                break ;
            case OFF :
            default :
                LED3_OFF;
                break ;
            }
            break ; 

      
        case 4: 
        
            switch ( state ) {
            case ON :
                LED4_ON;
                break ;
            case OFF :
            default :
                LED4_OFF;
                break ;
            }
        break;
        default : 
            LED1_OFF;
            LED2_OFF;
            LED3_OFF; 
            LED4_OFF;
        break ;
    }
}
/*************************************************************************
*
*  Enable / disable RS485 driver 
*
*************************************************************************/
void TxDriver(unsigned char state)
{
    switch ( state ) {
    case ON :                           /* driver on */
        SETBIT( PORTA.OUT,7);  
        //delay_ms(5);
         USART0.CTRLA|=USART_DREIE_bm;      //enable sending
       //USART0.TXDATAL=0;
        break;
    case OFF :
        //delay_ms(5);                          /* driver off */
        CLRBIT( PORTA.OUT,7);
        break;
    default :
        break;
    }
}
/*************************************************************************
*
*  Set com channel to a eeprom DS2430
*
*************************************************************************/
void SetEepromChannel(unsigned char channel)
{   
    SetGNDChannel ( channel);   // set GND on

    if ( channel == EEPCHOFF ) 
    {
        /* switch off any channel */  
        CLR_408A0;
        CLR_408A1;
        CLR_408A2;
        CLR_408E2; 
     } 
    else 
    {   CLR_408E2;
        switch (channel)
        {  default:
            case 0:  //add 1
            CLR_408A0;
            CLR_408A1;
            CLR_408A2;

           break;

           case 1: //add 2
            SET_408A0;
            CLR_408A1;
            CLR_408A2;
           break;
               
           case 2:  //add 3
            CLR_408A0;
            SET_408A1;
            CLR_408A2;
           break;
             
           case 3:  //add 4
            SET_408A0;
            SET_408A1;
            CLR_408A2;   
           break;
               
           case 4:  //add 5
            CLR_408A0;
            CLR_408A1;
            SET_408A2;   
           break;
               
           case 5:  //add 6
            SET_408A0;
            CLR_408A1;
            SET_408A2;   
           break;
               
           case 6:  //add 7
            CLR_408A0;
            SET_408A1;
            SET_408A2;   
           break;
               
           case 7:  //add 8
            SET_408A0;
            SET_408A1;
            SET_408A2;   
           break;     
        }    
        SET_408E2 ;  /* set channel and enable bit */
    }
}
/*************************************************************************
*
*  Set supply channel to a sensor
*
*************************************************************************/
void SetSupplyChannel(unsigned char channel)
{

    if ( channel == SUPPCHOFF ) 
    {
        CLR_406A0;                                 /* switch off any channel */
        CLR_406A1;
        CLR_406A2;
        CLR_406A3; 
        CLR_406E1;
    } 
    else 
    {   CLR_406E1;  // turn off mux power
        switch (channel)
        {      default:
                case 0:
                    CLR_406A0;                                 
                    CLR_406A1;
                    CLR_406A2;
                    CLR_406A3;  
                    SetGNDChannel (0); 
               break;

               case 1:
                    SET_406A0;                                 
                    CLR_406A1;
                    CLR_406A2;
                    CLR_406A3; 
                    SetGNDChannel (0); 
               break;
               
               case 2:
                    CLR_406A0;                                 
                    SET_406A1;
                    CLR_406A2;
                    CLR_406A3; 
                    SetGNDChannel (1); 
               break;
               
               case 3:
                    SET_406A0;                                 
                    SET_406A1;
                    CLR_406A2;
                    CLR_406A3; 
                    SetGNDChannel (1); 
               break;
               
               case 4:
                    CLR_406A0;                                 
                    CLR_406A1;
                    SET_406A2;
                    CLR_406A3; 
                    SetGNDChannel (2); 
               break;
               
               case 5:
                    SET_406A0;                                 
                    CLR_406A1;
                    SET_406A2;
                    CLR_406A3; 
                    SetGNDChannel (2); 
               break;
               
               case 6:
                    CLR_406A0;                                 
                    SET_406A1;
                    SET_406A2;
                    CLR_406A3;         
                    SetGNDChannel (3); 
               break;
               
               case 7:
                    SET_406A0;                                 
                    SET_406A1;
                    SET_406A2;
                    CLR_406A3;
                    SetGNDChannel (3);  
               break;
               
               case 8:
                    CLR_406A0;                                 
                    CLR_406A1;
                    CLR_406A2;
                    SET_406A3; 
                    SetGNDChannel (4);
               break;
               
               case 9:
                    SET_406A0;                                 
                    CLR_406A1;
                    CLR_406A2;
                    SET_406A3;      
                    SetGNDChannel (4);
               break;
               
               case 10:
                    CLR_406A0;                                 
                    SET_406A1;
                    CLR_406A2;
                    SET_406A3;
                    SetGNDChannel (5); 
               break;
               
               case 11:
                    SET_406A0;                                 
                    SET_406A1;
                    CLR_406A2;
                    SET_406A3;   
                    SetGNDChannel (5);
               break;
               
               case 12:
                    CLR_406A0;                                 
                    CLR_406A1;
                    SET_406A2;
                    SET_406A3;   
                    SetGNDChannel (6);
               break;
               
               case 13:
                    SET_406A0;                                 
                    CLR_406A1;
                    SET_406A2;
                    SET_406A3;  
                    SetGNDChannel (6);
               break;
               
               case 14:
                    CLR_406A0;                                 
                    SET_406A1;
                    SET_406A2;
                    SET_406A3;   
                    SetGNDChannel (7);
               break; 
               
               case 15:
                    SET_406A0;                                 
                    SET_406A1;
                    SET_406A2;
                    SET_406A3;   
                    SetGNDChannel (7);
               break;                  
               }
        SET_406E1;  // Enable Mux power
    }
}

/*************************************************************************
*
*  Set  channel to GND 
*
*************************************************************************/
void SetGNDChannel(unsigned char channel)
{
    if ( channel == EEPCHOFF ) 
    {
        /* switch off any channel */  
        CLR_408A0;
        CLR_408A1;
        CLR_408A2;
        CLR_408E1;
    } 
    else 
    {   CLR_408E1;
        switch (channel)
        {  default:
           case 0:  //add 1
            CLR_408A0;
            CLR_408A1;
            CLR_408A2;

           break;

           case 1: //add 2
            SET_408A0;
            CLR_408A1;
            CLR_408A2;
           break;
               
           case 2:  //add 3
            CLR_408A0;
            SET_408A1;
            CLR_408A2;
           break;
             
           case 3:  //add 4
            SET_408A0;
            SET_408A1;
            CLR_408A2;   
           break;
               
           case 4:  //add 5
            CLR_408A0;
            CLR_408A1;
            SET_408A2;   
           break;
               
           case 5:  //add 6
            SET_408A0;
            CLR_408A1;
            SET_408A2;   
           break;
               
           case 6:  //add 7
            CLR_408A0;
            SET_408A1;
            SET_408A2;   
           break;
               
           case 7:  //add 8
            SET_408A0;
            SET_408A1;
            SET_408A2;   
           break;            
               
        }    
        SET_408E1 ;  /* set channel and enable bit */
    }
}

/*************************************************************************
*
*  Set mux channel to a sensor
*  1 - 4 407 A0-A2 , 407E1
*  5 - 7 407 A0-A2 , 407E2
*
*************************************************************************/
void SetMuxChannel(unsigned char channel)
{

    if ( channel == MUXCHOFF ) 
    {
        CLR_407E1 ;                             /* switch off any channel */  
        CLR_407E2 ;                             /* switch off any channel */
    } 
    else 
    {
        CLR_407E1 ;                             /* switch off any channel */  
        CLR_407E2 ; 
        switch (channel)
               {
               default:
               case 0:
                    CLR_407A0;                                 
                    CLR_407A1;
                    CLR_407A2;
                    SET_407E1; 
               break;

               case 1:
                    SET_407A0;                                 
                    CLR_407A1;
                    CLR_407A2;
                    SET_407E1; 
               break;
               
               case 2:
                    CLR_407A0;                                 
                    SET_407A1;
                    CLR_407A2;
                    SET_407E1;  
               break;
               
               case 3:
                    SET_407A0;                                 
                    SET_407A1;
                    CLR_407A2;
                    SET_407E1; 
               break;
               
               case 4:
                    CLR_407A0;                                 
                    CLR_407A1;
                    SET_407A2;
                    SET_407E1;  
               break;
               
               case 5:
                    SET_407A0;                                 
                    CLR_407A1;
                    SET_407A2;
                    SET_407E1;  
               break;
               
               case 6:
                    CLR_407A0;                                 
                    SET_407A1;
                    SET_407A2;
                    SET_407E1; 
               break;
               
               case 7:
                    SET_407A0;                                 
                    SET_407A1;
                    SET_407A2;
                    SET_407E1;  
               break;
               
               case 8:
                    CLR_407A0;                                 
                    CLR_407A1;
                    CLR_407A2;
                    SET_407E2; 
               break;
               
               case 9:
                    SET_407A0;                                 
                    CLR_407A1;
                    CLR_407A2;
                    SET_407E2;  
               break;
               
               case 10:
                    CLR_407A0;                                 
                    SET_407A1;
                    CLR_407A2;
                    SET_407E2;  
               break;
               
               case 11:
                    SET_407A0;                                 
                    SET_407A1;
                    CLR_407A2;
                    SET_407E2; 
               break;
               
               case 12:
                    CLR_407A0;                                 
                    CLR_407A1;
                    SET_407A2;
                    SET_407E2; 
               break;
               
               case 13:
                    SET_407A0;                                 
                    CLR_407A1;
                    SET_407A2;
                    SET_407E2; 
               break; 
               
               case 14:         // Set cal 1K
                    CLR_407A0;                                 
                    SET_407A1;
                    SET_407A2;
                    SET_407E2; 
               break; 
               
               case 15:         // not used
                    SET_407A0;                                 
                    SET_407A1;
                    SET_407A2;
                    SET_407E2; 
               break;                
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
    if ( current == 10 ) 
    {
        CUR_10MA;                    /* set 10 mA */
    } 
    else 
    {
        CUR_1MA ;                    /* set 1 mA */
    }
}

    
/*************************************************************************
*
*  Select calibration resistance
*
*************************************************************************/
void SetCalResistance(unsigned char value)
{
    switch ( value ) 
    {
        case OHM_1R :   // 1 ohm resistor 
            SET_RES1R ;
            CLR_RES1K ;
            break ;
        case OHM_1K :  // 1000 ohm resistor 
            SET_RES1K ;
            CLR_RES1R ;
            break ;
        default :     // both off 
            CLR_RES1R ;    
            CLR_RES1K;
            break ;
    }
}

/*************************************************************************
*
*  Check new convertion*
*************************************************************************/
void CheckConvert(void)
{

    if ( ad_state == IDLE ) {            /* New channel? */
        ad_state = START_NEW_POINT ;
        if ( curr_ad_ch < (NOIOCH-1) ) 
        {   old_curr_ad_ch= curr_ad_ch; // debugg
            curr_ad_ch++ ;
        } 
        else 
        {
            curr_ad_ch = 0 ; 
            //if ( !time_e_cnt==0 )
            if ( time_e_cnt==0 ) {
                if ( ad_mode & 0x80 ) {               /* test */
                    ad_mode &= ~0x80 ;              /* test mode off */
                }
                CheckEepChannel()   ;                   /* Check the sensordata */
                time_e_cnt = TIME_BETWEEN_EEP ;
            }
            if ( not_mes_data && (ad_mode & 0x02) ) 
            {     /* autosend? */
                BuildHeader() ;                     /* Build send packet header */
                BuildMPData();                      /* Build data p. for pressure */
                BuildMTData();                      /* Build data p. for temp */
                BuildMOData();                      /* Build data p. for other */
                BuildTail(NO_MORE_DATA, 0) ;    /* Build tail */
                not_mes_data-- ;
            } 
            else if ( not_raw_data && (ad_mode & 0x02) )
             {  /* autosend? */
                BuildHeader() ;                     /* Build send packet header */
                BuildRPData();                      /* Build data p. for pressure */
                BuildRTData();                      /* Build data p. for temp */
                BuildROData();                      /* Build data p. for other */
                BuildTail(NO_MORE_DATA, 0) ;    /* Build tail */
                not_raw_data-- ;
            } 
            else if ( not_cal_data && (ad_mode & 0x02) ) {  /* autosend? */
                BuildHeader() ;                     /* Build send packet header */
                BuildCalData();                     /* Build data p. for calib */
                BuildTail(NO_MORE_DATA, 0) ;    /* Build tail */
                not_cal_data-- ;
            }
            if ( ad_mode & 0x08 ) 
            {           /* temp readings */
                ad_mode &= ~0x0e ;
                ad_mode |= 0x02 ;
                ad_state = START_CALIBRATION ;
            } 
            else if ( ad_mode & 0x04 ) 
            {    /* "other" */
                ad_mode &= ~0x0e ;
                ad_mode |= 0x08 ;
                ad_state = START_CALIBRATION ;
            } 
            else if ( ad_mode & 0x02 ) 
            {            /* pressure */
                //if ( !time_b_cnt ) 
                if ( time_b_cnt==0 ) 
                {
                    ad_mode &= ~0x0e ;
                    ad_mode |= 0x04 ;                   /* convert temp */
                    ad_state = START_CALIBRATION ;
                    time_b_cnt = time_b_temp ;      /* reload counter */
                }
            } 
            else 
                {
                    ad_mode &= ~0x0e ;
                    ad_mode |= 0x04 ;                       /* next pressure */
                }
        }
    }
    if ( tx_complete ) {
        ADConvert() ;                                   /* convert data */
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
	unsigned char tmpSwitch;
    unsigned long msrd_snsdata; 
    unsigned short tmp_cal_data;  
    float cal_val;
    switch ( ad_state ) 
    {
    case    START_NEW_POINT :
        ad_mode &= ~0x01 ;                           /* reset tx check marker */
        ad_timeout_cnt = AD_TIMEOUT ;                   /* timeout ad cnv */
		tmpSwitch = (ch_stat[curr_ad_ch]>> 2) & 0x03;
        //switch ( (ch_stat[curr_ad_ch]>> 2) & 0x03 ) { // OLDCODE
        switch (tmpSwitch ) 
        {
            case 0x03 :              /* pressure */
                if ( ad_mode & 0x02 ) {                       /* pressure readings */
                    SetCalResistance(OHM_1R);
                    SetSupplyChannel(curr_ad_ch) ;
                    SetSupplyCurrent(10) ;  // 10mA   
                    //SetSupplyCurrent(1) ;  // 1mA
                    SetMuxChannel(curr_ad_ch) ;
                    ad_gain = 3 ;
                    spi1_master_tx_rx(ad_gain | 0x10) ; // Next write SetupRegister 
                    // Ad setup data, bipolar
  //                  spi1_master_tx_rx(0x2a) ;//0b00101010  MD1&0:00, CLK=1 FS1&2 01 B/U:0 BUF=1 FSYNC 0
                    // same with clk 1MHz
//                   spi1_master_tx_rx(0b00001010) ; // MD1&0:00, CLK=0 FS1&2 01 B/U:0 BUF=1 FSYNC 0 -01-02-23 
//                   spi1_master_tx_rx(0b00001000) ;   // MD1&0:00, CLK=0 FS1&2 01 B/U:0 BUF=0 FSYNC 0 
                    // give same value. perhaps more stabil
                    spi1_master_tx_rx(0b00011010) ;   // MD1&0: 00 CLK:0,FSx:11, B/U:0 ;BUF:1 FSYNC:0 
                    ad_settling = AD_SET_TIME ;         // wait 67 ms 
                    ad_state = WAIT_FOR_INTERRUPT ;     //    next state 
                } else {
                    ad_state = IDLE ;
                }
                break;
            case 0x02 :               /* "OTHER " */
                if ( ad_mode & 0x04 ) {                       /* other readings */
                    SetCalResistance(OHM_1K);
                    SetSupplyChannel(curr_ad_ch) ;
                    SetSupplyCurrent(1) ;
                    SetMuxChannel(curr_ad_ch) ;
                    ad_gain = 0 ;
                    spi1_master_tx_rx(ad_gain | 0x10) ;            /* Next write data */
                    //spi1_master_tx_rx(0x2a) ;                      /* Ad setup data */  
                    spi1_master_tx_rx(0b00011000) ;       // MD1&0:00, CLK=0 FS1&9 11 B/U:0 BUF=0 FSYNC 0
                    ad_settling = AD_SET_TIME ;          /* wait 67 ms */
                    ad_state = WAIT_FOR_INTERRUPT ;          /* next state */
                } else {
                    ad_state = IDLE ;
                }
                break;
            case 0x01 :               /* temp */
                if ( ad_mode & 0x08 ) {                       /* convert temp? */
                    SetCalResistance(OHM_1K);
                    SetSupplyChannel(curr_ad_ch) ;
                    SetSupplyCurrent(1) ;
                    SetMuxChannel(curr_ad_ch) ;
                    ad_gain = 0 ;
                    spi1_master_tx_rx(ad_gain | 0x10) ;            /* Next write data */
                    // original value, but we have only 1 MHz clock
                    //spi1_master_tx_rx(0x2a) ;                     /* Ad setup data, bipolar*/ 
                    
                    // running test small jump for PT1000 +- 0,2c
                    spi1_master_tx_rx(0b00011000) ;       // MD1&0:00, CLK=0 FS1&0 11 B/U:0 BUF=0 FSYNC 0  
                    
                    // test if better stability with buffer flag on Result: bad a lot of value jump
                    //spi1_master_tx_rx(0b00011010) ;       // MD1&0:00, CLK=0 FS1&0 11 B/U:0 BUF=1 FSYNC 0  
                    
                    // Test if filter FS1&0:01 (original value but with 1MHz
                    // value of ADC is very high not like standard and a lot of jump
                    //spi1_master_tx_rx(0b00001000) ;       // MD1&0:00, CLK=0 FS1&0 11 B/U:0 BUF=0 FSYNC 0  
                    ad_settling = AD_SET_TIME ;          /* wait 67 ms */
                    ad_state = WAIT_FOR_INTERRUPT ;          /* next state */
                } else {
                    ad_state = IDLE ;
                }
                break;
            default :
                ad_state = IDLE ;
                break ;
            }
        break ;
    case    WAIT_FOR_INTERRUPT :
        break ;
    case    CONV_COMPLETE :
        spi1_master_tx_rx(ad_gain | 0x38) ;                   /* Next read data */
        ad_data = spi1_master_tx_rx(0xFF)* 256 ;              /* read data 16 bit data from ad */
        ad_data += spi1_master_tx_rx(0xFF); 
        if ( ad_mode & 0x40 ) {                           /* cal point ? */
            ad_mode &= ~0x40 ;
            SetSupplyCurrent(1) ;
            SetMuxChannel(MUXCHOFF) ;
            SetSupplyChannel(SUPPCHOFF) ;
            SetCalResistance(OFF);
            ad_state = IDLE ;
            ad_timeout_cnt = 0 ;                            /* timeout off */
            //if ( !(ad_mode & 0x01) ) 
            if ( (ad_mode & 0x01)==0 ) 
            {                    /* tx during conv? */
                tmp_cal_data = ad_data - 32767 ;    /* no, use data  */
				cal_data[curr_ad_ch]=tmp_cal_data;
                tmpSwitch = (ch_stat[curr_ad_ch]>> 2) & 0x03;
                switch ( tmpSwitch ) 
                {

                case 0x03 :                /* pressure */
				
				cal_val = tmp_cal_data* cal_gain;
                cal_data[curr_ad_ch] = (short)cal_val ;     /* adjust for resistor errors */      
                    // MAX_PRE_CAL =45000, orginal 35000 /2
                    if ( (tmp_cal_data > MAX_PRE_CAL) ||
                         (tmp_cal_data < MIN_PRE_CAL) ) {
                        ch_stat[curr_ad_ch] |= 0x02 ;         /* Calibration fail */
                    } 
                    else 
                    {
                        ch_stat[curr_ad_ch] &= ~0x02 ;  /* Calibration OK */
                    }
				
                    if ( (tmp_cal_data > FMAX_PRE_CAL)||
                         (tmp_cal_data < FMIN_PRE_CAL) )
					 {
                        ch_stat[curr_ad_ch] |= 0x01 ;       // Reading fail 
                        eep_type[curr_ad_ch >> 1] = 0 ;     // clear read status 
                        mes_data[curr_ad_ch] = 0.0 ;       // ASt mark ?? 
                        raw_data[curr_ad_ch] = curr_sens_data ; // sen raw raw ?  
                        
                        if ( ad_mode & 0x80 ) 
						{               /* test */
                            ch_stat[curr_ad_ch] &= ~0x60 ;  /* no sensor */
                        }
                     } 
					else                  
					 {   
                            if ( ad_mode & 0x80 ) 
                            {               /* test */
                                ch_stat[curr_ad_ch] |= 0x6c ;   /* pr. sensor  OK*/
                            }
                            ch_stat[curr_ad_ch] &= ~0x01 ;  /* Reading OK */  
                            msrd_snsdata= curr_sens_data -cal_zero ;
                                //curr_sens_data -= cal_zero ;
                            msrd_snsdata = msrd_snsdata * 20000;
                            msrd_snsdata = msrd_snsdata / cal_data[curr_ad_ch];
                            // test if raw data==0 and do use max 2 time    
                            if ( ( short)msrd_snsdata ==0 && ZeroCountPress < ZEROCOUNT )
                            {   ZeroCountPress++;
                            }
                            else
                               {    ZeroCountPress=0;
                                    raw_data[curr_ad_ch] = ( short)msrd_snsdata ;
                                    CalcPress(curr_ad_ch) ;             /* calculate pressure */
                               }
                             
                            
                    }
                    
                    break;  
                    
                case 0x02 :                                 /* "other" */
                    break;
                    
                case 0x01 :                                 /* temp */
                    if ( (tmp_cal_data > MAX_TMP_CAL ) ||
                         (tmp_cal_data < MIN_TMP_CAL ) ) {
                        ch_stat[curr_ad_ch] |= 0x02 ;         /* Calibration fail */
                    } 
                    else 
                    {
                        ch_stat[curr_ad_ch] &= ~0x02 ;        /* Calibration OK */
                    }
                    if ( (tmp_cal_data > FMAX_TMP_CAL) ||(tmp_cal_data < FMIN_TMP_CAL) ) 
                    {

                        ch_stat[curr_ad_ch] |= 0x01 ;       /* Reading fail */
                        mes_data[curr_ad_ch] = 0.0 ;         /* ASt mark ?? */
                        raw_data[curr_ad_ch] = curr_sens_data ; /* sen raw raw */
                        if ( ad_mode & 0x80 ) 
                        {               /* test */
                            ch_stat[curr_ad_ch] &= ~0x60 ;  /* no sensor */
                        }
                    } 
                    else 
                    {
                        if ( ad_mode & 0x80 ) {
                            ch_stat[curr_ad_ch] |= 0x24 ;   /* tmp sensor  OK*/
                        }
                        ch_stat[curr_ad_ch] &= ~0x01 ;  /* Reading OK */
//                        msrd_snsdata = (short)(((float)curr_sens_data * 1000.0
//                                                        / (float)cal_data[curr_ad_ch] ) * 10.0); 
                        msrd_snsdata = (short)((float)curr_sens_data * 10000.0
                                                        / (float)cal_data[curr_ad_ch] ); 
                                                        
//                        raw_data[curr_ad_ch] = (short)(((float)curr_sens_data * 1000.0
//                                                        / (float)cal_data[curr_ad_ch] ) * 10.0); 
                                                        
                        if (  (msrd_snsdata ==0) && (ZeroCountTemp < ZEROCOUNT) )
                        {  ZeroCountTemp++;
                        }
                        else
                        {   raw_data[curr_ad_ch]= msrd_snsdata;                            
                            CalcTemp(curr_ad_ch) ;              /* calculate temperature */  
                            ZeroCountTemp=0;
                        }
                    }
                    break;
                default :
                    break ;
                }
            } 
            else 
            {
                curr_ad_ch-- ;                                 // remeasure the chanell if skipped due to UART TX
            }
        } 
        else 
        {                                                /* normal conv enter point */
            curr_sens_data = (short)(ad_data - 32767) ;        /* use ad data */
			tmpSwitch=(ch_stat[curr_ad_ch]>> 2) & 0x03;
//            switch ( (ch_stat[curr_ad_ch]>> 2) & 0x03 ) {
            switch (tmpSwitch)
			 {
            case 0x03 :               /* pressure */
                SetMuxChannel(PRE_CAL_CH) ;         /* cal channel */
                ad_mode |= 0x40 ;                           /* next cal */
                ad_settling = AD_SET_TIME ;         /* wait 67 ms */
                ad_state = WAIT_FOR_INTERRUPT ;         /* wait for cal int */
                UnpackSensData(curr_ad_ch) ;            /* Unpack data */
                break;
            case 0x02 :                /* other */
                SetSupplyCurrent(1) ;                   /* no cal on this */
                SetMuxChannel(MUXCHOFF) ;
                SetSupplyChannel(SUPPCHOFF) ;
                SetCalResistance(OFF);
                ad_state = IDLE ;
                raw_data[curr_ad_ch] = curr_sens_data ;
                cal_data[curr_ad_ch] = 0 ;         /* do no use caldata  */
                ch_stat[curr_ad_ch] &= ~0x03 ;      /* Cal. and readings set to OK */
                ad_timeout_cnt = 0 ;                        /* timeout off */
                if ( ad_mode & 0x80 ) {                   /* test */
                    ch_stat[curr_ad_ch] |= 0x48 ;       /* other sensor  OK*/
                }
                CalcOther(curr_ad_ch) ;                 /* calculate "other" */
                break;
            case 0x01 :               /* temp */
                SetMuxChannel(TMP_CAL_CH) ;         /* cal channel */
                ad_mode |= 0x40 ;                           /* next cal */
                ad_settling = AD_SET_TIME ;         /* wait 67 ms */
                ad_state = WAIT_FOR_INTERRUPT ;         /* wait for cal int */
                break;
            default :
                ad_state = IDLE ;                           /* Start new point */
                break ;
            }
        }
        break ;
    case    START_CALIBRATION :                         // calibrate the AD chip itself
        Led(2, ON) ;                                        /* Led 2 on */
        ad_timeout_cnt = AD_TIMEOUT ;                   /* timeout ad cnv */
        ad_settling = 20 ;                              /* wait >mclock/128  */
        if ( tx_complete == TRUE ) {
            if ( ad_mode & 0x02 ) {                       /* pressure readings */
                ad_gain = 3;
            } else {
                ad_gain = 0;
            }
            ad_state = WAIT_FOR_CAL_INT ;               /* next state */
            spi1_master_tx_rx(ad_gain | 0x10) ;               /* Next write setup reg */
            //spi1_master_tx_rx(0x6a) ;                     /*  Ad setup data, bipolar */   
            if ( ad_gain == 3 ) // measure pressure
            {   //spi1_master_tx_rx(0b01001000) ;   // MD1&0: 01 CLK:0,FSx:01, B/U:0 ;BUF:0 FSYNC:0   
                // with or without buffer almost same, buffer was used in original design , 
                //spi1_master_tx_rx(0b01001010) ;   // MD1&0: 01 CLK:0,FSx:01, B/U:0 ;BUF:1 FSYNC:0 
                // use another filter setup
                spi1_master_tx_rx(0b01011010) ;   // MD1&0: 01 CLK:0,FSx:11, B/U:0 ;BUF:1 FSYNC:0 
                 
                
                // use for read pressure value  
                //spi1_master_tx_rx(0b00001000) ;   // MD1&0:00, CLK=0 FS1&2 01 B/U:0 BUF=0 FSYNC 0 
            }
            else
            {
                spi1_master_tx_rx(0b01011000) ;   // MD1&0: 01 CLK:0,FSx:11, B/U:0 ;BUF:0 FSYNC:0
            }
 
       }
        break ;
    case    WAIT_FOR_CAL_INT :
        break ;
    case    CAL_COMPLETE :
        ad_timeout_cnt = 0 ;                                /* timeout off */
        curr_ad_ch -= 1 ;                                   /* To start with ch 0 !! */
        ad_state = IDLE ;
        Led(2, OFF) ;                                       /* Led 2 off */
        break ;
    case    IDLE :
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
	float temp;
	float temp1, temp2;
    float temp_data ;
	//int selection=0;
	//int localRAW;

    Led(2, ON)  ;                               /* Led 2 on */
//	localRAW=raw_data[ch];
    if ( (sens_data[0]>0) && (raw_data[ch] < sens_data[0]) ) {
        temp_data = CalcPercent((sens_data[1]-sens_data[0]), sens_data[0],raw_data[ch], 0.0) ;
        temp_data *= 40.0 ;             /* caluclate %, using 0-40% cal data*/
//			selection=1;
    } 
    else if ( raw_data[ch] <  sens_data[1] ) {
        temp_data = CalcPercent((sens_data[1]-sens_data[0]), sens_data[0],raw_data[ch], (float)sens_nl1) ;
        temp_data *= 40.0 ;             /* caluclate % */
//		selection=2;
    } 
    else if ( raw_data[ch] < sens_data[2] ) {
        temp_data = CalcPercent((sens_data[2]-sens_data[1]), sens_data[1],raw_data[ch], (float)(sens_nl2 / 3)) ;
        temp_data = temp_data*(60.0 - 40.0)+40.0 ;              /* caluclate % */
//		selection=3;
    } 
    else if ( raw_data[ch] < sens_data[3] ) {
        temp_data = CalcPercent((sens_data[3]-sens_data[2]), sens_data[2],raw_data[ch], (float)sens_nl2 ) ;
        temp_data = temp_data*(100.0 - 60.0)+60.0 ;             /* caluclate % */
//	selection=4;
    } 
    else {
        temp_data = CalcPercent((sens_data[3]-sens_data[2]), sens_data[2],
                                raw_data[ch], 0.0) ;
        temp_data = temp_data*(100.0 - 60.0)+60.0 ;             /* caluclate % */
//		selection=5;
    }
	// conversion from  Millibars to Kilograms Per Square Meter Conversion 1 mbar = 10.197162 kgf/m�
	
//    temp_data *= ((((float)packed_data[ch >> 1][6]/10.0) - (float) packed_data[ch >> 1][5] / 100.0) /100.0 ) * 10.197162;
//    temp_data -= ((float) offset[ch] / 1000.0) ;
//    temp_data *=  gain[ch] ;
//    temp_data += ((float) packed_data[ch >> 1][5] / 100.0)  * 10.197162 ;
	
	//temp_data= temp_data * ((((float)packed_data[ch >> 1][6]/10.0) - (float) packed_data[ch >> 1][5] / 100.0) /100.0 ) ;
	temp=  ((((float)packed_data[ch >> 1][6]/10.0) - (float) packed_data[ch >> 1][5] / 100.0) /100.0 ) ;
	temp1=(float)(packed_data[ch >> 1][6]/10.0);
	temp2=(float) (packed_data[ch >> 1][5] / 100.0);
	temp= (temp1 -temp2)/100;
	
	temp_data= temp_data*temp;
	temp_data = temp_data * 10.197162;
    temp_data =temp_data - ((float) offset[ch] / 1000.0) ;
    temp_data =temp_data *  gain[ch] ;
	temp= ((float) packed_data[ch >> 1][5] / 100.0)  * 10.197162 ;
    temp_data =temp_data + temp;
	
	temp = (temp_data - mes_data[ch])/ ((float)p_filter + 1.0) ;
    mes_data[ch] = mes_data[ch] + temp;
	mes_data[ch]=temp_data;
//	temp = mes_data[ch];
//    if ( (mes_data[ch] > 500.0) || (mes_data[ch] < -50.0) ) {
//        mes_data[ch] = 0.0 ;
//    }
    Led(2, OFF) ;                                   /* Led 2 off */

}

/*************************************************************************
*
*  Calculate percentage for pressure
*
*************************************************************************/
float   CalcPercent( unsigned short span, short low_span, short raw_data,
                     float nl)
{

    float x, yy, fspan, range ;
	float temp;

//    range = (float)raw_data - (float)low_span ;
//    fspan = (float)span ;
	range = raw_data - low_span ;
    fspan = span ;
    x = (float)(range/fspan) ;
    yy = (fspan - fspan*x)*fspan*x*nl/(fspan * fspan / 4.0) ;
	// = fspam *( 1-x) * fspan *x*nl / (Fspan*fspan/4)
	// =(fspan)2 * (1-x)*nl *4 / Fspan2
	// =(1-x)*nl*4 
	temp=(1-x)*nl*4;
	yy=temp;
	
	
    return(range - yy)/fspan ;

}

/*************************************************************************
*
*  Calculate and filter temperature
*
*************************************************************************/
float GetTempFromR(float R)
{     float Tmp;
      const float C0 = -245.19;
      const float C1 = 2.5293;
      const float C2 = -0.066046;
      const float C3 = 4.0422e-3;
      const float C4 = -2.0697e-6;
      const float C5 = -0.025422;
      const float C6 = 1.6883e-3;
      const float C7 = -1.3601e-6;
      Tmp = C0 + R*(C1+R*(C2+R*(C3+C4*R)))/(1+R*(C5+R*(C6+C7*R)));
      return Tmp;
}

void CalcTemp(signed char ch)
{   float temp_data;
//    float old_value;
//    float delta;
    float resist = (float)raw_data[ch] ;
   resist /= 10.0 ;
    if ( resist > 500.0 && resist < 1400) {                              /* Pt 1000 ?*/
        resist /= 10.0 ;                                /* Yes */
    }
    if ( resist > 1500.0 ) {                              /* Pt 2000 ?*/
        resist /= 20.0 ;                                /* Yes */
    }
    temp_data = GetTempFromR(resist); 
    temp_data -= (float) offset[ch] / 10.0 ;
    temp_data *= gain[ch] ;
    mes_data[ch] += (temp_data - mes_data[ch])/ ((float)t_filter + 1.0) ; 
//    old_value = mes_data[ch];
//        old_value += (temp_data - old_value)/ ((float)t_filter + 1.0) ;   
//    delta=old_value - mes_data[ch];
//    if ( delta >0 && delta > 0.35 )
//        mes_data[ch]=old_value;
//    if ( delta <0 && delta < -0.35 )
//        mes_data[ch]=old_value;
//// if |delta| less than 0.35 not change old value                     

    
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
    unsigned int data_low;
    unsigned int data_high;
    
    short knst, d_knst, g1, g2, g3 ;
    float temp_data ;
    unsigned char  temp_byte ;
    signed char c_ch ;

    temp_byte = FindTemp(ch);
    if ( temp_byte >= NOIOCH ) {                 /* no temp. found */
        temp_data = 0 ;                                 /* 25. 0 - 25.0  */
    } else {
        temp_data = mes_data[temp_byte] - 25.0 ;
    }
    temp_data /= 100.0 ;              /* use 1/100 deg C in calc. */

    c_ch = ch >>1 ;                         /* start calculate data for 0 % FRO */
    if ( (eep_type[c_ch] & 0x01) || (eep_type[c_ch] & 0x10) ) { /* OK data */
        knst =  ((short) packed_data[c_ch][8] + packed_data[c_ch][9] * 256) & 0x1fff ;

        if ( knst & 0x1000 ) {                /* negative */
            knst |= 0xe000 ;
        }
        g1 =  ((short) ((packed_data[c_ch][9] >> 5) & 0x07) +
               (packed_data[c_ch][10] * 8) +
               ((packed_data[c_ch][11] & 0x03) * 2048)) & 0x1fff ;
        if ( g1 & 0x1000 ) {                /* negative */
            g1 |= 0xe000 ;
        }
        g2 =  ((short) ((packed_data[c_ch][11] >> 2) & 0x3f) +
               ((packed_data[c_ch][12] & 0x7f)* 64 )) & 0x1fff ;
        if ( g2 & 0x1000 ) {                /* negative */
            g2 |= 0xe000 ;
        }
        g3 =  ((short) ((packed_data[c_ch][12] >> 7) & 0x01) +
               (packed_data[c_ch][13] * 2) +
               ((packed_data[c_ch][14] & 0x0f) * 512)) & 0x1fff ;
        if ( g3 & 0x1000 ) {                /* negative */
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
        if ( g1 & 0x1000 ) {                /* negative */
            g1 |= 0xe000 ;
        }
        g2 =  ((short) ((packed_data[c_ch][17] >> 6) & 0x03) +
               (packed_data[c_ch][18] * 4) +
               ((packed_data[c_ch][19]& 0x07) * 1024)) & 0x1fff ;
        if ( g2 & 0x1000 ) {                /* negative */
            g2 |= 0xe000 ;
        }
        g3 =  ((short) ((packed_data[c_ch][19] >> 3) & 0x1f) +
               (packed_data[c_ch][20] * 32)) & 0x1fff ;
        if ( g3 & 0x1000 ) {                /* negative */
            g3 |= 0xe000 ;
        }
        knst += d_knst;                                 /* remember new value */
        sens_data[1] = CalcSensData(knst*2, g1*2, g2*2, g3*2, temp_data) ;
        /* sens value 40%FRO @ temp */

        /* start calculate data for 60 % FRO */
        d_knst =  ((short) packed_data[c_ch][21] +
                   packed_data[c_ch][22] * 256) & 0x1fff ;

        g1 =  ((short) ((packed_data[c_ch][22] >> 5) & 0x07) +
               (packed_data[c_ch][23] * 8) +
               ((packed_data[c_ch][24] & 0x03) * 2048)) & 0x1fff ;
        if ( g1 & 0x1000 ) {                /* negative */
            g1 |= 0xe000 ;
        }
        g2 =  ((short) ((packed_data[c_ch][24] >> 2) & 0x3f) +
               ((packed_data[c_ch][25] & 0x7f)* 64 )) & 0x1fff ;
        if ( g2 & 0x1000 ) {                /* negative */
            g2 |= 0xe000 ;
        }
        g3 =  ((short)((packed_data[c_ch][25] >> 7) & 0x01) +
               (packed_data[c_ch][26] * 2) +
               ((packed_data[c_ch][27] & 0x0f) * 512)) & 0x1fff ;
        if ( g3 & 0x1000 ) {                /* negative */
            g3 |= 0xe000 ;
        }
        knst += d_knst;                                 /* remember new value */
        sens_data[2] = CalcSensData(knst*2, g1*2, g2*2, g3*2, temp_data) ;
        /* sens value 60%FRO @ temp */

        /* start calculate data for 100 % FRO */
        d_knst = ((short)((packed_data[c_ch][27] >> 4) & 0x0f) +
                  (packed_data[c_ch][28] * 16) +
                  ((packed_data[c_ch][29] & 0x01)) * 4096)& 0x1fff ;

        g1 =  ((short) ((packed_data[c_ch][29] >> 1) & 0x7f) +
               ((packed_data[c_ch][30] & 0x3f) * 128)) & 0x1fff ;
        if ( g1 & 0x1000 ) {                /* negative */
            g1 |= 0xe000 ;
        }
        g2 =  ((short) ((packed_data[c_ch][30] >> 6) & 0x03) +
               (packed_data[c_ch][31] * 4) +
               ((packed_data[c_ch][32]& 0x07) * 1024)) & 0x1fff ;
        if ( g2 & 0x1000 ) {                /* negative */
            g2 |= 0xe000 ;
        }
        g3 =  ((short) ((packed_data[c_ch][32] >> 3) & 0x1f) +
               (packed_data[c_ch][33] * 32)) & 0x1fff ;
        if ( g3 & 0x1000 ) {                /* negative */
            g3 |= 0xe000 ;
        }
        knst += d_knst;                                 /* remember new value */
        sens_data[3] = CalcSensData(knst*2, g1*2, g2*2, g3*2, temp_data) ;
        /* sens value 100%FRO @ temp */

        sens_nl1 = (signed char)((packed_data[c_ch][34] >> 3) & 0x0f) ; /*  NL1 */
        if ( (packed_data[c_ch][34]) & 0x80 ) {
            sens_nl1 |= 0xf0 ;
        }
        sens_nl1 *= 3 ;

        sens_nl2 = (signed char) (packed_data[c_ch][34] & 0x07) ;         /* NL2 */
        if ( (packed_data[c_ch][34]) & 0x04 ) {
            sens_nl2 |= 0xf8 ;
        }
        sens_nl2 *= 3 ;
        
        offset[ch] =  (short) (packed_data[c_ch][35] +(packed_data[c_ch][36] * 256)) ;           /*offset*/ 
        data_low= packed_data[c_ch][37];
        data_high= packed_data[c_ch][38] * 256;        
        gain[ch] =  1.0 + (float)((int)((data_low + data_high))/100000.0) ;  /*gain*/
        //gain[ch] =  1.0 + (float)((packed_data[c_ch][37] + packed_data[c_ch][38] * 256)/100000.0) ;  /*gain*/
        /* 256 can not be 256.0 !!!*/
    } else {
        sens_data[0] =     0 ;                  /* dummy values to prevent */
        sens_data[1] =  4000 ;             /* divide by zero */
        sens_data[2] =  8000 ;
        sens_data[3] = 12000 ;
        sens_nl1 = 0 ;
        sens_nl2 = 0 ;
        offset[ch] =  0 ;                       /*offset*/
        gain[ch] =  1.0 ;                       /* gain */
    }
    if ( (eep_type[7] & 0x01) || (eep_type[7] & 0x10) ) 
	{     /* ok data */
        //cal_zero = (short) packed_data[7][35] + packed_data[7][36] * 256 ;  
        //data_low= packed_data[7][37];
        //data_high= packed_data[7][38] * 256;
		//cal_gain =  1.0 + (float)((int)((data_low + data_high))/100000.0) ; /*gain*/
        //cal_gain =  1.0 + (float)((packed_data[7][37] + packed_data[7][38] * 256)/100000.0) ; /*gain*/
        /* 256 can not be 256.0 !!!*/
		cal_zero = 0 ;
        cal_gain = 1.0 ;
    } 
	else {
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

    return(knst + (g1 * temp) +
           (g2 * temp * temp) +
           (g3 * temp * temp * temp)) ;    /* sens value ?%FRO @ temp */

}

/*************************************************************************
*
*  Find temperature for a channel
*
*************************************************************************/
short FindTemp(signed char ch)
{
//	unsigned char status=0;
    short temp_ch, i ;

    temp_ch = (short) ch + 1 ;
//	status= ch_stat[temp_ch] & 0x01;
	
    if ( ((ch_stat[temp_ch] & 0x0c) == 0x04) &&
         (mes_data[temp_ch] < 150.0) &&                     /* to high or */
         (mes_data[temp_ch] > -80.0) &&                     /* to low temp or */
         ((ch_stat[temp_ch] & 0x01)==0) )
	 {                    /* convertion error */
		 
		 return temp_ch ;
    } 
	else 
	{
//        temp_ch = NOIOCH ;                         /* used if no temp */
        for ( i = 0; i < NOIOCH; i++ )
		 {
            if ( (ch_stat[i] & 0x0c) == 0x04 ) 
			{  /* temp ? */
                if ( (mes_data[i] < 150.0) &&         /* to high or */
                     (mes_data[i] > -80.0) &&     /* to low temp or */
                     ((ch_stat[i] & 0x01)==0) ) 
					 {         /* convertion error */
						temp_ch = i ;
						i = NOIOCH ;                               /* exit */
                }
            }
        }
    }
    return temp_ch ;
    
	
}

/*************************************************************************
*
*  Reset pointer to RX received data on RS485
*
*************************************************************************/
void ResetRxPointer(void) 
{

    rx_indx = 1 ;
    rx_hndx = 0 ;
    rx_start = 0 ;
    rx_buff[0] = 0 ;
    rx_buff[1] = 0 ;
    rx_buff[2] = 0 ;
    rx_state = SYNC ;                   /* error in pack len */
    rx_timeout = OFF ;                 /* timeout on channel */
}

/*************************************************************************
*
* Calculate rx checksum
*
*************************************************************************/
int CalcRxChecksum(void)
{

    int             cnt ;
    unsigned char   csum ;

    csum = 0 ;
    for ( cnt=rx_start ; cnt < (rx_start+rx_packlen-2) ; cnt++ ) {
        csum = crc[csum ^ rx_buff[cnt]] ;
    }
    if ( csum == (rx_buff[rx_start + rx_packlen - 2]) ) {
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
    short     pointer, ndb, more ;

    Led(1, ON) ;
    sendtail = FALSE ;
    more    = TRUE ;
    pointer = 0 ;
    ndb = 2 ;                                           /* point to first command */
    pointer = rx_start;                             /* Point to  command */
    while ( more && (pointer < (rx_packlen + rx_start)) ) {
        pointer = pointer + ndb + 2;                /* Point to  command */
        ndb = rx_buff[pointer+1]    ;               /* Save pointer to next command */
        if ( !CheckAction(pointer) ) {
            more = FALSE ;                              /* terminate while  */
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
//    int   ret_val, cnt, new_sync ;
    int   ret_val ;

    ret_val = FALSE ;
    rx_timeout = RX_TO_TIME ;               /* timeout on channel */
    while ( rx_indx > rx_hndx ) 
    {                     /* more char to check */
        switch ( rx_state ) 
        {                     /* check state */
            case SYNC :
                // all functionallity moved to inerrupt routine for receive
                // on version 10
                break ;
            case HEADER :
                if ( (rx_hndx-rx_start) >= 3 ) 
				{             /* rec. header */
                    rx_packlen = ((rx_buff[rx_start+2] * 256) + rx_buff[rx_start+3] ) ;             /* calc. pack.len */
                    if ( (rx_packlen < ((short) RX_SIZE-rx_hndx)) &&    /* chk. header */
                         (rx_packlen >= MIN_PACK_LEN) &&
                         (rx_buff[rx_start+1] != 0xff) ) 
                    {
                        rx_state = RECEIVE ;                    /* header ok */
                        rx_counter = rx_hndx - rx_start + 1 ;
                    } else 
                    {
                        ResetRxPointer() ;
                    }
                }
                break ;
            case RECEIVE :
                if ( ++rx_counter >= rx_packlen ) {
                    if ( (rx_buff[rx_packlen + rx_start-1]) == ETX ) {
                        if ( CalcRxChecksum() ) 
                        {
                            if ( rx_buff[rx_start + 1] < PC_START_ADDRESS ) 
                            {
                            }
                            if ( (rx_buff[rx_start] == MYADRESS_LOCAL)||
                                 (rx_buff[rx_start] == 0) ) 
                            {        /* don't use address*/
                                ret_val = TRUE ;
                            }
                        } 
                        else 
                        {
                            ResetRxPointer() ;              /* reset pointer */
                        }
                    }
                }
                break ;
            default :
                ResetRxPointer() ;                          /* reset pointer */
                break ;
            }                                                       /* end switch */
            if ( ++rx_hndx >= RX_SIZE ) {                 /* check pointer */
                ResetRxPointer() ;                          /* reset pointer */
        }
    }                                                           /* end while.. */
    return ret_val ;
}

void     ResetADCBySW(void)
{   spi1_master_tx_rx (0xFF);
    spi1_master_tx_rx (0xFF);
    spi1_master_tx_rx (0xFF);
    spi1_master_tx_rx (0xFF);

}
void     ResetADCByHW(void)
{   ADC_CS_LOW; 
    delay_us(50);
    ADC_RST_LOW;
    delay_ms(10);
    ADC_RST_HIGH;
    //ADC_CS_HIGH; 
    delay_us(50); 
}

// UART interrupt
/*************************************************************************
*
*  Transmit interrupt routine  TX0
*
*  This routine is called on transmition on serial line 0 (RS485)
*
****************************************************************************/

// USART0 Transmitter interrupt service routine
interrupt [USART0_DRE_vect] void usart0_tx_isr(void)
{
    if ( tx_indx < tx_bytes )         /* More to send ? */
    {   USART0.TXDATAL = tx_buff[tx_indx++];  
        ad_mode |= 0x01 ; 
    }
    else
    {   delay_ms(2);// ADD TO FINSIH SENDING
        USART0.CTRLA&= ~USART_DREIE_bm; 
        tx_tail = TXTAIL ;            /* driver on for last char */
    }
}
/*************************************************************************
*
*  Receive interrupt routine  RX0
*
*  Char received on serial port 0
*
*************************************************************************/

// USART0 Receiver interrupt service routine
interrupt [USART0_RXC_vect] void usart0_rx_isr(void)
{

    char status, bufch;

    status=USART0.RXDATAH;
    bufch=USART0.RXDATAL;
    if ((status & (USART_FERR_bm | USART_PERR_bm | USART_BUFOVF_bm)) == 0)
    {    if ( tx_complete ) 
        {                      /* ok to receive? */
            switch ( rx_state ) {                     /* check state */
            case SYNC :
                if ( bufch == STX ) 
                {
                    sync_cnt ++ ;               // cont sync
                } 
                else if ( sync_cnt >= 2 ) 
                {
                    sync_cnt = 0 ;              // reset counter
                    rx_state = HEADER ;
                    rx_indx = 0 ;
                    rx_hndx = 0 ;
                    rx_start = rx_hndx ;            /* start after the two STX */
                    rx_buff[rx_indx++] = bufch;
                } 
                else 
                {
                    sync_cnt = 0 ;                  // start over once more
                }
                break;
            default:
                rx_buff[rx_indx++] = bufch;
                break;
            }
            if ( rx_indx >= RX_SIZE ) {           /* check rx pointer */
                ResetRxPointer() ;              // reset pointer
            }
        }
    }
}