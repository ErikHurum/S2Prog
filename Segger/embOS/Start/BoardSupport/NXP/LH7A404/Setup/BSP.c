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
Purpose : BSP for LH7A404 LogicPD card engine
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

#define __GPIO_BASE_ADDR      0x80000E00
#define __EXT_GPIO0_DATA  *(volatile unsigned long*)(__GPIO_BASE_ADDR + 0x20)
#define __EXT_GPIO0_DIR   *(volatile unsigned long*)(__GPIO_BASE_ADDR + 0x24)

/****** Assign LEDs to Ports ****************************************/
#define _LEDPORT      __EXT_GPIO0_DATA
#define _LED0_BIT  7    // LD1 on EVAL board
#define _LED1_BIT  6    // STATUS  on EVAL board

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
  __EXT_GPIO0_DIR |= (1 << _LED0_BIT)
                  |  (1 << _LED1_BIT);
  /* Initially switch off LEDs */
  _LEDPORT     &= ~((1 << _LED0_BIT) |(1 << _LED1_BIT));
}

/*********************************************************************
*
*       LED switching routines
*       LEDs are switched on by low level on port lines
*/
void BSP_SetLED(int Index) {
  if (Index == 0) {
    _LEDPORT  |=  (1 << _LED0_BIT);         /* Switch on LED 0  */
  } else if (Index == 1) {
    _LEDPORT  |=  (1 << _LED1_BIT);         /* Switch on LED1  */
  }
}

void BSP_ClrLED(int Index) {
  if (Index == 0) {
    _LEDPORT  &= ~(1 << _LED0_BIT);         /* Switch off LED 0 */
  } else if (Index == 1) {
    _LEDPORT  &= ~(1 << _LED1_BIT);         /* Switch off LED1 */
  }
}

void BSP_ToggleLED(int Index) {
  if (Index == 0) {
    _LEDPORT  ^=  (1 << _LED0_BIT);  /* Toggle LED 0 */
  } else if (Index == 1) {
    _LEDPORT  ^=  (1 << _LED1_BIT);  /* Toggle LED 1 */
  }
}

/****** EOF *********************************************************/

