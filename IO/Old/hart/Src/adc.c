/****************************************************************************************
/ AD converter functions and interrupt
/
***************************************************************************************/

#include "iom1280.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"

#pragma vector=ADC_vect
__interrupt void IntHandler_AD( void ){

    OS_EnterInterrupt();
    OS_EnterIntStack();
    ADInt.Result[ADChannel] = ADC; // Reading ADCL and ADCH in one run
    if (++ADChannel > 0x0f ) {                //set next ADchannel
          ADChannel = 0x0e ;
    }
    ADMUX  &= 0xe0 ;                           // set the channel
    ADMUX  |= ADChannel ;
   // ADCSRB |= 0x40 ;                           //start new convertion
	 //ADCSRA |= 1 << ADATE;
	 TIFR1 = 1;
    OS_LeaveIntStack();
    OS_LeaveInterruptNoSwitch();
}
