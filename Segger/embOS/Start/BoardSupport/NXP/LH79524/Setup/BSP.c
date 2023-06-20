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
Purpose : BSP LED interface for LH79524 LogicPD card engine
--------  END-OF-HEADER  ---------------------------------------------
*/

#include "BSP.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

/****** SFRs used for LED-Port **************************************/

#define __GPIO_BASE_ADDR      0x4CB00000
#define __EXT_GPIO0_DATA  *(volatile unsigned short*)(__GPIO_BASE_ADDR + 0x00)

/****** Assign LEDs to Ports ****************************************/
#define _LEDPORT      __EXT_GPIO0_DATA
#define _LED0_BIT  1    // LD1 on EVAL board
#define _LED1_BIT  2    // STATUS  on EVAL board

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
  _LEDPORT     = ((1 << _LED0_BIT) |(1 << _LED1_BIT));
}

/*********************************************************************
*
*       LED switching routines
*/
void BSP_SetLED(int Index) {
  _LEDPORT  &=  ~(1 << (Index + _LED0_BIT));  // Switch on LED
}

void BSP_ClrLED(int Index) {
  _LEDPORT  |=  (1 << (Index + _LED0_BIT));   // Switch off LED
}

void BSP_ToggleLED(int Index) {
  _LEDPORT  ^=  (1 << (Index + _LED0_BIT));   // Toggle LED
}

/****** EOF *********************************************************/

