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
File    : RTOSInit.c   (for SHARP LH7A400 CPU)
Purpose : Initializes and handles the hardware for the OS as far
          as required by the OS.
          Feel free to modify this file acc. to your
          target system.
--------  END-OF-HEADER  ---------------------------------------------
*/

#include "RTOS.H"
#include "JLINKDCC.h"
#include "intrinsics.h"

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
  #define OS_FSYS      199987200L // System clock frequency
#endif

#ifndef   OS_PCLK_TIMER
  #define OS_PCLK_TIMER   508469L // Peripheral clock frequency for timer
#endif

#ifndef   OS_PCLK_UART
  #define OS_PCLK_UART   7372800L // Peripheral clock frequency for UART
#endif

#ifndef   OS_TICK_FREQ
  #define OS_TICK_FREQ 1000
#endif

#define _OS_TIMER_PRESCALE  1     // prescaler for timer frequency

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

#define _OS_UART_USED  ((OS_UART == 0) || (OS_UART == 1) || (OS_UART == 2))
#define _BAUD_INT_PART (OS_U32)(OS_PCLK_UART / (16 * OS_BAUDRATE)) - 1

/*********************************************************************
*
*       Local defines (sfrs used in RTOSInit.c)
*
**********************************************************************
*/

/*****  Timer *******************************************************/
#define _TIMER1_BASE_ADDR   0x80000C00
#define _TIMER2_BASE_ADDR   0x80000C20
#define _TIMER3_BASE_ADDR   0x80000C80

#define _TIMER_OFF_LOAD     (0x0000)
#define _TIMER_OFF_VALUE    (0x0004)
#define _TIMER_OFF_CONTROL  (0x0008)
#define _TIMER_OFF_EOI      (0x000C)

#define _OS_TIMER_BASE_ADDR _TIMER1_BASE_ADDR
#define _OS_TIMER_LOAD      *(volatile OS_U32 *)(_OS_TIMER_BASE_ADDR + _TIMER_OFF_LOAD)
#define _OS_TIMER_VALUE     *(volatile OS_U32 *)(_OS_TIMER_BASE_ADDR + _TIMER_OFF_VALUE)
#define _OS_TIMER_CONTROL   *(volatile OS_U32 *)(_OS_TIMER_BASE_ADDR + _TIMER_OFF_CONTROL)
#define _OS_TIMER_EOI       *(volatile OS_U32 *)(_OS_TIMER_BASE_ADDR + _TIMER_OFF_EOI)

/* UART */
#define _UART0_BASE_ADDR  0x80000600
#define _UART1_BASE_ADDR  0x80000700
#define _UART2_BASE_ADDR  0x80000800

#define _UART_OFF_DATA    0x0000
#define _UART_OFF_FCON    0x0004
#define _UART_OFF_BRCON   0x0008
#define _UART_OFF_CON     0x000C
#define _UART_OFF_STATUS  0x0010
#define _UART_OFF_RAWISR  0x0014
#define _UART_OFF_INTEN   0x0018
#define _UART_OFF_ISR     0x001C

/****** Assign UART sfrs used for OSView communication ***********/

#if _OS_UART_USED
  #if   (OS_UART == 0)
    #define _OS_UART_BASE_ADDR _UART0_BASE_ADDR
    #define _OS_UART_ID   UART0_INT_ID
  #elif (OS_UART == 1)
    #define _OS_UART_BASE_ADDR _UART1_BASE_ADDR
    #define _OS_UART_ID   UART1_INT_ID

  #elif (OS_UART == 2)
    #define _OS_UART_BASE_ADDR _UART2_BASE_ADDR
    #define _OS_UART_ID   UART2_INT_ID
  #endif

  #define _OS_UART_DATA   *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_OFF_DATA)
  #define _OS_UART_FCON   *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_OFF_FCON)
  #define _OS_UART_BRCON  *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_OFF_BRCON)
  #define _OS_UART_CON    *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_OFF_CON)
  #define _OS_UART_STATUS *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_OFF_STATUS)
  #define _OS_UART_RAWISR *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_OFF_RAWISR)
  #define _OS_UART_INTEN  *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_OFF_INTEN)
  #define _OS_UART_ISR    *(volatile OS_U32*)(_OS_UART_BASE_ADDR + _UART_OFF_ISR)
#endif

/* INPUT/OUTPUT CONTROL */
#define _PINMUX  *(volatile OS_U32*)(0x80000E2C)

/* STATIC MEMORY CONTROLLER */
#define _SMCREGBASE  0x80002000
#define _SMC_BCR0           *(volatile OS_U32*)(_SMCREGBASE + 0x0000)
#define _SMC_BCR1           *(volatile OS_U32*)(_SMCREGBASE + 0x0004)
#define _SMC_BCR2           *(volatile OS_U32*)(_SMCREGBASE + 0x0008)
#define _SMC_BCR3           *(volatile OS_U32*)(_SMCREGBASE + 0x000C)
#define _SMC_BCR6           *(volatile OS_U32*)(_SMCREGBASE + 0x0018)
#define _SMC_BCR7           *(volatile OS_U32*)(_SMCREGBASE + 0x001C)
#define _SMC_PCCARD0_ATTRIB *(volatile OS_U32*)(_SMCREGBASE + 0x0020)
#define _SMC_PCCARD0_COMMON *(volatile OS_U32*)(_SMCREGBASE + 0x0024)
#define _SMC_PCCARD0_IO     *(volatile OS_U32*)(_SMCREGBASE + 0x0028)
#define _SMC_PCCARD1_ATTRIB *(volatile OS_U32*)(_SMCREGBASE + 0x0030)
#define _SMC_PCCARD1_COMMON *(volatile OS_U32*)(_SMCREGBASE + 0x0034)
#define _SMC_PCCARD1_IO     *(volatile OS_U32*)(_SMCREGBASE + 0x0038)
#define _SMC_PCMCIACON      *(volatile OS_U32*)(_SMCREGBASE + 0x0040)

/* SYNCHRONOUS DYNAMIC RAM CONTROLLER */
#define _SDMCBASE   0x80002400
#define _SDMC_GBLCNFG    *(volatile OS_U32*)(_SDMCBASE + 0x0004)
#define _SDMC_RFSHTMR    *(volatile OS_U32*)(_SDMCBASE + 0x0008)
#define _SDMC_BOOTSTAT   *(volatile OS_U32*)(_SDMCBASE + 0x000C)
#define _SDMC_SDCSC0     *(volatile OS_U32*)(_SDMCBASE + 0x0010)
#define _SDMC_SDCSC1     *(volatile OS_U32*)(_SDMCBASE + 0x0014)
#define _SDMC_SDCSC2     *(volatile OS_U32*)(_SDMCBASE + 0x0018)
#define _SDMC_SDCSC3     *(volatile OS_U32*)(_SDMCBASE + 0x001C)

/* CLOCK AND STATE CONTROLLER  */
#define _CSCBASE
#define _CSC_PWRCNT      *(volatile OS_U32*)(_CSCBASE + 0x0000)
#define _CSC_HALT        *(volatile OS_U32*)(_CSCBASE + 0x0008)
#define _CSC_STBY        *(volatile OS_U32*)(_CSCBASE + 0x000C)
#define _CSC_BLEOI       *(volatile OS_U32*)(_CSCBASE + 0x0010)
#define _CSC_MCEOI       *(volatile OS_U32*)(_CSCBASE + 0x0014)
#define _CSC_TEOI        *(volatile OS_U32*)(_CSCBASE + 0x0018)
#define _CSC_STFCLR      *(volatile OS_U32*)(_CSCBASE + 0x001C)
#define _CSC_CLKSET      *(volatile OS_U32*)(_CSCBASE + 0x0020)
#define _CSC_SCREG0      *(volatile OS_U32*)(_CSCBASE + 0x0040)
#define _CSC_SCREG1      *(volatile OS_U32*)(_CSCBASE + 0x0044)
#define _CSC_USBRESET    *(volatile OS_U32*)(_CSCBASE + 0x004C)

//VECTORED INTERRUPT CONTROLLER
#define _INTBASE   0x80000500
#define _IRQSTATUS       *(volatile OS_U32*)(_INTBASE + 0x0000)
#define _RAWSTATUS       *(volatile OS_U32*)(_INTBASE + 0x0004)
#define _INTENABLE       *(volatile OS_U32*)(_INTBASE + 0x0008)
#define _INTENABLECLEAR  *(volatile OS_U32*)(_INTBASE + 0x000C)

#define GPIO0_FIQ_ID        0  // IRQ0
#define BATTERYLOW_INT_ID   1  // IRQ1
#define WD_TIMER_INT_ID     2  // IRQ2
#define MEDIA_CHANGE_INT_ID 3  // IRQ3
#define AC_INT_ID           4  // IRQ4
#define GPIO1_INT_ID        5  // IRQ5
#define GPIO2_INT_ID        6  // IRQ6
#define GPIO3_INT_ID        7  // IRQ7
#define _TIMER1_INT_ID      8  // IRQ8
#define _TIMER2_INT_ID      9  // IRQ9
#define RTC_INT_ID         10  // IRQ10
#define TIME_INT_ID        11  // IRQ11
#define UART0_INT_ID       12  // IRQ12
#define UART1_INT_ID       13  // IRQ13
#define LCD_INT_ID         14  // IRQ14
#define SSI_INT_ID         15  // IRQ15
#define UART2_INT_ID       16  // IRQ16
#define SCI_INT_ID         17  // IRQ17
#define AC97_INT_ID        18  // IRQ18
#define MMC_INT_ID         19  // IRQ19
#define USB_INT_ID         20  // IRQ20
#define DMA_INT_ID         21  // IRQ21
#define _TIMER3_INT_ID     22  // IRQ22
#define GPIO4_INT_ID       23  // IRQ23
#define GPIO5_INT_ID       24  // IRQ24
#define GPIO6_INT_ID       25  // IRQ25
#define GPIO7_INT_ID       26  // IRQ26
#define BMI_INT_ID         27  // IRQ27

#ifndef NUM_INT_SOURCES
  #define NUM_INT_SOURCES  28
#endif

#if   (_OS_TIMER_BASE_ADDR == _TIMER1_BASE_ADDR)
  #define _OS_TIMER_INT_ID     _TIMER1_INT_ID
#elif (_OS_TIMER_BASE_ADDR == _TIMER2_BASE_ADDR)
  #define _OS_TIMER_INT_ID     _TIMER2_INT_ID
#elif (_OS_TIMER_BASE_ADDR == _TIMER3_BASE_ADDR)
  #define _OS_TIMER_INT_ID     _TIMER3_INT_ID
#endif

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
*       _Delay
*/
static void _Delay(volatile int * pTime) {
  while(*pTime) {
    *pTime -= 1;
  }
}

/*********************************************************************
*
*       _SetupSDRAM
*/
static _SetupSDRAM(void) {
  volatile int Delay;            // Declare as volatile to ensure, compiler does not optimize the dummy read later !
  Delay = 0x400;
  _Delay(&Delay);                // Wait for SDRAM controller
  _SDMC_SDCSC0  = 0x01320008;    // Setup SDRAM Controller (Domain CS Configuration)
  Delay = 0x400;
  _Delay(&Delay);                // Wait for SDRAM controller
  _SDMC_RFSHTMR = 0x00000014;    // Setup SDRAM Controller (Refresh Timer)
  _SDMC_GBLCNFG = 0x80000003;    // Issue continuous NOP commands (INIT & MRS set)
  Delay = 0x5000;
  _Delay(&Delay);                // Wait for SDRAM controller
  _SDMC_GBLCNFG = 0x80000001;    // Issue a "pre-charge all" command
  Delay = 0xf00;
  _Delay(&Delay);                // Wait for SDRAM controller
  _SDMC_RFSHTMR = 0x000005dc;    // Setup SDRAM Controller (Refresh Timer)
  _SDMC_GBLCNFG = 0x80000002;    // Select mode register update mode
  Delay = *(OS_U32*)(0xC000C800);
  Delay = 0x10;
  _Delay(&Delay);                // Wait for SDRAM controller
  _SDMC_SDCSC0  = 0x01320028;    // Setup SDRAM Controller (Domain CS Configuration)
  _SDMC_GBLCNFG = 0x80000000;    // Setup SDRAM Controller (Global configuration)
}

/*********************************************************************
*
*       _InitPLL
*
* Function description
*   Initialize main clock and PLL
*/
static void _InitPLL(void) {
  int Delay;
  _SMC_PCMCIACON = 0x00000003;    // Set PCMCIA Controller -> 2 Cards @ 0x40000000 & 0x50000000
  _PINMUX        = 0x0000000B;
  _SMC_BCR0      = 0x200041c0;
  _SMC_BCR6      = 0x1000FBE0;
  _SMC_BCR7      = 0x1000FBE0;
  _CSC_CLKSET    = 0x0004EE39;    // GCLK = FCLK = 200 MHz
                                  // HCLK = FCLK / 2
                                  // Predivisor for PLL1 = 14 (01110b)
                                  // Main Divisor1   for PLL1 = 12  (1100b)
                                  // Main Divisor2   for PLL1 = 29 (11101b)
                                  // PCLK = HCLK / 2
                                  // PS Divisor = 1
                                  // Static memory controller is clocked
                                  // Use the 33 MHz Clock to boot.
  Delay = 100;
  _Delay(&Delay);
  _CSC_PWRCNT   = (0x3ff << 16) | (0x01 << 8); // Enable all DMA channels and setup programmable clock = 14,7456 MHz
}

/*********************************************************************
*
*       _OS_ISR_Tick() OS timer tick interrupt handler
*/
static void _OS_ISR_Tick(void) {
  _OS_TIMER_EOI = 1;
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
static void _OS_ISR_Undefined(int Index) {
  #if (OS_IGNORE_UNDEFINED_INTERRUPT == 0)
    volatile OS_U32 Dummy;
    Dummy = Index;
    /* You may set a breakpoint here to detect undefined interrupts */
    while (Dummy) {
    }
  #endif
}

#if _OS_UART_USED

/*********************************************************************
*
*       _OS_ISR_UART() OS gerneral UART interrupt handler
*/
#define _RX_INT             (1 << 0)
#define _TX_INT             (1 << 1)
#define _RX_INT_TIMEOUT     (1 << 4)

#define _RX_FIFO_EMPTY      (1 << 4)
#define _TX_FIFO_EMPTY      (1 << 7)

static void _OS_ISR_UART(void) {
  OS_U8 Pending;
  Pending = _OS_UART_ISR;
  do {
    if ((Pending & (_RX_INT | _RX_INT_TIMEOUT)) != 0) {
      do {
        OS_U8 RxData, RxError;
        RxData   = _OS_UART_DATA & 0xff;
        RxError  = (_OS_UART_DATA >> 8);
        if (RxError == 0) {
          OS_OnRx(RxData & 0xff);
        }
      } while ((_OS_UART_STATUS & _RX_FIFO_EMPTY) == 0);
    }
    if (Pending & _TX_INT) {
      if (OS_OnTx()) {
        /*  No more bytes sent, disable tx interrupt   */
        /*  Will be re-enabled in OS_COM_Send1()       */
        _OS_UART_INTEN &= ~_TX_INT;
      }
    }
    Pending = _OS_UART_ISR & (_RX_INT | _TX_INT | _RX_INT_TIMEOUT);
  } while (Pending);   /* Handle all interrupts */
}

#endif /* _OS_UART_USED */

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
  int i;
  volatile OS_U32 Dummy;

  OS_DI();
  for (i = 0; i < NUM_INT_SOURCES; i++) {
    OS_ARM_DisableISR(i);
  }

  // Initialize the OS timer (timer, reload)
  OS_ARM_DisableISR(_OS_TIMER_INT_ID);       // Disable timer interrupt.
  _OS_TIMER_CONTROL = (1 << 7)               // Enable the timer
                    | (1 << 6)               // Periodic mode
                    | (1 << 3);              // Use 508 kHz Clock
  _OS_TIMER_LOAD    = _OS_TIMER_RELOAD;      // Set compare register
  // Setup interrupt controller for the OS timer interrupt using timer 0
  Dummy = _OS_TIMER_EOI;                     // Clears timer/counter interrupt.
  OS_ARM_InstallISRHandler(_OS_TIMER_INT_ID, &_OS_ISR_Tick); // Setup the Timer Interrupt
  OS_ARM_EnableISR(_OS_TIMER_INT_ID);                        // Enable timer interrupt.
  OS_COM_Init();                                             // Initialize UART for OSView
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
*       resolution time management functions.
*       It returns the system time in timer clock cycles.
*/
OS_U32 OS_GetTime_Cycles(void) {
  unsigned int t_cnt = _OS_TIMER_LOAD;         // Read current timer value
  OS_U32 time = OS_GetTime32();                // Read current OS time
  if (_IRQSTATUS & (1 << _OS_TIMER_INT_ID)) {  // Timer Interrupt pending ?
    t_cnt = _OS_TIMER_VALUE;                   // Adjust result
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
  Cycles *= _OS_TIMER_PRESCALE;          // eliminate effect of prescaler
  #if (_OS_TIMER_BASE_ADDR == _TIMER3_BASE_ADDR)   // Timer3 uses higher (or external) frequency
    return Cycles/(OS_PCLK_TIMER/1000000);
  #else                                  // Timer1 or timer2 use fixed frequency
    return Cycles * 2;                   // due to frequncy, we get an error of approx. 2%
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
  _OS_UART_DATA  = c;
  _OS_UART_INTEN |= _TX_INT;
}

/*********************************************************************
*
*       OS_COM_Init()
*       Initialize UART for OSView
*/
void OS_COM_Init(void) {  // Initialize UART, enable UART interrupts
  volatile OS_U32 Dummy;

  OS_ARM_DisableISR(_OS_UART_ID);     // Disable timer interrupt.
  // initialize serial port
  _OS_UART_CON   = 0;                 // First disable the UART for setup
  _OS_UART_FCON  = (3 << 5);          // Setup UART as 8bit data, no FIFO, 1 Stopbit, no parity
  _OS_UART_BRCON = _BAUD_INT_PART;
  _OS_UART_INTEN = 0;                 // Disable all UART interrupts
  _OS_UART_CON   = (1 << 0);          // Enable UART
  do {
    Dummy = _OS_UART_DATA;
  } while ((_OS_UART_STATUS & _RX_FIFO_EMPTY) == 0);
  _OS_UART_RAWISR = (1 << 4);         // Clear the modem status interrupt
  _OS_UART_INTEN = _RX_INT            // Enable Receive interrupt
                 | _TX_INT            // Enable Transmit interrupt
                 | _RX_INT_TIMEOUT;   // Enable Receive Timeout interrupt.
  OS_ARM_InstallISRHandler(_OS_UART_ID, &_OS_ISR_UART);
  OS_ARM_EnableISR(_OS_UART_ID);      // Enable UART interrupt of interrupt controller.
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
*       OS_irq_handler
*
*       Detect reason for IRQ and call correspondig service routine.
*       OS_irq_handler is called from OS_IRQ_SERVICE function
*       found in RTOSVect.asm
*/
OS_INTERWORK void OS_irq_handler(void) {
  OS_ISR_HANDLER* pISR;
  int i;
  int ISRIndex;
  int Status;
  Status = _IRQSTATUS;                      // Perform a dummy vector read to update CICR
  for (i = 0; i < NUM_INT_SOURCES; i++) {
    if ((Status & (1L << i)) == (1L << i)) {
      pISR = _apOS_ISRHandler[i];           // Read interrupt vector
#if ALLOW_NESTED_INTERRUPTS
      OS_EnterNestableInterrupt();          // Now interrupts may be reenabled. If nesting should be allowed
#else
      OS_EnterInterrupt();                  // Inform OS that interrupt handler is running
#endif
      if (pISR != NULL) {
        pISR();                             // Call installed interrupt service routine
      } else {
        _OS_ISR_Undefined(ISRIndex);
      }
      OS_DI();                              // Disable interrupts and unlock
#if ALLOW_NESTED_INTERRUPTS
  OS_LeaveNestableInterrupt();              // Leave nestable interrupt, perform task switch if required
#else
  OS_LeaveInterrupt();                      // Leave interrupt, perform task switch if required
#endif
    }
  }
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
  _INTENABLE = (1 << ISRIndex);
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
  _INTENABLECLEAR = (1 << ISRIndex);
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_ISRSetPrio
*/
int OS_ARM_ISRSetPrio(int ISRIndex, int Prio) {
  return 0;
}

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
void MMUSetup(void);                      // LH7A400_MMU.s79

#pragma diag_suppress=Pe940 // IAR specific: No warning for missing return
OS_U32 GetPC(void);
OS_U32 GetPC(void) {
  __asm("mov r0, pc");
}

static __interwork __arm void _SetBusMode(void) {
  OS_U32 MRCValue;
  MRCValue = __MRC(15, 0, 1, 0, 0);
  MRCValue &= 0xC0000000;
  MRCValue |= 0x40000000;
  __MCR(15, 0, MRCValue, 1, 0, 0);
}


OS_INTERWORK int __low_level_init(void);  /* Avoid "no ptototype" warning */
OS_INTERWORK int __low_level_init(void) {
  _SetBusMode();
  _InitPLL();
  if ((GetPC() & 0xC0000000) == 0) {   // Not running in SDRAM ?
    _SetupSDRAM();
  }

  MMUSetup();
  //
  // MMUSetup() initializes the CPU to have the exception vectors on high address base (0xffff0000)
  // This allows to have the complete CS0 area (0x00000000 - 0x0FFFFFFF) available.
  // In order to have the correct exception table at 0xffff0000, we shall copy the orginal
  // expection base address to the said address.
  //
#if DEBUG
  #define VECTOR_BASE_ADDR   0xC0000000
#else
  #define VECTOR_BASE_ADDR   0x00000000
#endif
  //
  // Copy exception vectors from Program start (in SDRAM) into RAM at 0xFFFF0000
  //
  memcpy((void *)0xFFFF0000, (void *)VECTOR_BASE_ADDR, 0x40);
  return 1;
}

/*****  EOF  ********************************************************/

