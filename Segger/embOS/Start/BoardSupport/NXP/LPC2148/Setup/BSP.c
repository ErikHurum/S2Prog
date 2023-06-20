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
Purpose : BSP for LPC2148
          Due to the fact that the IAR LPC2148 board has no LEDs we
          toggle the PIO pins 1.16 and 1.17 on the board. The pins
          are connected to the connector pins on the board marked
          with 1.16 and 1.17.
--------  END-OF-HEADER  ---------------------------------------------
*/

#include "BSP.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

/****** Addresses of sfrs and peripheral identifiers ****************/

#define _GPIO_BASE_ADDR      (0xE0028000)
#define _PCB_BASE_ADDR       (0xE002C000)  /* Pin connect block           */

#define _PCB_PINSEL2_OFFS    (0x14)
#define _GPIO_IO1PIN_OFFS    (0x10)        /* Output data status register */
#define _GPIO_IO1SET_OFFS    (0x14)        /* Set output data register    */
#define _GPIO_IO1DIR_OFFS    (0x18)        /* Output direction register   */
#define _GPIO_IO1CLR_OFFS    (0x1C)        /* Clear output data register  */

/****** SFRs and identifiers used for LED demo **********************/

/****** Assign LEDs to Ports ****************************************/

/****** Target specific configuration *******************************/

#define _LEDPORT_BASE_ADDR  (_GPIO_BASE_ADDR)
#define _GPIO_BIT           (3)   /* GPIO/Trace selector                    */
#define _LED0_BIT           (16)  /* Pin 1.16 on LPC2148 board, active high */
#define _LED1_BIT           (17)  /* Pin 1.17 on LPC2148 board, active high */

#define _LEDPORT_DIR   (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _GPIO_IO1DIR_OFFS))
#define _LEDPORT_SET   (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _GPIO_IO1SET_OFFS))
#define _LEDPORT_CLR   (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _GPIO_IO1CLR_OFFS))
#define _LEDPORT_STATE (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _GPIO_IO1PIN_OFFS))

#define _PCB_PINSEL2   (*(volatile unsigned int*) (_PCB_BASE_ADDR + _PCB_PINSEL2_OFFS))

#define _LEDMASK_ALL   ((1 << _LED0_BIT) | (1 << _LED1_BIT))


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
  _PCB_PINSEL2 &= ~(1 << _GPIO_BIT);  /* Enable GPIO pins      */
  _LEDPORT_DIR  = _LEDMASK_ALL;       /* switch to output mode */
  _LEDPORT_SET &= ~(_LEDMASK_ALL);       /* Initially clear pins  */
}

/*********************************************************************
*
*       LED switching routines
*       LEDs are switched on with low level on port lines
*/
void BSP_SetLED(int Index) {
  _LEDPORT_SET = (1 << (16 + Index));          /* Switch on pin 1.16  */
}

void BSP_ClrLED(int Index) {
  _LEDPORT_CLR = (1 << (16 + Index));          /* Switch off pin 1.16 */
}

void BSP_ToggleLED(int Index) {
  if (_LEDPORT_STATE & (1 << (16 + Index))) {  /* Pin is toggled      */
    BSP_ClrLED(Index);
  } else {
    BSP_SetLED(Index);
  }
}

/****** EOF *********************************************************/


