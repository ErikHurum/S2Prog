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
Purpose : BSP for AT91EB40A
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

#define _AT91_PIO_BASE_ADDR    (0xFFFF0000)

#define _PIO_PER_OFFS     (0x00)
#define _PIO_OER_OFFS     (0x10)
#define _PIO_SODR_OFFS    (0x30)    /* Set output data              */
#define _PIO_CODR_OFFS    (0x34)    /* Clear output data register   */
#define _PIO_ODSR_OFFS    (0x38)    /* output data status register  */
#define _PIO_PDSR_OFFS    (0x3c)    /* pin data status register     */

/****** SFRs and identifiers used for LED demo **********************/

/****** Assign LEDs to Ports ****************************************/

/****** Target specific configuration *******************************/

#define _LEDPORT_BASE_ADDR  (_AT91_PIO_BASE_ADDR)
#define _LED0_BIT      (16)  /* LED1 on AT91EB40A board, active low */
#define _LED1_BIT      (17)  /* LED2 on AT91EB40A board, active low */

#define _LEDPORT_PER   (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _PIO_PER_OFFS))
#define _LEDPORT_OER   (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _PIO_OER_OFFS))
#define _LEDPORT_SODR  (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _PIO_SODR_OFFS))
#define _LEDPORT_CODR  (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _PIO_CODR_OFFS))
#define _LEDPORT_STATE (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _PIO_PDSR_OFFS))

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
  _LEDPORT_PER   = _LEDMASK_ALL;  /* enable Port           */
  _LEDPORT_OER   = _LEDMASK_ALL;  /* switch to output mode */
  _LEDPORT_SODR |= _LEDMASK_ALL;  /* Initially clear LEDs  */
}

/*********************************************************************
*
*       LED switching routines
*       LEDs are switched on with low level on port lines
*/
void BSP_SetLED(int Index) {
  _LEDPORT_CODR = (1 << (16 + Index));         /* Switch on LED  */
}

void BSP_ClrLED(int Index) {
  _LEDPORT_SODR = (1 << (16 + Index));         /* Switch off LED */
}

void BSP_ToggleLED(int Index) {
  if (_LEDPORT_STATE & (1 << (16 + Index))) {  /* LED is toggled */
    BSP_SetLED(Index);
  } else {
    BSP_ClrLED(Index);
  }
}

/****** EOF *********************************************************/

