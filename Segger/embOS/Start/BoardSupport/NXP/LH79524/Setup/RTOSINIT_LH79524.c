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
File    : RTOSInit_LH79524.c (for NXP LH79524 CPU)
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
  #define OS_PCLK_TIMER  51609600L // Peripheral clock frequency for timer
#endif

#ifndef   OS_PCLK_UART
  #define OS_PCLK_UART   11289600L // Peripheral clock frequency for UART
#endif

#ifndef   OS_TICK_FREQ
  #define OS_TICK_FREQ 1000
#endif

#define _OS_TIMER_PRESCALE 4       // prescaler for timer frequency

/*********************************************************************
*
*       UART settings for OSView
*       If you do not want (or can not due to hardware limitations)
*       to dedicate a UART to OSView, please define it to be -1
*       Currently the standard code enables UART 1 per default
*       and supports UART0 to UART2
*/
#ifndef   OS_UART
  #define OS_UART 0
#endif

#ifndef   OS_BAUDRATE
  #define OS_BAUDRATE 38400
#endif

/****** End of configuration settings *******************************/

#define _OS_TIMER_RELOAD OS_PCLK_TIMER / _OS_TIMER_PRESCALE / OS_TICK_FREQ

#define _OS_UART_USED    ((OS_UART == 0) || (OS_UART == 1) || (OS_UART == 2))
#define _BAUD_INT_PART   (OS_PCLK_UART / (16 * OS_BAUDRATE))
#define _BAUD_FRAC_PART  (((((OS_PCLK_UART * 8) / OS_BAUDRATE) + 1) / 2) & 0x3F)

/*********************************************************************
*
*       Local defines (sfrs used in RTOSInit.c)
*
**********************************************************************
*/

/****** timer *******************************************************/

#define _TIMER0_BASE_ADDR  0xFFFC4000
#define _TIMER1_BASE_ADDR  0xFFFC4030
#define _TIMER2_BASE_ADDR  0xFFFC4050

#define _TIMER_OFF_CTRL    (0x0000)
#define _TIMER_OFF_INTEN   (0x0004)
#define _TIMER_OFF_STATUS  (0x0008)
#define _TIMER_OFF_CNT     (0x000C)
#define _TIMER_OFF_CMP0    (0x0010)
#define _TIMER_OFF_CMP1    (0x0014)

/* Interrupt identifiers (number of input to interrupt controller)  */
#define _TIMER0_INT_ID    4
#define _TIMER1_INT_ID    5
#define _TIMER2_INT_ID    6

#define _OS_TIMER_BASE_ADDR _TIMER1_BASE_ADDR

#define _OS_TIMER_CTRL      *(volatile OS_U32 *)(_OS_TIMER_BASE_ADDR + _TIMER_OFF_CTRL)
#define _OS_TIMER_INTEN     *(volatile OS_U32 *)(_OS_TIMER_BASE_ADDR + _TIMER_OFF_INTEN)
#define _OS_TIMER_STATUS    *(volatile OS_U32 *)(_OS_TIMER_BASE_ADDR + _TIMER_OFF_STATUS)
#define _OS_TIMER_CNT       *(volatile OS_U32 *)(_OS_TIMER_BASE_ADDR + _TIMER_OFF_CNT)
#define _OS_TIMER_CMP0      *(volatile OS_U32 *)(_OS_TIMER_BASE_ADDR + _TIMER_OFF_CMP0)
#define _OS_TIMER_CMP1      *(volatile OS_U32 *)(_OS_TIMER_BASE_ADDR + _TIMER_OFF_CMP1)

/****** assign timer used for OS *********************************/

#if   (_OS_TIMER_BASE_ADDR == _TIMER0_BASE_ADDR)
  #define _OS_TIMER_INT_ID  _TIMER0_INT_ID
  #error "TIMER0 not supported by current version of RTOSInit_LH79524"
#elif (_OS_TIMER_BASE_ADDR == _TIMER1_BASE_ADDR)
  #define _OS_TIMER_INT_ID  _TIMER1_INT_ID
#elif (_OS_TIMER_BASE_ADDR == _TIMER2_BASE_ADDR)
  #define _OS_TIMER_INT_ID  _TIMER2_INT_ID
#endif

/* INPUT/OUTPUT CONTROL */
#define _IOCONBASE  0xFFFE5000
#define _MUXCTL5         *(volatile OS_U32*)(_IOCONBASE + 0x0020)
#define _RESCTL5         *(volatile OS_U32*)(_IOCONBASE + 0x0024)

/****** UART ********************************************************/

#define _UART0_BASE_ADDR  0xFFFC0000
#define _UART1_BASE_ADDR  0xFFFC1000
#define _UART2_BASE_ADDR  0xFFFC2000

#define _UART_DR_OFFS    0x0000
#define _UART_RSR_OFFS   0x0004
#define _UART_ECR_OFFS   0x0004
#define _UART_FR_OFFS    0x0018
#define _UART_IBRD_OFFS  0x0024
#define _UART_FBRD_OFFS  0x0028
#define _UART_LCR_H_OFFS 0x002C
#define _UART_CR_OFFS    0x0030
#define _UART_IFLS_OFFS  0x0034
#define _UART_IMSC_OFFS  0x0038
#define _UART_RIS_OFFS   0x003C
#define _UART_MIS_OFFS   0x0040
#define _UART_ICR_OFFS   0x0044

/****** Assign UART sfrs used for OSView communication ***********/

#if _OS_UART_USED
  #if   (OS_UART == 0)
    #define _OS_UART_BASE_ADDR _UART0_BASE_ADDR
    #define _OS_UART_CLK_BIT   0
    #define _OS_UART_ID        27
    #define _OS_UART_MUX_MASK  ((3 << 10) | (3 << 8))
    #define _OS_UART_MUX_VALUE ((2 << 10) | (2 << 8))
  #elif (OS_UART == 1)
    #define _OS_UART_BASE_ADDR _UART1_BASE_ADDR
    #define _OS_UART_CLK_BIT   1
    #define _OS_UART_ID        28
    #define _OS_UART_MUX_MASK  ((3 << 6) | (3 << 4))
    #define _OS_UART_MUX_VALUE ((2 << 4) | (2 << 4))
  #elif (OS_UART == 2)
    #define _OS_UART_BASE_ADDR _UART2_BASE_ADDR
    #define _OS_UART_CLK_BIT 2
    #define _OS_UART_ID      29
    #define _OS_UART_MUX_MASK  ((3 << 14) | (3 << 12))
    #define _OS_UART_MUX_VALUE ((2 << 12) | (2 << 12))
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

#define _OS_UART_MUX     _MUXCTL5

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

/*      Reset, Clock, and Power Controller */
#define _RCPC_BASE_ADDR  (0xFFFE2000)
#define _RCPC_CTRL       (*(volatile OS_U32*) (_RCPC_BASE_ADDR))
#define _RCPC_CORECONFIG (*(volatile OS_U32*) (_RCPC_BASE_ADDR + 0x88))
#define _RCPC_AHBCLKCTRL (*(volatile OS_U32*) (_RCPC_BASE_ADDR + 0x1C))
#define _RCPC_PCLKCTRL0  (*(volatile OS_U32*) (_RCPC_BASE_ADDR + 0x24))
#define _RCPC_PCLKCTRL1  (*(volatile OS_U32*) (_RCPC_BASE_ADDR + 0x28))
#define _RCPC_SYSPLLCNTL (*(volatile OS_U32*) (_RCPC_BASE_ADDR + 0xC0))
#define _RCPC_SYSCLKPRE  (*(volatile OS_U32*) (_RCPC_BASE_ADDR + 0x18))
#define _RCPC_CPUCLKPRE  (*(volatile OS_U32*) (_RCPC_BASE_ADDR + 0x1C))
#define _RCPC_REMAP      (*(volatile OS_U32*) (_RCPC_BASE_ADDR + 0x08))


/*      External Memory Controller */
#define _EMC_BASE_ADDR        (0xFFFF1000)
#define _EMC_CONTROL     (*(volatile OS_U32*) (_EMC_BASE_ADDR))

#define _EMC_SCONFIG1    (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x220))
#define _EMC_SWAITWEN1   (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x224))
#define _EMC_SWAITOEN1   (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x228))
#define _EMC_SWAITRD1    (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x22C))
#define _EMC_SWAITPAGE1  (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x230))
#define _EMC_SWAITWR1    (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x234))
#define _EMC_STURN1      (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x238))

#define _EMC_SCONFIG3    (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x260))
#define _EMC_SWAITWEN3   (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x264))
#define _EMC_SWAITOEN3   (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x268))
#define _EMC_SWAITRD3    (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x26C))
#define _EMC_SWAITPAGE3  (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x270))
#define _EMC_SWAITWR3    (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x274))
#define _EMC_STURN3      (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x278))

#define _EMC_DYNRCON     (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x28))
#define _EMC_DYNCFG0     (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x100))
#define _EMC_DYNRASCAS0  (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x104))
#define _EMC_PRECHARGE   (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x30))
#define _EMC_DYNM2PRE    (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x34))
#define _EMC_REFEXIT     (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x38))
#define _EMC_DOACTIVE    (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x3C))
#define _EMC_DIACTIVE    (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x40))
#define _EMC_DWRT        (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x44))
#define _EMC_DYNACTCMD   (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x48))
#define _EMC_DYNAUTO     (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x4C))
#define _EMC_DYNREFEXIT  (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x50))
#define _EMC_DYNACTIVEAB (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x54))
#define _EMC_DYNAMICMRD  (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x58))
#define _EMC_DYNMCTRL    (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x20))
#define _EMC_DYNMREF     (*(volatile OS_U32*) (_EMC_BASE_ADDR + 0x24))

/*      Multiplexing Controller */
#define _MUXCTL_BASE_ADDR     (0xFFFE5000)
#define _MUXCTL_7        (*(volatile OS_U32*) (_MUXCTL_BASE_ADDR + 0x30))
#define _MUXCTL_10       (*(volatile OS_U32*) (_MUXCTL_BASE_ADDR + 0x48))
#define _MUXCTL_11       (*(volatile OS_U32*) (_MUXCTL_BASE_ADDR + 0x50))
#define _MUXCTL_12       (*(volatile OS_U32*) (_MUXCTL_BASE_ADDR + 0x58))
#define _MUXCTL_19       (*(volatile OS_U32*) (_MUXCTL_BASE_ADDR + 0x90))
#define _MUXCTL_20       (*(volatile OS_U32*) (_MUXCTL_BASE_ADDR + 0x98))

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

#ifndef _NUM_INT_VECTORS
  #define _NUM_INT_VECTORS  16
#endif

/* Configuration of interrupts used by the OS ***********************/

#define _OS_TIMER_INT_INDEX    15 // Assign to lowest priority interrupt channel
#define _OS_UART_INT_INDEX     14 // Assign to low priority interrupt channel


/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
#if OS_USE_MMU
//#include "MMU.h"
#pragma data_alignment=16384
#pragma location="MMU_TABLE"
static __no_init unsigned int _TranslationTable [0x1000];
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

  _VIC_INTENABLECLEAR = 0xFFFFFFFF;           // Disable all source interrupts
  _VIC_VECTORADDR     = 0;                    // Write to vector, reset VIC
  for (Index = 0; Index < _NUM_INT_VECTORS; Index++) {
    OS_ARM_DisableISR(Index);                 // Disable channel
    OS_ARM_AssignISRSource(Index, 0);         // Assign to hardware channel 0
    OS_ARM_InstallISRHandler(Index, NULL);    // Set vector to 0;
  }
  _VIC_SOFTINTCLEAR   = 0xFFFFFFFF;           // Disable all soft interrupts
  _VIC_INTSELECT      = 0;                    // Set all channels to generate IRQ
  _VIC_DEFVECTADDR    = 0;                    // Set default vector to 0
}

/*********************************************************************
*
*       OS_Tick interrupt Handler
*/
static void _OS_ISR_Tick (void) {
  _OS_TIMER_STATUS = (1 << 2);  // Clear compare 1 match interrupt
  OS_HandleTick();              // Call OS tick handler
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
   volatile OS_U32 Dummy;
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
  } while (Pending);   /* Handle all interrupts */
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
  _Init_VIC();                                  // Initialize VIC, clear and disable all interrupts
  // Initialize timer for OS
  _OS_TIMER_CTRL   = 0;                         // Initially stop timer
  _OS_TIMER_INTEN  = 0;                         // Disable all timer interrupts
  _OS_TIMER_CMP1   = _OS_TIMER_RELOAD;          // Compare register 1 used for periodic timer
  _OS_TIMER_CTRL   = 0                          // Initialize timer in intervall mode
                   | (0 << 14)                  // Output is normal
                   | (1 << 13)                  // Clear counter on compare 1 match
                   | (0 << 11)                  // No change on output on compare 1 match
                   | (0 <<  9)                  // No change on output on compare 0 match
                   | (0 <<  7)                  // Capture input CAP1B ignored
                   | (0 <<  5)                  // Capture input CAP1A ignored
                   | (1 <<  2)                  // Select HCLK/4 as timer clock
                   | (1 <<  1)                  // Start timer
                   ;

  // Setup interrupt controller to handle OS timer tick
  OS_ARM_InstallISRHandler(_OS_TIMER_INT_INDEX, &_OS_ISR_Tick); // Timer/counter interrupt vector.
  OS_ARM_AssignISRSource(_OS_TIMER_INT_INDEX, _OS_TIMER_INT_ID);
  OS_ARM_EnableISR(_OS_TIMER_INT_INDEX);        // Enable timer/counter interrupt.
  OS_ARM_EnableISRSource(_OS_TIMER_INT_ID);     // Enable timer/counter interrupt.
  _OS_TIMER_INTEN = (1 << 2);                   // Enable timer compare 1 match interrupt
  OS_COM_Init();                                // initialize UART for OSView
  OS_RestoreI();
}

#if (_OS_TIMER_PRESCALE != 4)
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

  t_cnt = _OS_TIMER_CNT;             // Read current timer value
  time  = OS_GetTime32();            // Read current OS time
  if (_OS_TIMER_STATUS & (1 << 2)) { // Timer Interrupt pending ?
    t_cnt = _OS_TIMER_CNT;           // Adjust result
    if (t_cnt == _OS_TIMER_RELOAD) {
      t_cnt = 0;
    }
    time++;
  }
  return _OS_TIMER_RELOAD * time + t_cnt;
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
  _OS_UART_DR  = c;
  _OS_UART_IMSC  |= (1 << 5);
}

/*********************************************************************
*
*       OS_COM_Init()
*       Initialize UART for OSView
*/
void OS_COM_Init(void) {  // Initialize UART, enable UART interrupts
  _OS_UART_CR          = 0;                        // Disable UART
  OS_ARM_DisableISRSource(_OS_UART_ID);            // Disable UART interrupts
  _OS_UART_MUX        &= ~_OS_UART_MUX_MASK;       // Reset I/O configuration for UART
  _OS_UART_MUX        |= _OS_UART_MUX_VALUE;       // Select I/O configuration for UART
  _PERIPHCLKCTRL      &= ~(1 << _OS_UART_CLK_BIT); // Enable UART Clock
  _PERPIHCLKSELECT    &= ~(1 << _OS_UART_CLK_BIT); // Use crystal clock
  _OS_UART_IBRD        = _BAUD_INT_PART;           // Set baudrate
  _OS_UART_FBRD        = _BAUD_FRAC_PART;
  _OS_UART_LCR_H       = (0 << 4)                  // Disable FIFO
                       | (1 << 5)                  // Set 8bit data
                       | (1 << 6);                 // Set 8bit data
  _OS_UART_IFLS        = (1 << 0)                  // TX Fifo size
                       | (1 << 3);                 // RX Fifo size
  _OS_UART_ICR         = 0x7F0;                    // Clear any pending interrupts
  OS_ARM_InstallISRHandler (_OS_UART_INT_INDEX, &_OS_ISR_UART);
  OS_ARM_AssignISRSource(_OS_UART_INT_INDEX, _OS_UART_ID);  // Assign priority (Index) to input
  OS_ARM_EnableISR(_OS_UART_INT_INDEX);            // Enable UART interrupt.
  OS_ARM_EnableISRSource(_OS_UART_ID);             // Enable UART interrupt.

  _OS_UART_IMSC        = (1 << 4)                  // Enable receive interrupt
                       | (1 << 5)                  // Enable transmit interrupt
                       | (1 << 6);                 // Enable runtime error

  _OS_UART_CR          = (1 << 9)                  // Enable UART receive
                       | (1 << 8)                  // Enable UART transmit
                       | (1 << 0);                 // Enable UART
}

#else  /* selected UART not supported, using dummies */

void OS_COM_Init(void) {}
void OS_COM_Send1(OS_U8 c) {
  OS_USEPARA(c);           // avoid compiler warning
  OS_COM_ClearTxActive();  // let the OS know that Tx is not busy
}

#endif /*  (_OS_UART_USED) */

/*********************************************************************
*
*       Generic Interrupt controller handling functions
*
**********************************************************************
*/

/*********************************************************************
*
*       OS_ARM_InstallISRHandler
*
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
*
*/
void OS_ARM_AssignISRSource(int ISRIndex, int Source) {
  OS_U32* pCntlRegister;
  OS_U32 ControlReg;

#if DEBUG
  if ((unsigned)ISRIndex >= _NUM_INT_VECTORS) {
    OS_Error(OS_ERR_ISR_INDEX);
    return;
  }
#endif
  pCntlRegister = (OS_U32*) &_VIC_VECTCNTL_BASE_ADDR;
  OS_DI();
  ControlReg  = *(pCntlRegister + ISRIndex) & ~_INT_SOURCE_MASK;
  *(pCntlRegister + ISRIndex) = (ControlReg | (Source & _INT_SOURCE_MASK));
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_EnableISR
*
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
*
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
*
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
*
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
  // Not supported for CPU with VIC
  return 0;
}

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
  _MUXCTL_12      = 0x00005000; //MUXCTL12: IO pins data bus(D) 8,26
  _MUXCTL_11      = 0x00005555; //MUXCTL11: IO pins data bus(D) 9-12,17-20
  _MUXCTL_10      = 0x00005555; //MUXCTL10: IO pins data bus(D) 13-15,21-25
  _MUXCTL_20      = 0x00001110; //MUXCTL20: IO pins data bus(D) 26-28
  _MUXCTL_19      = 0x00000441; //MUXCTL19: IO pins data bus(D) 29-31
  _MUXCTL_7       = 0x00005555; //MUXCTL7:  IO pins addr bus(A) 16-23

  _EMC_SCONFIG1   = 0x00000081; //SCONFIG1:  CS1(Flash) 16bit,BLE=1
  _EMC_SWAITWEN1  = 0x00000001; //SWAITWEN1: CS1(Flash) _WE DELAY=1
  _EMC_SWAITOEN1  = 0x00000001; //SWAITOEN1: CS1(Flash) _OE DELAY=1
  _EMC_SWAITRD1   = 0x00000006; //SWAITRD1:  CS1(Flash) _RD DELAY=6
  _EMC_SWAITPAGE1 = 0x00000002; //SWAITPAGE1:CS1(Flash) PAGE DELAY=6
  _EMC_SWAITWR1   = 0x00000006; //SWAITWR1:  CS1(Flash) WRITE DELAY=6
  _EMC_STURN1     = 0x00000002; //STURN1:    CS1(Flash) TURN DELAY=2

  _EMC_SCONFIG3   = 0x00000081; //SCONFIG3:  CS3(CPLD) 16bit,BLE=1
  _EMC_SWAITWEN3  = 0x00000002; //SWAITWEN3: CS3(CPLD) _WE DELAY=1
  _EMC_SWAITOEN3  = 0x00000002; //SWAITOEN3: CS3(CPLD) _OE DELAY=1
  _EMC_SWAITRD3   = 0x00000005; //SWAITRD3:  CS3(CPLD) _RD DELAY=6
  _EMC_SWAITPAGE3 = 0x00000002; //SWAITPAGE3:CS3(CPLD) PAGE DELAY=6
  _EMC_SWAITWR3   = 0x00000005; //SWAITWR3:  CS3(CPLD) WRITE DELAY=6
  _EMC_STURN3     = 0x00000002; //STURN3:    CS3(CPLD) TURN DELAY=2
}

/*********************************************************************
*
*       _InitClocks
*
* Function description
*   Initialize main clock and PLLs
*
* NOTE: Settings used here are for LogicPD LH79524 eval board
*       and may have to be modified for other target board or frequency
*/
static void _InitClocks(void) {
  _RCPC_CTRL       = 0x00000260; //RCPC_CTRL: Enable APB register Write Access
  _RCPC_CORECONFIG = 0x00000001; //CORECONFIG: Set Chip in Fastbus Mode
  _RCPC_AHBCLKCTRL = 0x0000001C; //AHBCLKCTRL: Disable Ethernet Clk
  _RCPC_PCLKCTRL0  = 0x00000207; //PCLKCTRL0: En RTC Dis UART clks
  _RCPC_PCLKCTRL1  = 0x0000000F; //PCLKCTRL1: En LCD Dis ADC,USB clks
  _RCPC_SYSPLLCNTL = 0x00003049; //SYSPLLCNTL: PLL = 101.6064 Mhz
  _RCPC_SYSCLKPRE  = 0x00000001; //SYSCLKPRE: HCLK = 50.8032 MHz
  _RCPC_CPUCLKPRE  = 0x00000001; //CPUCLKPRE: FCLK = 50.8032 MHz
  _EMC_CONTROL     = 0x00000001; //EMC_CONTROL: Enable external memory controller
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
  if (_EMC_DYNCFG0 != 0x00085680) {
    // Setup SDRAM
    _EMC_DYNRCON     = 0x00000001; // Dynamic Memory Read Configuration Register
    _EMC_DYNCFG0     = 0x00005680; // Dynamic Configuration Register for nDCS0
    _EMC_DYNRASCAS0  = 0x00000203; // Dynamic Memory RAS and CAS Delay for nDCS0
    _EMC_PRECHARGE   = 0x00000001; // Dynamic Memory Precharge Command Period
    _EMC_DYNM2PRE    = 0x00000003; // Dynamic Memory Active to Precharge Command Period
    _EMC_REFEXIT     = 0x00000006; // Dynamic Memory Self-Refresh Exit Time
    _EMC_DOACTIVE    = 0x00000006; // Dynamic Memory Last Data Out to Active Time
    _EMC_DIACTIVE    = 0x00000006; // Dynamic Memory Data-In to Active Command Time
    _EMC_DWRT        = 0x00000002; // Dynamic Memory Write Recovery Time
    _EMC_DYNACTCMD   = 0x00000006; // Dynamic Memory Active to Active Command Period
    _EMC_DYNAUTO     = 0x00000006; // Dynamic Memory Auto-Refresh Period, and Auto-Refresh to Active Command Period
    _EMC_DYNREFEXIT  = 0x00000006; // Dynamic Memory Exit Self-Refresh to Active Command Time
    _EMC_DYNACTIVEAB = 0x00000002; // Dynamic Memory Active Bank A to Active Bank B Time
    _EMC_DYNAMICMRD  = 0x00000002; // Dynamic Memory Load Mode Register to Active Command Time
    _EMC_DYNMCTRL    = 0x00000003; // Dynamic Memory Control Register
    _Delay(200);                   // Wait for SDRAM controller
    _EMC_DYNMCTRL    = 0x00000183; // Dynamic Memory Control Register
    _Delay(200);                   // Wait for SDRAM controller
    _EMC_DYNMCTRL    = 0x00000103; // Dynamic Memory Control Register
    _EMC_DYNMREF     = 0x00000001; // Dynamic Memory Refresh Timer
    _Delay(250);                   // Wait for SDRAM controller
    _EMC_DYNMREF     = 0x00000018; // Dynamic Memory Refresh Timer
    _Delay(250);                   // Wait for SDRAM controller
    _EMC_DYNMCTRL    = 0x00000083; // Dynamic Memory Control Register
    Dummy = *(volatile OS_U32 *)(SDRAM_BASE_ADDR + 0x11000);
    _EMC_DYNMCTRL    = 0x00000003; // Dynamic Memory Control Register
    _EMC_DYNCFG0     = 0x00085680; // Dynamic Configuration Register for nDCS0
    _Delay(2500);                  // Wait for SDRAM controller
  }
}

/*********************************************************************
*
*       _Copy
*
* Function description
*   Used to copy code from Flash to SDRAM
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
#pragma segment="INTVEC"
#pragma segment="PROGRAM_END"
  if (_RCPC_REMAP != 0x01) {
    _Copy(__segment_begin("INTVEC"),(OS_U32 *)SDRAM_BASE_ADDR, (unsigned long)((OS_U32)__segment_begin("PROGRAM_END") - (OS_U32)__segment_begin("INTVEC")));
    _RCPC_REMAP = 0x01;  // Map SDRAM to 0x00000000
  }
#endif
  //
  // Init MMU and caches
  //
#if OS_USE_MMU
  OS_ARM720_MMU_InitTT      (&_TranslationTable[0]);
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_C_B  , 0x000, 0x000, 0x020);   // Either CS0/CS1/internal SRAM, SDRAM, depends on REMAP
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_C_B  , 0x200, 0x200, 0x010);   // SDRAM, first 16MB, cacheable, bufferable
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_NC_NB, 0x210, 0x210, 0x010);   // SDRAM, second 16MB, NON cacheable, NON bufferable
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_NC_NB, 0x400, 0x400, 0x020);   // CS 0, 32MB, NON cacheable, NON bufferable
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_NC_NB, 0x440, 0x440, 0x020);   // CS 1, 32MB, NON cacheable, NON bufferable
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_NC_NB, 0x480, 0x480, 0x020);   // CS 2, 32MB, NON cacheable, NON bufferable
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_NC_NB, 0x4C0, 0x4C0, 0x020);   // CS 3, 32MB, NON cacheable, NON bufferable
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_C_B  , 0x600, 0x600, 0x001);   // Internal SRAM, cacheable, bufferable
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_C_B  , 0x800, 0x800, 0x001);   // BootROM
  OS_ARM720_MMU_AddTTEntries(&_TranslationTable[0], OS_ARM_CACHEMODE_NC_NB, 0xFFF, 0xFFF, 0x001);   // SFR area NON cacheable, NON bufferable
  OS_ARM720_MMU_Enable      (&_TranslationTable[0]);
  OS_ARM720_CACHE_Enable();
#endif
  //
  //  Perform other initialization here, if required
  //
  return 1;
}


/*****  EOF  ********************************************************/

