/****************************************************************************************
/ AD converter functions and interrupt
/
***************************************************************************************/

#include "iom128a.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"

void OS_ISR_IntHandler_AD( void ){
    ADInt.Result[ADChannel] = ADC; // Reading ADCL and ADCH in one run
    if (++ADChannel > 0x01 ) {                //set next ADchannel
          ADChannel = 0x00 ;
    }
    ADMUX &= 0xe0 ;                           // set the channel
    ADMUX |= ADChannel ;
    ADCSR |= 0x40 ;                           //start new convertion
}
#pragma vector=ADC_vect
__interrupt void Int_AD( void ){
    OS_CallISR(OS_ISR_IntHandler_AD);
}
