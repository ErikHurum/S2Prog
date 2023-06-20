/**********************************************************
*  
*   Main file for TPC* program       
*  
***********************************************************/

#include "iom128.h"
#include "stdio.h"
#include "math.h"
#include "variables.h"
#include "version.h"
#include "inavr.h"
#include "string.h"


OS_STACKPTR int Stack0[100], Stack3[60], Stack5[60], Stack10[100], Stack20[75]; /* Task stacks */
OS_TASK     TCB_USART0, TCB_WATCHDOG, TCB_DispCtl, TCB_Blink, TCB_Info;               /* Task-control-blocks */
OS_RSEMA    UARTSEND;
OS_TIMER    TimerUSART0;

/**********************************************************
*
*       main
*
**********************************************************/

void main(void) {

    OS_InitKern();        /* initialize OS                 */
    OS_InitHW();          /* initialize Hardware for OS    */
    InitSystem();           // init the system according to board


    OS_CREATERSEMA(&UARTSEND);                          // semaphore for sending on UARTs
    OS_CREATETASK(&TCB_USART0, "USART0", Usart0Handler, 150, Stack0);
    OS_CREATETIMER(&TimerUSART0, TimoutUSART0, 200);                 // Start timeout timer RX on
    OS_CREATETASK(&TCB_Blink, "Blink", DisplayBlink, 120, Stack5);  // Blink on display
    OS_CREATETASK(&TCB_Info, "Info", Info, 110, Stack20);  // Blink on display

    switch (UnitID) {                                    // Starting taasks for modules:
    case TPC140:                                          // TPC140 
    case TPC196:                                          // TPC196 
        OS_CREATETASK(&TCB_DispCtl, "Display_Control", DisplayHandler, 190, Stack10);
        break;
    }
    OS_CREATETASK(&TCB_WATCHDOG, "Watch dog", WatchDogHandler, 50, Stack3);
    OS_Start();                                         // Start multitasking
}

