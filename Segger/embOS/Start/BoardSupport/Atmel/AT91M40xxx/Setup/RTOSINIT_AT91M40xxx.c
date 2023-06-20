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
File    : RTOSInit.c   (for ATMEL AT91M40800 CPU and IAR compiler)
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
  #define OS_FSYS 66000000
#endif

#ifndef   OS_TICK_FREQ
  #define OS_TICK_FREQ 1000
#endif

#define   OS_TIMER_PRESCALE  2        // prescaler for timer frequency

#ifndef   OS_PCLK_TIMER
  #define OS_PCLK_TIMER OS_FSYS
#endif

#ifndef   OS_PCLK_UART
  #define OS_PCLK_UART OS_FSYS
#endif

#ifndef   OS_UART
  #define OS_UART 1
#endif

#ifndef   OS_BAUDRATE
  #define OS_BAUDRATE 38400
#endif

/****** End of configuration settings *******************************/

#define OS_UART_USED ((OS_UART == 0) || (OS_UART == 1))

/*********************************************************************
*
*       Local defines (sfrs used in RTOSInit.c)
*
**********************************************************************
*/

/*      USART0 */
#define __US_CR     *(volatile OS_U32*)0xfffd0000
#define __US_MR     *(volatile OS_U32*)0xfffd0004
#define __US_IER    *(volatile OS_U32*)0xfffd0008
#define __US_IDR    *(volatile OS_U32*)0xfffd000c
#define __US_IMR    *(volatile OS_U32*)0xfffd0010
#define __US_CSR    *(volatile OS_U32*)0xfffd0014
#define __US_RHR    *(volatile OS_U32*)0xfffd0018
#define __US_THR    *(volatile OS_U32*)0xfffd001c
#define __US_BRGR   *(volatile OS_U32*)0xfffd0020
#define __US_RTOR   *(volatile OS_U32*)0xfffd0024
#define __US_TTGR   *(volatile OS_U32*)0xfffd0028

/*      USART1 */
#define __US_CR1    *(volatile OS_U32*)0xfffcc000
#define __US_MR1    *(volatile OS_U32*)0xfffcc004
#define __US_IER1   *(volatile OS_U32*)0xfffcc008
#define __US_IDR1   *(volatile OS_U32*)0xfffcc00c
#define __US_IMR1   *(volatile OS_U32*)0xfffcc010
#define __US_CSR1   *(volatile OS_U32*)0xfffcc014
#define __US_RHR1   *(volatile OS_U32*)0xfffcc018
#define __US_THR1   *(volatile OS_U32*)0xfffcc01c
#define __US_BRGR1  *(volatile OS_U32*)0xfffcc020
#define __US_RTOR1  *(volatile OS_U32*)0xfffcc024
#define __US_TTGR1  *(volatile OS_U32*)0xfffcc028

/*      PIO control register */
#define __PIO_PDR   *(volatile OS_U32*)0xffff0004  // PIO A disable register

/*      Timer 0  */
#define __TC_CCRC0  *(volatile OS_U32*)0xfffe0000
#define __TC_CMRC0  *(volatile OS_U32*)0xfffe0004
#define __TC_CVC0   *(volatile OS_U32*)0xfffe0010
#define __TC_RCC0   *(volatile OS_U32*)0xfffe001c
#define __TC_SRC0   *(volatile OS_U32*)0xfffe0020
#define __TC_IERC0  *(volatile OS_U32*)0xfffe0024
#define __TC_IDRC0  *(volatile OS_U32*)0xfffe0028
#define __TC_BMR    *(volatile OS_U32*)0xfffe00c4

/*      Peripheral clock enable register */
#define __PCER      *(volatile OS_U32*)0xffff4004

/*      Advanced interrupt controller (AIC) */
#define __AIC_SMR2  *(volatile OS_U32*)0xfffff008
#define __AIC_SMR3  *(volatile OS_U32*)0xfffff00c
#define __AIC_SMR4  *(volatile OS_U32*)0xfffff010
#define __AIC_SVR2  *(volatile OS_U32*)0xfffff088
#define __AIC_SVR3  *(volatile OS_U32*)0xfffff08c
#define __AIC_SVR4  *(volatile OS_U32*)0xfffff090
#define __AIC_IVR   *(volatile OS_U32*)0xfffff100
#define __AIC_IPR   *(volatile OS_U32*)0xfffff10c
#define __AIC_ICCR  *(volatile OS_U32*)0xfffff128
#define __AIC_IECR  *(volatile OS_U32*)0xfffff120
#define __AIC_EOICR *(volatile OS_U32*)0xfffff130

/*      Advanced interrupt controller interrupt sources */
#define US0IRQ 2  /* USART channel 0 interrupt          */
#define US1IRQ 3  /* USART channel 1 interrupt          */
#define TC0IRQ 4  /* Timer channel 0 interrupt          */

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

/*********************************************************************
*
*       OS_Tick interrupt Handler
*/
static void OS_ISR_Tick (void) {
  volatile OS_U32 Dummy;

  Dummy = __TC_SRC0;    // Reset Timer Interrupt to reset/reenable further interrupts
  OS_HandleTick();      // Call OS tick handler
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
#define TIMER_RELOAD OS_PCLK_TIMER/OS_TIMER_PRESCALE/OS_TICK_FREQ
#define TIMER_ID TC0IRQ

void OS_InitHW(void) {
  volatile OS_U32 Dummy;

  OS_DI();
  // Initialize OS timer (timer 0, capture mode channel C)
  __PCER     = (1 << TIMER_ID);     // Enable peripheral clock for timer 0
  __TC_IDRC0 = 0xff;                // Disable all timer/counter 0 interrupts.
  __TC_BMR   = 0x02;                // Runs on internal clock
  __TC_CMRC0 = 0x00004000;          // Capture mode, CPCTRG=1, TCCLKS=0 (=> MCLK/2)
  __TC_RCC0  = TIMER_RELOAD;        // Set compare register
  __TC_CCRC0 = 1;                   // Enable the clock.
  __TC_CCRC0 = 5;                   // Software trigger.
  Dummy      = __TC_SRC0;           // Read timer/counter 0 status register to clear flags.
  __TC_IERC0 = (1<<4);              // Interrupt on RC compare.
  // Setup interrupt controller for OS timer interrupt using timer 0
  __AIC_ICCR = 0x40;                // Clears timer/counter 0 interrupt.
  __AIC_SVR4 = (unsigned long)&OS_ISR_Tick; // Timer/counter 0 interrupt vector.
  __AIC_SMR4 = 0x00;                // Timer/counter 0 interrupt level sensitive at lowest priority (0).
  __AIC_ICCR = (1 << TIMER_ID);     // Clears timer/counter 0 interrupt.
  __AIC_IECR = (1 << TIMER_ID);     // Enable timer/counter 0 interrupt.
  // optionally initialize UART for OSView
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
  unsigned int t_cnt = __TC_CVC0;     // Read current timer value
  OS_U32 time = OS_GetTime32();       // Read current OS time
  if (__AIC_IPR & ( 1 << TIMER_ID)) { // Timer Interrupt pending ?
    t_cnt = __TC_CVC0;                // Adjust result
    time++;
  }
  return TIMER_RELOAD*time + t_cnt;
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
  Cycles *= OS_TIMER_PRESCALE;           // eliminate effect of prescaler
  return Cycles/(OS_PCLK_TIMER/1000000);
}

/*********************************************************************
*
*       Communication for OSView via UART (optional)
*
**********************************************************************
*/
#if OS_UART_USED

#if (OS_UART == 0)         // Assign internal sfr names to USART0 sfrs
  #define US_CR   __US_CR
  #define US_MR   __US_MR
  #define US_IER  __US_IER
  #define US_IDR  __US_IDR
  #define US_IMR  __US_IMR
  #define US_CSR  __US_CSR
  #define US_RHR  __US_RHR
  #define US_THR  __US_THR
  #define US_BRGR __US_BRGR
  #define US_RTOR __US_RTOR
  #define US_TTGR __US_TTGR
  #define AIC_SMR __AIC_SMR2
  #define AIC_SVR __AIC_SVR2
  #define USART_ID US0IRQ
  #define PIO_PDR_USART ((1<<14) | (1<<15))
#elif (OS_UART == 1)       // Assign internal sfr names to USART1 sfrs
  #define US_CR   __US_CR1
  #define US_MR   __US_MR1
  #define US_IER  __US_IER1
  #define US_IDR  __US_IDR1
  #define US_IMR  __US_IMR1
  #define US_CSR  __US_CSR1
  #define US_RHR  __US_RHR1
  #define US_THR  __US_THR1
  #define US_BRGR __US_BRGR1
  #define US_RTOR __US_RTOR1
  #define US_TTGR __US_TTGR1
  #define AIC_SMR __AIC_SMR3
  #define AIC_SVR __AIC_SVR3
  #define USART_ID US1IRQ
  #define PIO_PDR_USART ((1<<21) | (1<<22))
#endif

#define US_RXRDY 0x01                    // Rx status flag
#define US_TXRDY 0x02                    // Tx Status flag
#define USART_RX_ERROR_FLAGS 0xE0        // Parity, framing, overrun error

/*********************************************************************
*
*       OS_COM_ISR_Usart() OS USART interrupt handler
*       handles both, Rx and Tx interrupt
*/
static void OS_COM_ISR_Usart(void) {
  int UsartStatus;
  volatile OS_U32 Dummy;

  do {
    UsartStatus = US_CSR;                  // Examine status register
    if (UsartStatus & US_RXRDY) {          // Check Rx status
      if (UsartStatus & USART_RX_ERROR_FLAGS) {  // Any error ?
        Dummy = US_RHR;                    // => Discard data
        US_CR = (1<<8);                    // RSTSTA: Reset Status Bits PARE, FRAME, OVRE and RXBRK
      } else {
        OS_OnRx(US_RHR);                   // Process actual byte
      }
    }
    if (UsartStatus & US_IMR & US_TXRDY) { // Check Tx status => Send next character
      if (OS_OnTx()) {                     // No more characters to send ?
        US_IDR = US_TXRDY;                 // Disable further tx interrupts
      }
    }
  } while (UsartStatus & US_IMR & (US_TXRDY | US_RXRDY));
}

/*********************************************************************
*
*       OS_COM_Send1()
*       Never call this function directly from your application
*/
void OS_COM_Send1(OS_U8 c) {
  US_THR = c;         // Send character
  US_IER = US_TXRDY;  // enable Tx Empty interrupt
}

/*********************************************************************
*
*       OS_COM_Init()
*       Initialize UART for OSView
*/
void OS_COM_Init(void) {  // Initialize UART, enable UART interrupts
  // initialize serial port
  __PCER  = (1 << USART_ID);     // Enable peripheral clock for selected USART
  __PIO_PDR   = PIO_PDR_USART;   // Enable peripheral output signals (disable PIO Port A)
  /* Init UART */
  US_CR   = (1 <<  2) |          // RSTRX: Reset Receiver: 1 = The receiver logic is reset.
            (1 <<  3);           // RSTTX: Reset Transmitter: 1 = The transmitter logic is reset.
  US_CR   = (0 <<  2) |          // RSTRX: Reset Receiver: 1 = The receiver logic is reset.
            (0 <<  3) |          // RSTTX: Reset Transmitter: 1 = The transmitter logic is reset.
            (1 <<  4) |          // RXEN: Receiver Enable: 1 = The receiver is enabled if RXDIS is 0.
            (0 <<  5) |          // RXDIS: Receiver Disable: 0 = Noeffect.
            (1 <<  6) |          // TXEN: Transmitter Enable: 1 = The transmitter is enabled if TXDIS is 0.
            (0 <<  7) |          // TXDIS: Transmitter Disable: 0 = Noeffect.
            (1 <<  8) |          // RSTSTA: Reset Status Bits: 1 = Resets the status bits PARE, FRAME, OVRE and RXBRK in the US_CSR.
            (0 <<  9) |          // STTBRK: Start Break: 0 = Noeffect.
            (0 << 10) |          // STPBRK: Stop Break: 0 = Noeffect.
            (0 << 11) |          // STTTO: Start Time-out: 0 = Noeffect.
            (0 << 12);           // SENDA: Send Address: 0 = Noeffect.
  US_MR   = (0 <<  4) |          // USCLKS: Clock Selection: 0 = MCK
            (3 <<  6) |          // CHRL: Character Length: 3 = Eight bits
            (0 <<  8) |          // SYNC: Synchronous Mode Select: 0 = USART operates in Asynchronous Mode.
          (0x4 <<  9) |          // PAR: Parity Type: 0x4 = No parity
            (0 << 12) |          // NBSTOP: Number of Stop Bits: 0 = 1 stop bit
            (0 << 14) |          // CHMODE: Channel Mode: 0 = Normal mode
            (0 << 17) |          // MODE9: 9-bit Character Length: 0 = CHRL defines character length.
            (0 << 18);           // CKLO: Clock Output Select: 0 = The USART does not drive the SCK pin.
  US_BRGR = (OS_PCLK_UART / (OS_BAUDRATE * 16));
  US_IER  = (1<<0) |             // Enable Rx Interrupt
            (1<<1);              // (Enable Tx Interrupt
  // Setup interrupt controller for OS USART
  AIC_SVR = (unsigned long)&OS_COM_ISR_Usart; // OS UART interrupt handler vector
  AIC_SMR = 0x00;                             // Level sensitive, lowest priority (0).
  __AIC_ICCR = (1 << USART_ID);               // Clear OS usart interrupt.
  __AIC_IECR = (1 << USART_ID);               // Enable OS usart interrupts
}

#else  /* selected UART not supported, using dummies */

void OS_COM_Init(void) {}
void OS_COM_Send1(OS_U8 c) {
  OS_USEPARA(c);           // avoid compiler warning
  OS_COM_ClearTxActive();  // let OS know that Tx is not busy
}

#endif /*  OS_UART_USED  */

/*********************************************************************
*
*       OS_irq_handler
*
*       Detect reason for IRQ and call correspondig service routine.
*       OS_irq-handler is called from OS_IRQ_SERVICE function
*       found in RTOSVect.asm
*/
typedef void (voidISRHandler)(void);
typedef char tpfVoid(void);

OS_INTERWORK void OS_irq_handler(void) {
  tpfVoid* pISR;
  pISR = (tpfVoid*) __AIC_IVR;  // Read interrupt vector to release NIRQ to CPU core
#if ALLOW_NESTED_INTERRUPTS
  OS_EnterNestableInterrupt();  // Now interrupts may be reenabled. If nesting should be allowed
#else
  OS_EnterInterrupt();          // Inform OS that interrupt handler is running
#endif
  (*pISR)();                    // Call interrupt service routine
  OS_DI();                      // Disable interrupts and unlock
  __AIC_EOICR = 0;              // interrupt controller =>  Restore previous priority
#if ALLOW_NESTED_INTERRUPTS
  OS_LeaveNestableInterrupt();  // Leave nestable interrupt, perform task switch if required
#else
  OS_LeaveInterrupt();          // Leave interrupt, perform task switch if required
#endif
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

