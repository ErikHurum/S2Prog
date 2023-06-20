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
Purpose : BSP for LPC21x KickStart or MCB2100 board
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

#define __IOPORT0_BASE_ADDR   0xE0028000
#define __IOPORT1_BASE_ADDR   0xE0028010

#define __GPIO0_PIN   *(volatile unsigned int*)(__IOPORT0_BASE_ADDR + 0x00)
#define __GPIO0_IOSET *(volatile unsigned int*)(__IOPORT0_BASE_ADDR + 0x04)
#define __GPIO0_IODIR *(volatile unsigned int*)(__IOPORT0_BASE_ADDR + 0x08)
#define __GPIO0_IOCLR *(volatile unsigned int*)(__IOPORT0_BASE_ADDR + 0x0C)

#define __GPIO1_PIN   *(volatile unsigned int*)(__IOPORT1_BASE_ADDR + 0x00)
#define __GPIO1_IOSET *(volatile unsigned int*)(__IOPORT1_BASE_ADDR + 0x04)
#define __GPIO1_IODIR *(volatile unsigned int*)(__IOPORT1_BASE_ADDR + 0x08)
#define __GPIO1_IOCLR *(volatile unsigned int*)(__IOPORT1_BASE_ADDR + 0x0C)

/****** Assign LEDs to Ports ****************************************/

#define _PORT0_LED0_BIT  14    // DS15 on Kickstart board
#define _PORT0_LED1_BIT  15    // DS16 on Kickstart board

#define _PORT1_LED0_BIT  22    // LED1 on MCB2100 board
#define _PORT1_LED1_BIT  23    // LED2 on MCB2100 board

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
void BSP_Init(void) {
  __GPIO0_IODIR  = 0;  // Initially set ports to input
  __GPIO1_IODIR  = 0;
  __GPIO0_IODIR |= ((1 << _PORT0_LED0_BIT) | (1 << _PORT0_LED1_BIT));   // Set LED-Port to output
  __GPIO1_IODIR |= ((1 << _PORT1_LED0_BIT) | (1 << _PORT1_LED1_BIT));
  /* Switch off LEDs */
  __GPIO0_IOCLR  = ((1 << _PORT0_LED0_BIT) | (1 << _PORT0_LED1_BIT));
  __GPIO1_IOCLR  = ((1 << _PORT1_LED0_BIT) | (1 << _PORT1_LED1_BIT));
}

/*********************************************************************
*
*       LED switching routines
*/
void BSP_SetLED(int Index) {
  if (Index == 0) {
    __GPIO0_IOSET =  (1 << _PORT0_LED0_BIT);    // Switch on LED 0
    __GPIO1_IOSET =  (1 << _PORT1_LED0_BIT);    // Switch on LED 0
  } else {
    __GPIO0_IOSET = (1 << _PORT0_LED1_BIT);     // Switch on LED1
    __GPIO1_IOSET = (1 << _PORT1_LED1_BIT);     // Switch on LED1
  }
}

void BSP_ClrLED(int Index) {
  if (Index == 0) {
    __GPIO0_IOCLR =  (1 << _PORT0_LED0_BIT);    // Switch off LED 0
    __GPIO1_IOCLR =  (1 << _PORT1_LED0_BIT);    // Switch off LED 0
  } else {
    __GPIO0_IOCLR =  (1 << _PORT0_LED1_BIT);    // Switch off LED 1
    __GPIO1_IOCLR =  (1 << _PORT1_LED1_BIT);    // Switch off LED 1
  }
}

void BSP_ToggleLED(int Index) {
  if (Index == 0) {
    if (__GPIO0_PIN & (1 << _PORT0_LED0_BIT)) {
      BSP_ClrLED(0);
    } else {
      BSP_SetLED(0);
    }
  } else {
    if (__GPIO0_PIN & (1 << _PORT0_LED1_BIT)) {
      BSP_ClrLED(1);
    } else {
      BSP_SetLED(1);
    }
  }
}

/****** EOF *********************************************************/

