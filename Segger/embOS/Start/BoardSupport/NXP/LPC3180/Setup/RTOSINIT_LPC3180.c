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
File    : RTOSINIT_LPC3180.c   (for NXP LPC3180 CPUs)
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

#ifndef   OS_FSYS                   /* CPU main clock freqeuncy     */
  #define OS_FSYS 208000000L        /* may depend on PLL            */
#endif

#ifndef   OS_PCLK_TIMER              /* Peripheral clock for timer   */
  #define OS_PCLK_TIMER (OS_FSYS/16) /* defaults to CPU clock / 16   */
#endif

#ifndef   OS_PCLK_UART               /* Peripheral clock for UART    */
  #define OS_PCLK_UART (OS_FSYS/16)  /* defaults to CPU clock / 16   */
#endif

/****** OS internal timing settings ******************************/

#define _OS_TIMER_INTERVAL (OS_PCLK_TIMER / 1000)

/*********************************************************************
*
*       UART settings for OSView
*       If you do not want (or can not due to hardware limitations)
*       to dedicate a UART to OSView, please define it to be -1
*       Current version does not Support UART for embOSView
*/
#ifndef   OS_UART
  #define OS_UART -1
#endif
#ifndef   OS_BAUDRATE
  #define OS_BAUDRATE 38400L
#endif

/****** Define behavior of undefined interrupt handling *************/

#ifndef   OS_IGNORE_UNDEFINED_INTERRUPT
  #define OS_IGNORE_UNDEFINED_INTERRUPT 0
#endif

/****** End of configuration settings *******************************/

#define OS_UART_USED ((OS_UART == 0) || (OS_UART == 1))

/*********************************************************************
*
*       Local defines (sfrs used in RTOSInit.c)
*
**********************************************************************
*/

/****** Master Interrupt Controller *********************************/
#define __MIC_BASE_ADDR     0x40008000
#define __MIC_ER       *(volatile unsigned int*)(__MIC_BASE_ADDR)
#define __MIC_SR       *(volatile unsigned int*)(__MIC_BASE_ADDR + 0x8)
#define __MIC_APR      *(volatile unsigned int*)(__MIC_BASE_ADDR + 0xC)
#define __MIC_ATR      *(volatile unsigned int*)(__MIC_BASE_ADDR + 0x10)
#define __MIC_ITR      *(volatile unsigned int*)(__MIC_BASE_ADDR + 0x14)

/****** Slave Interrupt Controller 1 ********************************/
#define __SIC1_BASE_ADDR    0x4000C000
#define __SIC1_ER      *(volatile unsigned int*)(__SIC1_BASE_ADDR)
#define __SIC1_SR      *(volatile unsigned int*)(__SIC1_BASE_ADDR + 0x8)
#define __SIC1_ITR     *(volatile unsigned int*)(__SIC1_BASE_ADDR + 0x14)

/****** Slave Interrupt Controller 2 ********************************/
#define __SIC2_BASE_ADDR    0x40010000
#define __SIC2_ER      *(volatile unsigned int*)(__SIC2_BASE_ADDR)
#define __SIC2_SR      *(volatile unsigned int*)(__SIC2_BASE_ADDR + 0x8)
#define __SIC2_ITR     *(volatile unsigned int*)(__SIC2_BASE_ADDR + 0x14)

/****** Millisecond Timer  ******************************************/
#define __MSTIM_BASE_ADDR   0x40034000
#define __MSTIM_INT    *(volatile unsigned int*)(__MSTIM_BASE_ADDR)
#define __MSTIM_CTRL   *(volatile unsigned int*)(__MSTIM_BASE_ADDR + 0x4)
#define __MSTIM_MCTRL  *(volatile unsigned int*)(__MSTIM_BASE_ADDR + 0x14)
#define __MSTIM_MATCH0 *(volatile unsigned int*)(__MSTIM_BASE_ADDR + 0x18)

/****** HCLK Divider Control Register  ******************************/
#define __HCLKDIV_CTRL *(volatile unsigned int*)(0x40004040)

/****** HCLK PLL Control Register  **********************************/
#define __HCLKPLL_CTRL *(volatile unsigned int*)(0x40004058)

/****** Power Control Register  *************************************/
#define __PWR_CTRL     *(volatile unsigned int*)(0x40004044)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

#define NUM_INT_SOURCES (3*32)   // 3 interrupt controller

static OS_ISR_HANDLER* _apOS_ISRHandler[NUM_INT_SOURCES];

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/

/*********************************************************************
*
*       _InitPLL
*
* Function description
*   Initialize PLL
*   WARNING: Improper settings may lock CPU
*   Please examine whether init sequence fits your harware configuration
*   We assume a CPU running with external oscillator which is multilied by four
*   which is allowed for a maximum external frequency of 15MHz
*/
static void _InitPLL(void) {
  // Set Clk dividers
  __HCLKDIV_CTRL  = (1 << 0)             // 1/2  Pll_clk_out
                  | ((16 -1) << 2)       // 1/16 Pll_clk_out
                  ;
  // PLL Init - OSC * 16 = 208MHz
  __HCLKPLL_CTRL  = (0 << 15)            // OSC connected to PLL input
                  | (1 << 14)            // CCO connected to PLL_Clk output
                  | (0 << 13)            // CC0 connected to N divider input
                  | (0 <<  9)            // set divide
                  | (16 << 1)            // set multiplier
                  ;
  __HCLKPLL_CTRL |= (1 << 16);           // Enable Pll
  while((__HCLKPLL_CTRL & 1) == 0);      // Wait until PLL lock
  __PWR_CTRL     |= (1 << 2);            // Connect Pll_clk_out
}

/*********************************************************************
*
*       _Init_MIC()
*
* Function description
*   Clears and disables all interrut sources in Interrupt controller.
*/
static void _Init_MIC(void) {
  OS_DI();
  memset(_apOS_ISRHandler, 0x00, sizeof(_apOS_ISRHandler));
  __MIC_ER   = 0x00;    // Disable all interrupts of main controller
  __SIC1_ER  = 0x00;    // Disable all interrupts of slave controller 1
  __SIC2_ER  = 0x00;    // Disable all interrupts of slave controller 2
  __MIC_ITR  = 0x00;    // Assign all inputs to IRQ
  __SIC1_ITR = 0x00;    // Assign all inputs to IRQ
  __SIC2_ITR = 0x00;    // Assign all inputs to IRQ
  __MIC_ER   = (1 << 31) | (1 << 30) | (1 << 1) | (1 << 0);   // Enable interrupts from slave controller
  OS_RestoreI();
}

/*********************************************************************
*
*       _ISRMaskToIndex
*
*       Calculates index of highest pending interrupt from Mask
*/
static OS_U32 _ISRMaskToIndex(OS_U32 Mask) {
  OS_U32 Index;

  Index = 0;
  if (Mask & 0xFFFF0000) {
    Index += 16;
    Mask >>= 16;
  }
  if (Mask & 0xFF00) {
    Index += 8;
    Mask >>= 8;
  }
  if (Mask & 0xF0) {
    Index += 4;
    Mask >>= 4;
  }
  if (Mask & 0xC) {
    Index += 2;
    Mask >>= 2;
  }
  if (Mask & 0x2) {
    Index += 1;
  }
  return Index;
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
    while (Dummy) {
    }
  #endif
}

/*********************************************************************
*
*       _OS_ISR_Tick() interrupt Handler
*/
static void _OS_ISR_Tick(void) {
  __MSTIM_INT |= 1;   // Clear interrupt flag
  OS_HandleTick();    // Call OS tick handler
#if DEBUG
  DCC_Process();
#endif
}

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

/*********************************************************************
*
*       __low_level_init()
*
* Function description
*   Called from startup code.
*   Used to initialize PLL and memory accelerator as early as possible
*/
OS_INTERWORK int __low_level_init(void);       /* Avoid "No prototype" warning */
OS_INTERWORK int __low_level_init(void) {
  _InitPLL();
  return 1;                       // Always initialize segments !
};

/*********************************************************************
*
*       OS_InitHW()
*
*       Initialize the hardware (timer) required for the OS to run.
*       May be modified, if an other timer should be used
*       Also enables memory accelerator module
*/
void OS_InitHW(void) {
  OS_DI();
  _Init_MIC();      // Initialize MIC, clear and disable all interrupts
  // Initialize timer for OS
  // Init Timer
  __MSTIM_CTRL  = 2;        // Reset and stop timer counters
  __MSTIM_MCTRL = (1 << 1)  // Reset timer counter on match 0
                | (1 << 0)  // Enable interrupt by match 0
                ;
  __MSTIM_MATCH0 = 32768UL/1000;        // Set timer period
  // Init timer interrupts
  __MIC_APR |=  (1 << 27);  // on a low level signal
  __MIC_ATR &= ~(1 << 27);  // Set level sensetive interrupt
  __MIC_ITR &= ~(1 << 27);  // assign to IRQ line
  __MSTIM_CTRL = 1;         // Enable milisecond timer and release reset
  OS_ARM_InstallISRHandler (27, _OS_ISR_Tick);
  OS_ARM_EnableISR(27);
  OS_COM_Init();
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
  return 0;
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
  return Cycles/(OS_PCLK_TIMER/1000000);
}

/*********************************************************************
*
*       Communication for OSView via UART (optional)
*
**********************************************************************
*/

#if OS_UART_USED
#error "UART support for OSView not implemented so far."

/*********************************************************************
*
*       OS_COM_ISR_Usart() OS USART interrupt handler
*       handles both, Rx and Tx interrupt
*/
static void _OS_COM_ISR(void) {
  // xxx TBD
}

/*********************************************************************
*
*       OS_COM_Send1()
*       Never call this function directly from your application
*/
void OS_COM_Send1(OS_U8 c) {
  // xxx TBD
}

/*********************************************************************
*
*       OS_COM_Init()
*       Initialize UART for OSView
*/
#define _BAUDDIVIDE ((OS_PCLK_UART+OS_BAUDRATE*8L)/(OS_BAUDRATE*16L))

void OS_COM_Init(void) {
  // xxx TBD
}

#else  /* selected UART not supported, using dummies */

void OS_COM_Init(void) {}
void OS_COM_Send1(OS_U8 c) {
  OS_USEPARA(c);           // avoid compiler warning
  OS_COM_ClearTxActive();  // let the OS know that Tx is not busy
}

#endif /*  OS_UART_USED  */

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
*       OS_irq_handler
*
*       Detect reason for IRQ and call correspondig service routine.
*       OS_irq_handler is called from OS_IRQ_SERVICE function
*       found in RTOSVect.asm
*/
OS_INTERWORK void OS_irq_handler(void) {
  OS_ISR_HANDLER* pISR;
  OS_U32 ISRIndex;
  OS_U32 ISRMask;
  OS_U32 ISRPending;

  ISRMask = __MIC_SR & 0x3FFFFFFF;     // Examine current interrupt source, ignore FIQs
  if (ISRMask & (1 << 0)) {            // Slave 1 pending ?
    ISRMask    = __SIC1_SR;
    ISRIndex   = _ISRMaskToIndex(ISRMask) + 32;
    ISRPending = (1 << 0);
  } else if (ISRMask & (1 << 1)) {     // Slave 2 pending ?
    ISRMask    = __SIC2_SR;
    ISRIndex   = _ISRMaskToIndex(ISRMask) + 64;
    ISRPending = (1 << 1);
  } else {
    ISRIndex   = _ISRMaskToIndex(ISRMask);
    ISRPending = (1 << ISRIndex);
  }
  __MIC_ER &= ~ISRPending;             // Disable pending interrupt source to avoid recursion
#if ALLOW_NESTED_INTERRUPTS
  OS_EnterNestableInterrupt();         // Now interrupts may be reenabled. If nesting should be allowed
#else
  OS_EnterInterrupt();                 // Inform OS that interrupt handler is running
#endif
  pISR = _apOS_ISRHandler[ISRIndex];   // Read interrupt vector from Table
  if (pISR != NULL) {
    pISR();                            // Call installed interrupt service routine
  } else {
    _OS_ISR_Undefined(ISRIndex);
  }
  OS_DI();                             // Disable interrupts
  __MIC_ER |= ISRPending;              // Re-enable interrupt source
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
*       OS_ARM_EnableISR
*/
void OS_ARM_EnableISR(int ISRIndex) {
#if DEBUG
  if ((unsigned)ISRIndex >= NUM_INT_SOURCES) {
    OS_Error(OS_ERR_ISR_INDEX);
    return;
  }
#endif
  OS_DI();
  if (ISRIndex < 32) {        // Main interrupt controller affected ?
    __MIC_ER |= (1 << ISRIndex);
  } else if (ISRIndex < 64) { // Slave 1 affected?
    ISRIndex -= 32;
    __SIC1_ER |= (1 << ISRIndex);
  } else {                    // Slave 2
    ISRIndex -= 64;
    __SIC2_ER |= (1 << ISRIndex);
  }
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_DisableISR
*/
void OS_ARM_DisableISR(int ISRIndex) {
#if DEBUG
  if ((unsigned)ISRIndex >= NUM_INT_SOURCES) {
    OS_Error(OS_ERR_ISR_INDEX);
    return;
  }
#endif
  OS_DI();
  if (ISRIndex < 32) {        // Main interrupt controller affected ?
    __MIC_ER &= ~(1 << ISRIndex);
  } else if (ISRIndex < 64) { // Slave 1 affected?
    ISRIndex -= 32;
    __SIC1_ER &= ~(1 << ISRIndex);
  } else {                    // Slave 2
    ISRIndex -= 64;
    __SIC2_ER &= ~(1 << ISRIndex);
  }
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_ISRSetPrio
*/
int OS_ARM_ISRSetPrio(int ISRIndex, int Prio) {
  /* individual interrupt priorities are not supported by MIC */
  return 0;
}

/*****  EOF  ********************************************************/
