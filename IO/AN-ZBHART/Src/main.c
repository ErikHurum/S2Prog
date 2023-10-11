/**********************************************************
*  
*   Main file for AN-ZB* program       
*  
***********************************************************/

#include "iom1280.h"
#include "stdio.h"
#include "math.h"
#include "variables.h"
#include "version.h"
#include "inavr.h"
#include "string.h"
#include <intrinsics.h>
#include "hart.h"
#include "hart_diag.h"

extern void InternalADCHandler(void);
extern void WDT_off(void);
extern void WDT_Prescaler_Change(void);
__no_init int RestartCnt             @0x21FD;


/* Task stacks */
#if defined( OS_LIBMODE_D) || defined( OS_LIBMODE_S )
char StackTest1[] = { "123456789" };
#endif
OS_STACKPTR int Stack1[175];
#if defined( OS_LIBMODE_D) || defined( OS_LIBMODE_S )
char StackTest2[] = { "123456789" };
#endif
OS_STACKPTR int Stack2[100];
#if defined( OS_LIBMODE_D) || defined( OS_LIBMODE_S )
char StackTest3[] = { "123456789" };
#endif
OS_STACKPTR int Stack3[150];
#if defined( OS_LIBMODE_D) || defined( OS_LIBMODE_S )
char StackTest4[] = { "123456789" };
#endif
/* Task-control-blocks */
OS_TASK TCB_USART0;
OS_TASK TCB_WATCHDOG;
OS_TASK TCB_INT_ADC;


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

void main(void) {
    WDT_off();
    RestartCnt++;

    int SByte1 = ReadSignatureRow(0);
    int SByte3 = ReadSignatureRow(2);
    int SByte5 = ReadSignatureRow(4);
    OS_InitKern();          /* initialize OS                 */
    OS_InitHW();            /* initialize Hardware for OS    */
    InitSystem();           // init the system according to board


    memset(&TData, sizeof(TData), 0);
    hart_diag_task_start();
    hart_start();

    OS_CreateMB(&My485UART.RxMailBox, 1, MBUF_SIZE, My485UART.MailBuf);

    OS_CREATETASK(&TCB_USART0, "UART0", Usart0Handler, 130, Stack1);
    OS_CREATETASK(&TCB_WATCHDOG, "Watch dog", WatchDogHandler,  50, Stack3);
    OS_CREATETASK(&TCB_INT_ADC, "Internal ADC ", InternalADCHandler,  60, Stack2);
    WDT_Prescaler_Change();
    OS_Start();                            // Start multitasking
    OS_Delay(100);
    My_ClrBit(PORTE, 0x04);                   // TXE0 off

}
