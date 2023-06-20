/****************************************************************************************
/ AD converter functions and interrupt
/
***************************************************************************************/

#include "iom1280.h"
#include "stdio.h"
#include "externals.h"
#include "version.h"
#include "hart.h"

// Voltage Reference: AVCC pin
#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR))
// Voltage Reference: 2.56V, cap. on AREF
//#define ADC_VREF_TYPE ((1<<REFS1) | (1<<REFS0) | (0<<ADLAR))


// Read the AD conversion result
unsigned read_adc(unsigned char adc_input) {
    ADMUX = (adc_input & 0x1f) | ADC_VREF_TYPE;
    if ( adc_input & 0x20 ) ADCSRB |= (1 << MUX5);
    else ADCSRB &= ~(1 << MUX5);
// Delay needed for the stabilization of the ADC input voltage
    OS_Delayus(10);
    //OS_Delay(1);
// Start the AD conversion
    ADCSRA |= (1 << ADSC);
// Wait for the AD conversion to complete
    while ( (ADCSRA & (1 << ADIF)) == 0 );
    ADCSRA |= (1 << ADIF);
    return ADC; // Reading ADCL and ADCH in one run;
}


/*************************************************************************
*   (This is a task)
*  InternalADCHandler
*
*************************************************************************/
float FileterdADVal = 24.0;  // Initialize to 24V as default
void InternalADCHandler(void) {
	while (1) {
		OS_Delay(1000);
		ADInt.Result[0] = (short)read_adc(38);
	}
}

