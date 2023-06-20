/****************************************************************************************
/ AD converter functions and interrupt
/
***************************************************************************************/

#include "iom128.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"

#pragma vector=ADC_vect
__interrupt void IntHandler_AD( void ){   

    OS_EnterInterrupt();
    OS_EnterIntStack();
    ADInt.Result[ADChannel] = (ADCL + ADCH *256) ;
//    if (++ADChannel > 0x03 ) {                //set next ADchannel
    //      ADChannel = 0x00 ;            
    //}
    //   ADMUX &= 0xe0 ;                           // set the channel
    // ADMUX |= ADChannel ;
    ADCSR |= 0x40 ;                           //start new convertion
    OS_LeaveIntStack();
    OS_LeaveInterrupt();
}
