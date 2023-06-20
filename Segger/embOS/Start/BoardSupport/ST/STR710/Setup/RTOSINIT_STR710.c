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
File    : RTOSINIT_STR710.c   (for ST STR710 CPUs)
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
  #define OS_FSYS 48000000L         /* may depend on PLL            */
#endif

#ifndef   OS_PCLK_TIMER             /* Peripheral clock for timer   */
  #define OS_PCLK_TIMER OS_FSYS/2   /* May vary from CPU clock      */
#endif                              /* depending on CPU             */

#ifndef   OS_PCLK_UART              /* Peripheral clock for UART    */
  #define OS_PCLK_UART OS_FSYS/2    /* May vary from CPU clock      */
#endif                              /* depending on CPU             */

#ifndef   OS_INIT_PLL               /* PLL may be initialized       */
  #define OS_INIT_PLL 1             /* during startup               */
#endif

#define _OS_TIMER_INTERVAL (OS_PCLK_TIMER / 1000)

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

/****** End of configuration settings *******************************/

#define OS_UART_USED ((OS_UART == 0) || (OS_UART == 1) || (OS_UART == 2) || OS_UART == 3)

/*********************************************************************
*
*       Local defines (sfrs used in RTOSInit.c)
*
**********************************************************************
*/

/****** UART sfdr definition ****************************************/
/****** UART0 *******************************************************/

#define __UART0_BASE_ADDR   0xC0004000
#define __UART1_BASE_ADDR   0xC0005000
#define __UART2_BASE_ADDR   0xC0006000
#define __UART3_BASE_ADDR   0xC0007000

#define __UART_BR_OFFS     0x00
#define __UART_TxBUFR_OFFS 0x04
#define __UART_RxBUFR_OFFS 0x08
#define __UART_CR_OFFS     0x0C
#define __UART_IER_OFFS    0x10
#define __UART_SR_OFFS     0x14
#define __UART_GTR_OFFS    0x18
#define __UART_TOR_OFFS    0x1C
#define __UART_TxRSTR_OFFS 0x20
#define __UART_RxRSTR_OFFS 0x24

/****** Assign UART sfrs used for OSView communication ***********/

#if OS_UART_USED
  #if   (OS_UART == 0)
    #define _OS_UART_BASE_ADDR __UART0_BASE_ADDR
    #define _OS_UART_ID   UART0_VECT_ID
    #define _UART_RX_PIN  (0x0001<<8)
    #define _UART_TX_PIN  (0x0001<<9)
  #elif (OS_UART == 1)
    #define _OS_UART_BASE_ADDR __UART1_BASE_ADDR
    #define _OS_UART_ID   UART1_VECT_ID
    #define _UART_RX_PIN  (0x0001<<10)
    #define _UART_TX_PIN  (0x0001<<11)
  #elif (OS_UART == 2)
    #define _OS_UART_BASE_ADDR __UART2_BASE_ADDR
    #define _OS_UART_ID   UART2_VECT_ID
    #define _UART_RX_PIN  (0x0001<<13)
    #define _UART_TX_PIN  (0x0001<<14)
  #elif (OS_UART == 3)
    #define _OS_UART_BASE_ADDR __UART3_BASE_ADDR
    #define _OS_UART_ID   UART3_VECT_ID
    #define _UART_RX_PIN  (0x0001<<1)
    #define _UART_TX_PIN  (0x0001<<0)
  #endif

  #define _OS_UART_BR      *(volatile OS_U16*)(_OS_UART_BASE_ADDR + __UART_BR_OFFS)
  #define _OS_UART_TxBUFR  *(volatile OS_U16*)(_OS_UART_BASE_ADDR + __UART_TxBUFR_OFFS)
  #define _OS_UART_RxBUFR  *(volatile OS_U16*)(_OS_UART_BASE_ADDR + __UART_RxBUFR_OFFS)
  #define _OS_UART_CR      *(volatile OS_U16*)(_OS_UART_BASE_ADDR + __UART_CR_OFFS)
  #define _OS_UART_IER     *(volatile OS_U16*)(_OS_UART_BASE_ADDR + __UART_IER_OFFS)
  #define _OS_UART_SR      *(volatile OS_U16*)(_OS_UART_BASE_ADDR + __UART_SR_OFFS)
  #define _OS_UART_GTR     *(volatile OS_U16*)(_OS_UART_BASE_ADDR + __UART_GTR_OFFS)
  #define _OS_UART_TOR     *(volatile OS_U16*)(_OS_UART_BASE_ADDR + __UART_TOR_OFFS)
  #define _OS_UART_TxRSTR  *(volatile OS_U16*)(_OS_UART_BASE_ADDR + __UART_TxRSTR_OFFS)
  #define _OS_UART_RxRSTR  *(volatile OS_U16*)(_OS_UART_BASE_ADDR + __UART_RxRSTR_OFFS)

  #define _TX_EMPTY_INT_BIT 2
  #define _RX_FULL_INT_BIT  0
  #define _UART_RX_ERROR_FLAGS ((1 << 3) | (1 << 4) | (1 << 5))  // Parity, framing, overrun error
  #define _OS_UART_PRIO     0x01     // lowest priority for OS UART interrupts
  #define _TXRDY_FLAG       (1 << _TX_EMPTY_INT_BIT)
  #define _RXRDY_FLAG       (1 << _RX_FULL_INT_BIT)
#endif

/****** GPIO register ***********************************************/

#define __IOPORT0_BASE_ADDR   0xE0003000

#define __GPIO0_PC0 *(volatile OS_U16*)(__IOPORT0_BASE_ADDR + 0x00)
#define __GPIO0_PC1 *(volatile OS_U16*)(__IOPORT0_BASE_ADDR + 0x04)
#define __GPIO0_PC2 *(volatile OS_U16*)(__IOPORT0_BASE_ADDR + 0x08)
#define __GPIO0_PD  *(volatile OS_U16*)(__IOPORT0_BASE_ADDR + 0x0C)

/****** Power, reset clock control unit register ********************/

#define __PRCCU_CFR    *(volatile OS_U32*)0xA0000008
#define __PRCCU_PLL1CR *(volatile OS_U32*)0xA0000018
#define __PRCCU_PDIVR  *(volatile OS_U32*)0xA0000044

/****** Timer sfr definition ****************************************/

#define __TIM0_BASE_ADDR     0xE0009000
#define __TIM1_BASE_ADDR     0xE000A000
#define __TIM2_BASE_ADDR     0xE000B000
#define __TIM3_BASE_ADDR     0xE000C000

#define __TIM_ICAR_OFFS 0x00
#define __TIM_ICBR_OFFS 0x04
#define __TIM_OCAR_OFFS 0x08
#define __TIM_OCBR_OFFS 0x0C
#define __TIM_CNTR_OFFS 0x10
#define __TIM_CR1_OFFS  0x14
#define __TIM_CR2_OFFS  0x18
#define __TIM_SR_OFFS   0x1C

/****** Assign timer sfrs used for OS timer *************************/
/****** initially, we use timer 1        ****************************/

#define _OS_TIM_BASE_ADDR        __TIM1_BASE_ADDR
#define _OS_TIM_OCR         *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + __TIM_OCAR_OFFS)
#define _OS_TIM_CR1         *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + __TIM_CR1_OFFS)
#define _OS_TIM_CR2         *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + __TIM_CR2_OFFS)
#define _OS_TIM_CNTR        *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + __TIM_CNTR_OFFS)
#define _OS_TIM_SR          *(volatile OS_U16*)(_OS_TIM_BASE_ADDR + __TIM_SR_OFFS)

#define _TIMER_INT_BIT_NO  14

/****** PLL *********************************************************/

//#define __APMC_CGMR  *(volatile unsigned int*)0xffff4020
//#define __APMC_SR    *(volatile unsigned int*)0xffff4030

/****** Enhanced interrupt controller (EIC) *************************/

#define __EIC_ICR   *(volatile OS_U32*)0xfffff800
#define __EIC_CICR  *(volatile OS_U32*)0xfffff804
#define __EIC_CPIR  *(volatile OS_U32*)0xfffff808
#define __EIC_IVR   *(volatile OS_U32*)0xfffff818
#define __EIC_FIR   *(volatile OS_U32*)0xfffff81C
#define __EIC_IER   *(volatile OS_U32*)0xfffff820
#define __EIC_IPR   *(volatile OS_U32*)0xfffff840
#define __EIC_SIR0  *(volatile OS_U32*)0xfffff860

/****** Enhanced interrupt controller interrupt sources *************/

#define T0_EFTI_VECT_ID    0  // IRQ0  T0.EFTI Timer 0 global interrupt 5
#define FLASH_VECT_ID      1  // IRQ1  FLASH FLASH global interrupt
#define PRCCU_VECT_ID      2  // IRQ2  PRCCU PRCCU global interrupt
#define RTC_VECT_ID        3  // IRQ3  RTC Real Time Clock global interrupt 2
#define WDG_VECT_ID        4  // IRQ4  WDG.IRQ Watchdog timer interrupt 1
#define XTI_VECT_ID        5  // IRQ5  XTI.IRQ XTI external interrupt 16
#define USB_VECT_ID        6  // IRQ6  USB.HPIRQ USB high priority event interrupt 0-7
#define I2C0_ERR_VECT_ID   7  // IRQ7  I2C0.ITERR I2C 0 error interrupt
#define I2C1_ERR_VECT_ID   8  // IRQ8  I2C1.ITERR I2C 1 error interrupt
#define UART0_VECT_ID      9  // IRQ9  UART0.IRQ UART 0 global interrupt 9
#define UART1_VECT_ID     10  // IRQ10 UART1.IRQ UART 1 global interrupt 9
#define UART2_VECT_ID     11  // IRQ11 UART2.IRQ UART 2 global interrupt 9
#define UART3_VECT_ID     12  // IRQ12 UART3.IRQ UART 3 global interrupt 9
#define SPI0_VECT_ID      13  // IRQ13 SPI0.IRQ BSPI 0 global interrupt 5
#define SPI1_VECT_ID      14  // IRQ14 SPI1.IRQ BSPI 1 global interrupt 5
#define I2C0_VECT_ID      15  // IRQ15 I2C0.Iobal interrupt 32
#define ADC_VECT_ID       18  // IRQ18 ADC.IRQ ADC sample ready interrupt 1
#define T1_GI_VECT_ID     19  // IRQ19 T1.GI Timer 1 global interrupt 5
#define T2_GI_VECT_ID     20  // IRQ20 T2.GI Timer 2 global interrupt 5
#define T3_GI_VECT_ID     21  // IRQ21 T3.GI Timer 3 global interrupt 5
#define Reserved1_VECT_ID 22  // IRQ22 Reserved
#define Reserved2_VECT_ID 23  // IRQ23 Reserved
#define Reserved3_VECT_ID 24  // IRQ24 Reserved
#define HDLC_IR_VECT_ID   25  // IRQ25 HDLC.IRQ HDLC global interrupt
#define USB_LPI_VECT_ID   26  // IRQ26 USB.LPIRQ USB low priority event interrupt 7-15
#define Reserved4_VECT_ID 27  // IRQ27 Reserved
#define Reserved5_VECT_ID 28  // IRQ28 Reserved
#define T0_TOI_VECT_ID    29  // IRQ29 T0.TOI Timer 0 Overflow interrupt 1
#define T0_OC1_VECT_ID    30  // IRQ30 T0.OC1 Timer 0 Output Compare 1 interrupt 1
#define T0_OC2_VECT_ID    31  // IRQ31 T0.OC2 Timer 0 Output Compare 2 interrupt 1

#ifndef NUM_INT_SOURCES
  #define NUM_INT_SOURCES  32
#endif
#define _INT_CHANNEL_MASK  0x1F

#define _INT_PRIORITY_MASK 0x0F

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
*       _InitPLL
*
* Function description
*   Initialize main clock and PLL
*   Should be called as early as possible in order to keep boot time short
*   WARNING: Improper settings may lock CPU
*   Please examine whether init sequence fits your harware configuration
*   We assume a CPU running with external 16MHz oscillator and switch to 48 MHz
*/
static void _InitPLL(void) {
  #if OS_INIT_PLL
    __PRCCU_PDIVR = (1 << 8) | (1 << 0); // Divide peripheral clocks by two (to ensure max. clock limit)
    __PRCCU_PLL1CR = (__PRCCU_PLL1CR & 0xFF00) | 0x0051;
    __PRCCU_CFR   |= (1 << 15) | (1 << 3) | (1 << 0);
  #endif
}

/*********************************************************************
*
*       OS_Tick interrupt Handler
*/
static void _OS_ISR_Tick(void) {
  _OS_TIM_SR  &= ~(1 << _TIMER_INT_BIT_NO);  // Clear OS timer interrupt flag
  _OS_TIM_OCR += _OS_TIMER_INTERVAL;         // Advance to next count;
  OS_HandleTick();                           // Call OS tick handler
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
*       OS_InitHW()
*
*       Initialize the hardware (timer) required for the OS to run.
*       May be modified, if an other timer should be used
*/
#define _OS_TIMER_ID     T1_GI_VECT_ID  // Assign to TC1 global interrupt
#define _OS_TIMER_PRIO   0x01           // lowest priority

void OS_InitHW(void) {
  OS_DI();
  // Initialize Peripheral clock divider
  __PRCCU_PDIVR = (1 << 8) | (1 << 0); // Divide peripheral clocks by two (to ensure max. clock limit)
  // Initialize timer for OS, we use Timer 1
  _OS_TIM_CR1 = 0;                     // Stop timer, reset mode
  _OS_TIM_CR2 = 0;                     // Disable all interrupts, clear prescaler
  _OS_TIM_OCR = _OS_TIMER_INTERVAL;    // Setup compare register, initially use 1000 ticks per second
  _OS_TIM_CR1 = (1 << 15);             // Start timer
  _OS_TIM_CR2 = (1 << 14);             // Enable output capture interrupt A

  OS_ARM_InstallISRHandler(_OS_TIMER_ID, &_OS_ISR_Tick); // Timer/counter interrupt vector.
  OS_ARM_ISRSetPrio(_OS_TIMER_ID, _OS_TIMER_PRIO);       // Timer/counter interrupt priority.
  OS_ARM_EnableISR(_OS_TIMER_ID);                        // Enable timer/counter 0 interrupt.
  // optionally initialize UART for OSView
  OS_COM_Init();
  __EIC_ICR |= 0x01; // Enable interrupt controller
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
  OS_I16 count;

  time  = _OS_TIM_CNTR;
  count = _OS_TIM_OCR - time;            // Read current timer value
  time  = OS_GetTime32();                // Read current OS time
  if (count < 0) {                       // Timer Interrupt pending ?
    time++;                              // Adjust result, read timer again
    count = 0 - count;
  } else {
    count = _OS_TIMER_INTERVAL - count;
  }
  return (_OS_TIMER_INTERVAL) * time + count;
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

/*********************************************************************
*
*       OS_COM_ISR_Usart() OS USART interrupt handler
*       handles both, Rx and Tx interrupt
*/
static void _OS_COM_ISR(void) {
  int UartStatus;
  volatile OS_U32 Dummy;

  do {
    UartStatus = _OS_UART_SR;                      // Examine status register
    if (UartStatus & _RXRDY_FLAG) {                // Data received?
      if (UartStatus & _UART_RX_ERROR_FLAGS) {     // Any error ?
        Dummy = _OS_UART_RxBUFR;                   // => Discard data
      } else {
        OS_OnRx(_OS_UART_RxBUFR);                  // Process actual byte
      }
    }
    if (UartStatus & _TXRDY_FLAG) {                // Check Tx status => Send next character
      _OS_UART_SR &= ~_TXRDY_FLAG;                 // Clear Tx Int
      if (OS_OnTx()) {                             // No more characters to send ?
        _OS_UART_IER &= ~(1 << _TX_EMPTY_INT_BIT); // Disable further tx interrupts
      }
    }
  } while (UartStatus & _OS_UART_IER & (_TXRDY_FLAG | _RXRDY_FLAG));
}

/*********************************************************************
*
*       OS_COM_Send1()
*       Never call this function directly from your application
*/
void OS_COM_Send1(OS_U8 c) {
  _OS_UART_TxBUFR = c;                       // Send character
  _OS_UART_IER |= (1 << _TX_EMPTY_INT_BIT);  // enable Tx Empty interrupt
}

/*********************************************************************
*
*       OS_COM_Init()
*       Initialize UART for OSView
*/
#define _BAUDDIVIDE ((OS_PCLK_UART+OS_BAUDRATE*8L)/(OS_BAUDRATE*16L))

void OS_COM_Init(void) {
  OS_DI();
  // Setup Port-Mode to alternate function, TX: push-pull, RX: open drain, CMOS input
  __GPIO0_PC0 &= ~(_UART_RX_PIN);               // Rx set to open drain
  __GPIO0_PC0 |= _UART_TX_PIN;                  // Tx set to push pull
  __GPIO0_PC1 |= (_UART_RX_PIN | _UART_TX_PIN); // Select alternate function
  __GPIO0_PC2 &= ~(_UART_RX_PIN);               // Select CMOS input
  __GPIO0_PC2 |= _UART_TX_PIN;                  // Select output

  _OS_UART_BR = _BAUDDIVIDE;  // Setup baudrate generator
  _OS_UART_CR =  0x01         // Setup UART control register, 8 data bits
               | (1 << 3)     // 1 Stop bit (bit 4:3 = 01)
               | (0 << 5)     // Parity, don't care
               | (0 << 6)     // Loopback disabled
               | (1 << 7)     // Baudrate generator on
               | (1 << 8)     // Rx Enable
               | (0 << 9)     // Smartcard mode disabled
               | (0 << 10);   // FIFO disabled

  _OS_UART_TxRSTR = 0;        // Clear Rx FIFO
  _OS_UART_RxRSTR = 0;        // Clear Tx FIFO
  /*  Install OS UART interrupt handler */
  OS_ARM_InstallISRHandler(_OS_UART_ID, &_OS_COM_ISR); // UART interrupt vector.
  OS_ARM_ISRSetPrio(_OS_UART_ID, _OS_UART_PRIO);       // UART interrupt level.
  OS_ARM_EnableISR(_OS_UART_ID);                       // Enable OS UART interrupt
  _OS_UART_IER |= (1 << _RX_FULL_INT_BIT);             // Enable Rx interrupts
  OS_RestoreI();
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
  ISRIndex = __EIC_IVR;                       // Perform a dummy vector read to update CICR
  ISRIndex = __EIC_CICR & _INT_CHANNEL_MASK;  // Examine current interrupt source (channel number)
  pISR = _apOS_ISRHandler[ISRIndex];          // Read interrupt vector
#if ALLOW_NESTED_INTERRUPTS
  OS_EnterNestableInterrupt();                // Now interrupts may be reenabled. If nesting should be allowed
#else
  OS_EnterInterrupt();                        // Inform OS that interrupt handler is running
#endif
  if (pISR != NULL) {
    pISR();                                   // Call installed interrupt service routine
  } else {
    _OS_ISR_Undefined(ISRIndex);
  }
  OS_DI();                                    // Disable interrupts and unlock
  __EIC_IPR |= (1 << ISRIndex);               // Clear current interrupt pending bit, reset EIC
#if ALLOW_NESTED_INTERRUPTS
  OS_LeaveNestableInterrupt();                // Leave nestable interrupt, perform task switch if required
#else
  OS_LeaveInterrupt();                        // Leave interrupt, perform task switch if required
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
  __EIC_IER |= (1 << ISRIndex);
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
  __EIC_IER &= ~(1 << ISRIndex);
  OS_RestoreI();
}

/*********************************************************************
*
*       OS_ARM_ISRSetPrio
*/
int OS_ARM_ISRSetPrio(int ISRIndex, int Prio) {
  OS_U32* pPrio;
  int     OldPrio;
#if DEBUG
  if ((unsigned)ISRIndex >= NUM_INT_SOURCES) {
    OS_Error(OS_ERR_ISR_INDEX);
    return 0;
  }
#endif

  OS_DI();
  pPrio = (OS_U32*)&__EIC_SIR0;
  OldPrio = pPrio[ISRIndex];
  pPrio[ISRIndex] = (OldPrio & ~_INT_PRIORITY_MASK) | (Prio & _INT_PRIORITY_MASK);
  OS_RestoreI();
  return OldPrio & _INT_PRIORITY_MASK;
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
  return 1;                       // Always initialize segments !
}

/*****  EOF  ********************************************************/
