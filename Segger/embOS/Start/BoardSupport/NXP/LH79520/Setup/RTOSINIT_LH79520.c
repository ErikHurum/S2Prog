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
File    : RTOSInit_LH79520.c  (for NXP LH79520 CPU)
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
*       MMU and cache settings
*/
#ifndef   OS_USE_MMU
  #define OS_USE_MMU (1)
#endif

/*********************************************************************
*
*       SDRAM initialization and run option
*/
#ifndef   COPY_CODE_TO_SDRAM
  #define COPY_CODE_TO_SDRAM  1
#endif

#define SDRAM_BASE_ADDR  0x20000000

/*********************************************************************
*
*       Clock frequency settings
*/

#ifndef   OS_FSYS
  #define OS_FSYS        51609600L
#endif

#ifndef   OS_PCLK_TIMER
  #define OS_PCLK_TIMER  OS_FSYS   // Peripheral clock frequency for timer
#endif

#ifndef   OS_PCLK_UART
  #define OS_PCLK_UART   14745600L // Peripheral clock frequency for UART
#endif

#ifndef   OS_TICK_FREQ
  #define OS_TICK_FREQ 1000
#endif

#define _OS_TIMER_PRESCALE 1       // prescaler for timer frequency

/*********************************************************************
*
*       UART settings for OSView
*       If you do not want (or can not due to hardware limitations)
*       to dedicate a UART to OSView, please define it to be -1
*       Currently the standard code enables UART 1 per default
*       and supports UART0 to UART2
*/
#ifndef   OS_UART
  #define OS_UART 1
#endif

#ifndef   OS_BAUDRATE
  #define OS_BAUDRATE 38400
#endif

/****** End of configuration settings *******************************/

#define _OS_TIMER_RELOAD OS_PCLK_TIMER / _OS_TIMER_PRESCALE / OS_TICK_FREQ

#define _OS_UART_USED ((OS_UART == 0) || (OS_UART == 1) || (OS_UART == 2))
#define _BAUD_INT_PART   (OS_PCLK_UART / (16 * OS_BAUDRATE))
#define _BAUD_FRAC_PART  (((((OS_PCLK_UART * 8) / OS_BAUDRATE) + 1) / 2) & 0x3F)

/*********************************************************************
*
*       Local defines (sfrs used in RTOSInit.c)
*
**********************************************************************
*/

/*****  Timer *******************************************************/
#define _TIMER0_BASE_ADDR  0xFFFC4000
#define _TIMER1_BASE_ADDR  0xFFFC4000
#define _TIMER2_BASE_ADDR  0xFFFC4000
#define _TIMER3_BASE_ADDR  0xFFFC4000

#define _TIMER_OFF_LOAD    (0x0000)
#define _TIMER_OFF_VALUE   (0x0004)
#define _TIMER_OFF_CONTROL (0x0008)
#define _TIMER_OFF_CLEAR   (0x000C)

/* Interrupt identifiers (number of input to interrupt controller)  */
#define _TIMER0_INT_ID    17
#define _TIMER1_INT_ID    18
#define _TIMER2_INT_ID    19
#define _TIMER3_INT_ID    20

#define _OS_TIMER_BASE_ADDR    _TIMER0_BASE_ADDR

#define _OS_TIMER_LOAD     *(volatile OS_U32*)(_OS_TIMER_BASE_ADDR + _TIMER_OFF_LOAD)
#define _OS_TIMER_VALUE    *(volatile OS_U32*)(_OS_TIMER_BASE_ADDR + _TIMER_OFF_VALUE)
#define _OS_TIMER_CONTROL  *(volatile OS_U32*)(_OS_TIMER_BASE_ADDR + _TIMER_OFF_CONTROL)
#define _OS_TIMER_CLEAR    *(volatile OS_U32*)(_OS_TIMER_BASE_ADDR + _TIMER_OFF_CLEAR)

/****** assign timer used for OS *********************************/

#if   (_OS_TIMER_BASE_ADDR == _TIMER0_BASE_ADDR)
  #define _OS_TIMER_INT_ID  _TIMER0_INT_ID
  #define _OS_TIMER_CLK_BIT 4
#elif (_OS_TIMER_BASE_ADDR == _TIMER1_BASE_ADDR)
  #define _OS_TIMER_INT_ID  _TIMER1_INT_ID
  #define _OS_TIMER_CLK_BIT 4
#elif (_OS_TIMER_BASE_ADDR == _TIMER2_BASE_ADDR)
  #define _OS_TIMER_INT_ID  _TIMER2_INT_ID
  #define _OS_TIMER_CLK_BIT 5
#elif (_OS_TIMER_BASE_ADDR == _TIMER3_BASE_ADDR)
  #define _OS_TIMER_INT_ID  _TIMER3_INT_ID
  #define _OS_TIMER_CLK_BIT 5
#endif

/* INPUT/OUTPUT CONTROL */
#define _IOCONBASE   0xFFFE5000
#define _MEMMUX      *(volatile OS_U32*)(_IOCONBASE + 0x0000)
#define _LCDMUX      *(volatile OS_U32*)(_IOCONBASE + 0x0004)
#define _MISCMUX     *(volatile OS_U32*)(_IOCONBASE + 0x0008)
#define _DMAMUX      *(volatile OS_U32*)(_IOCONBASE + 0x000C)
#define _UARTMUX     *(volatile OS_U32*)(_IOCONBASE + 0x0010)
#define _SSPMUX      *(volatile OS_U32*)(_IOCONBASE + 0x0014)

/****** UART ********************************************************/

#define _UART0_BASE_ADDR  0x0FFFC0000
#define _UART1_BASE_ADDR  0x0FFFC1000
#define _UART2_BASE_ADDR  0x0FFFC2000

#define _UART_DR_OFFS     0x0000
#define _UART_RSR_OFFS    0x0004
#define _UART_ECR_OFFS    0x0004
#define _UART_FR_OFFS     0x0018
#define _UART_IBRD_OFFS   0x0024
#define _UART_FBRD_OFFS   0x0028
#define _UART_LCR_H_OFFS  0x002C
#define _UART_CR_OFFS     0x0030
#define _UART_IFLS_OFFS   0x0034
#define _UART_IMSC_OFFS   0x0038
#define _UART_RIS_OFFS    0x003C
#define _UART_MIS_OFFS    0x0040
#define _UART_ICR_OFFS    0x0044

/****** Assign UART sfrs used for OSView communication ***********/

#if _OS_UART_USED
  #if   (OS_UART == 0)
    #define _OS_UART_BASE_ADDR _UART0_BASE_ADDR
    #define _OS_UART_CLK_BIT 0
    #define _OS_UART_ID   23
    #define _OS_UART_MUX _UARTMUX
    #define _OS_UART_MUX_MASK  ((1 << 1) | (1 << 0))
    #define _OS_UART_MUX_VALUE ((1 << 1) | (1 << 0))
  #elif (OS_UART == 1)
    #define _OS_UART_BASE_ADDR _UART1_BASE_ADDR
    #define _OS_UART_CLK_BIT 1
    #define _OS_UART_ID   24
    #define _OS_UART_MUX _UARTMUX
    #define _OS_UART_MUX_MASK  ((1 << 3) | (1 << 2))
    #define _OS_UART_MUX_VALUE ((1 << 3) | (1 << 2))
  #elif (OS_UART == 2)
    #define _OS_UART_BASE_ADDR _UART2_BASE_ADDR
    #define _OS_UART_CLK_BIT 2
    #define _OS_UART_ID   25
    #define _OS_UART_MUX _SSPMUX
    #define _OS_UART_MUX_MASK  ((1 << 1) | (1 << 0))
    #define _OS_UART_MUX_VALUE ((1 << 1) | (1 << 0))
  #endif

  #define _OS_UART_DR    *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_DR_OFFS)
  #define _OS_UART_RSR   *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_RSR_OFFS)
  #define _OS_UART_ECR   *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_ECR_OFFS)
  #define _OS_UART_FR    *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_FR_OFFS)
  #define _OS_UART_IBRD  *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_IBRD_OFFS)
  #define _OS_UART_FBRD  *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_FBRD_OFFS)
  #define _OS_UART_LCR_H *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_LCR_H_OFFS)
  #define _OS_UART_CR    *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_CR_OFFS)
  #define _OS_UART_IFLS  *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_IFLS_OFFS)
  #define _OS_UART_IMSC  *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_IMSC_OFFS)
  #define _OS_UART_RIS   *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_RIS_OFFS)
  #define _OS_UART_MIS   *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_MIS_OFFS)
  #define _OS_UART_ICR   *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_ICR_OFFS)
#endif

/* STATIC MEMORY CONTROLLER */
#define _SMCREGBASE  0xFFFF1000
#define _SMCBCR0         *(volatile OS_U32*)(_SMCREGBASE + 0x0000)
#define _SMCBCR1         *(volatile OS_U32*)(_SMCREGBASE + 0x0004)
#define _SMCBCR2         *(volatile OS_U32*)(_SMCREGBASE + 0x0008)
#define _SMCBCR3         *(volatile OS_U32*)(_SMCREGBASE + 0x000C)
#define _SMCBCR4         *(volatile OS_U32*)(_SMCREGBASE + 0x0010)
#define _SMCBCR5         *(volatile OS_U32*)(_SMCREGBASE + 0x0014)
#define _SMCBCR6         *(volatile OS_U32*)(_SMCREGBASE + 0x0018)

/* SYNCHRONOUS DYNAMIC RAM CONTROLLER */
#define _SDRAMBASE  0xFFFF2000
#define _SDRCCONFIG0     *(volatile OS_U32*)(_SDRAMBASE + 0x0000)
#define _SDRCCONFIG1     *(volatile OS_U32*)(_SDRAMBASE + 0x0004)
#define _SDRCREFTIMER    *(volatile OS_U32*)(_SDRAMBASE + 0x0008)
#define _SDRCWBTIMEOUT   *(volatile OS_U32*)(_SDRAMBASE + 0x000C)

/* RESET, CLOCK AND POWER CONTROLLER */
#define _RCPCBASE  0xFFFE2000
#define _RCPCCTRL         *(volatile OS_U32*)(_RCPCBASE + 0x0000)
#define _REMAPCTRL        *(volatile OS_U32*)(_RCPCBASE + 0x0008)
#define _SOFTRESET        *(volatile OS_U32*)(_RCPCBASE + 0x000C)
#define _RESETSTATUS      *(volatile OS_U32*)(_RCPCBASE + 0x0010)
#define _RESETSTATUSCLEAR *(volatile OS_U32*)(_RCPCBASE + 0x0014)
#define _HCLKPRESCALE     *(volatile OS_U32*)(_RCPCBASE + 0x0018)
#define _CPUCLKPRESCALE   *(volatile OS_U32*)(_RCPCBASE + 0x001C)
#define _PERIPHCLKCTRL    *(volatile OS_U32*)(_RCPCBASE + 0x0024)
#define _PERIPHCLKCTRL2   *(volatile OS_U32*)(_RCPCBASE + 0x0028)
#define _AHBCLKCTRL       *(volatile OS_U32*)(_RCPCBASE + 0x002C)
#define _PERPIHCLKSELECT  *(volatile OS_U32*)(_RCPCBASE + 0x0030)
#define _PERIPHCLKSELECT2 *(volatile OS_U32*)(_RCPCBASE + 0x0034)
#define _PWM0PRESCALE     *(volatile OS_U32*)(_RCPCBASE + 0x0038)
#define _PWM1PRESCALE     *(volatile OS_U32*)(_RCPCBASE + 0x003C)
#define _LCDCLKPRESCALE   *(volatile OS_U32*)(_RCPCBASE + 0x0040)
#define _SSPCLKPRESCALE   *(volatile OS_U32*)(_RCPCBASE + 0x0044)
#define _INTCONFIG        *(volatile OS_U32*)(_RCPCBASE + 0x0080)
#define _INTCLEAR         *(volatile OS_U32*)(_RCPCBASE + 0x0084)
#define _CORECLKCONFIG    *(volatile OS_U32*)(_RCPCBASE + 0x0088)

/****** Vectored interrupt controller (VIC) *************************/

#define _VIC_BASE_ADDR  0xFFFFF000

#define _VIC_IRQSTATUS       *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x0000)
#define _VIC_FIQSTATUS       *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x0004)
#define _VIC_RAWINTERRUPT    *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x0008)
#define _VIC_INTSELECT       *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x000C)
#define _VIC_INTENABLE       *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x0010)
#define _VIC_INTENABLECLEAR  *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x0014)
#define _VIC_SOFTINT         *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x0018)
#define _VIC_SOFTINTCLEAR    *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x001C)
#define _VIC_VECTORADDR      *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x0030)
#define _VIC_DEFVECTADDR     *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x0034)

#define _VIC_VECT_BASE_ADDR       *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x0100)
#define _VIC_VECTCNTL_BASE_ADDR   *(volatile OS_U32*)(_VIC_BASE_ADDR + 0x0200)

#define _NUM_INT_SOURCES  32      // Maximum number of sources. Specific devices may support less
#define _INT_SOURCE_MASK  0x1F

#ifndef   _NUM_INT_VECTORS
  #define _NUM_INT_VECTORS  16
#endif

/* Configuration of interrupts used by OS ************************/

#define _OS_TIMER_INT_INDEX    15 // Assign to lowest priority interrupt channel
#define _OS_UART_INT_INDEX     14 // Assign to low priority interrupt channel

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

#if OS_USE_MMU
// #include "MMU.h"
#pragma data_alignment=16384
#pragma location="MMU_TABLE"
__no_init unsigned int _TranslationTable [0x1000];
#endif  /* OS_USE_MMU */

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/

/*********************************************************************
*
*       _Init_VIC()
*
* Function description
*   Clears and disables all interrut vectors in VIC.
*/
static void _Init_VIC(void) {
  int Index;

  _VIC_INTENABLECLEAR = 0xFFFFFFFF;            // Disable all source interrupts
  _VIC_VECTORADDR     = 0;                     // Write to vector, reset VIC
  for (Index = 0; Index < _NUM_INT_VECTORS; Index++) {
    OS_ARM_DisableISR(Index);                  // Disable channel
    OS_ARM_AssignISRSource(Index, 0);          // Assign to hardware channel 0
    OS_ARM_InstallISRHandler(Index, NULL);     // Set vector to 0;
  }
  _VIC_SOFTINTCLEAR   = 0xFFFFFFFF;            // Disable all soft interrupts
  _VIC_INTSELECT      = 0;                     // Set all channels to generate IRQ
  _VIC_DEFVECTADDR    = 0;                     // Set default vector to 0
}

/*********************************************************************
*
*       OS_Tick interrupt Handler
*/
static void _OS_ISR_Tick (void) {
  _OS_TIMER_CLEAR = 0;      // Clear timer interrupt
  OS_HandleTick();          // Call OS tick handler
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
static void _OS_ISR_Undefined(void) {
  #if (OS_IGNORE_UNDEFINED_INTERRUPT == 0)
    volatile int Dummy;
    Dummy = 1;
    /* You may set a breakpoint here to detect undefined interrupts */
    while (Dummy > 0) {
    }
  #endif
}

#if _OS_UART_USED
/*********************************************************************
*
*       _ISR_UART() OS gerneral UART interrupt handler
*/
#define RX_PENDING     (1 << 4)
#define TX_PENDING     (1 << 5)
#define RX_TIMEOUT     (1 << 6)
#define RX_FIFO_EMPTY  (1 << 4)
#define TX_FIFO_EMPTY  (1 << 7)

static void _OS_ISR_UART(void) {
  OS_U8 Pending;
  Pending = _OS_UART_MIS;
  do {
    if ((Pending & (RX_PENDING | RX_TIMEOUT)) != 0) {
      _OS_UART_ICR  = (RX_PENDING | RX_TIMEOUT);    /* reset interrupts */
      do {
        OS_U8 RxData, RxError;
        RxData   = _OS_UART_DR & 0xff;
        RxError  = _OS_UART_RSR;
        if (RxError) {
          _OS_UART_ECR = 0;          /* Clear all errors */
        } else {
          OS_OnRx(RxData);
        }
      } while ((_OS_UART_FR & RX_FIFO_EMPTY) == 0);
    }
    if (Pending & TX_PENDING) {
      _OS_UART_ICR  = TX_PENDING;    /* reset interrupt  */
      if (OS_OnTx()) {
        /*  No more bytes sent, disable tx interrupt   */
        /*  Will be re-enabled in OS_COM_Send1()       */
        _OS_UART_IMSC &= ~TX_PENDING;
      }
    }
    Pending = _OS_UART_MIS & (RX_PENDING | TX_PENDING | RX_TIMEOUT);
  } while (Pending);          /* Handle all interrupts */
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
void OS_InitHW(void) {
  OS_DI();
  _Init_VIC();                                    // Initialize VIC, clear and disable all interrupts
  // Initialize OS timer
  _OS_TIMER_CONTROL  = 0;                         // Disable timer
  _PERIPHCLKCTRL    &= ~(1 << _OS_TIMER_CLK_BIT); // Enable peripheral clock for timer 0 and 1
  _OS_TIMER_CONTROL  = 0                          // Disable timer, not cascaded and prescale = 1
                     |( 1 << 6)                   // Periodic mode
                     ;
  _OS_TIMER_LOAD     = _OS_TIMER_RELOAD;          // Set reload value
  _OS_TIMER_CLEAR = 0x00;                         // Clears timer/counter interrupt.
  _OS_TIMER_CONTROL |=  (1 << 7);                 // Enable timer.
  // Setup interrupt controller
  OS_ARM_InstallISRHandler(_OS_TIMER_INT_INDEX, &_OS_ISR_Tick); // Timer/counter interrupt vector.
  OS_ARM_AssignISRSource(_OS_TIMER_INT_INDEX, _OS_TIMER_INT_ID);
  OS_ARM_EnableISR(_OS_TIMER_INT_INDEX);                        // Enable timer/counter 0 interrupt.
  OS_ARM_EnableISRSource(_OS_TIMER_INT_ID);                     // Enable timer/counter 0 interrupt.
  OS_COM_Init();                                                // initialize UART for OSView
  OS_RestoreI();
}

#if (_OS_TIMER_PRESCALE != 1)
  #error "OS_InitHW() is written for a prescaler of 4 and has to be modified"
#endif

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
*       resolution time management functions.
*       It returns the system time in timer clock cycles.
*/
OS_U32 OS_GetTime_Cycles(void) {
  unsigned int t_cnt;
  OS_U32   time;

  t_cnt = _OS_TIMER_VALUE;                             // Read current timer value
  time  = OS_GetTime32();                              // Read current OS time
  if (_VIC_RAWINTERRUPT & (1 << _OS_TIMER_INT_ID)) {   // Timer Interrupt pending ?
    t_cnt = _OS_TIMER_VALUE;                           // Adjust result
    time++;
  }
  return _OS_TIMER_RELOAD * time - t_cnt;
}

/*********************************************************************
*
*       OS_ConvertCycles2us
*
*       Convert Cycles into micro seconds. (For profiling only)
*
*       If your clock frequency is not a multiple of 1 MHz,
*       you may have to modify this routine in order to get proper
*       diagonstics.
*
*       This routine is required for profiling only.
*       It does not affect operation of the OS.
*/
OS_U32 OS_ConvertCycles2us(OS_U32 Cycles) {
  Cycles *= _OS_TIMER_PRESCALE;              // eliminate effect of prescaler
  return Cycles/(OS_PCLK_TIMER/1000000);
}

/*********************************************************************
*
*       OS_irq_handler
*
*       Detect reason for IRQ and call correspondig service routine.
*       OS_irq-handler is called from OS_IRQ_SERVICE function
*       found in RTOSVect.asm
*/
OS_INTERWORK void OS_irq_handler(void) {
  OS_ISR_HANDLER* pISR;
  pISR = (OS_ISR_HANDLER*) _VIC_VECTORADDR;  // Get current interrupt handler
#if ALLOW_NESTED_INTERRUPTS
  OS_EnterNestableInterrupt();               // Now interrupts may be reenabled. If nesting should be allowed
#else
  OS_EnterInterrupt();                       // Inform OS that interrupt handler is running
#endif
  if (pISR != NULL) {
    pISR();                                  // Call installed interrupt service routine
  } else {
    _OS_ISR_Undefined();
  }
  OS_DI();                                   // Disable interrupts and unlock
  _VIC_VECTORADDR = 0;                       // Clear current interrupt pending condition, reset VIC
#if ALLOW_NESTED_INTERRUPTS
  OS_LeaveNestableInterrupt();               // Leave nestable interrupt, perform task switch if required
#else
  OS_LeaveInterrupt();                       // Leave interrupt, perform task switch if required
#endif
}

/*********************************************************************
*
*       Communication for OSView via UART (optional)
*
**********************************************************************
*/

#if (_OS_UART_USED)
/*********************************************************************
*
*       OS_COM_Send1()
*       Never call this function directly from your application
*/
void OS_COM_Send1(OS_U8 c) {
  _OS_UART_DR    = c;
  _OS_UART_IMSC |= (1 << 5);
}

/*********************************************************************
*
*       OS_COM_Init()
*       Initialize UART for OSView
*/
void OS_COM_Init(void) {  // Initialize UART, enable UART interrupts
  _OS_UART_CR          = 0;                         // Disable UART
  OS_ARM_DisableISRSource(_OS_UART_ID);             // Disable UART interrupts

  _OS_UART_MUX        &= ~_OS_UART_MUX_MASK;        // Reset I/O configuration for UART
  _OS_UART_MUX        |= _OS_UART_MUX_VALUE;        // Select I/O configuration for UART

  _UARTMUX            = 0x0f;

  _PERIPHCLKCTRL     &= ~(1 << _OS_UART_CLK_BIT);   // Enable UART clock
  _PERPIHCLKSELECT   &= ~(1 << _OS_UART_CLK_BIT);   // Use crystal clock (14.7456 MHz)

  _OS_UART_IBRD        = _BAUD_INT_PART;            // Set baudrate
  _OS_UART_FBRD        = _BAUD_FRAC_PART;
  _OS_UART_LCR_H       = (0 << 4)                   // Disable FIFO
                       | (1 << 5)                   // Set 8bit data
                       | (1 << 6);                  // Set 8bit data
  _OS_UART_IFLS        = (1 << 0)                   // TX Fifo size
                       | (1 << 3);                  // RX Fifo size
  _OS_UART_ICR         = 0x7FF;                     // Clear any pending interrupts

  OS_ARM_InstallISRHandler (_OS_UART_INT_INDEX, &_OS_ISR_UART);
  OS_ARM_AssignISRSource(_OS_UART_INT_INDEX, _OS_UART_ID);  // Assign priority (Index) to input
  OS_ARM_EnableISR(_OS_UART_INT_INDEX);             // Enable UART interrupt.
  OS_ARM_EnableISRSource(_OS_UART_ID);              // Enable UART interrupt.

  _OS_UART_IMSC        = (1 << 4)                   // Enable receive interrupt
                       | (1 << 5)                   // Enable transmit interrupt
                       | (1 << 6)
                       ;                            // Enable runtime error

  _OS_UART_CR          = (1 << 9)                   // Enable UART receive
                       | (1 << 8)                   // Enable UART transmit
                       | (1 << 0);                  // Enable UART
}

#else  /* selected UART not supported, using dummies */

void OS_COM_Init(void) {}
void OS_COM_Send1(OS_U8 c) {
  OS_USEPARA(c);           // avoid compiler warning
  OS_COM_ClearTxActive();  // let the OS know that Tx is not busy
}

#endif /*  (OS_UART_USED) */

/*********************************************************************
*
*       OS_ARM_InstallISRHandler
*/
OS_ISR_HANDLER* OS_ARM_InstallISRHandler (int ISRIndex, OS_ISR_HANDLER* pISRHandler) {
  OS_ISR_HANDLER*  pOldHandler;
  OS_ISR_HANDLER** papISR;

#if DEBUG
  if ((unsigned)ISRIndex >= _NUM_INT_VECTORS) {
    OS_Error(OS_ERR_ISR_INDEX);
    return NULL;
  }
#endif
  OS_DI();
  papISR = (OS_ISR_HANDLER**) &_VIC_VECT_BASE_ADDR;
  pOldHandler          = *(papISR + ISRIndex);
  *(papISR + ISRIndex) = pISRHandler;
  OS_RestoreI();
  return pOldHandler;
}

/*********************************************************************
*
*       OS_ARM_AssignISRSource
*/
void OS_ARM_AssignISRSource(int ISRIndex, int Source) {
  OS_U32* pCntlRegister;
  OS_U32 ControlReg;
  pCntlRegister = (OS_U32*) &_VIC_VECTCNTL_BASE_ADDR;

#if DEBUG
  if ((unsigned)ISRIndex >= _NUM_INT_VECTORS) {
    OS_Error(OS_ERR_ISR_INDEX);
    return;
  }
#endif
  OS_DI();
  ControlReg  = *(pCntlRegister + ISRIndex) & ~_INT_SOURCE_MASK;
  *(pCntlRegister + ISRIndex) = (ControlReg | (Source & _INT_SOURCE_MASK));
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_EnableISR
*/
void OS_ARM_EnableISR(int ISRIndex) {
  OS_U32* pCntlRegister;

#if DEBUG
  if ((unsigned)ISRIndex >= _NUM_INT_VECTORS) {
    OS_Error(OS_ERR_ISR_INDEX);
    return;
  }
#endif
  pCntlRegister = (OS_U32*) &_VIC_VECTCNTL_BASE_ADDR;
  OS_DI();
  *(pCntlRegister + ISRIndex) |= (1 << 5);
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_DisableISR
*/
void OS_ARM_DisableISR(int ISRIndex) {
  OS_U32* pCntlRegister;

#if DEBUG
  if ((unsigned)ISRIndex >= _NUM_INT_VECTORS) {
    OS_Error(OS_ERR_ISR_INDEX);
    return;
  }
#endif
  pCntlRegister = (OS_U32*) &_VIC_VECTCNTL_BASE_ADDR;
  OS_DI();
  *(pCntlRegister + ISRIndex) &= ~(1 << 5);
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_EnableISRSource
*/
void OS_ARM_EnableISRSource(int SourceIndex) {
#if DEBUG
  if ((unsigned)SourceIndex >= _NUM_INT_SOURCES) {
    OS_Error(OS_ERR_ISR_INDEX);
    return;
  }
#endif
  OS_DI();
  _VIC_INTENABLE |= (1 << SourceIndex);
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_DisableISRSource
*/
void OS_ARM_DisableISRSource(int SourceIndex) {
#if DEBUG
  if ((unsigned)SourceIndex >= _NUM_INT_SOURCES) {
    OS_Error(OS_ERR_ISR_INDEX);
    return;
  }
#endif
  OS_DI();
  _VIC_INTENABLECLEAR = (1 << SourceIndex);
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_ISRSetPrio
*/
int OS_ARM_ISRSetPrio(int ISRIndex, int Prio) {
  // Not supported for CPU with this type of VIC
  return 0;
}

/*********************************************************************
*
*       local functions
*
**********************************************************************
*/

/*********************************************************************
*
*       _InitFlash
*
* Function description
*   Initialize wait states and BUS interface for external Flash access
*   Needs to be called before main clock is switched to high speed
*   Depends on specific hardware and has to be implemented by user.
*/
static void _InitFlash(void) {
  _SMCBCR0         = 0x100024EF; // Setup static memory CS0
  _SMCBCR1         = 0x1000FFEF; // Setup static memory CS1
  _SMCBCR2         = 0x1000FFEF; // Setup static memory CS2
  _SMCBCR3         = 0x0000FBEF; // Setup static memory CS3
  _SMCBCR4         = 0x10007580; // Setup static memory CS4
  _SMCBCR5         = 0x100034c0; // Setup static memory CS5
  _SMCBCR6         = 0x1000ffef; // Setup static memory CS6
  _MEMMUX          = 0x000017EF;
  _MISCMUX         = 0x000001FE;
  _UARTMUX         = 0x0000000F;
}

/*********************************************************************
*
*       _InitClocks
*
* Function description
*   Initialize main clock and PLLs
*
* NOTE: Settings used here are for LogicPD LH79520 eval board
*       and may have to be modified for other target board or frequency
*/
static void _InitClocks(void) {
  _CPUCLKPRESCALE  = 0x00000003; // Set CPU  divider to 6   (CPU/FCLK = (309.6576 MHz) / 6 = 51.609600 MHz)
  _HCLKPRESCALE    = 0x00000003; // Set HCLK divider to 6   (HCLK     = (309.6576 MHz) / 6 = 51.609600 MHz)
  _RCPCCTRL        = (1 << 0)    // Enable PLL
                   | (1 << 1)    // Enable internal crystal oscillator (14.7456 MHz)
                   | (2 << 5)    // CLKOUT = FCLK
                   | (0 << 7)    // HCLK is derived from the 309.6576 MHz output of the PLL
                   | (1 << 9)    // All RCPC registers are RW (write-enabled)
                   ;
  _CORECLKCONFIG   = 1;          // Use FastBus mode extension; Core and HCLK must have the same clock config.
}

/*********************************************************************
*
*       _Delay
*/
static void _Delay(unsigned us) {
  volatile unsigned Time;

  Time = us * 160;
  do {} while(--Time);
}

/*********************************************************************
*
*       _InitSDRAM
*
* Function description
*   Initialize SDRAM controller
*
* NOTE: Settings used here are for LogicPD LH79524 eval board
*       and may have to be modified for other target board
*/
static void _InitSDRAM(void) {
  volatile OS_U32  Dummy;
  //
  // Check if SDRAM already initiliazed thru macro file.
  // In this case SDRAM is not initialized once again.
  //
  if ((_AHBCLKCTRL & 0x02)) {
    _AHBCLKCTRL      = 0x00000005;                                      // Enable HCLK signals for SDRAM/DMA controller
    _Delay(200);                                                        // Wait for SDRAM controller
    _SDRCCONFIG1     = 0x00000003;                                      // Issue a NOP to the SDRAM
    _Delay(200);                                                        // Wait for SDRAM controller
    _SDRCCONFIG1     = 0x00000001;                                      // Issue a PALL (Precharge All) to the SDRAM
    _Delay(250);                                                        // Wait for SDRAM controller
    _SDRCREFTIMER    = 750;                                             // Update SDRAM refresh timer
    _Delay(250);                                                        // Wait for SDRAM controller
    _SDRCCONFIG1     = 0x00000002;                                      // Enable the SDRAM MODE command
    Dummy            = *(volatile OS_U32 *)(SDRAM_BASE_ADDR + 0x22000); //
    while (_SDRCCONFIG1 & (1 << 5));                                    // Wait til SDRAM controller is idle
    _SDRCCONFIG0     = (0 <<  1)                                        // No 256M device (DCS0)
                     | (0 <<  2)                                        // x16/x32 device (DCS0)
                     | (1 <<  3)                                        // 4 bank device  (DCS0)
                     | (0 <<  5)                                        // No 256M device (DCS1)
                     | (0 <<  6)                                        // x16/x32 device (DCS1)
                     | (0 <<  7)                                        // 2 bank device  (DCS1)
                     | (0 <<  7)                                        // 2 bank device  (DCS1)
                     | (0 << 17)                                        // SDCLK signal runs continuously
                     | (1 << 18)                                        // Clock Enables are driven continuously HIGH
                     | (0 << 19)                                        // External Bus width = 32
                     | (2 << 20)                                        // CAS Latency = 2
                     | (2 << 22)                                        // RAS Latency = 2
                     | (1 << 24)                                        // Enable auto-precharge
                     ;
    while (_SDRCCONFIG1 & (1 << 5));                                    // Wait til SDRAM controller is idle
    _SDRCCONFIG1     = 0x0000000c;                                      // Set to normal mode
    while (_SDRCCONFIG1 & (1 << 5));                                    // Wait til SDRAM controller is idle
    _Delay(200);                                                        // Wait for SDRAM controller
  }
}

/*********************************************************************
*
*       _Copy
*
* Function description
*   Copies code from flash to SDRAM
*/
#if COPY_CODE_TO_SDRAM
static void _Copy(OS_U32 * pSrc, OS_U32 * pDest, unsigned NumBytes)  {
  unsigned NumItems;

  NumItems = NumBytes >> 2;
  while(NumItems--) {
    *pDest++ = *pSrc++;
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
*       __low_level_init()
*
*       Initialize memory controller, clock generation and pll
*
*       Has to be modified, if another CPU clock frequency should be
*       used. This function is called during startup and
*       has to return 1 to perform segment initialization
*/
OS_INTERWORK int __low_level_init(void);  // Avoid "no ptototype" warning
OS_INTERWORK int __low_level_init(void) {
  //
  //  Initialize main clock oscillator and PLLs
  //
  _InitClocks();
  //
  //  Setup waitstates for external BUS interface before switching to high speed
  //
  _InitFlash();
  //
  //  Initialize SDRAM
  //
  _InitSDRAM();
#if COPY_CODE_TO_SDRAM
  //
  // Check if SDRAM already remapped to 0x00000000?
  // In this case we do not copy application to SDRAM
  //
  if (_REMAPCTRL != 0x01) {
  #pragma segment="INTVEC"
  #pragma segment="PROGRAM_END"
    _Copy(__segment_begin("INTVEC"),(OS_U32 *)SDRAM_BASE_ADDR, (unsigned long)((OS_U32)__segment_begin("PROGRAM_END") - (OS_U32)__segment_begin("INTVEC")));
    _REMAPCTRL  = 0x01;  // Map SDRAM to 0x00000000
  }
#endif
  //
  // Init MMU and caches
  //
#if OS_USE_MMU
  OS_ARM720_MMU_InitTT      (&_TranslationTable[0]);
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_C_B  , 0x000, 0x000, 0x020 );  // Either CS0/CS1/internal SRAM, SDRAM, depends on REMAP
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_C_B  , 0x200, 0x200, 0x010 );  // SDRAM, first 16MB, cacheable, bufferable
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_NC_NB, 0x210, 0x210, 0x010 );  // SDRAM, second 16MB, NON cacheable, NON bufferable
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_NC_NB, 0x400, 0x400, 0x020 );  // CS 0, 32MB, NON cacheable, NON bufferable
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_NC_NB, 0x440, 0x440, 0x020 );  // CS 1, 32MB, NON cacheable, NON bufferable
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_NC_NB, 0x480, 0x480, 0x020 );  // CS 2, 32MB, NON cacheable, NON bufferable
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_NC_NB, 0x4C0, 0x4C0, 0x020 );  // CS 3, 32MB, NON cacheable, NON bufferable
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_NC_NB, 0x500, 0x500, 0x020 );  // CS 4, 32MB, NON cacheable, NON bufferable
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_NC_NB, 0x540, 0x540, 0x020 );  // CS 5, 32MB, NON cacheable, NON bufferable
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_NC_NB, 0x580, 0x580, 0x020 );  // CS 6, 32MB, NON cacheable, NON bufferable
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_C_B  , 0x600, 0x600, 0x001 );  // Internal SRAM, cacheable, bufferable
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_NC_NB, 0xFFF, 0xFFF, 0x001 );  // SFR area NON cacheable, NON bufferable
  OS_ARM720_MMU_Enable      (&_TranslationTable[0]);
  OS_ARM720_CACHE_Enable();
#endif
  //
  //  Perform other initialization here, if required
  //
  return 1;
}

/*****  EOF  ********************************************************/

