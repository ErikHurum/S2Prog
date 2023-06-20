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
File    : RTOSInit_TI_TMS470R1.c

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

#define OS_EXT_CLK 7500000L             // external crystal frequency
#define OS_FSYS    (OS_EXT_CLK * 8)

#define OS_ICLK_DIVIDER 4               // ICLK runs with 1/4 of MCLK

#ifndef   OS_TICK_FREQ
  #define OS_TICK_FREQ (1000)
#endif

#ifndef   OS_PCLK_TIMER
  #define OS_PCLK_TIMER (OS_FSYS / OS_TIMER_PRESCALE)
#endif

#define OS_TIMER_PRESCALE (4)

#define OS_TIMER_RELOAD ((OS_PCLK_TIMER/OS_TICK_FREQ) - 1)
#if (OS_TIMER_RELOAD >= 0x00100000)
  #error "RTI timer can not be used, please check configuration"
#endif

/*********************************************************************
*
*       UART settings for OSView
*       If you do not want (or can not due to hardware limitations)
*       to dedicate a UART to OSView, please define it to be -1
*       Currently the standard code enables UART 0 (SCI1) per default
*/
#ifndef   OS_UART
  #define OS_UART (0)
#endif

#ifndef   OS_PCLK_UART
  #define OS_PCLK_UART (OS_FSYS / OS_ICLK_DIVIDER)
#endif

#ifndef   OS_BAUDRATE
  #define OS_BAUDRATE (38400)
#endif

/****** End of configuration settings *******************************/

#define OS_UART_USED ((OS_UART == 0) || (OS_UART == 1))

/*********************************************************************
*
*       Local defines (sfrs used in RTOSInit.c)
*
**********************************************************************
*/

#ifndef   NUM_INT_SOURCES
  #define NUM_INT_SOURCES  32
#endif
#define _INT_CHANNEL_MASK  0xFF

#define _OS_TIMER_IRQ_ID    CIM_COMP1

/****** Global control register     *********************************/
#define GLBCTRL  (*(volatile OS_U32*) 0xffffffdc)

/****** Peripheral control register *********************************/
#define PCR      (*(volatile OS_U32*) 0xfffffd30)

/****** System exception control registers  *************************/
#define SYSECR   (*(volatile OS_U32*) 0xffffffe0)

/****** Flash control registers     *********************************/

#define FMREGOPT (*(volatile OS_U32*) 0xffe89c00)

#define FMMAC1   (*(volatile OS_U16*) 0xffe8bc02)
#define FMMAC2   (*(volatile OS_U16*) 0xffe8bc06)
#define FMBAC1   (*(volatile OS_U16*) 0xffe88002)
#define FMBAC2   (*(volatile OS_U16*) 0xffe88006)

#define BANK0_ENA      ((unsigned int) 0x00 <<  0)    // 0:2  BANK Enable 0
#define BANK1_ENA      ((unsigned int) 0x01 <<  0)    // 0:2  BANK Enable 1
#define PMPPWR_ACTIVE  ((unsigned int) 0x03 <<  3)    // 4:3  Flash pump fallback power mode
#define BNKPWR_ACTIVE  ((unsigned int) 0x03 <<  0)    // 1:0  Bank power mode
#define PIPELINE_MODE  ((unsigned int) 0x11 <<  0)    // 0:7  Set Pipeline mode
#define ENPIPE         ((unsigned int) 0x1  <<  0)    // 0    Flash pipeline mode enable

#define BSTDBY_MAX     ((unsigned int) 0x06 <<  2)    // 7:2    Bank standby (100nS at 60MHz)
#define BSLEEP_MAX     ((unsigned int) 0x72 <<  8)    // 14:8   Bank sleep (1.9uS at 60MHz)
#define PSTDBY_MAX     ((unsigned int) 0x3C <<  5)    // 15:5   Pump standby (1.0uS at 60MHz)
#define PSLEEP_MAX     ((unsigned int) 0x78 <<  0)    // 14:1   Pump sleep (2.0uS at 60MHz)

/****** Other registers ***********************************************/
#define RTICNTR  (*(volatile OS_U32*) 0xFFFFFF00)
#define RTIPCTL  (*(volatile OS_U32*) 0xFFFFFF04)
#define RTICNTL  (*(volatile OS_U32*) 0xFFFFFF08)
#define RTICMP1  (*(volatile OS_U32*) 0xFFFFFF10)
#define RTICINT  (*(volatile OS_U32*) 0xFFFFFF18)
#define RTICNTEN (*(volatile OS_U32*) 0xFFFFFF1C)
#define IRQIVEC  (*(volatile OS_U32*) 0xFFFFFF20)
#define FIRQPR   (*(volatile OS_U32*) 0xFFFFFF2C)
#define REQMASK  (*(volatile OS_U32*) 0xFFFFFF34)

/****** Bit definitions *********************************************/
#define CMP1FLAG          (1 << 7) //   7, Compare 1 flag
#define PENABLE           (1 << 0) //   0, Peripheral enable
#define CNTEN_NOCNT       (3 << 0) // 1:0, Counter enable No Count
#define CMP1ENA           (1 << 5) //   5, Compare 1 enable
#define CNTEN_UP          (0)      // 1:0, Counter enable User / Privilege
#define TX_ACTION_ENA     (1 << 3) //   3, Tx DMA or interrupt enable
#define RX_ACTION_ENA     (1 << 4) //   4, Rx DMA or interrupt enable
#define SW_NRESET         (1 << 7) //   7, Software reset (active low)
#define RXENA             (1)      //   0, Rx enable
#define TXENA             (1)      //   0, Tx enable
#define CLOCK             (1 << 5) //   5, Internal clock enable
#define RX_FUNC           (1 << 1) //   1, SCIRX pin function
#define TX_FUNC           (1 << 1) //   1, SCITX pin function
#define TIMING_MODE_ASYNC (1 << 4) // Timing Mode
#define CHAR_8            (7)      // Character length control 8
#define CIM_COMP1         (2)      // COMP1 interrupt
#define CIM_SCI1RX        (10)     // SCI1 receive interrupt
#define CIM_SCI1TX        (20)     // SCI1 transmit interrupt
#define CIM_SCI2RX        (17)     // SCI2 receive interrupt
#define CIM_SCI2TX        (26)     // SCI2 transmit interrupt

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
  RTICINT &= ~CMP1FLAG;        // Clear timer interrupt pending condition
  RTICMP1 += OS_TIMER_RELOAD;  // Advance comparator to next interrupt
  // Interrupts might be re-enabled now
  OS_HandleTick();             // Call OS tick handler
#if DEBUG
  DCC_Process();
#endif
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
*       _InitCIM()
*
*       Initialize interrupt controller
*/
static void _InitCIM(void) {
  OS_DI();
  FIRQPR  = 0;        // Assign all sources to IRQ, clear FIQ priority
  REQMASK = 0;        // Disable all Interrupts
  OS_RestoreI();
}

/*********************************************************************
*
*       _InitFlash()
*
*       Initialize Flash module timing
*/
static void _InitFlash(void) {
  //
  // Setup Flash access timing, wait states, enable pipeline mode
  //
  GLBCTRL |= (1 << 4);                                 // Set Flash configuration mode
  FMMAC1   = PSLEEP_MAX;                               // pump sleep to standby time
  FMMAC2   = BANK0_ENA + PMPPWR_ACTIVE + PSTDBY_MAX;   // bank0
  FMBAC1   = BNKPWR_ACTIVE+ BSTDBY_MAX;                // active
  FMBAC2   = PIPELINE_MODE + BSLEEP_MAX;               // 0 wait states
  FMMAC2   = BANK1_ENA + PMPPWR_ACTIVE + PSTDBY_MAX;   // bank1
  FMBAC1   = BNKPWR_ACTIVE+ BSTDBY_MAX;                // active
  FMBAC2   = PIPELINE_MODE + BSLEEP_MAX;               // 0 wait states
  FMREGOPT = ENPIPE;                                   // ENABLE PIPELINE MODE
  GLBCTRL     &= ~(1 << 4);                            // Disable Flash configuration mode
  //
  // Enable peripherals, setup ICLK divider
  //
  PCR      = 0x00;                              // Disable and reset peripherals
  PCR      = ((OS_ICLK_DIVIDER-1) & 0xF) << 1;  // Setup Divider
  PCR     |= 1;                                 // Enable peripherals
  //
  // Initialize PLL, Multiply input frequency by 8
  //
  GLBCTRL &= ~(0x07);      // Clear divider prescaler => MCLK = PLLCLK
  GLBCTRL &= ~(1 << 3);    // Switch PLL multiplier to * 8 mode
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
void OS_InitHW(void) {
  OS_IncDI();                 // Initially disable interrupts
  SYSECR   = 0x00004007;      // Disable illegal address reset

  _InitFlash();
  _InitCIM();                 // Initialize interrupt controller
  PCR |= PENABLE;             // enable peripheral clock
  //
  // Setup OS timer: periodic interrupt using RTI with RTICMP1
  //
  RTICNTEN = CNTEN_NOCNT;                 // Stop counting
  RTICNTR  = 0x00;                        // clear 21-bits CNTR
  // CMP1 used to generate interrupt.
  RTIPCTL  = 0x3;                         // preload 11-bits MOD
  RTICMP1  = OS_TIMER_RELOAD;             //
  RTICNTL  = 0x00;                        // clear and disable tap
  RTICINT  = 0x00;
  RTICINT |= CMP1ENA;
  // Start count, CNTR and MOD will count in both USER and SYSTEM mode
  RTICNTEN = CNTEN_UP;
  /* Install and enable timer interrupt */
  OS_ARM_InstallISRHandler(_OS_TIMER_IRQ_ID, _OS_ISR_Tick);
  OS_ARM_EnableISR(_OS_TIMER_IRQ_ID);

  OS_COM_Init();
  OS_DecRI();
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
void OS_Idle(void) {         /* Idle loop: No task is ready to exec */
  while (1) {
  }
}

/*********************************************************************
*
*       Get time [cycles]
*
*       This routine is required for task-info via OSView or high
*       resolution time measurement functions.
*       It returns the system time in timer clock cycles.
*/
OS_U32 OS_GetTime_Cycles(void) {
  OS_U32 Time;
  int    Count;
  int    Compare;

  Time    = OS_Time;
  Compare = RTICMP1 << 11;
  Count   = RTICNTR & ~((1 << 11) - 1);
  Count   = Compare - Count;

  if (Count < 0) {  // missed a counter interrupt, adjust time
    Time++;
    Count = 0 - Count;
  } else {
    Count = (OS_TIMER_RELOAD << 11) - Count;
  }
  Count >>= 11;
  return (OS_PCLK_TIMER/OS_TICK_FREQ) * Time + Count;
}

/*********************************************************************
*
*       OS_ConvertCycles2us
*
*       Convert Cycles into micro seconds.
*
*       If your timer clock frequency is not a multiple of 1 MHz,
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
  int ISRIndex;

  ISRIndex = (IRQIVEC & 0xFF) - 1;     // Examine current interrupt source (channel number)
  if (ISRIndex >= 0) {
    REQMASK &= ~(1 << ISRIndex);       // Disable pending interrupt source to avoid recursion

#if ALLOW_NESTED_INTERRUPTS
    OS_EnterNestableInterrupt();       // Interrupts may be reenabled now, because pending interrupt was disabled
#else
    OS_EnterInterrupt();               // Inform OS that interrupt handler is running
#endif
    pISR = _apOS_ISRHandler[ISRIndex]; // Read interrupt vector from Table
    if (pISR != NULL) {
      pISR();                          // Call installed interrupt service routine
    } else {
      _OS_ISR_Undefined(ISRIndex);
    }
    REQMASK |= (1 << ISRIndex);        // Re-enable pending interrupt source

#if ALLOW_NESTED_INTERRUPTS
    OS_LeaveNestableInterrupt();       // Perform task switch if required.
#else
    OS_LeaveInterrupt();               // Perform task switch if required.
#endif
  }
}

/*********************************************************************
*
*       OS_ARM_InstallISRHandler
*/
OS_ISR_HANDLER* OS_ARM_InstallISRHandler (int ISRIndex, OS_ISR_HANDLER* pISRHandler) {
  OS_ISR_HANDLER*  pOldHandler;

  pOldHandler = NULL;
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
*/
void OS_ARM_EnableISR(int ISRIndex) {
  OS_DI();
  if (ISRIndex < NUM_INT_SOURCES) {
    REQMASK |= (1 << ISRIndex);
  }
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_DisableISR
*/
void OS_ARM_DisableISR(int ISRIndex) {
  OS_DI();
  if (ISRIndex < NUM_INT_SOURCES) {
    REQMASK &= ~(1 << ISRIndex);
  }
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_ISRSetPrio
*/
int OS_ARM_ISRSetPrio(int ISRIndex, int Prio) {
  /* individual interrupt priorities are not supported by CIM */
  return 0;
}

/*****  UART, used for communication with OSView *****************/

#if OS_UART_USED
  #define _UART0_BASE  (0xFFF7F400)
  #define _UART1_BASE  (0xFFF7F500)
  #define _UART2_BASE  (0xFFF7F600)

  #if (OS_UART == 0)
    #define _OS_UART_BASE     (_UART0_BASE)
    #define _OS_RX_IRQ_ID  (CIM_SCI1RX)
    #define _OS_TX_IRQ_ID  (CIM_SCI1TX)
  #elif (OS_UART == 1)
    #define _OS_UART_BASE     (_UART1_BASE)
    #define _OS_RX_IRQ_ID  (CIM_SCI2RX)
    #define _OS_TX_IRQ_ID  (CIM_SCI2TX)
  #endif

  #define _SCICCR    (*(volatile OS_U8*)(_OS_UART_BASE + 0x03))
  #define _SCICTL1   (*(volatile OS_U8*)(_OS_UART_BASE + 0x07))
  #define _SCICTL2   (*(volatile OS_U8*)(_OS_UART_BASE + 0x0b))
  #define _SCICTL3   (*(volatile OS_U8*)(_OS_UART_BASE + 0x0f))
  #define _SCIRXST   (*(volatile OS_U8*)(_OS_UART_BASE + 0x13))
  #define _SCIHBAUD  (*(volatile OS_U8*)(_OS_UART_BASE + 0x17))
  #define _SCIMBAUD  (*(volatile OS_U8*)(_OS_UART_BASE + 0x1b))
  #define _SCILBAUD  (*(volatile OS_U8*)(_OS_UART_BASE + 0x1f))
  #define _SCIRXBUF  (*(volatile OS_U8*)(_OS_UART_BASE + 0x27))
  #define _SCITXBUF  (*(volatile OS_U8*)(_OS_UART_BASE + 0x2b))
  #define _SCIPC1    (*(volatile OS_U8*)(_OS_UART_BASE + 0x2f))
  #define _SCIPC2    (*(volatile OS_U8*)(_OS_UART_BASE + 0x33))
  #define _SCIPC3    (*(volatile OS_U8*)(_OS_UART_BASE + 0x37))

#define BAUDDIVIDE ((OS_PCLK_UART + OS_BAUDRATE * 4L) / (OS_BAUDRATE*8L)-1)

/*********************************************************************
*
*       OS_COM_ISR_Rx() OS UART interrupt handler for Rx interrupt
*/
static void OS_COM_ISR_Rx(void) {
  OS_U8 Data;
  OS_U8 Status;

  Data   = _SCIRXBUF;
  Status = _SCIRXST;
  if (Status & 0x3F) {          /* Check if errors occurred    */
    _SCIRXST = 0x3F;            /* Clear all errors            */
  } else {
    OS_OnRx(Data);
  }
}

/*********************************************************************
*
*       OS_COM_ISR_Tx() OS UART interrupt handler for Tx interrupt
*/
static void OS_COM_ISR_Tx(void) {
  if (OS_OnTx()) { // no more characters to send?
    _SCICTL3 &= ~TX_ACTION_ENA;              // disable Tx interrrupt
  }
}

/*********************************************************************
*
*       OS_COM_Send1()
*       Never call this function directly from your application
*/
void OS_COM_Send1(OS_U8 c) {
  _SCITXBUF = c;
  _SCICTL3 |= TX_ACTION_ENA;                // enable Tx interrrupt
}

/*********************************************************************
*
*       OS_COM_Init()
*       Initialize UART for OSView
*/
void OS_COM_Init(void) {

  _SCICTL3 &= ~SW_NRESET;                   // Reset SCI state machine
  _SCICCR   = TIMING_MODE_ASYNC + CHAR_8;   // Async, 8-bit Char
  _SCICTL1 |= RXENA;                        // RX enabled
  _SCICTL2 |= TXENA;                        // TX enabled
  _SCICTL3 |= CLOCK + RX_ACTION_ENA;        // Internal clock, enable Rx interrrupt
  _SCIHBAUD = (BAUDDIVIDE >> 16) & 0xFF;
  _SCIMBAUD = (BAUDDIVIDE >> 8)  & 0xFF;
  _SCILBAUD = BAUDDIVIDE & 0xFF;            //
  _SCIPC2  |= RX_FUNC;                      // SCIRX is the SCI receive pin
  _SCIPC3  |= TX_FUNC;                      // SCITX is the SCI transmit pin
  _SCICTL3 |= SW_NRESET;                    // Configure SCI2 state machine
  /* Setup interrupt controller for OS UART */
  OS_ARM_InstallISRHandler(_OS_RX_IRQ_ID, &OS_COM_ISR_Rx);  /* OS UART interrupt handler Rx */
  OS_ARM_InstallISRHandler(_OS_TX_IRQ_ID, &OS_COM_ISR_Tx);  /* OS UART interrupt handler Tx */
  OS_ARM_EnableISR(_OS_RX_IRQ_ID);                          /* Enable OS UART interrupts    */
  OS_ARM_EnableISR(_OS_TX_IRQ_ID);                          /* Enable OS UART interrupts    */
}

#else  /* selected UART not supported, using dummies */
void OS_COM_Init(void) {}
void OS_COM_Send1(OS_U8 c) {
  OS_USEPARA(c);           /* avoid compiler warning */
  OS_COM_ClearTxActive();  /* let the OS know that Tx is not busy */
}

#endif /*  OS_UART_USED  */

/*****  EOF  ********************************************************/
