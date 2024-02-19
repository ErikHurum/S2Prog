/****************************************************************************************
/  Misc. routines
/
***************************************************************************************/
#include "iom1280.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "externals.h"
#include "version.h"
#include "inavr.h"
#include "string.h"
#include "hart.h"

__no_init int RestartCnt             @0x21FD;
volatile char RestartCmd = 0;


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
#define NUMBER_OF_TASKS 7
void WatchDogHandler(void) {
#if defined( OS_LIBMODE_D) || defined( OS_LIBMODE_S )
    static const char *StackCheck[] = { 
        StackTest1              , StackTest2            , 
        StackTest3              , StackTest4            , 
        StackTest5              , StackTest6            , 
        _hart_task0.StackTest1  , _hart_task0.StackTest2, 
        _hart_task1.StackTest1  , _hart_task1.StackTest2,
        _hart_task2.StackTest1  , _hart_task2.StackTest2 };
#endif
    char HartComCheckTimeCnt = 0;
#ifdef OS_LIBMODE_DP
    char LoadCnt            = 0;
    int RawPerformance[NUMBER_OF_TASKS];
    static OS_TASK *MyTasks[NUMBER_OF_TASKS] = { &_hart_task0.tcb, &_hart_task1.tcb, &_hart_task2.tcb, &TCB_USART0, &TCB_AD7715, &TCB_INT_ADC, &TCB_WATCHDOG };
#endif
    OS_Delay(100);                         // wait 1 seconds for other tasks to start and set TaskStatus
    //asm("WDR");                             // kick the dog!!
    //WDTCSR = 0x1f;
    //WDTCSR = 0x0f;
    //asm("WDR");                             // kick the dog!!
    while (1) {
        OS_Delay(500);
        OS_U32 CurrentTime = OS_Time;
        if (CriticalComError) {
            OS_Error(ZB_ERR_UART);
        } else if (HartComCheckTimeCnt++ >= 10) {
            if (labs(CurrentTime - _hart_task0.LastHartTaskRunTime) > 10000) {
                OS_Error(ZB_ERR_MODEM_0);
            }
            if (labs(CurrentTime - _hart_task1.LastHartTaskRunTime) > 10000) {
                OS_Error(ZB_ERR_MODEM_1);
            }
            if (labs(CurrentTime - _hart_task2.LastHartTaskRunTime) > 10000) {
                OS_Error(ZB_ERR_MODEM_2);
            }
        } else if (labs(CurrentTime - Last_ADC_OK_Time) > 5000) {
            OS_Error(ZB_ERR_EXT_ADC);
        }
        if (!RestartCmd) {
            __watchdog_reset();               //kick the dog
        }
#if defined( OS_LIBMODE_D) || defined( OS_LIBMODE_S )
        char ErrorStack = 0;
        for (char i = 0; i < NELEMENTS(StackCheck); i++) {
            if (memcmp(StackCheck[i], "123456789", 10)) {
                ErrorStack = i + 1;
            }
        }
#endif
#ifdef OS_LIBMODE_DP
        if (LoadCnt++ > 5) {
            OS_STAT_Sample();
            OS_Delay(10);
            int tmpRawLoad = 0;
            for (char i = 0; i < NUMBER_OF_TASKS; i++) {
                RawPerformance[i] = OS_STAT_GetLoad(MyTasks[i]);
                tmpRawLoad       += RawPerformance[i];
            }
        }
#endif
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
    int Address = (~(PINE >> 4) & 0x0f);
    return Address;
    //return(~(PINE>>4) & 0x0f) ;
#endif
}

/*************************************************************************
*
*  Check for legal float
*
*************************************************************************/
char IsFloat(float A) {
    long exp;
    // A NAN has an exponent of 255 (shifted left 23 positions) and
    // Denormalized has an exponent set to 0
    exp = *(long *)&A & 0x7F800000L;
    //int mantissa = *(int*)&A & 0x007FFFFF;
    if (exp && (exp != 0x7F800000L)) {
        return (true);
    }
    return (false);
}

