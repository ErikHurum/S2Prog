/****************************************************************************************
/ AD converter functions and interrupt
/
***************************************************************************************/

#include "iom1281.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"

#pragma vector=ADC_vect
__interrupt void IntHandler_AD( void ){
    short temp;

    OS_EnterInterrupt();
    OS_EnterIntStack();

    //
    //  volatile undefined behavior
    // ADInt.Result[ADChannel] = ADC; // Reading ADCL and ADCH in one run
    //
    temp = ADC;
    ADInt.Result[ADChannel] = temp; // Reading ADCL and ADCH in one run
    if (++ADChannel > 0x01 ) {                //set next ADchannel
          ADChannel = 0x00 ;
    }
    ADMUX &= 0xe0 ;                           // set the channel
    // volatile undefined behavior
    // ADMUX |= ADChannel;
    //
    temp = ADChannel;
    ADMUX |= temp;
    // 128 -> 1281
    ADCSRA |= 0x40 ;                           //start new convertion
    OS_LeaveIntStack();
    OS_LeaveInterruptNoSwitch();
}
