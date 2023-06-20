/*********************************************************************
*               SEGGER MICROCONTROLLER GmbH & Co KG                  *
*       Solutions for real time microcontroller applications         *
**********************************************************************
*                                                                    *
*       (c) 1995 - 2008  SEGGER Microcontroller GmbH & Co KG         *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       embOS * Real time operating system for microcontrollers      *
*                                                                    *
*                                                                    *
*       Please note:                                                 *
*                                                                    *
*       Knowledge of this file may under no circumstances            *
*       be used to write a similar product or a real-time            *
*       operating system for in-house use.                           *
*                                                                    *
*       Thank you for your fairness !                                *
*                                                                    *
**********************************************************************
*                                                                    *
*       embOS version: 3.60d                                         *
*                                                                    *
**********************************************************************

----------------------------------------------------------------------
File    : RTOSInit.c   (for OKI ML6200 CPU and ADS compiler)
Purpose : Initializes and handles the hardware for the OS as far
          as required by the OS.
          Feel free to modify this file acc. to your
          target system.
--------  END-OF-HEADER  ---------------------------------------------
*/

#include "RTOS.H"
#include "JLINKDCC.h"

/*********************************************************************
*
*       Configuration
*
**********************************************************************
*/

#define ALLOW_NESTED_INTERRUPTS 0   // Caution: Nesting interrupts will cause higher stack load on system stack CSTACK

/*********************************************************************
*
*       Clock frequency settings
*/

#ifndef   OS_FSYS
  #define OS_FSYS 60000000uL
#endif

#ifndef   OS_PCLK_TIMER
  #define OS_PCLK_TIMER (7500000ul / 16)  /* fixed for System timer */
#endif

#ifndef   OS_PCLK_UART
  #define OS_PCLK_UART  (OS_FSYS / 2)
#endif

#ifndef   OS_TICK_FREQ
  #define OS_TICK_FREQ 1000
#endif

/*********************************************************************
*
*       UART settings for OSView
*       If you do not want (or can not due to hardware limitations)
*       to dedicate a UART to OSView, please define it to be -1
*       Currently the standard code enables UART 0 per default
*       and supports UART0 only
*/
#ifndef   OS_UART
  #define OS_UART 0
#endif

#ifndef   OS_BAUDRATE
  #define OS_BAUDRATE 38400
#endif

/****** End of configuration settings *******************************/

#define OS_UART_USED (OS_UART == 0)

/************************************** *******************************
*
*       Local defines (sfrs used in RTOSInit.c)
*
**********************************************************************
*/

// Interrupt Controller

#ifndef   NUM_INT_SOURCES
  #define NUM_INT_SOURCES   64
#endif

#define _INT_CHANNEL_MASK  0x1F
#define _INT_PRIORITY_MASK 0x07

#ifndef   OS_IGNORE_UNDEFINED_INTERRUPT
  #define OS_IGNORE_UNDEFINED_INTERRUPT 0
#endif

#define __IRC_IRN    *(volatile OS_U32*)0x78000014
#define __IRC_ILC0   *(volatile OS_U32*)0x78000020
#define __IRC_ILC1   *(volatile OS_U32*)0x78000024
#define __IRC_CICL   *(volatile OS_U32*)0x78000028

#define __IRC_EXILCA_ADDR 0x7BF00018
#define __IRC_EXILCB_ADDR 0x7BF00028
#define __IRC_EXILCC_ADDR 0x7BF00038
#define __IRC_EXILCA *(volatile OS_U32*)__IRC_EXILCA_ADDR
#define __IRC_EXILCB *(volatile OS_U32*)__IRC_EXILCB_ADDR
#define __IRC_EXILCC *(volatile OS_U32*)__IRC_EXILCC_ADDR

#define __SC_BASE_ADDR    *(volatile OS_U32*)(0xB8002000) /* base address */
#define __SIOBUF     *(volatile OS_U32*)(0xB8002000) /* transmiting/receiving buffer register (RW,16,0x0000) */
#define __SIOSTA     *(volatile OS_U32*)(0xB8002004) /* SIO status register (RW,16,0x0000) */
#define __SIOCON     *(volatile OS_U32*)(0xB8002008) /* SIO control register (RW,16,0x0000) */
#define __SIOBCN     *(volatile OS_U32*)(0xB800200C) /* baud rate control register (RW,16,0x0000) */
#define __SIOBT      *(volatile OS_U32*)(0xB8002014) /* baud rate timer register (RW,16,0x0000) */
#define __SIOTCN     *(volatile OS_U32*)(0xB8002018) /* SIO test control register (RW,16,0x0000) */

// Serial Port

/* bit field of SIOBCN register */
#define SIOBCN_BGRUN     (0x0010)       /* count start */

/* bit field of SIOCON register */
#define _SIOCON_LN7      (0x0001)       /* data length : 7bit */
#define _SIOCON_LN8      (0x0000)       /* data length : 8bit */
#define _SIOCON_PEN      (0x0002)       /* parity enabled */
#define _SIOCON_PDIS     (0x0000)       /* parity disabled */
#define _SIOCON_EVN      (0x0004)       /* even parity */
#define _SIOCON_ODD      (0x0000)       /* odd parity */
#define _SIOCON_TSTB1    (0x0008)       /* stop bit : 1 */
#define _SIOCON_TSTB2    (0x0000)       /* stop bit : 2 */

/* bit definitions of SIOSTA register */
#define _SIOSTA_FERR_BIT   (0)          /* framing error */
#define _SIOSTA_OERR_BIT   (1)          /* overrun error */
#define _SIOSTA_PERR_BIT   (2)          /* parity error */
#define _SIOSTA_RVIRQ_BIT  (4)          /* receive ready */
#define _SIOSTA_TRIRQ_BIT  (5)          /* transmit ready */

/* bit masks for SIOSTA register bits */
#define _SIOSTA_FERR_MASK  (1 << _SIOSTA_FERR_BIT)  /* framing error */
#define _SIOSTA_OERR_MASK  (1 << _SIOSTA_OERR_BIT)  /* overrun error */
#define _SIOSTA_PERR_MASK  (1 << _SIOSTA_PERR_BIT)  /* parity error */
#define _SIOSTA_RVIRQ_MASK (1 << _SIOSTA_RVIRQ_BIT) /* receive ready */
#define _SIOSTA_TRIRQ_MASK (1 << _SIOSTA_TRIRQ_BIT) /* transmit ready */

#define _SIOSTA_ERR_MASK   (_SIOSTA_FERR_MASK | _SIOSTA_OERR_MASK | _SIOSTA_PERR_MASK)
#define _OS_UART_PRIO      (0x01)       /* lowest priority for OS UART */

// System Timer

#define __OS_TIM_BASE_ADDR  *(volatile OS_U32*)0xB8001000
#define __OS_TIM_TMEN  *(volatile OS_U32*)0xB8001004
#define __OS_TIM_TMRLR *(volatile OS_U32*)0xB8001008
#define __OS_TIM_TMOVF *(volatile OS_U32*)0xB8001010

#define __OS_TIM_TMVAL *(volatile OS_U32*)0xB800100C /* NOT SURE IF THIS IS CORRECT ADDRESS */

// GPIO Control
#define __PIOCTL  *(volatile OS_U32*)0x80000008
#define CNFIG_UNLOCK    0x0000003c

#define _TIMER_INT_BIT_NO   0
#define _OS_UART_INT_ID     10

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static OS_ISR_HANDLER* _apOS_ISRHandler[NUM_INT_SOURCES];

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/

/*********************************************************************
*
*       OS_Tick interrupt Handler
*/
static void _OS_ISR_Tick(void) {
  if (__OS_TIM_TMOVF &= (1 << _TIMER_INT_BIT_NO)) { // System timer interrupt pending?
    __OS_TIM_TMOVF   &= (1 << _TIMER_INT_BIT_NO);   // Clear OS timer interrupt flag
    OS_HandleTick();                                // Call OS tick handler
#if DEBUG
    DCC_Process();
#endif
  }
}

/*********************************************************************
*
*       _OS_ISR_Undefined
*
*       Is called when an uninstalled interrupt was detected
*       As interrupt pending condition of peripherals has to be reset,
*       program will not continue when interrupt is ignored.
*/
static void _OS_ISR_Undefined(int Index) {
  #if (OS_IGNORE_UNDEFINED_INTERRUPT == 0)
    volatile OS_U32 Dummy;

    Dummy = Index;
    /* You may set a breakpoint here to detect undefined interrupts */
    while (Dummy < (_INT_CHANNEL_MASK + 1)) {
    }
  #endif
}

/*********************************************************************
*
*       _ISRSetPrio
*/
static int _ISRSetPrio(int ISRIndex, int Prio) {
  int  OldPrio;
  int  IsrPrio;
  int* pICR_Reg;

#if DEBUG
  if ((unsigned)ISRIndex >= NUM_INT_SOURCES) {
    OS_Error(OS_ERR_ISR_INDEX);
    return 0;
  }
#endif

  Prio &= _INT_PRIORITY_MASK;
  OS_DI();
  if (ISRIndex < 8) {
    OldPrio = __IRC_ILC0;
    if (ISRIndex < 1) {
      IsrPrio = (OldPrio & ~_INT_PRIORITY_MASK) | Prio;
    } else if (ISRIndex < 4) {
      IsrPrio = (OldPrio & ~(_INT_PRIORITY_MASK << 4)) | (Prio << 4);
      OldPrio >>= 4;
    } else if (ISRIndex < 6) {
      OldPrio = __IRC_ILC0;
      IsrPrio = (OldPrio & ~(_INT_PRIORITY_MASK << 16)) | (Prio << 16);
      OldPrio >>= 16;
    } else {
      IsrPrio = (OldPrio & ~(_INT_PRIORITY_MASK << 24)) | (Prio << 24);
      OldPrio >>= 24;
    }
    __IRC_ILC0 = IsrPrio;
  } else if (ISRIndex < 16) {
    ISRIndex  -= 8;
    IsrPrio    = __IRC_ILC1;
    OldPrio    = (IsrPrio >> (ISRIndex << 2)) & _INT_PRIORITY_MASK;
    IsrPrio    = IsrPrio & ~(_INT_PRIORITY_MASK << (ISRIndex << 2));
    IsrPrio   |= (Prio << (ISRIndex << 2));
    __IRC_ILC1 = IsrPrio;
  } else {
    if (ISRIndex < 32) {
      pICR_Reg  = (int*)__IRC_EXILCA_ADDR;
      ISRIndex -= 16;
    } else if (ISRIndex < 48) {
      pICR_Reg  = (int*)__IRC_EXILCB_ADDR;
      ISRIndex -= 32;
    } else if (ISRIndex < 64) {
      pICR_Reg  = (int*)__IRC_EXILCC_ADDR;
      ISRIndex -= 48;
    }
    ISRIndex >>= 1;  // odd and even isr numbers share the same control register entry
    IsrPrio   = *pICR_Reg;
    OldPrio   = (IsrPrio >> (ISRIndex << 2)) & _INT_PRIORITY_MASK;
    IsrPrio   = IsrPrio & ~(_INT_PRIORITY_MASK << (ISRIndex << 2));
    IsrPrio  |= (Prio << (ISRIndex << 2));
    *pICR_Reg = IsrPrio;
  }
  OS_RestoreI();
  return OldPrio & _INT_PRIORITY_MASK;
}

#if OS_UART_USED
/*********************************************************************
*
*       OS_COM_ISR() OS USART interrupt handler
*       handles both, Rx and Tx interrupt
*/
static void _OS_COM_ISR(void) {
  unsigned int  State;

  State = __SIOSTA;
  if (State & _SIOSTA_RVIRQ_MASK) {   /* reception interrupt ? */
    __SIOSTA = _SIOSTA_RVIRQ_MASK;    /* Clear Interrupt pendig condition */
    OS_OnRx(__SIOBUF);                /* Process actual byte  */
  }
  if(State & _SIOSTA_ERR_MASK) {      /* Any reception error occured? */
    __SIOSTA = _SIOSTA_ERR_MASK;      /* clear error status */
  }
  if(State & _SIOSTA_TRIRQ_MASK) {    /* Tx interrupt pending ? */
    __SIOSTA = _SIOSTA_TRIRQ_MASK;    /* clear TRIRQ flag before processing data */
    if (OS_OnTx()) {                  /* No more characters to send ? */
    }
  }
}
#endif

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

/*********************************************************************
*
*       OS_InitHW()
*
*       Initialize the hardware (timer) required for the OS to run.
*       May be modified, if an other timer should be used
*/
#define _OS_TIMER_INT_ID _TIMER_INT_BIT_NO // Assign to System Timer global interrupt
#define _OS_TIMER_PRIO   1                 // lowest priority
#define _TMRLR_VALUE     (65536 - (OS_PCLK_TIMER/OS_TICK_FREQ))

void OS_InitHW(void) {
  OS_DI();
  // Initialize timer for OS, we use system timer
  __OS_TIM_TMEN  = 0;                      // Stop timer, reset mode
  __OS_TIM_TMRLR = 0;                      // Clear the reload value
  __OS_TIM_TMOVF = 1;                      // Clear the overflow bit
  __OS_TIM_TMRLR = _TMRLR_VALUE;           // Setup reload register
  __OS_TIM_TMEN  = 1;                      // Start timer
  // Install interrupt handler for OS timer
  OS_ARM_InstallISRHandler(_OS_TIMER_INT_ID, &_OS_ISR_Tick); // Timer/counter interrupt vector.
  OS_ARM_ISRSetPrio(_OS_TIMER_INT_ID, _OS_TIMER_PRIO);
  OS_COM_Init();                                         //initialize UART for OSView
  OS_RestoreI();
}

/*********************************************************************
*
*       Idle loop  (OS_Idle)
*
*       Please note:
*       This is basically the "core" of the idle loop.
*       This core loop can be changed, but:
*       The idle loop does not have a stack of its own, therefore no
*       functionality should be implemented that relies on the stack
*       to be preserved. However, a simple program loop can be programmed
*       (like toggeling an output or incrementing a counter)
*/
void OS_Idle(void) {     // Idle loop: No task is ready to exec
  while (1) {
  }
}

/*********************************************************************
*
*       Get time [cycles]
*
*       This routine is required for task-info via OSView or high
*       resolution time maesurement functions.
*       It returns the system time in timer clock cycles.
*/
OS_U32 OS_GetTime_Cycles(void) {
  OS_U32 time;
  OS_U32 count;

  count = __OS_TIM_TMVAL - _TMRLR_VALUE;  // Read current timer value
  time  = OS_GetTime32();                 // Read current OS time
  if (__OS_TIM_TMOVF &= (1 << _TIMER_INT_BIT_NO)) { // System timer interrupt pending?
    time++;                                         // Adjust result, read timer again
    count = __OS_TIM_TMVAL - _TMRLR_VALUE;          // Read current timer value
  }
  return (OS_PCLK_TIMER * time) + count;
}

/*********************************************************************
*
*       OS_ConvertCycles2us
*
*       Convert Cycles into micro seconds.
*
*       If your clock frequency is not a multiple of 1 MHz,
*       you may have to modify this routine in order to get proper
*       diagonstics.
*
*       This routine is required for profiling or high resolution time
*       measurement only. It does not affect operation of the OS.
*/
OS_U32 OS_ConvertCycles2us(OS_U32 Cycles) {
  #if OS_PCLK_TIMER == (7500000ul / 16)
    // As OS_PCLK_TIMER is below 1MHz, when system timer is used, we have to do some calculation
    if (Cycles < 0x08000000) {
      Cycles *= 32;
    return Cycles/(OS_PCLK_TIMER/31250);
    } else {
      // Can not be calculated exactly, round result
      return (Cycles / 100) * 213;
    }
  #else
    // Assume OS_PCLK_TIMER is a multiple of 1 MHz
    return (Cycles/(OS_PCLK_TIMER/1000000);
  #endif
}

/*********************************************************************
*
*       Communication for OSView via SIO (UART) (optional)
*
**********************************************************************
*/

#if OS_UART_USED

/*********************************************************************
*
*       OS_COM_Send1()
*       Never call this function directly from your application
*/
void OS_COM_Send1(OS_U8 c) {
  __SIOBUF = c;                  // Send character
}

/*********************************************************************
*
*       OS_COM_Init()
*       Initialize SIO (UART) for OSView
*/
#define _BT_VALUE  (256 - (OS_PCLK_UART / ( 16 * OS_BAUDRATE)))

void OS_COM_Init(void) {

  OS_DI();
  if (OS_UART == 0) {
  } else {
    return;                   /* major error */
  }
  __SIOBCN = 0x00;            /* stop baud rate timer */
  __SIOSTA = 0x37;            /* clear SIOSTA */
  __SIOTCN = 0x00;            /* clear SIOTCN */

  __SIOBT   = _BT_VALUE;      /* Initialize baud rate generator */
  __SIOBCN  = SIOBCN_BGRUN;   /* start baud rate timer */

  /* Set communication format: 8 data bits, No parity, 1 stop bit */
  __SIOCON = (_SIOCON_LN8 | _SIOCON_PDIS | _SIOCON_TSTB1);

  /*  Install OS UART interrupt handler */
  OS_ARM_InstallISRHandler(_OS_UART_INT_ID, &_OS_COM_ISR); // UART interrupt vector.
  OS_ARM_ISRSetPrio(_OS_UART_INT_ID, _OS_UART_PRIO);

  /* set special function for related port */
  __PIOCTL  = CNFIG_UNLOCK;   /* protect for wrong access */
  __PIOCTL  = 0xC000;         /* selection of secondary function (gpctl 1bit)*/

  OS_RestoreI();
}

#else  /* selected UART not supported, using dummies */

void OS_COM_Init(void) {}
void OS_COM_Send1(OS_U8 c) {
  OS_USEPARA(c);           // avoid compiler warning
  OS_COM_ClearTxActive();  // let the OS know that Tx is not busy
}
#endif /*  OS_UART_USED  */

/*********************************************************************
*
*       OS_irq_handler
*
*       Detect reason for IRQ and call correspondig service routine.
*       OS_irq_handler is called from OS_IRQ_SERVICE function
*       found in RTOSVect.asm
*/
OS_INTERWORK void OS_irq_handler(void) {
  OS_ISR_HANDLER* pISR;
  int ISRIndex;

  ISRIndex = __IRC_IRN;                // Examine current interrupt source (channel number)
  pISR = _apOS_ISRHandler[ISRIndex];   // Read interrupt vector
#if ALLOW_NESTED_INTERRUPTS
  OS_EnterNestableInterrupt();         // Now interrupts may be reenabled. If nesting should be allowed
#else
  OS_EnterInterrupt();                 // Inform OS that interrupt handler is running
#endif
  if (pISR != NULL) {
    pISR();                            // Call installed interrupt service routine
  } else {
    _OS_ISR_Undefined(ISRIndex);
  }
  OS_DI();                             // Disable interrupts and unlock
  __IRC_CICL |= (1 << ISRIndex);       // Clear current interrupt pending bit, reset EIC
#if ALLOW_NESTED_INTERRUPTS
  OS_LeaveNestableInterrupt();         // Leave nestable interrupt, perform task switch if required
#else
  OS_LeaveInterrupt();                 // Leave interrupt, perform task switch if required
#endif
}

/*********************************************************************
*
*       OS_ARM_InstallISRHandler
*/
OS_ISR_HANDLER* OS_ARM_InstallISRHandler (int ISRIndex, OS_ISR_HANDLER* pISRHandler) {
  OS_ISR_HANDLER*  pOldHandler;

#if DEBUG
  if ((unsigned)ISRIndex >= NUM_INT_SOURCES) {
    OS_Error(OS_ERR_ISR_INDEX);
    return NULL;
  }
#endif
  OS_DI();
  pOldHandler                = _apOS_ISRHandler[ISRIndex];
  _apOS_ISRHandler[ISRIndex] = pISRHandler;
  OS_RestoreI();
  return pOldHandler;
}

/*********************************************************************
*
*       OS_ARM_DisableISR
*
*/
void OS_ARM_DisableISR(int ISRIndex) {
  _ISRSetPrio(ISRIndex, 0);
}

/*********************************************************************
*
*       OS_ARM_ISRSetPrio
*
*/
int OS_ARM_ISRSetPrio(int ISRIndex, int Prio) {
  return _ISRSetPrio(ISRIndex, Prio);
}

/*********************************************************************
*
*       Final check of configuration
*
**********************************************************************
*/

#ifndef OS_UART_USED
  #error "OS_UART_USED has to be defined"
#endif

/*****  EOF  ********************************************************/

