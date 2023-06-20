/*********************************************************************
*               SEGGER MICROCONTROLLER SYSTEME GmbH                  *
*       Solutions for real time microcontroller applications         *
**********************************************************************
*                                                                    *
*       (C) 2002   SEGGER Microcontroller Systeme GmbH               *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       embOS * Real time operating system for microcontrollers      *
*                                                                    *
**********************************************************************

----------------------------------------------------------------------
File    : RTOSInit.c   (for ATMEL AT90)
Purpose : Initializes and handles the hardware for embOS as far
          as required by embOS.
          Feel free to modify this file acc. to your
          target system.
--------  END-OF-HEADER  ---------------------------------------------
*/

#include "RTOS.H"
#include "iom128a.h"
#include "constants.h"
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

//#define OS_FSYS CPU_XTAL    // System frequency [Hz]

/* Select UART for embOSView.
   If you do not want (or can not due to hardware limitations) to dedicate
   a UART to embOSView, please define it to be -1
   Currently the standard code below supports only UART 1
   (But is easily changed to UART 0)
*/
#ifndef OS_UART
    #define OS_UART 0
#endif
#ifndef OS_BAUDRATE
    #define OS_BAUDRATE 19200L
#endif

/*********************************************************************
*
*       OS_InitHW
*
**********************************************************************

Initialize the hardware required for the OS to run. This will work
on any target hardware, but may have to be tailored a little
(regarding the clock frequency). Of course the same holds true
if for some reason you choose to use an other timer.
Here we use Timer 1 with Compare match. If other Timer has to be used,
also change the interrupt vector number in OS_ISR_Tick()
*/


void OS_InitHW(void) {
    TCCR1A=  (0<<6)       // 0: No output
             |(0<<4)             // 0: No output
             |(0<<0);            // No PWM
    TCCR1B=  (1<<7)       // 0: Disable noise canceler
             |(0<<6)             // X: Capture edge
             |(1<<3)             // 1: Reset on compare match
             |(1<<0);            // 1: clock source CK/1
    OCR1A = (XTAL_CPU/1000)-1;         // generate 1ms interrupts
    TIMSK |= (1<<4);      // Output CompareA Match Interrupt Enable
    //  SREG  = 0x80 ;        // global interrupt
    OS_COM_Init();        // Initialize communication to embOS Viewer

}

/*********************************************************************
*
*       Idle loop  (OS_Idle)
*
**********************************************************************

 Please note:
 This is basically the "core" of the idle loop
 This core loop can be changed, but:
 The idle loop does not have a stack of its own, therefore no
 functionality should be implemented that relies on the stack
 to be preserved. However, a simple program loop can be programmed
 (like toggeling an output or incrementing a counter)
*/

void OS_Idle(void) {          // Idle loop: No task is ready to exec
    for (;;);                   // Nothing to do ... wait for a interrupt
}

/*********************************************************************
*
*       Get time [cycles]
*
**********************************************************************

    This routine is required for task-info via embOS Viewer.
    It returns the system time in clock cycles.
*/

static int ReadHWTimer(void) {
    OS_U16 r = TCNT1L;
    asm ("nop");
    return r |(TCNT1H<<8);
}

OS_U32 OS_GetTime_Cycles(void) {
    unsigned int t_cnt = ReadHWTimer();
    OS_U32 time = OS_Time;
    //
    // Check if timer interrupt pending ...
    if (TIFR&(1<<4)) {
        t_cnt = ReadHWTimer();
        time++;
    }
//  return (XTAL_CPU/1000)*time  + t_cnt;
    return(XTAL_CPU/1000)*time  + t_cnt;
}

/*********************************************************************
*
*       OS_ConvertCycles2us
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
    return Cycles/(XTAL_CPU/1000000);
}

/*********************************************************************
*
*       OS_Tick interrupt
*
**********************************************************************
*/

#pragma vector = TIMER1_COMPA_vect
__interrupt void OS_ISR_Tick (void) { OS_TickHandler();}

/*********************************************************************
*
*       Communication for embOSView (UART 0)
*
**********************************************************************
*/

#if (OS_UART == 0)

void OS_COM_Init(void) {
    UBRR0L  = ((XTAL_CPU / 16 / OS_BAUDRATE )-1) & 0xff;
    UBRR0H  = (((XTAL_CPU / 16 / OS_BAUDRATE )-1)>> 8) & 0xff;
    UCSR0C  = 0x06;       /* n,8,1 */
    UCSR0A  = 0x00;
    UCSR0B =  (0<<0)      // X
              |(0<<1)      // X
              |(0<<2)      // CHR9: 9-bit Characters
              |(1<<3)      // TXEN: Transmitter Enable
              |(1<<4)      // RXEN: Receiver Enable
              |(0<<5)      // UDRIE: UART Data Register Empty Interrupt Enable
              |(0<<6)      // TXCIE Tx complete interrupt enable
              |(0<<7);     // RXCIE Rx complete interrupt enable
    UCSR0B =  (0<<0)      // X
              |(0<<1)      // X
              |(0<<2)      // CHR9: 9-bit Characters
              |(1<<3)      // TXEN: Transmitter Enable
              |(1<<4)      // RXEN: Receiver Enable
              |(0<<5)      // UDRIE: UART Data Register Empty Interrupt Enable
              |(1<<6)      // TXCIE Tx complete interrupt enable
              |(1<<7);     // RXCIE Rx complete interrupt enable
}

void OS_COM_Send1(unsigned char c) {
    UDR0 = c;
    UCSR0B |=  (1<<6);      // Generate interrupt on transmit buffer emtpy
}

    #pragma vector = USART0_RXC_vect
__interrupt void ISR_uart0_rx (void) {
    UCSR0B &=  ~(1<<7);     // Avoid nesting itself !!!
    OS_EnterNestableInterrupt();
    OS_OnRx(UDR0);
    OS_DI();             // Disable before allowing Rx interrupt
    UCSR0B |=  (1<<7);
    OS_LeaveNestableInterrupt();
}

    #pragma vector = USART0_TXC_vect
__interrupt void ISR_uart0_tx (void) {/*USART0_TXC_vect*/
    OS_EnterNestableInterrupt();
    if (OS_OnTx()) {
        UCSR0B &=  ~(1<<6);   // Do not generate any more interrupts
    }
    OS_LeaveNestableInterrupt();
}

#else  /* No communication routines, just dummies  */
void OS_COM_Init(void) {}
void OS_COM_Send1(OS_U8 c) {
    OS_COM_ClearTxActive();    /* let OS know that transmitter is not busy */
    OS_USEPARA(c);             /* Avoid compiler warning */
}
#endif /* defined (OS_UART) */

/*****  EOF  ********************************************************/


