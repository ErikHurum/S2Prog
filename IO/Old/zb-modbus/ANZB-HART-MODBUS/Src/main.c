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


OS_STACKPTR int Stack1[80], Stack3[50];                                       /* Task stacks */
OS_TASK     TCB_USART0, TCB_WATCHDOG;                                         /* Task-control-blocks */
OS_RSEMA    UARTSEND;
OS_TIMER    TimerUSART0, TimerUSART0On;


unsigned char ReadSignatureRow(unsigned int addr)	
{
  return (__AddrToZByteToSPMCR_LPM((void __flash*)(addr),(1 <<SPMEN) | (1<<SIGRD)));
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

void main(void)
{
#if 1
  asm("WDR");                             // Enable watchdog here because the OS hang some times during startup
  WDTCSR = 0x1f;
  WDTCSR = 0x0f;
  asm("WDR");                             // kick the dog!!
#endif
 // SPMCSR |= 1 << 5;
  
  int SByte1 = ReadSignatureRow(0); 
  int SByte3 = ReadSignatureRow(2); 
  int SByte5 = ReadSignatureRow(4); 
  
  OS_IncDI();
  OS_InitKern();          /* initialize OS                 */

  OS_InitHW();            /* initialize Hardware for OS    */
  InitSystem();           // init the system according to board

  hart_start();
  
#if USE_MODBUS_PROTOCOL == 0
  OS_CREATERSEMA(&UARTSEND);                          // semaphore for sending on UARTs
  OS_CREATETASK(&TCB_USART0, "USART0", Usart0Handler, 110, Stack1);
  OS_CREATETIMER(&TimerUSART0, TimoutUSART0, 200);                 // Start timeout timer RX on
  OS_CREATETIMER(&TimerUSART0On, TimoutUSART0On, 5);                 // Start on timer TX on
#else
  {
    extern void modbus_rtu_task_init(void);
    
    modbus_rtu_task_init();
  }
#endif

  OS_CREATETASK(&TCB_WATCHDOG, "Watch dog", WatchDogHandler, 50, Stack3);

  OS_Start();                                         // Start multitasking
}
