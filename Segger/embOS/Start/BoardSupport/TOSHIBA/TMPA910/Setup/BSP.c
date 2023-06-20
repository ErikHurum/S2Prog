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
Purpose : BSP for TMPA910 TOPAS 910 eval board
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

/****** Addresses of sfrs and peripheral identifiers ****************/


/****** SFRs and identifiers used for LED demo **********************/

#define _GPIOB_BASE_ADDR  (0xF0801000)

/****** Assign LEDs to Ports ****************************************/

/****** Target specific configuration *******************************/

#define _LEDPORT_BASE_ADDR  (_GPIOB_BASE_ADDR)

#define _LEDPORT       (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + 0x3FC))

#define _LEDMASK_ALL   0xFF

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

/*********************************************************************
*
*       BSP_ETH_Init()
*/
void BSP_ETH_Init(unsigned Unit) {
}

/*********************************************************************
*
*       LED_Init()
*/
void BSP_Init(void) {
  _LEDPORT |= _LEDMASK_ALL; // turn off al leds
}

/*********************************************************************
*
*       LED switching routines
*       LEDs are switched on with low level on port lines
*/
void BSP_SetLED(int Index) {
  _LEDPORT &= ~(1 << Index);
}

void BSP_ClrLED(int Index) {
  _LEDPORT |= (1 << Index);
}

void BSP_ToggleLED(int Index) {
  _LEDPORT ^= (1 << Index);
}

/****** EOF *********************************************************/

