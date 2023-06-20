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
Purpose : BSP for AT91SAM9260-EK
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

#define _AT91C_PIOA_BASE_ADDR  (0xFFFFF400)

#define _AT91C_PMC_BASE_ADDR   (0xFFFFFC00)

#define _PIOA_ID          (2)
#define _PIO_PER_OFFS     (0x00)
#define _PIO_OER_OFFS     (0x10)
#define _PIO_SODR_OFFS    (0x30)    /* Set output data              */
#define _PIO_CODR_OFFS    (0x34)    /* Clear output data register   */
#define _PIO_ODSR_OFFS    (0x38)    /* output data status register  */

/****** SFRs and identifiers used for LED demo **********************/

#define _PMC_PCER (*(volatile unsigned int*) (_AT91C_PMC_BASE_ADDR + 0x10))

/****** Assign LEDs to Ports ****************************************/

/****** Target specific configuration *******************************/

#define _LEDPORT_BASE_ADDR  (_AT91C_PIOA_BASE_ADDR)
#define _LEDPORT_ID    (_PIOA_ID)
#define _LED0_BIT      (6)  /* User LED on AT91SAM9260-EK board, active low  */
#define _LED1_BIT      (9)  /* POWERLED on AT91SAM9260-EK board, active high */

#define _LEDPORT_PER   (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _PIO_PER_OFFS))
#define _LEDPORT_OER   (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _PIO_OER_OFFS))
#define _LEDPORT_SODR  (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _PIO_SODR_OFFS))
#define _LEDPORT_CODR  (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _PIO_CODR_OFFS))
#define _LEDPORT_STATE (*(volatile unsigned int*) (_LEDPORT_BASE_ADDR + _PIO_ODSR_OFFS))

#define _LED0_MASK     (1 << _LED0_BIT)
#define _LED1_MASK     (1 << _LED1_BIT)
#define _LEDMASK_ALL   (_LED0_MASK | _LED1_MASK)

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
  _PMC_PCER     |= (1 << _LEDPORT_ID); /* Enable peripheral clock for LED-Port    */
  _LEDPORT_PER   = _LEDMASK_ALL;       /* enable Port           */
  _LEDPORT_OER   = _LEDMASK_ALL;       /* switch to output mode */
  _LEDPORT_SODR |= _LED0_MASK;         /* Initially clear LEDs  */
  _LEDPORT_CODR |= _LED1_MASK;         /* Initially clear LEDs  */
}

/*********************************************************************
*
*       LED switching routines
*       LEDs are switched on by low level on port lines
*/
void BSP_SetLED(int Index) {
  if (Index == 0) {
    _LEDPORT_CODR = (1 << _LED0_BIT);         /* Switch on LED 0  */
  } else if (Index == 1) {
    _LEDPORT_SODR = (1 << _LED1_BIT);         /* Switch on LED1  */
  }
}

void BSP_ClrLED(int Index) {
  if (Index == 0) {
    _LEDPORT_SODR = (1 << _LED0_BIT);         /* Switch off LED 0 */
  } else if (Index == 1) {
    _LEDPORT_CODR = (1 << _LED1_BIT);         /* Switch off LED1 */
  }
}

void BSP_ToggleLED(int Index) {
  if (Index == 0) {
    if (_LEDPORT_STATE & (1 << _LED0_BIT)) {  /* LED is switched off */
      BSP_SetLED(0);
    } else {
      BSP_ClrLED(0);
    }
  } else if (Index == 1) {
    if (_LEDPORT_STATE & (1 << _LED1_BIT)) {  /* LED is switched on */
      BSP_ClrLED(1);
    } else {
      BSP_SetLED(1);
    }
  }
}

/****** End of file *************************************************/


