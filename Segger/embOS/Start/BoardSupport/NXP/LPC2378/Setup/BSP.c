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
Purpose : BSP for LPC2378
          Due to the fact that the IAR LPC2378 board has no LEDs we
          toggle the PIO pins 0.23 and 0.24. The pins are connected
          to pin 7 and 8 of the EXT2 connector on the board.
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

#define _GPIO_BASE_ADDR    (0xE0028000)

#define _GPIO_IO0PIN_OFFS  (0x00)  /* Output data status register */
#define _GPIO_IO0SET_OFFS  (0x04)  /* Set output data register    */
#define _GPIO_IO0DIR_OFFS  (0x08)  /* Output direction register   */
#define _GPIO_IO0CLR_OFFS  (0x0C)  /* Clear output data register  */

/****** SFRs and identifiers used for LED demo **********************/

/****** Assign LEDs to Ports ****************************************/

/****** Target specific configuration *******************************/

#define _LEDPORT_BASE_ADDR  (_GPIO_BASE_ADDR)
#define _LED0_BIT           (23)  /* Pin 0.23 on LPC2378 board, active high */
#define _LED1_BIT           (24)  /* Pin 0.24 on LPC2378 board, active high */

#define _LEDPORT_DIR        (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _GPIO_IO0DIR_OFFS))
#define _LEDPORT_SET        (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _GPIO_IO0SET_OFFS))
#define _LEDPORT_CLR        (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _GPIO_IO0CLR_OFFS))
#define _LEDPORT_STATE      (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _GPIO_IO0PIN_OFFS))

#define _LEDMASK_ALL        ((1 << _LED0_BIT) | (1 << _LED1_BIT))


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
  _LEDPORT_DIR |= _LEDMASK_ALL;       /* Switch to output mode */
  _LEDPORT_CLR |= _LEDMASK_ALL;       /* Initially clear pins  */
}

/*********************************************************************
*
*       LED switching routines
*       LEDs are switched on with low level on port lines
*/
void BSP_SetLED(int Index) {
  _LEDPORT_SET = (1 << (_LED0_BIT + Index));          /* Switch on pin  */
}

void BSP_ClrLED(int Index) {
  _LEDPORT_CLR = (1 << (_LED0_BIT + Index));          /* Switch off pin */
}

void BSP_ToggleLED(int Index) {
  if (_LEDPORT_STATE & (1 << (_LED0_BIT + Index))) {  /* Pin is toggled */
    BSP_ClrLED(Index);
  } else {
    BSP_SetLED(Index);
  }
}

/****** EOF *********************************************************/


