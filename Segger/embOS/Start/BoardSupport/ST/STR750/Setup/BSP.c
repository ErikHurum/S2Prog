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
Purpose : BSP for ST STR750-EVAL board
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

/****** SFR used by LED module **************************************/

#define _MRCC_PCLKEN  *(volatile unsigned int*)(0x60000020 + 0x10)
#define _MRCC_GPIO_EN_BIT (24)

/****** SFRs used for LED-Port **************************************/

#define _GPIO0_BASE_ADDR   0xFFFFE400
#define _GPIO1_BASE_ADDR   0xFFFFE440
#define _GPIO2_BASE_ADDR   0xFFFFE480

/****** Assign LEDs to Ports ****************************************/

#define _LED_BASE_ADDR    _GPIO2_BASE_ADDR

#define _LED_PC0 *(volatile unsigned int*)(_LED_BASE_ADDR + 0x00)
#define _LED_PC1 *(volatile unsigned int*)(_LED_BASE_ADDR + 0x04)
#define _LED_PC2 *(volatile unsigned int*)(_LED_BASE_ADDR + 0x08)
#define _LED_PD  *(volatile unsigned int*)(_LED_BASE_ADDR + 0x0C)

#define _LED0_BIT  18    // LD4 on EVAL board
#define _LED1_BIT  19    // LD5 on EVAL board

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
  //
  // Enable peripheral clock for GPIO
  //
  _MRCC_PCLKEN |= (1 << _MRCC_GPIO_EN_BIT);
  //
  // Setup port mode: output, push-pull
  //
  _LED_PC0 |=  ((1 << _LED0_BIT) | (1 << _LED1_BIT));
  _LED_PC1 &= ~((1 << _LED0_BIT) | (1 << _LED1_BIT));
  _LED_PC2 |=  ((1 << _LED0_BIT) | (1 << _LED1_BIT));
  //
  // Initially switch off LEDs
  //
  _LED_PD  |=  ((1 << _LED0_BIT) | (1 << _LED1_BIT));
}

/*********************************************************************
*
*       LED switching routines
*       LEDs are switched on with low level on port lines
*/
void BSP_SetLED(int Index) {
  _LED_PD  &= ~(1 << (_LED0_BIT + Index));  /* Switch on LED 0  */
}

void BSP_ClrLED(int Index) {
  _LED_PD  |= (1 << (_LED0_BIT + Index));   /* Switch off LED 0 */
}

void BSP_ToggleLED(int Index) {
  _LED_PD  ^=  (1 << (_LED0_BIT + Index));  /* LED is switched off */
}

/****** EOF *********************************************************/

