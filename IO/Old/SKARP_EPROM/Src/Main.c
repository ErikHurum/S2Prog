/**********************************************************
*
*   Main file for AN-ZB* program
*
***********************************************************/

#include "iom128.h"
#include "stdio.h"
#include "math.h"
#include "variables.h"
#include "version.h"
#include "inavr.h"
#include "string.h"


OS_STACKPTR int Stack0[90], Stack1[90], Stack3[50], Stack10[110], Stack11[110]; /* Task stacks */
OS_TASK     TCB_USART0, TCB_USART1, TCB_WATCHDOG, TCB_RS485Ctl, TCB_RS485Rec, TCB_AD7715;               /* Task-control-blocks */
OS_RSEMA    UARTSEND;
OS_TIMER    TimerUSART0, TimerUSART1, TimerUART0, TimerUART1;

/**********************************************************
*
*       main
*
**********************************************************/

void main(void) {

    asm("WDR");                             // Enable watchdog here because the OS hang some times during startup
    WDTCR = 0x1f;
    WDTCR = 0x0f;
    asm("WDR");                             // kick the dog!!

    OS_InitKern();        /* initialize OS                 */
    OS_InitHW();          /* initialize Hardware for OS    */
    InitSystem();           // init the system according to board


    OS_CREATERSEMA(&UARTSEND);                          // semaphore for sending on UARTs
    OS_CREATETASK(&TCB_USART0, "USART0", Usart0Handler, 110, Stack0);
    OS_CREATETIMER(&TimerUSART0, TimoutUSART0, 200);                 // Start timeout timer RX on
    OS_CREATETASK(&TCB_USART1, "USART1", Usart1Handler, 100, Stack1);
    OS_CREATETIMER(&TimerUSART1, TimoutUSART1, 200);                 // Start timeout timer RX on

    switch (UnitID) {                                    // Starting taasks for modules:
    case 0x00:                                          // AN-ZB485
        OS_CREATETASK(&TCB_RS485Ctl, "ExtRS485_Control", ExtRS485Ctl, 80, Stack10);
        OS_CREATETIMER(&TimerUART0, TimoutUART0, 200);                 // Start timeout timer RX on
        OS_CREATETASK(&TCB_RS485Rec, "ExtRS485_Receive", ExtRS485Rec, 90, Stack11);
        OS_CREATETIMER(&TimerUART1, TimoutUART1, 200);                 // Start timeout timer RX on
        break;
    case 0x01:                                          // AN-ZBANA
    //    OS_CREATETASK(&TCB_AD7715, "AD7715", AD7715,  90, Stack10);
        break;
    }
    OS_CREATETASK(&TCB_WATCHDOG, "Watch dog", WatchDogHandler, 50, Stack3);
    OS_Start();                                         // Start multitasking
}
