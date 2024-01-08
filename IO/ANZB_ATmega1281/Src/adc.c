/****************************************************************************************
/ AD converter functions and interrupt
/
***************************************************************************************/

#include "iom1281.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"
#pragma diag_suppress=Pa082

void Int_Handler_AD( void ){
    //
    //  volatile undefined behavior
    // ADInt.Result[ADChannel] = ADC; // Reading ADCL and ADCH in one run
    //
    ADInt.Result[ADChannel] = ADC; // Reading ADCL and ADCH in one run
    if (++ADChannel > 0x01 ) {                //set next ADchannel
          ADChannel = 0x00 ;
    }
    ADMUX &= 0xe0 ;                           // set the channel
    // volatile undefined behavior
    // ADMUX |= ADChannel;
    //
    ADMUX |= ADChannel;
    // 128 -> 1281
    ADCSRA |= 0x40 ;                           //start new convertion
}


#pragma vector=ADC_vect
__interrupt void IntHandler_AD( void ){
    OS_CallISR(Int_Handler_AD);
}

