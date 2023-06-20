/*********************************************************************
*               SEGGER MICROCONTROLLER GmbH & Co KG                  *
*       Solutions for real time microcontroller applications         *
**********************************************************************
*                                                                    *
*       (c) 1995 - 2012  SEGGER Microcontroller GmbH & Co KG         *
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
*       OS version: 3.86g                                            *
*                                                                    *
**********************************************************************

----------------------------------------------------------------------
Licensing information
Licensor:                 SEGGER Microcontroller GmbH
Licensed to:              Scanjet Ariston AS, Moen  12, 3948  Porsgrunn, Norway
Licensed SEGGER software: embOS
License number:           OS-01417
License model:            SOL [Single Developer Single Platform Object Code License]
Licensed product:         -
Licensed platform:        AtMega 128, IAR
Licensed number of seats: 1
----------------------------------------------------------------------
Support and Update Agreement (SUA)
SUA period:               2022-12-21 - 2023-06-22
Contact to extend SUA:    sales@segger.com
----------------------------------------------------------------------
File    : BSP.c
Purpose : BSP for ATmega128 eval board (STK500)
--------  END-OF-HEADER  ---------------------------------------------
*/

#include "BSP.h"
#include "IOM128.H"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/


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
  DDRB  = 0xFF;
  PORTB = 0xFF;
}

/*********************************************************************
*
*       LED switching routines
*       LEDs are switched on with low level on port lines
*/
void BSP_SetLED(int Index) {
  PORTB &= ~(1ul << Index);
}

void BSP_ClrLED(int Index) {
  PORTB |= (1ul << Index);
}

void BSP_ToggleLED(int Index) {
  PORTB ^= (1ul << Index);
}

/****** End Of File *************************************************/
