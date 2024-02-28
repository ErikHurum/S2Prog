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
__no_init int  RestartCnt            @0x21FD;
__no_init char BootloaderRevision    @0x21FF;



OS_STACKPTR int Stack3[300], Stack10[300], Stack11[300]; /* Task stacks */

OS_TASK     TCB_WATCHDOG, TCB_RS485Ctl, TCB_RS485Rec, TCB_AD7715;               /* Task-control-blocks */
OS_RSEMA    UARTSEND;
#if USE_1281_RX_INT_TASK == 0
OS_STACKPTR int Stack0[200], Stack1[200];
OS_TIMER    TimerUSART0, TimerUSART1;
OS_TASK     TCB_USART0, TCB_USART1;
#endif
OS_TIMER    TimerUART0, TimerUART1, TimerUSART0On, TimerUSART1On;

#if USE_MODBUS_PROTOCOL == 1
OS_RSEMA    adc_lock;
OS_RSEMA    rs485_tx_lock[2];
#endif

unsigned char ReadSignatureRow(unsigned int addr)	{
    return (__AddrToZByteToSPMCR_LPM((void __flash *)(addr), (1 << SPMEN) | (1 << SIGRD)));
}


/**********************************************************
*
*       main
*  
* CPU signatures:
* ATmega128 : 0x1E, 0x97, 0x03
* ATmega1280: 0x1E, 0x97, 0x02
* 0x1E=Manufactured by Atmel
* 0x97= Indicates 128Kbyte Flash memory
* Last digit is type of device.
* 
**********************************************************/

/**********************************************************
*
*       main
*
**********************************************************/
// 0x1970403F for 1281
void main(void) {
    int SByte1 = ReadSignatureRow(0);
    int SByte3 = ReadSignatureRow(2);
    int SByte5 = ReadSignatureRow(4);

    __watchdog_reset();               //kick the dog
    WDT_Prescaler_Change();

    RestartCnt++;

    
    //OS_IncDI();
    OS_InitKern();        /* initialize OS                 */
    OS_InitHW();          /* initialize Hardware for OS    */
    InitSystem();           // init the system according to board
    //WDT_Prescaler_Change();
#if USE_MODBUS_PROTOCOL == 0
    OS_CREATERSEMA(&UARTSEND);                          // semaphore for sending on UARTs
    // Create timers before tasks
#if USE_1281_RX_INT_TASK == 1
//    OS_CREATETIMER(&TimerUSART0, TimoutUSART0, 200);                 // Start timeout timer RX on
//    OS_CREATETIMER(&TimerUSART1, TimoutUSART1, 200);                 // Start timeout timer RX on
#endif
    OS_CREATETIMER(&TimerUSART0On, TimoutUSART0On, 5);                 // Start on timer TX on
    OS_CREATETIMER(&TimerUSART1On, TimoutUSART1On, 5);                 // Start on timer TX on

#if USE_1281_RX_INT_TASK == 1
        {
          extern void ATMega1281_driver_task_init(void);
          ATMega1281_driver_task_init();
        }
#else
// Start UART tasks
    OS_CREATETASK(&TCB_USART0, "USART0", Usart0Handler, 110, Stack0);
    OS_CREATETASK(&TCB_USART1, "USART1", Usart1Handler, 100, Stack1);
#endif
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
      
        OS_CREATETASK(&TCB_RS485Ctl    , "ExtRS485_Control" , ExtRS485Ctl, 80, Stack10);
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

    //OS_CREATETASK(&TCB_WATCHDOG, "Watch dog", WatchDogHandler, 50, Stack3);
    OS_Start();                                         // Start multitasking
}
