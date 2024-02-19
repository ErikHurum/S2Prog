/****************************************************************************************
/  Misc. routines
/
***************************************************************************************/
#include "iom1281.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"
#include "inavr.h"
#include "string.h"


void WDT_off(void)
{
    __disable_interrupt();
    __watchdog_reset();
    /* Clear WDRF in MCUSR */
    MCUSR &= ~(1<<WDRF);
    /* Write logical one to WDCE and WDE */
    /* Keep old prescaler setting to prevent unintentional time-out
    */
    WDTCSR = (1<<WDE) | (1<<WDP2) | (1<<WDP1) | (1<<WDP0);
    /* Turn off WDT */
    WDTCSR = 0x00;
    __enable_interrupt();
}

void WDT_Prescaler_Change(void)
{
    __disable_interrupt();
    __watchdog_reset();
    /* Start timed equence */
    WDTCSR |= (1<<WDCE) | (1<<WDE);
    /* Set new prescaler(time-out) value = 64K cycles (~0.5 s) */
    //WDTCSR = (1<<WDE) | (1<<WDP2) | (1<<WDP0);
    /* Set new prescaler(time-out) value = 256K cycles (~2.0 s) */
    WDTCSR = (1<<WDE) | (1<<WDP2) | (1<<WDP1) | (1<<WDP0);


__enable_interrupt();
}


/*************************************************************************
*   (This is a task)
*  Watchdog handler
*
*************************************************************************/
void WatchDogHandler(void) {

    //OS_Delay(100);                         // wait 1 seconds for other tasks to start and set TaskStatus
    //__watchdog_reset();               //kick the dog
    //WDTCSR = 0x1f;
    //WDTCSR = 0x0f;
    __watchdog_reset();               //kick the dog
    WDT_Prescaler_Change();
    while (1) {
        OS_Delay(500);
        __watchdog_reset();               //kick the dog
    }
}


/*************************************************************************
*
*  Get my address
*
*************************************************************************/
char MyAddress(void) {

#if (OS_UART == 0)
    return 0;                   // Debug only
#else
    return(~(PIND>>4) & 0x0f) ;
#endif
}

/*************************************************************************
*
*  Check for legal float
*
*************************************************************************/
char IsFloat(float A){
  long exp;
	// A NAN has an exponent of 255 (shifted left 23 positions) and
	// Denormalized has an exponent set to 0
	exp = *(long*)&A & 0x7F800000L;
	//int mantissa = *(int*)&A & 0x007FFFFF;
	if ( exp && (exp != 0x7F800000L)  ) {
		return(true);
  }
	return(false);
}
