/**********************************************************
*  
*   Main file for AN-ZB* program       
*  
***********************************************************/

#include "iom1281.h"
#include "stdio.h"
#include "math.h"
#include "variables.h"
#include "version.h"
#include "inavr.h"
#include "string.h"


OS_STACKPTR int Stack0[160], Stack1[160], Stack3[150], Stack10[200], Stack11[200]; /* Task stacks */
OS_TASK     TCB_USART0, TCB_USART1, TCB_WATCHDOG, TCB_RS485Ctl, TCB_RS485Rec, TCB_AD7715;               /* Task-control-blocks */
OS_RSEMA    UARTSEND;
OS_TIMER    TimerUSART0, TimerUSART1, TimerUART0, TimerUART1, TimerUSART0On, TimerUSART1On;

#if USE_MODBUS_PROTOCOL == 1
OS_RSEMA    adc_lock;
OS_RSEMA    rs485_tx_lock[2];
#endif
/**********************************************************
*
*       main
*
**********************************************************/

void main(void) {
    __watchdog_reset();               //kick the dog
    WDTCSR = 0x1f;
    WDTCSR = 0x0f;
    __watchdog_reset();               //kick the dog

    
    OS_IncDI();
    OS_InitKern();        /* initialize OS                 */
    OS_InitHW();          /* initialize Hardware for OS    */
    InitSystem();           // init the system according to board

#if USE_MODBUS_PROTOCOL == 0
    OS_CREATERSEMA(&UARTSEND);                          // semaphore for sending on UARTs
    OS_CREATETASK(&TCB_USART0, "USART0", Usart0Handler, 110, Stack0);
    OS_CREATETIMER(&TimerUSART0, TimoutUSART0, 200);                 // Start timeout timer RX on
    OS_CREATETIMER(&TimerUSART0On, TimoutUSART0On, 5);                 // Start on timer TX on
    OS_CREATETASK(&TCB_USART1, "USART1", Usart1Handler, 100, Stack1);
    OS_CREATETIMER(&TimerUSART1, TimoutUSART1, 200);                 // Start timeout timer RX on
    OS_CREATETIMER(&TimerUSART1On, TimoutUSART1On, 5);                 // Start on timer TX on
#else
    OS_CREATERSEMA(&UARTSEND); // semaphore for sending on UARTs
    OS_CREATERSEMA(&adc_lock); // semaphore for sending on UARTs

    OS_CREATERSEMA(&rs485_tx_lock[0]);
    OS_CREATERSEMA(&rs485_tx_lock[1]);

    {
      extern void modbus_rtu_task_init(void);

      modbus_rtu_task_init();
    }
#endif

    switch (UnitID) {                                    // Starting taasks for modules:
    case 0x00:                                          // AN-ZB485 
      
        OS_CREATETASK(&TCB_RS485Ctl, "ExtRS485_Control", ExtRS485Ctl, 80, Stack10);
        OS_CREATETIMER(&TimerUART0, TimoutUART0, 200);                 // Start timeout timer RX on
        OS_CREATETASK(&TCB_RS485Rec, "ExtRS485_Receive", ExtRS485Rec, 90, Stack11);
        OS_CREATETIMER(&TimerUART1, TimoutUART1, 200);                 // Start timeout timer RX on
#if USE_16552_DRIVER_TASK == 1
        {
          extern void _16552_driver_task_init(void);

          _16552_driver_task_init();
        }
#endif
        break;
    case 0x01:                                          // AN-ZBANA 
        OS_CREATETASK(&TCB_AD7715, "AD7715", AD7715,  90, Stack10);
        break;
    }

    OS_CREATETASK(&TCB_WATCHDOG, "Watch dog", WatchDogHandler, 50, Stack3);
    OS_Start();                                         // Start multitasking
}
