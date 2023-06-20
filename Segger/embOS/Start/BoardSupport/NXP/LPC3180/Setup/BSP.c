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
File    : BSP.c
Purpose : BSP for LPC3180 Starter boards and IAR compiler
--------  END-OF-HEADER  ---------------------------------------------
*/

#define BSP_C
#include "BSP.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

/****** SFRs used for LED-Port **************************************/
#define __IOPORT0_BASE_ADDR   0x40028000
#define __PIO_OUTP_SET   *(volatile unsigned int*)(__IOPORT0_BASE_ADDR + 0x4)
#define __PIO_OUTP_CLR   *(volatile unsigned int*)(__IOPORT0_BASE_ADDR + 0x8)
#define __PIO_OUTP_STATE *(volatile unsigned int*)(__IOPORT0_BASE_ADDR + 0xC)

/****** Assign LEDs to Ports ****************************************/

#define _LED0_BIT   9    // LED3 on Eval board
#define _LED1_BIT  10    // LED4 on Eval board
#define _LED0_MASK (1 << _LED0_BIT)
#define _LED1_MASK (1 << _LED1_BIT)

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

/*********************************************************************
*
*       LED_Init()
*/
void BSP_Init(void) {  // Initially switch off LEDs
  __PIO_OUTP_SET = (_LED0_MASK | _LED1_MASK);  // LEDS are active low
}

/*********************************************************************
*
*       LED switching routines
*/
void BSP_SetLED(int Index) {
  if (Index == 0) {
    __PIO_OUTP_CLR = _LED0_MASK;    // Switch on LED 0
  } else {
    __PIO_OUTP_CLR = _LED1_MASK;    // Switch on LED 1
  }
}

void BSP_ClrLED(int Index) {
  if (Index == 0) {
    __PIO_OUTP_SET = _LED0_MASK;    // Switch off LED 0
  } else {
    __PIO_OUTP_SET = _LED1_MASK;    // Switch off LED 1
  }
}

void BSP_ToggleLED(int Index) {
  if (Index == 0) {
    if (__PIO_OUTP_STATE & _LED0_MASK) {
      BSP_SetLED(0);
    } else {
      BSP_ClrLED(0);
    }
  } else {
    if (__PIO_OUTP_STATE & _LED1_MASK) {
      BSP_SetLED(1);
    } else {
      BSP_ClrLED(1);
    }
  }
}

/****** EOF *********************************************************/

