/****************************************************************************************
/ AD converter functions and interrupt
/
***************************************************************************************/

#ifdef __ATMEGA_1280__
#include	"iom1280.h"
#endif

#ifdef __ATMEGA_1281__
#include	"iom1281.h"
#endif
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"

#pragma vector=ADC_vect
__interrupt void IntHandler_AD( void ){

    OS_EnterInterrupt();
    OS_EnterIntStack();
    ADInt.Result[ADChannel] = ADC; // Reading ADCL and ADCH in one run
    if (++ADChannel > 0x01 ) {                //set next ADchannel
          ADChannel = 0x00 ;
    }
    ADMUX &= 0xe0 ;                           // set the channel
    ADMUX |= ADChannel ;
    ADCSR |= 0x40 ;                           //start new convertion
    OS_LeaveIntStack();
    OS_LeaveInterruptNoSwitch();
}
