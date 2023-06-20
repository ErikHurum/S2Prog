/*******************************************************

*
*     Program for signal convertion card, AN-SGCNV
*
*     Company: ARISTON Norway as
*
*     Author: Thierry Pottier
*
*    * @file     DS2430A.h
	 * @brief    EEprom Header File
	 * @version  V0.00
	 * @date     18. October 2022
     * @note
*

*******************************************************/
#ifndef _DS2430A_INCLUDED_
#define _DS2430A_INCLUDED_

// define IO for HW
//only for HW with one pin for OUT and one for input
#define ONEWIRE_CLR     SETBIT( PORTF.OUT,1);   // turn on the mosfet and set data line low
#define ONEWIRE_SET     CLRBIT( PORTF.OUT,1);   // turn off mosfet and release data line to pullup
#define ONEWIRE_READ    TSTBIT (PORTF.IN,0)    // Read data line with external pull-up

// timing
//#define ONEWRIRE_RESET  960     // time us min 480 to 960us max
#define ONEWRIRE_RESET  600     // time us min 480 to 640us max DS2431
#define ONEWIRE_MSR     60      // mini Presence Detect SampleTime

// bit transmition 
// one bit = 65us min
// Time line low for "1" = 1us min 15us max
// mosfet + 1K pull-up
#define TW1_LOW  5
#define TW1_SLOT   60  // 65us min

#define TW0_LOW  60
#define TW0_SLOT   5  // 65us min

// read data
#define TW_RL     2  // max 15us
#define TW_MSR     15 // total TW_RL& TW_MSR 15um max 
#define TWR_SLOT   55  // 65us min
 

char ResetONEWIRE (void);
void    WriteTo_1Wire ( unsigned char data );
char    Read_1Wire (void);
#endif
