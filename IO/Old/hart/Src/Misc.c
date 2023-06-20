/****************************************************************************************
/  Misc. routines
/
***************************************************************************************/
#include "iom1280.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"
#include "inavr.h"
#include "string.h"
#include "hart.h"


/*************************************************************************
*   (This is a task)
*  Watchdog handler
*
*************************************************************************/
void WatchDogHandler(void) {
    int HarComCheckTimeCnt = 0;
    OS_Delay(100);                         // wait 1 seconds for other tasks to start and set TaskStatus
    asm("WDR");                             // kick the dog!!
    WDTCSR = 0x1f;
    WDTCSR = 0x0f;
    asm("WDR");                             // kick the dog!!
    while (1) {
        char Restart = false;
        OS_Delay(500);
        if ( HarComCheckTimeCnt>=10 ) {
            if ( labs(OS_Time - _hart_task0.LastHartTaskRunTime) > 10000 ) Restart  = true;
            if ( labs(OS_Time - _hart_task1.LastHartTaskRunTime) > 10000 ) Restart |= true;
            if ( labs(OS_Time - _hart_task2.LastHartTaskRunTime) > 10000 ) Restart |= true;
        }
        if ( Restart ) {
            OS_Delay(15000);
        } else {
            __watchdog_reset();               //kick the dog
        }
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
    int Address = (~(PINE>>4) & 0x0f) ;
    return Address;
    //return(~(PINE>>4) & 0x0f) ;
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

