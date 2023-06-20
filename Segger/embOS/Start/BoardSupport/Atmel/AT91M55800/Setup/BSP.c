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
Purpose : BSP for AT91EB55-EK
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

#define _AT91C_PIOA_BASE_ADDR  (0xFFFEC000)
#define _AT91C_PIOB_BASE_ADDR  (0xFFFF0000)

#define _AT91C_PMC_BASE_ADDR   (0xFFFF4000)

#define _PIOA_ID          (13)
#define _PIOB_ID          (14)
#define _PIO_PER_OFFS     (0x00)
#define _PIO_OER_OFFS     (0x10)
#define _PIO_SODR_OFFS    (0x30)    /* Set output data              */
#define _PIO_CODR_OFFS    (0x34)    /* Clear output data register   */
#define _PIO_ODSR_OFFS    (0x38)    /* Output data status register  */
#define _PIO_PDSR_OFFS    (0x3c)    /* Pin data status register     */

#define _PMC           (*(volatile unsigned int*) (_AT91C_PMC_BASE_ADDR + 0x10))

/****** Target specific configuration *******************************/
/****** Assign LEDs to Ports ****************************************/

#define _LEDPORT_BASE_ADDR  (_AT91C_PIOB_BASE_ADDR)
#define _LEDPORT_ID         (_PIOB_ID)
#define _LED0_BIT           (8)
#define _LED1_BIT           (9)

#define _LEDPORT_PER   (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _PIO_PER_OFFS))
#define _LEDPORT_OER   (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _PIO_OER_OFFS))
#define _LEDPORT_SODR  (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _PIO_SODR_OFFS))
#define _LEDPORT_CODR  (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _PIO_CODR_OFFS))
#define _LEDPORT_STATE (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _PIO_ODSR_OFFS))

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
  _PMC |= (1 << _LEDPORT_ID);     /* Enable peripheral clock for LED-Port    */
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
  _LEDPORT_CODR = (1 << (Index + _LED0_BIT));  /* Switch on selected LED */
}

void BSP_ClrLED(int Index) {
  _LEDPORT_SODR = (1 << (Index + _LED0_BIT));  /* Switch off selected LED */
}

void BSP_ToggleLED(int Index) {
  if (_LEDPORT_STATE & (1 << (Index + _LED0_BIT))) {  /* LED is switched off */
    BSP_SetLED(Index);
  } else {
    BSP_ClrLED(Index);
  }
}

/****** EOF *********************************************************/


