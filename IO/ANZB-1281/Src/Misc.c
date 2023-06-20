/****************************************************************************************
/  Misc. routines
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
#include "inavr.h"
#include "string.h"

/*************************************************************************
*   (This is a task)
*  Watchdog handler
*
*************************************************************************/
void WatchDogHandler(void) {

    OS_Delay(100);                         // wait 1 seconds for other tasks to start and set TaskStatus
    asm("WDR");                             // kick the dog!!
    WDTCR = 0x1f;
    WDTCR = 0x0f;
    asm("WDR");                             // kick the dog!!
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