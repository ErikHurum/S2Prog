/*********************************************************************
*               SEGGER MICROCONTROLLER GmbH & Co KG                  *
*       Solutions for real time microcontroller applications         *
**********************************************************************
*                                                                    *
*       (c) 1995 - 2012  SEGGER Microcontroller GmbH & Co KG         *
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
*
*                                                                    *       Thank you for your fairness !                                *
*                                                                    *
**********************************************************************
*                                                                    *
*       OS version: 3.86g                                            *
*                                                                    *
**********************************************************************

----------------------------------------------------------------------
Licensing information
Licensor:                 SEGGER Microcontroller GmbH
Licensed to:              Scanjet Ariston AS, Moen  12, 3948  Porsgrunn, Norway
Licensed SEGGER software: embOS
License number:           OS-01417
License model:            SOL [Single Developer Single Platform Object Code License]
Licensed product:         -
Licensed platform:        AtMega 128, IAR
Licensed number of seats: 1
----------------------------------------------------------------------
Support and Update Agreement (SUA)
SUA period:               2022-12-21 - 2023-06-22
Contact to extend SUA:    sales@segger.com
----------------------------------------------------------------------
File    : RTOSInit_ATmega128.c for ATmega128 CPU and IAR compiler

Purpose : Initializes and handles the hardware for embOS as far
          as required by embOS
          Feel free to modify this file acc. to your target system.
--------  END-OF-HEADER  ---------------------------------------------
*/

#include "RTOS.h"
#include "iom1281.h"
#include "constants.h"
#include "inavr.h"
/*
#if (((__TID__ >> 4) & 0x0F) == 1)
  #include "IO8535.H"
#elif (((__TID__ >> 4) & 0x0F) == 3)
  #include "IOM603.H"
#else
  #error "This CPU version (selected by -v) is not supported !"
#endif
*/

/*********************************************************************
*
*       Configuration
*
**********************************************************************
*/

/*********************************************************************
*
*       Clock frequency settings
*/
#ifndef   OS_FSYS                   /* CPU Main clock frequency     */
#define OS_FSYS 16000000LuL        /* Assume 16 MHz            */
#endif

#ifndef   OS_PCLK_TIMER             /* Peripheral clock for timer   */
    #define OS_PCLK_TIMER (OS_FSYS)   /* May vary from CPU clock      */
#endif                              /* depending on CPU             */

#ifndef   OS_PCLK_UART              /* Peripheral clock for UART    */
    #define OS_PCLK_UART (OS_FSYS)    /* May vary from CPU clock      */
#endif                              /* depending on CPU             */

#ifndef   OS_TICK_FREQ
    #define OS_TICK_FREQ (1000)
#endif

/*********************************************************************
*
*       Configuration of communication to OSView
*/
#ifndef   OS_VIEW_ENABLE            // Global enable of communication
    #define OS_VIEW_ENABLE    (1)     // Default: on
#endif

#ifndef   OS_VIEW_USE_UART          // If set, UART will be used for communication
    #define OS_VIEW_USE_UART  (1)     // Default: 1 => Uart is used
#endif                              // if OS_VIEW_ENABLE is on

/*********************************************************************
*
*       UART settings for OSView
*       If you do not want (or can not due to hardware limitations)
*       to dedicate a UART to OSView, please define it to be -1
*       Currently UART1 is supported and the standard
*       setup enables UART1 per default
*/
#ifndef   OS_UART
    #define OS_UART (0)
#endif

#ifndef   OS_BAUDRATE
    #define OS_BAUDRATE (19200)
#endif

/****** End of configurable options *********************************/

#define OS_UART_USED  ((OS_VIEW_ENABLE && (OS_VIEW_USE_UART != 0)) && ((OS_UART == 0)))

#if OS_UART_USED
    #define OS_COM_INIT() OS_COM_Init()
#else
    #define OS_COM_INIT()
#endif

#define OS_TIMER_RELOAD (OS_PCLK_TIMER / OS_TICK_FREQ)

/*********************************************************************
*
*       Check configuration
*
**********************************************************************
*/

#ifndef   DEBUG     /* Should normally be defined as project option */
    #define DEBUG  (0)
#endif

/*********************************************************************
*
*       Local defines (sfrs used in RTOSInit.c)
*
**********************************************************************
*/

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
*       _ReadHWTimer()
*
*/
static int _ReadHWTimer(void) {
    OS_U16 r = TCNT1L;
    asm("nop");
    return r | (TCNT1H << 8);
}

/*********************************************************************
*
*       OS_ISR_Tick()
*       The embOS timer tick interrupt Handler
*/
static void OS_ISR_Tick_Handler(void);
static void OS_ISR_Tick_Handler(void) {
    OS_TICK_Handle();
}

/*********************************************************************
*
*       OS_ISR_Tick()
*       The embOS timer tick interrupt Handler
*/
#pragma vector = TIMER1_COMPA_vect
__interrupt void OS_ISR_Tick(void);
#pragma vector = TIMER1_COMPA_vect
__interrupt void OS_ISR_Tick(void) {
    OS_CallISR(OS_ISR_Tick_Handler);
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
*       Initialize the hardware (timer) required for embOS to run.
*       May be modified, if an other timer should be used
*/


void OS_InitHW(void) {
    TCCR1A_COM1A1 = 0;    // 0: No output
    TCCR1A_COM1A0 = 0;    // 0: No output
    TCCR1A_WGM11  = 0;    // 0: No PWM
    TCCR1A_WGM10  = 0;    // 0: No PWM

    TCCR1B_ICNC1  = 0;     // 0: Disable noise canceler
    TCCR1B_ICES1  = 0;     // 0: capturee edge
    TCCR1B_WGM12  = 1;     // 1: Reset on compare match
    TCCR1B_CS12   = 0;     // Clock-Source: 001 = CK/1 no prescaler
    TCCR1B_CS11   = 0;     // Clock-Source: 010 = CK/8
    TCCR1B_CS10   = 1;     // Clock-Source: 001 = CK/1
                  
    OCR1A         = (OS_TIMER_RELOAD); // generate 1ms interrupts
    TIMSK1_OCIE1A = 1;      // Output CompareA Match Interrupt Enable

    /*
    TCCR1A=  (0<<6)       // 0: No output
             |(0<<4)             // 0: No output
             |(0<<0);            // No PWM
    TCCR1B=  (1<<7)       // 0: Disable noise canceler
             |(0<<6)             // X: Capture edge
             |(1<<3)             // 1: Reset on compare match
             |(1<<0);            // 1: clock source CK/1
    OCR1A = (XTAL_CPU/1000)-1;         // generate 1ms interrupts
    TIMSK1 |= (1<<1);      // Output CompareA Match Interrupt Enable
    */
    //  SREG  = 0x80 ;        // global interrupt
    OS_COM_INIT();        // Initialize communication to embOSView
}

/*********************************************************************
*
*       OS_Idle()
*
*       Please note:
*       This is basically the "core" of the idle loop.
*       This core loop can be changed, but:
*       The idle loop does not have a stack of its own, therefore no
*       functionality should be implemented that relies on the stack
*       to be preserved. However, a simple program loop can be programmed
*       (like toggeling an output or incrementing a counter)
*/
static OS_I32 WatchDogTime = 0;
void OS_Idle(void) {          // Idle loop: No task is ready to execute
    while (1) {           // Nothing to do ... wait for interrupt
        if ( OS_Time > WatchDogTime) {
            WatchDogTime = OS_Time + 500;
            __watchdog_reset();               //kick the dog
        }
#if (DEBUG == 0)
        // Switch CPU into sleep mode
#endif
    }
}

/*********************************************************************
*
*       OS_GetTime_Cycles()
*
*       This routine is required for task-info via OSView or high
*       resolution time measurement functions.
*       It returns the system time in timer clock cycles.
*/
OS_U32 OS_GetTime_Cycles(void) {
    OS_U32 Time;
    OS_U32 Cnt;

    Time = OS_Time;
    Cnt  = _ReadHWTimer();
    //
    // Check if timer interrupt pending ...
    //
    if (TIFR1 & (1 << 4)) {  // Check if timer interrupt pending ...
        Cnt = _ReadHWTimer();
        Time++;
    }
    return (OS_TIMER_RELOAD * Time) + Cnt;
}

/*********************************************************************
*
*       OS_ConvertCycles2us()
*
*       Convert Cycles into micro seconds.
*
*       If your clock frequency is not a multiple of 1 MHz,
*       you may have to modify this routine in order to get proper
*       diagnostics.
*
*       This routine is required for profiling or high resolution time
*       measurement only.
   It does not affect operation of the OS.
*/

OS_U32 OS_ConvertCycles2us(OS_U32 Cycles) {
    return Cycles / (OS_PCLK_TIMER / 1000000);
}

/*********************************************************************
*
*       Optional communication with embOSView
*
**********************************************************************
*/
#if OS_UART_USED
    #define OS_BAUDDIVIDE ((OS_FSYS+OS_BAUDRATE*8L)/(OS_BAUDRATE*16L)-1)

/*********************************************************************
*
*       OS_COM_Init()
*/
void OS_COM_Init(void) {
    UBRR0H  = OS_BAUDDIVIDE >> 8;
    UBRR0L = OS_BAUDDIVIDE;
    UCSR0B =  (0 << 0)      // X
        | (0 << 1)      // X
        | (0 << 2)      // CHR9: 9-bit Characters
        | (1 << 3)      // TXEN: Transmitter Enable
        | (1 << 4)      // RXEN: Receiver Enable
        | (0 << 5)      // UDRIE: UART Data Register Empty Interrupt Enable
        | (0 << 6)      // TXCIE Tx complete interrupt enable
        | (0 << 7);     // RXCIE Rx complete interrupt enable
    UCSR0B =  (0 << 0)      // X
        | (0 << 1)      // X
        | (0 << 2)      // CHR9: 9-bit Characters
        | (1 << 3)      // TXEN: Transmitter Enable
        | (1 << 4)      // RXEN: Receiver Enable
        | (1 << 5)      // UDRIE: UART Data Register Empty Interrupt Enable
        | (0 << 6)      // TXCIE Tx complete interrupt enable
        | (1 << 7);     // RXCIE Rx complete interrupt enable
}

/*********************************************************************
*
*       OS_COM_Send1()
*       Send one character via UART.
*       Never call this function from your application
*/
void OS_COM_Send1(unsigned char c) {
    UDR0 = c;
    UCSR0B |=  (1 << 5);      // Generate interrupt on transmit buffer emtpy
}

/*********************************************************************
*
*       OS_ISR_rx_Handler()
*       embOS UART rx interrupt handler
*/
void OS_ISR_rx_Handler(void);
void OS_ISR_rx_Handler(void) {
    UCSR0B &=  ~(1 << 7);     // Avoid nesting itself !!!
    OS_OnRx(UDR0);
    OS_DI();             // Disable before allowing Rx interrupt
    UCSR0B |=  (1 << 7);
}

/*********************************************************************
*
*       OS_ISR_rx()
*       embOS UART rx interrupt handler
*/
    #pragma vector = USART0_RXC_vect
__interrupt void OS_ISR_rx(void);
    #pragma vector = USART0_RXC_vect
__interrupt void OS_ISR_rx(void) {
    OS_CallISR(OS_ISR_rx_Handler);
}

/*********************************************************************
*
*       OS_ISR_tx_Handler()
*       embOS UART tx interrupt handler
*/
void OS_ISR_tx_Handler(void);
void OS_ISR_tx_Handler(void) {
    UCSR0B &=  ~(1 << 5);   // Do not generate any more interrupts
    if (OS_OnTx() == 0) {
        OS_DI();             // Disable before allowing Tx interrupt
        UCSR0B |=  (1 << 5);   // Re-enable Tx interrupts
    }
}

/*********************************************************************
*
*       OS_ISR_tx()
*       embOS UART tx interrupt handler
*/
    #pragma vector = USART0_UDRE_vect
__interrupt void OS_ISR_tx(void);
    #pragma vector = USART0_UDRE_vect
__interrupt void OS_ISR_tx(void) {
    OS_CallISR(OS_ISR_tx_Handler);
}

#else  /* UART for communication not used, define dummy functions */

void OS_COM_Send1(OS_U8 c) {
    OS_USEPARA(c);           /* Avoid compiler warning */
    OS_COM_ClearTxActive();    /* Let the OS know that Tx is not busy */
}
#endif

/****** End Of File *************************************************/
