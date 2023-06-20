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
Purpose : BSP for TI TMS470R1B1M kick-start board
--------  END-OF-HEADER  ---------------------------------------------
*/

#define BSP_C
#include "BSP.h"
//#include "iotms470r1b1m.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

/****** Addresses of sfrs and peripheral identifiers ****************/


/****** SFRs and identifiers used for LED demo **********************/
#define GIODIRE  (*(volatile unsigned*) 0xFFF7EC74)
#define GIODOUTE (*(volatile unsigned*) 0xFFF7EC7C)

/****** Assign LEDs to Ports ****************************************/

/****** Target specific configuration *******************************/


#define _LEDPORT_OER   (GIODIRE)  // LED-Port output enable
#define _LEDPORT       (GIODOUTE) // LED-Port data port

#define _LED0_BIT      (0)
#define _LED1_BIT      (1)
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
  _LEDPORT_OER = _LEDMASK_ALL;  // Set GIO output direction to drive LEDs
  _LEDPORT     = ~_LEDMASK_ALL; // Outputs OFF
}

/*********************************************************************
*
*       LED switching routines
*       LEDs are switched on with low level on port lines
*/
void BSP_SetLED(int Index) {
  _LEDPORT |= (1 << Index);  /* Switch on LED */
}

void BSP_ClrLED(int Index) {
  _LEDPORT &= ~(1 << Index); /* Switch off LED */
}

void BSP_ToggleLED(int Index) {
  _LEDPORT ^= (1 << Index);  /* Toggle LED */
}

/****** EOF *********************************************************/

