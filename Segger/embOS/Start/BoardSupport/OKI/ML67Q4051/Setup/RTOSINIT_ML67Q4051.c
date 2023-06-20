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
File    : RTOSInit_ML674050_60.c   (for Oki ML674050_60 CPUs)
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

#ifndef   OS_FSYS                   /* CPU main clock frequncy      */
  #define OS_FSYS 32768000L         /* may depend on PLL            */
#endif

#ifndef   OS_PCLK_TIMER             /* Peripheral clock for timer   */
  #define OS_PCLK_TIMER OS_FSYS     /* May vary from CPU clock      */
#endif                              /* depending on CPU             */

#ifndef   OS_PCLK_UART              /* Peripheral clock for UART    */
  #define OS_PCLK_UART OS_FSYS      /* May vary from CPU clock      */
#endif                              /* depending on CPU             */

#ifndef   OS_TICK_FREQ
  #define OS_TICK_FREQ 1000         /* Ticks per second             */
#endif

/*********************************************************************
*
*       UART settings for OSView
*       If you do not want (or can not due to hardware limitations)
*       to dedicate a UART to OSView, please define it to be -1
*       Currently the standard code enables UART 0 per default
*       and supports UART0 to UART3
*/
#ifndef   OS_UART
  #define OS_UART 0
#endif
#ifndef   OS_BAUDRATE
  #define OS_BAUDRATE 38400L
#endif

/****** Define behaviour of undefined interrupt handling ************/

#ifndef   OS_IGNORE_UNDEFINED_INTERRUPT
  #define OS_IGNORE_UNDEFINED_INTERRUPT 0
#endif

/****** Default interrupt priority used for OS_ARM_EnableISR ********/

#define _OS_DEFAULT_INT_PRIORITY 1

/****** End of configuration settings *******************************/

#define OS_UART_USED ((OS_UART == 0) || (OS_UART == 1))

/*********************************************************************
*
*       Local defines (sfrs used in RTOSInit.c)
*
**********************************************************************
*/

/****** UART sfdr definition ****************************************/
#define __UART0_BASE_ADDR   0xB7B00000
#define __UART1_BASE_ADDR   0xB7B01000

#define __UART_TxBUFR_OFFS 0x00 // Tx Buffer
#define __UART_RxBUFR_OFFS 0x00 // Rx Buffer
#define __UART_IER_OFFS    0x04 // Interrupt enable
#define __UART_IIR_OFFS    0x08 // Interrupt ID
#define __UART_FIFO_OFFS   0x08 // FIFO Control
#define __UART_LCR_OFFS    0x0c // Line Control
#define __UART_MCR_OFFS    0x10 // Modem Control
#define __UART_LSR_OFFS    0x14 // Line Status
#define __UART_MSR_OFFS    0x18 // Modem Status
#define __UART_SCR_OFFS    0x1c // Scratchpad
#define __UART_DLL_OFFS    0x00 // Divisor Latch
#define __UART_DLM_OFFS    0x04 // Divisor Latch

#define UARTLCR_LEN8    0x0003  /* data length : 8bit */
#define UARTLCR_STB1    0x0000  /* stop bit : 1 */
#define UARTLCR_PDIS    0x0000  /* parity disabled */
#define UARTIER_ERBF    0x0001  /* enable received data available interrupt */
#define UARTIER_ETBEF   0x0002  /* enable transmitter holding register empty interrupt */
#define UARTIER_ELSI    0x0004  /* enable receiver line status interrupt */
#define UARTFCR_FE      0x0001  /* FIFO enable */
#define UARTFCR_RFCLR   0x0002  /* receiver FIFO clear */
#define UARTFCR_TFCLR   0x0004  /* transmitter FIFO clear */
#define UARTFCR_RFLV14  0x00C0  /* RCVR FIFO interrupt trigger level : 14byte */


/****** Assign UART sfrs used for OSView communication ***********/

#if OS_UART_USED
  #if   (OS_UART == 0)
    #define _OS_UART_BASE_ADDR __UART0_BASE_ADDR
    #define _OS_UART_ID   INT_UART0
  #elif (OS_UART == 1)
    #define _OS_UART_BASE_ADDR __UART1_BASE_ADDR
    #define _OS_UART_ID   INT_UART1
  #endif

  #define _OS_UART_BR      *(volatile OS_U8*)(_OS_UART_BASE_ADDR + 0)
  #define _OS_UART_TxBUFR  *(volatile OS_U8*)(_OS_UART_BASE_ADDR + __UART_TxBUFR_OFFS)
  #define _OS_UART_RxBUFR  *(volatile OS_U8*)(_OS_UART_BASE_ADDR + __UART_RxBUFR_OFFS)
  #define _OS_UART_IER     *(volatile OS_U8*)(_OS_UART_BASE_ADDR + __UART_IER_OFFS)
  #define _OS_UART_IIR     *(volatile OS_U8*)(_OS_UART_BASE_ADDR + __UART_IIR_OFFS)
  #define _OS_UART_FIFO    *(volatile OS_U8*)(_OS_UART_BASE_ADDR + __UART_FIFO_OFFS)
  #define _OS_UART_LCR     *(volatile OS_U8*)(_OS_UART_BASE_ADDR + __UART_LCR_OFFS)
  #define _OS_UART_MCR     *(volatile OS_U8*)(_OS_UART_BASE_ADDR + __UART_MCR_OFFS)
  #define _OS_UART_LSR     *(volatile OS_U8*)(_OS_UART_BASE_ADDR + __UART_LSR_OFFS)
  #define _OS_UART_MSR     *(volatile OS_U8*)(_OS_UART_BASE_ADDR + __UART_MSR_OFFS)
  #define _OS_UART_SCR     *(volatile OS_U8*)(_OS_UART_BASE_ADDR + __UART_SCR_OFFS)
  #define _OS_UART_DLL     *(volatile OS_U8*)(_OS_UART_BASE_ADDR + __UART_DLL_OFFS)
  #define _OS_UART_DLM     *(volatile OS_U8*)(_OS_UART_BASE_ADDR + __UART_DLM_OFFS)


  #define _TX_EMPTY_INT_BIT 2
  #define _RX_FULL_INT_BIT  0
  #define _UART_RX_ERROR_FLAGS ((1 << 3) | (1 << 4) | (1 << 5))  // Parity, framing, overrun error
  #define _OS_UART_PRIO     0x01                      // lowest priority for OS UART interrupts
  #define _TXRDY_FLAG       (1 << _TX_EMPTY_INT_BIT)
  #define _RXRDY_FLAG       (1 << _RX_FULL_INT_BIT)
#endif

/****** Port select register  ***********************************************/
#define __SCR_BASE2_ADDR 0xB7000000    /* base address */
#define __PORTSEL1_OFFS 0x24      /* port control register 1 */

#define  _OS_SCR_BASE2_ADDR  __SCR_BASE2_ADDR
#define  _PORTSEL1      *(volatile OS_U32*)(_OS_SCR_BASE2_ADDR + __PORTSEL1_OFFS)

/****** Power, reset clock control unit register ********************/

/****** Timer sfr definition ****************************************/

#define __TIM_BASE_ADDR       0xB8001004
#define __TIM_TMEN_OFFS  0x00
#define __TIM_TMRLR_OFFS 0x04
#define __TIM_TMOVF_OFFS 0x0c

#define __TIM_TMVAL_OFFS 0x08 // NOT SURE IF THIS IS CORRECT ADDRESS


/****** Assign timer sfrs used for OS timer    ****************************/
/****** initially, we use SYSTEM timer         ****************************/

#define _OS_TIM_BASE_ADDR        __TIM_BASE_ADDR
#define _OS_TIM_TMEN        *(volatile OS_U32*)(_OS_TIM_BASE_ADDR + __TIM_TMEN_OFFS)
#define _OS_TIM_TMRLR       *(volatile OS_U32*)(_OS_TIM_BASE_ADDR + __TIM_TMRLR_OFFS)
#define _OS_TIM_TMOVF       *(volatile OS_U32*)(_OS_TIM_BASE_ADDR + __TIM_TMOVF_OFFS)
#define _OS_TIM_TMVAL       *(volatile OS_U32*)(_OS_TIM_BASE_ADDR + __TIM_TMVAL_OFFS)

#define _TIMER_INT_BIT_NO  0

/****** PLL *********************************************************/


/****** Enhanced interrupt controller (EIC) *************************/

// OKI Definitions
#define __IRC_IRN   *(volatile OS_U32*)0x78000014
#define __IRC_ILC0  *(volatile OS_U32*)0x78000020
#define __IRC_ILC1  *(volatile OS_U32*)0x78000024
#define __IRC_CICL  *(volatile OS_U32*)0x78000028

#define __IRC_EXILCA_ADDR 0x7BF00018
#define __IRC_EXILCB_ADDR 0x7BF00028
#define __IRC_EXILCC_ADDR 0x7BF00038
#define __IRC_EXILCA *(volatile OS_U32*)__IRC_EXILCA_ADDR
#define __IRC_EXILCB *(volatile OS_U32*)__IRC_EXILCB_ADDR
#define __IRC_EXILCC *(volatile OS_U32*)__IRC_EXILCC_ADDR

/****** Enhanced interrupt controller interrupt sources *************/

/*****************************************************/
/*    interrupt number                               */
/*****************************************************/
#define INT_SYSTEM_TIMER    0
#define INT_WDT             1
#define INT_IVT             2
#define INT_GPIOA           4
#define INT_GPIOB           5
#define INT_GPIOC           6
#define INT_GPIOD           7
#define INT_SOFTIRQ         8
#define INT_UART0           9
#define INT_SIO0            10
#define INT_AD              11
#define INT_UART1           12
#define INT_SPI0            13
#define INT_TIMER0          16
#define INT_TIMER1          17
#define INT_TIMER2          18
#define INT_TIMER3          19
#define INT_TIMER4          20
#define INT_TIMER5          21
#define INT_DMA0            24
#define INT_DMA1            25
#define INT_GPIOE           28
#define INT_GPIOF           29
#define INT_EXINT1          34
#define INT_EXINT2          36
#define INT_EXINT3          38
#define INT_EXINT4          40

#ifndef   NUM_INT_SOURCES
  #define NUM_INT_SOURCES   64
#endif
#define _INT_CHANNEL_MASK  0x1F

#define _INT_PRIORITY_MASK 0x07

volatile int to_count;

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
  if (_OS_TIM_TMOVF &= (1 << _TIMER_INT_BIT_NO)) { // System timer interrupt pending?
    _OS_TIM_TMOVF &= (1 << _TIMER_INT_BIT_NO);     // Clear OS timer interrupt flag
    OS_HandleTick();                               // Call OS tick handler
#if DEBUG
    DCC_Process();
#endif
  }
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
#define _OS_TIMER_ID     INT_SYSTEM_TIMER // Assign to System Timer global interrupt
#define _OS_TIMER_PRIO   1                // lowest priority
#define _TMRLR_VALUE     (65536 - (OS_PCLK_TIMER/OS_TICK_FREQ/16))

void OS_InitHW(void) {
  OS_DI();
  // Initialize timer for OS, we use system timer
  _OS_TIM_TMEN  = 0;                      // Stop timer, reset mode
  _OS_TIM_TMRLR = 0;                      // Clear the reload value
  _OS_TIM_TMOVF = 1;                      // Clear the overflow bit
  _OS_TIM_TMRLR = _TMRLR_VALUE;           // Setup reload register
  _OS_TIM_TMEN  = 1;                      // Start timer
  // Install interrupt handler for OS timer
  OS_ARM_InstallISRHandler(_OS_TIMER_ID, &_OS_ISR_Tick); // Timer/counter interrupt vector.
  OS_ARM_ISRSetPrio(_OS_TIMER_ID, _OS_TIMER_PRIO);
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

  count = _OS_TIM_TMVAL - _TMRLR_VALUE;  // Read current timer value
  time  = OS_GetTime32();                // Read current OS time
  if (_OS_TIM_TMOVF &= (1 << _TIMER_INT_BIT_NO)) { // System timer interrupt pending?
    time++;                                        // Adjust result, read timer again
    count = _OS_TIM_TMVAL - _TMRLR_VALUE;          // Read current timer value
  }
  return ((OS_PCLK_TIMER/16) * time) + count;
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
  return Cycles/(OS_PCLK_TIMER/16/1000000);
}

/*********************************************************************
*
*       Communication for OSView via UART (optional)
*
**********************************************************************
*/

#if OS_UART_USED

#define TRIGGER_LEVEL   14      // FIFO Level
#define UARTIIR_NOINT   0x0001  // no interrupt
#define UARTIIR_TRA     0x0002  // transmitter interrupt
#define UARTIIR_RCV     0x0004  // receiver interrupt
#define UARTIIR_LINE    0x0006  // receive line error interrupt
#define UARTIIR_TO      0x000C  // time out interrupt
#define UARTLSR_OE      0x0002  // overrun error
#define UARTLSR_PE      0x0004  // parity error
#define UARTLSR_FE      0x0008  // framing error
#define UARTLSR_BI      0x0010  // break interrupt

/*********************************************************************
*
*       OS_COM_ISR_Usart() OS UART interrupt handler
*       handles both, Rx and Tx interrupt
*/
static void _OS_COM_ISR(void) {
  int UartStatus;
  int i;
  volatile OS_U32 Dummy;

  UartStatus  = _OS_UART_IIR;         // Examine status register
  UartStatus &= 0x0f;

  switch (UartStatus) {
  case UARTIIR_NOINT :                // no interrupt
    break;

  case UARTIIR_LINE :                 // receiving line status interrupt
    Dummy = _OS_UART_LSR;             // clear interrupt
    break;

  case  UARTIIR_RCV : // receiving data effective interrupt
    for (i = 0; i < TRIGGER_LEVEL; i++) {
      OS_OnRx(_OS_UART_RxBUFR);       // Process actual byte
    }
    break;

  case UARTIIR_TO :   // time out interrupt
    to_count++;
    OS_OnRx(_OS_UART_RxBUFR);
    break;

  case UARTIIR_TRA :  // transmission empty interrupt
    if (OS_OnTx()) {  // No more characters to send ?
      // interrupt is cleared by "UartStatus = _OS_UART_IIR;"
      _OS_UART_IER &= ~(UARTIIR_TRA); // Disable further tx interrupts
    }
    break;
  default:
    break;
  }
}

/*********************************************************************
*
*       OS_COM_Send1()
*       Never call this function directly from your application
*/
void OS_COM_Send1(OS_U8 c) {
  _OS_UART_TxBUFR = c;                 // Send character
  _OS_UART_IER |= (UARTIIR_TRA);       // enable Tx Empty interrupt
}

/*********************************************************************
*
*       OS_COM_Init()
*       Initialize UART for OSView
*/
void OS_COM_Init(void) {
  OS_DI();
  if (OS_UART == 0) {
    /* PORT B secondary function */
    _PORTSEL1 =  0x050000;   // UART0 TX, RX enabled
  } else if (OS_UART == 1) {
    /* PORT B secondary function */
    _PORTSEL1 =  0x500000;   // UART1 TX, RX enabled
  } else {
    return;                  // major error
  }

  /***********************************************************
        The value of a baud rate is set as 38,400 bps
  ***********************************************************/

  _OS_UART_LCR |=  0x0080;  // divisor latch access bit
  _OS_UART_DLL  =  0x36;    // Setup baudrate generator
  _OS_UART_DLM  =  0x00;    // Setup baudrate generator
  _OS_UART_LCR &= ~0x0080;  // divisor latch access bit

  _OS_UART_FIFO =  (UARTFCR_FE | UARTFCR_RFCLR | UARTFCR_TFCLR | UARTFCR_RFLV14);
  _OS_UART_LCR  =  (UARTLCR_LEN8|UARTLCR_STB1|UARTLCR_PDIS);
  _OS_UART_MCR  =  0x0;
  _OS_UART_IER  =  (UARTIER_ERBF | UARTIER_ETBEF | UARTIER_ELSI);

  /*  Install OS UART interrupt handler */
  OS_ARM_InstallISRHandler(_OS_UART_ID, &_OS_COM_ISR); // UART interrupt vector.
  OS_ARM_ISRSetPrio(_OS_UART_ID, _OS_UART_PRIO);

  OS_RestoreI();
}

#else  // selected UART not supported, using dummies

void OS_COM_Init(void) {}
void OS_COM_Send1(OS_U8 c) {
  OS_USEPARA(c);           // avoid compiler warning
  OS_COM_ClearTxActive();  // let the OS know that Tx is not busy
}

#endif //  OS_UART_USED  //

/****** Final check of configuration ********************************/
#ifndef OS_UART_USED
  #error "OS_UART_USED has to be defined"
#endif

/*********************************************************************
*
*       OS interrupt handler and ISR specific functions
*
**********************************************************************
*/

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
  if (ISRIndex < NUM_INT_SOURCES) {
    pOldHandler                = _apOS_ISRHandler[ISRIndex];
    _apOS_ISRHandler[ISRIndex] = pISRHandler;
  }
  OS_RestoreI();
  return pOldHandler;
}

/*********************************************************************
*
*       OS_ARM_EnableISR
*
*  Note:
*       As some interrupt sources share the same control register,
*       Enabling one source might enable an other interrupt source also
*
*       Enabling an interrupt using this function will set interrupt
*       priority to _OS_DEFAULT_INT_PRIORITY
*
*       You might use OS_ARM_ISRSetPrio instead of OS_ARM_EnableISR
*/
void OS_ARM_EnableISR(int ISRIndex) {
  _ISRSetPrio(ISRIndex, _OS_DEFAULT_INT_PRIORITY);
}

/*********************************************************************
*
*       OS_ARM_DisableISR
*
*       Set interrupt priority of selected interrupt channel to zero.
*
*  Note:
*       As some interrupt sources share the same control register,
*       disabling one source might disable an other interrupt source also
*/
void OS_ARM_DisableISR(int ISRIndex) {
  _ISRSetPrio(ISRIndex, 0);
}

/*********************************************************************
*
*       OS_ARM_ISRSetPrio
*/
int OS_ARM_ISRSetPrio(int ISRIndex, int Prio) {
  return _ISRSetPrio(ISRIndex, Prio);
}

/*****  EOF  ********************************************************/

