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
Purpose : BSP for STR710-EVAL board
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

#define __IOPORT0_BASE_ADDR   0xE0003000

#define __GPIO0_PC0 *(volatile unsigned short*)(__IOPORT0_BASE_ADDR + 0x00)
#define __GPIO0_PC1 *(volatile unsigned short*)(__IOPORT0_BASE_ADDR + 0x04)
#define __GPIO0_PC2 *(volatile unsigned short*)(__IOPORT0_BASE_ADDR + 0x08)
#define __GPIO0_PD  *(volatile unsigned short*)(__IOPORT0_BASE_ADDR + 0x0C)

/****** Assign LEDs to Ports ****************************************/

#define _LEDPORT_PC0  __GPIO0_PC0
#define _LEDPORT_PC1  __GPIO0_PC1
#define _LEDPORT_PC2  __GPIO0_PC2
#define _LEDPORT      __GPIO0_PD

#define _LED0_BIT  3    // LD3 on EVAL board
#define _LED1_BIT  2    // LD4 on EVAL board

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

/*********************************************************************
*
*       BSP_Init()
*/
void BSP_Init(void) {
  /* Setup port mode: output, push-pull */
  _LEDPORT_PC0 |=  ((1 << _LED0_BIT) | (1 << _LED1_BIT));
  _LEDPORT_PC1 &= ~((1 << _LED0_BIT) | (1 << _LED1_BIT));
  _LEDPORT_PC2 |=  ((1 << _LED0_BIT) | (1 << _LED1_BIT));
  /* Initially switch off LEDs */
  _LEDPORT     &= ~((1 << _LED0_BIT) | (1 << _LED1_BIT));
}

/*********************************************************************
*
*       LED switching routines
*/
void BSP_SetLED(int Index) {
  if (Index == 0) {
    _LEDPORT  |=  (1 << _LED0_BIT);   // Switch on LED 0
  } else {
    _LEDPORT  |=  (1 << _LED1_BIT);   // Switch on LED 1
  }
}

void BSP_ClrLED(int Index) {
  if (Index == 0) {
    _LEDPORT  &= ~(1 << _LED0_BIT);   // Switch off LED 0
  } else {
    _LEDPORT  &= ~(1 << _LED1_BIT);   // Switch off LED 1
  }
}

void BSP_ToggleLED(int Index) {
  if (Index == 0) {
    _LEDPORT  ^=  (1 << _LED0_BIT);   // Toggle LED 0
  } else {
    _LEDPORT  ^=  (1 << _LED1_BIT);   // Toggle LED 1
  }
}

/****** EOF *********************************************************/

