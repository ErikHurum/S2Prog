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
File   : RTOSInit_ADuC702x.c
Purpose: Initializes and handles the hardware for the OS as far
         as required by the OS.
         Feel free to modify this file acc. to your
         target system.
-------- END-OF-HEADER -----------------------------------------------
*/

#include "RTOS.H"

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
  #define OS_FSYS 41779200       /* maximum speed at fixed pll rate */
#endif

#ifndef   OS_PCLK_TIMER          /* Peripheral clock for timer   */
  #define OS_PCLK_TIMER OS_FSYS  /* defaults to CPU clock        */
#endif

#ifndef   OS_TICK_FREQ
  #define OS_TICK_FREQ 1000
#endif

#define TIMER_PRESCALE  1        /* prescaler for timer frequency */

/*********************************************************************
*
*       UART settings for OSView
*       If you do not want (or can not due to hardware limitations)
*       to dedicate a UART to OSView, please define it to be -1
*       Currently the standard code enables UART 0 per default
*       and supports one UART
*/

#ifndef   OS_UART
  #define OS_UART 0
#endif

#ifndef   OS_BAUDRATE
  #define OS_BAUDRATE 38400
#endif

#ifndef   OS_PCLK_UART              /* Peripheral clock for UART    */
  #define OS_PCLK_UART OS_FSYS      /* defaults to CPU clock        */
#endif                              /*                              */


#define OS_UART_USED (OS_UART == 0)

/*********************************************************************
*
*       Local defines (sfrs used in RTOSInit.c)
*
**********************************************************************
*/

/****** Timer 0 *****************************************************/

#define T0LD        (*(volatile unsigned long *) 0xFFFF0300)
#define T0VAL       (*(volatile unsigned long *) 0xFFFF0304)
#define T0CON       (*(volatile unsigned long *) 0xFFFF0308)
#define T0CLRI      (*(volatile unsigned long *) 0xFFFF030C)

/****** Interrupt control *******************************************/

#define IRQSTA      (*(volatile unsigned long *) 0xFFFF0000)
#define IRQSIG      (*(volatile unsigned long *) 0xFFFF0004)
#define IRQEN       (*(volatile unsigned long *) 0xFFFF0008)
#define IRQCLR      (*(volatile unsigned long *) 0xFFFF000C)


/****** Power and PLL ontrol ****************************************/

#define POWKEY1     (*(volatile unsigned long *) 0xFFFF0404)
#define POWCON      (*(volatile unsigned long *) 0xFFFF0408)
#define POWKEY2     (*(volatile unsigned long *) 0xFFFF040C)

#define PLLKEY1     (*(volatile unsigned long *) 0xFFFF0410)
#define PLLCON      (*(volatile unsigned long *) 0xFFFF0414)
#define PLLKEY2     (*(volatile unsigned long *) 0xFFFF0418)

/*  Definiton of sfrs assigned to UART used for OSView */

#if OS_UART_USED
  #define COMSTA0   (*(volatile unsigned long *) 0xFFFF0714)
  #define COMRX     (*(volatile unsigned long *) 0xFFFF0700)
  #define COMTX     (*(volatile unsigned long *) 0xFFFF0700)

  #define COMIEN0   (*(volatile unsigned long *) 0xFFFF0704)
  #define COMIID0   (*(volatile unsigned long *) 0xFFFF0708)
  #define COMCON0   (*(volatile unsigned long *) 0xFFFF070C)
  #define COMCON1   (*(volatile unsigned long *) 0xFFFF0710)
  #define COMDIV0   (*(volatile unsigned long *) 0xFFFF0700)
  #define COMDIV1   (*(volatile unsigned long *) 0xFFFF0704)
  #define COMDIV2   (*(volatile unsigned long *) 0xFFFF072C)

  #define GP1CON    (*(volatile unsigned long *) 0xFFFFF404)

#endif

/****** interrupt sources and peripheral IDs ************************/

#define SWI_ID_BIT    1
#define TIMER0_ID_BIT 2
#define TIMER1_ID_BIT 3
#define UART_ID_BIT   14

#define TIMER0_ID_MASK ( 1 << TIMER0_ID_BIT)
#define UART_ID_MASK   ( 1 << UART_ID_BIT)

#define OS_TIMER_TICK_PENDING_MASK ( 1 << TIMER0_ID_BIT)
#define OS_UART_INT_PENDING_MASK   ( 1 << UART_ID_BIT)

#define OS_RX_ERROR_INT_STAT   (0x06)
#define OS_RX_INT_STAT         (0x04)
#define OS_TX_INT_STAT         (0x02)
#define OS_UART_NO_INT_PENDING (0x01)

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/


/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/

#if OS_UART_USED
/*********************************************************************
*
*       _OS_UART_ISR_Handler
*/
static void _OS_UART_ISR_Handler(void) {
  OS_U32 IntStat;
  volatile OS_U32 Dummy;

  do {
    IntStat = COMIID0;
    switch (IntStat) {
    case OS_RX_INT_STAT:
      OS_OnRx(COMRX);    // Process data
      break;
    case OS_TX_INT_STAT:
      OS_OnTx();
      break;
    case OS_RX_ERROR_INT_STAT:
      Dummy = COMSTA0;  // Read Line state to clear interrupt
      Dummy = COMRX;    // Clear Rx Buffer
      break;
    }
  } while (IntStat != OS_UART_NO_INT_PENDING);
}
#endif /* OS_UART_USED */

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
void OS_InitHW(void) {
  #define TIMER_RELOAD       OS_PCLK_TIMER/TIMER_PRESCALE/OS_TICK_FREQ
  OS_DI();
  IRQCLR = 0xFFFFFFFF;     // Initially disable all interrupts

  T0CON  = 0;              // Initially disable timer
  T0LD   = TIMER_RELOAD;   // initialize time constant
  T0CON  = 0               // Initialize timer
         | (1 << 7)        // Enable Timer
         | (1 << 6)        // in periodic mode
         | (0 << 4)        // bits 5 and 4 reserved, write 0
         | (0 << 2)        // bits 3 and 2: 00 => runs at core clock
         ;                 // bits 1 and 0 reserved, write 0
  T0CLRI = 0;              // Clear timer interrupt
  IRQEN |= TIMER0_ID_MASK; // Enable timer interrupt
  OS_COM_Init();
  OS_RestoreI();
}

/*********************************************************************
*
*       _InitPLL
*
* Function description
*   Initialize main clock and PLL
*   Called from startup code; Should be called as early as possible
*   in order to keep boot time short
*/
static void _InitPLL(void) {
  /* Init PLL */
  PLLKEY1 = 0xAA;    /* Unlock PLL configuration register   */
  PLLCON  = 0x01;    /* Normal mode, use ext. crystal       */
  PLLKEY2 = 0x55;    /* Write configuration                 */

  POWKEY1 = 0x01;    /* Unlock power configuration register */
  POWCON  = 0        /* Select div1 = full speed            */
          | (1 << 3) /* FINT allways at full speed          */
          | (0 << 4) /* Normal mode (not power down)        */
          ;
  POWKEY2 = 0xF4;    /* Write configuration                 */
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
void OS_Idle(void) { /* Idle loop: No task is ready to exec */
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
#define HW_TIMER_INTERRUPT_PENDING() (IRQSTA & OS_TIMER_TICK_PENDING_MASK)

OS_U32 OS_GetTime_Cycles(void) {
  unsigned int t_cnt;
  OS_U32 time;

  t_cnt = TIMER_RELOAD - T0VAL;
  time  = OS_Time;
  if (HW_TIMER_INTERRUPT_PENDING()) {
    t_cnt = TIMER_RELOAD - T0VAL;
    time++;
  }
  return (OS_PCLK_TIMER/TIMER_PRESCALE/OS_TICK_FREQ) * time  + t_cnt;
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
*       measurement only. It does not affect operation of the the OS.
*/
OS_U32 OS_ConvertCycles2us(OS_U32 Cycles) {
  Cycles *= TIMER_PRESCALE;               /* eliminate effect of prescaler */
  return Cycles/(OS_PCLK_TIMER/1000000);
}

#if OS_UART_USED
/*********************************************************************
*
*       Communication for OSView via UART0 or UART1 (optional)
*
**********************************************************************
*/

/*********************************************************************
*
*       OS_COM_Init()
*       Initialize UART for OSView
*/
void OS_COM_Init(void) {
  #define _BAUDDIVIDE  ((OS_PCLK_UART + (OS_BAUDRATE*16L)) / (OS_BAUDRATE*32L))
  volatile char Dummy;
  //
  //  Initialize P1.0 and P1.1 as SIN and SOUT
  //
  GP1CON &= 0xFFFFFF00;    // Mask configuration for P1.0 and P1.1
  GP1CON |= ((0x01 << 0) | (0x01 << 4));  // Set P1.0 to SIN function, Set P1.1 to SOUT function
  //
  //  Disable all UART interrupts
  //
  COMIEN0 = 0;
  //
  //  Initialize Baudrate generator
  //
  COMCON0 |= (1 << 7);   // Enable access to divisor latch
  COMDIV0  =  (_BAUDDIVIDE & 0xFF);
  COMDIV1  = ((_BAUDDIVIDE >> 8) & 0xFF);
  COMDIV2  = 0;          // Disable fractional baudrate divider
  COMCON0 &= ~(1 << 7);
  //
  //  Initialize Data-Format 8N1
  //
  COMCON0  = 0x3         // 3 => 8 data bits
           | (0 << 2)    // 1 Stop bit
           | (0 << 3)    // Parity disabled
           | (0 << 4)    // ODD parity; don't care if parity is disabled
           | (0 << 5)    // Stick parity; don't care if parity is disabled
           | (0 << 6)    // Normal mode (no Break)
           | (0 << 7)    // Access Rx and Tx data registers
           ;
  COMCON1  = 0           //
           | (0 << 0)    // DTR passive
           | (0 << 1)    // RTS passive
           | (0 << 2)    // undefined
           | (0 << 3)    // undefined
           | (0 << 4)    // Loopback disabled
           | (0 << 5)    // reserved
           | (0 << 6)    // reserved
           | (0 << 7)    // reserved
           ;
  //
  //  Clear all UART erros
  //
  Dummy = COMRX;
  Dummy = COMSTA0;      // Read Line state to clear error
  //
  // Finally enable UART interrupts
  //
  COMIEN0 = 0
          | (1 << 0)    // Enable Rx interrupt
          | (1 << 1)    // Enable Tx interrupt
          | (1 << 2)    // Enable Rx error (Line Status) interrupt
          ;

  IRQEN |= UART_ID_MASK; // Enable UART interrupt
}

/*********************************************************************
*
*       OS_COM_Send1()
*       Never call this function directly from your application
*/
void OS_COM_Send1(OS_U8 c) {
  COMTX = c;
}

/*********************************************************************
*
*       Communication for OSView not selected
*
**********************************************************************
*/

#else  /* No communication routines required, use dummies  */
  void OS_COM_Init(void) {}
  void OS_COM_Send1(OS_U8 c) {
    OS_USEPARA(c);
    OS_COM_ClearTxActive();  /* Free OS transmitter buffer */
  }
#endif /* OS_UART_USED */

/*********************************************************************
*
*       OS_irq_handler
*
*       Detect reason for IRQ and call correspondig service routine.
*       OS_irq_handler is called from OS_IRQ_SERVICE function
*       found in RTOSVect.asm
*/
OS_INTERWORK void OS_irq_handler(void) {
  int IntStat;

#if ALLOW_NESTED_INTERRUPTS
  OS_EnterNestableInterrupt();                   // Now interrupts may be reenabled. If nesting should be allowed
#else
  OS_EnterInterrupt();                           // Inform OS that interrupt handler is running
#endif
  IntStat = IRQSTA;
  OS_USER_irq_func();
  #if OS_UART_USED
    if (IntStat & OS_UART_INT_PENDING_MASK) {
      _OS_UART_ISR_Handler();
    }
  #endif /* OS_UART_USED */
  if (IntStat & OS_TIMER_TICK_PENDING_MASK) {
    T0CLRI = 0;                 /* clear timer interrupt    */
    OS_HandleTick();            /* OS timer tick handler    */
  }
#if ALLOW_NESTED_INTERRUPTS
  OS_LeaveNestableInterrupt();                   // Leave nestable interrupt, perform task switch if required
#else
  OS_LeaveInterrupt();                           // Leave interrupt, perform task switch if required
#endif
}

/*********************************************************************
*
*       OS_USER_irq_func()
*
*       Application specific interrupts have to be handled here
*       This function is called from the OS IRQ handler
*/
void OS_USER_irq_func(void) {
}

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
  return 1;                            // Always initialize segments !
};

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

