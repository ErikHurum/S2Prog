/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************

File        : RTOSInit.c
Purpose     : Initializes and handles the hardware for embOS as far
              as required by embOS.
              Feel free to modify this file acc. to your
              target system.
---------------------------END-OF-HEADER------------------------------
*/

/*
  Please note:
  We do automatic release tests for embOS. These tests are done with the
  CPU_KS32C50100. You will find drivers for additional CPUs, which are used
  by our customers. These drivers have also been   tested at least one time,
  but they are not part of our periodic automatic release tests. Therefore
  it might happen, that you encounter a problem with these additional drivers.
*/

#include "RTOS.H"

void OS_USER_irq_func(void);

/*
**********************************************************************
*
*                    Configuration
*
**********************************************************************
*/

/* Select UART for embOSView, set baudrate,
   define clock frequency for CPU used

   If you do not want (or can not due to hardware limitations) to dedicate
   a UART to embOSView, please define OS_UART to -1
*/

#ifndef CPU_KS32C50100
  #error "This file is for KS32C50100 CPU"
#endif

#include "ks32c50100.h"
#define TIMER_PRESCALE  1              /* prescaler for timer frequency */

/*********************************************************************
*
*         Non HW dependent configuration defaults
*
**********************************************************************
*/
						
#define OS_FSYS 180000000					


#ifndef OS_TICK_FREQ
  #define OS_TICK_FREQ 1000
#endif

#ifndef USE_CACHE
  #define USE_CACHE 1   /* 0: No chache */
#endif

#ifndef OS_FSYS
  #define OS_FSYS 50000000
#endif

#ifndef OS_UART
  #define OS_UART 0
#endif

#ifndef OS_BAUDRATE
  #define OS_BAUDRATE 38400
#endif

#ifndef OS_RAMVECT
  #define OS_RAMVECT 0
#endif


/*
**********************************************************************
*
*                    OS_InitHW
*
**********************************************************************

Initialize the hardware required for the OS to run. This will work
on any target hardware, but may have to be tailored a little
(regarding the clock frequency). Of course the same holds true
if for some reason you choose to use an other timer.
*/

void OS_InitHW(void) {
  #if OS_RAMVECT
  {
    unsigned int vec;
    unsigned int *vector;
    extern void OS_IRQ_SERVICE(void);
    OS_DI();
    vector = (unsigned int*) 0x18;
    vec = (((unsigned int)&OS_IRQ_SERVICE - (unsigned int)vector - 8) >> 2);
    vec |= 0xea000000; /* add opcode for B instruction */
    *vector = vec;
    OS_EI();
  }
  #endif

  #if USE_CACHE
    OS_DI();
    __SYSCFG &= 0xffffffd8;
    __SYSCFG |= 0x0016;    /* 8 KB cache & wb */
    OS_EI();
  #endif
  #define TIMER_RELOAD       OS_FSYS/TIMER_PRESCALE/OS_TICK_FREQ
  #define TIMER_TICK_PND     (1 <<10)
  __TMOD   = 0;
  __INTPND = 0x00000000;   /* Clear pending interrupts */
  __INTMOD = 0x00000000;
  __TDATA0 = TIMER_RELOAD;
  __TMOD  |= 0x1;
  __INTMSK &= ~((1 << 21) | TIMER_TICK_PND);
  OS_COM_Init();
}


/*
**********************************************************************
*
*                     Idle task  (OS_Idle)
*
**********************************************************************

 Please note:
 This is basically the "core" of the idle task.
 This core loop can be changed, but:
 The idle task does not have a stack of its own, therefor no
 functionality should be implemented that relies on the stack
 to be preserved. However, a simple program loop can be programmed
 (like toggeling an output or incrementing a counter)
*/

void OS_Idle(void) {     // Idle task: No task is ready to exec
  while (1) {
  }
}

/*
**************************************************************
*
*             Run-time error reaction  (OS_Error)
*
**************************************************************

 Run-time error reaction

 When this happens, a fatal error has occured and the kernel
 can not continue. In linux, the equivalent would be a
 "kernel panic"

 This routine can be modified to suit your needs ...
 E.g. a red LED could light up. When using an
 emulator, you may set a breakpoint here.
 In the release builds of the library (R), this routine is not required
 (as no checks are performed).
 In the stack check builds (S/SP), only error 120 may occur.
 In the debug builds(D/DP), all of the listed errors may occur.

  The following are the current errorcodes (V2.80) :
  (Please refer to the documentation for more info)

OS_ERR_STACK                          (120)
*** invalid or non-initialized data structures ***
OS_ERR_INV_TASK                       (128)
OS_ERR_INV_TIMER                      (129)
OS_ERR_INV_MAILBOX                    (130)
OS_ERR_INV_CSEMA                      (132)
OS_ERR_INV_RSEMA                      (133)

*** Using GetMail1 or PutMail1 or GetMailCond1 or PutMailCond1 on a non-1 byte mailbox  ***
OS_ERR_MAILBOX_NOT1                   (135)

***internal errors, please contact SEGGER Microcontrollersysteme ***
OS_ERR_MAILBOX_NOT_IN_LIST            (140)
OS_ERR_TASKLIST_CORRUPT               (142)


*** not matching routine calls or macro usage ***
OS_ERR_UNUSE_BEFORE_USE               (150)
OS_ERR_LEAVEREGION_BEFORE_ENTERREGION (151)
OS_ERR_LEAVEINT                       (152)
OS_ERR_DICNT                          (153)
OS_ERR_INTERRUPT_DISABLED             (154)

*** not a legal system call during interrupt ***
OS_ERR_ILLEGAL_IN_ISR                 (160)
*** not a legal system call during timer ***
OS_ERR_ILLEGAL_IN_TIMER               (161)

** double used data structures **
OS_ERR_2USE_TASK                      (170)
OS_ERR_2USE_TIMER                     (171)
OS_ERR_2USE_MAILBOX                   (172)
OS_ERR_2USE_BSEMA                     (173)
OS_ERR_2USE_CSEMA                     (174)
OS_ERR_2USE_RSEMA                     (175)

*/

void OS_Error(int ErrCode) {
  OS_EnterRegion();     /* Avoid further task switches */
  OS_DICnt =0;          /* Allow interrupts so we can communicate */
  OS_EI();
  OS_Status = ErrCode;
  while (OS_Status);
}


/*
**********************************************************************
*
*                    Get time [cycles]
*
**********************************************************************

    This routine is required for task-info via embOS Viewer.
    It returns the system time in clock cycles.
*/

#define HW_TIMER __TCNT0
#define HW_TIMER_INTERRUPT_PENDING() (__INTPND & 0x0400)

OS_U32 OS_GetTime_Cycles(void) {
  unsigned int t_cnt = TIMER_RELOAD - HW_TIMER;
  OS_U32 time = OS_Time;
  if (HW_TIMER_INTERRUPT_PENDING()) {
    t_cnt = TIMER_RELOAD - HW_TIMER;
    time++;
  }
  return (OS_FSYS/TIMER_PRESCALE/OS_TICK_FREQ)*time  + t_cnt;
}


/*
**********************************************************************
*
*                    OS_ConvertCycles2us
*
**********************************************************************

Purpose:
   Convert Cycles into micro seconds. (For profiling only)

   If you have a clock frequency which is not a multiple of 1 MHz,
   you may have to modify this routine in order to get proper
   diagonstics.
Please note:
   This routine is required for profiling only.
   It does not affect operation of the OS.
*/

OS_U32 OS_ConvertCycles2us(OS_U32 Cycles) {
  Cycles *= TIMER_PRESCALE;               /* eliminate effect of prescaler */
  return Cycles/(OS_FSYS/1000000);
}

/*********************************************************************
*
*          Communication (UART)
*
**********************************************************************
*/

#if (OS_UART!=-1)
  #if (OS_UART==1)
    #define TX_PENDING       0x0040
    #define RX_PENDING       0x0080
    #define UART_STATUS      __USTAT1
    #define UART_RXBUF       __URXBUF1
    #define UART_TXBUF       __UTXBUF1
    #define UART_LINECON     __ULCON1
    #define UART_CONTROL     __UCON1
    #define UART_BAUD        __UBRDIV1
  #elif (OS_UART==0)
    #define TX_PENDING       0x0010
    #define RX_PENDING       0x0020
    #define UART_STATUS      __USTAT0
    #define UART_RXBUF       __URXBUF0
    #define UART_TXBUF       __UTXBUF0
    #define UART_LINECON     __ULCON0
    #define UART_CONTROL     __UCON0
    #define UART_BAUD        __UBRDIV0
  #endif

  void OS_COM_Init(void) {
    UART_CONTROL = 0x00;
    UART_LINECON = 0x03;
    UART_CONTROL = 0x0d;
    UART_BAUD = (((OS_FSYS/2)/(16*OS_BAUDRATE)-1) << 4);
    __INTMSK &= ~(TX_PENDING | RX_PENDING);
  }

  void OS_ISR_rx(void) {
    if(UART_STATUS&0x20) {
      OS_OnRx(UART_RXBUF);
    }
  }

  void OS_ISR_tx(void) {
    OS_OnTx();
  }

  void OS_COM_Send1(OS_U8 c) {
    UART_TXBUF = c;
  }

#else  /* UART handlers not defined, using dummys */

  void OS_COM_Init(void) {}
  void OS_COM_Send1(OS_U8 c) {
    OS_USEPARA(c);
    OS_COM_ClearTxActive();  /* let OS know that transmitter is not busy */
  }

#endif

/*
**********************************************************************
*
*                    OS_irq_handler
*
**********************************************************************

Purpose:
   Detect reason for IRQ and call correspondig service routine.

Please note:
   If you allow nesting, bits in __INTPND must be cleared before
   calling OS_EnterNestableInterrupt.
*/

void OS_irq_handler(void) {
  int pnd;

  OS_EnterInterrupt();
  OS_USER_irq_func();
  pnd = __INTPND;
#if ((OS_UART == 0) || (OS_UART == 1))
  if (pnd & RX_PENDING) {
    __INTPND = RX_PENDING;
    OS_ISR_rx();
  }
  if (pnd&TX_PENDING) {
    __INTPND = TX_PENDING;
    OS_ISR_tx();
  }
#endif
  if (pnd&TIMER_TICK_PND) {
    __INTPND = TIMER_TICK_PND;
    OS_TickHandler();
  }
  OS_LeaveInterrupt();
}

