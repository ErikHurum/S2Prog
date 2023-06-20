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
Purpose : BSP for AT91SAM9261-EK
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

#define _PIOA_BASE_ADDR    (0xfffff200)
#define _PIOB_BASE_ADDR    (0xfffff400)
#define _PIOC_BASE_ADDR    (0xfffff600)

#define _PMC_BASE_ADDR     (0xFFFFFC00)

#define _PIOA_ID          (2)
#define _PIOB_ID          (3)
#define _PIOC_ID          (4)
#define _PIO_PER_OFFS     (0x00)
#define _PIO_OER_OFFS     (0x10)
#define _PIO_SODR_OFFS    (0x30)    /* Set output data              */
#define _PIO_CODR_OFFS    (0x34)    /* Clear output data register   */
#define _PIO_ODSR_OFFS    (0x38)    /* output data status register  */
#define _PIO_PDSR_OFFS    (0x3c)    /* pin data status register     */

/****** SFRs and identifiers used for LED demo **********************/

#define _PMC_PCER (*(volatile unsigned int*) (_PMC_BASE_ADDR + 0x10))

/****** Assign LEDs to Ports ****************************************/

/****** Target specific configuration *******************************/

#define _LEDPORT0_BASE_ADDR  (_PIOB_BASE_ADDR)
#define _LEDPORT1_BASE_ADDR  (_PIOC_BASE_ADDR)

#define _LEDPORT0_ID    (_PIOB_ID)
#define _LEDPORT1_ID    (_PIOC_ID)

#define _LED0_BIT      ( 8) /* LED1 on AT91SAM9263-EK board, active low */
#define _LED1_BIT      (29) /* LED2 on AT91SAM9263-EK board, active low */

#define _LEDPORT0_PER   (*(volatile unsigned int*) (_LEDPORT0_BASE_ADDR + _PIO_PER_OFFS))
#define _LEDPORT0_OER   (*(volatile unsigned int*) (_LEDPORT0_BASE_ADDR + _PIO_OER_OFFS))
#define _LEDPORT0_SODR  (*(volatile unsigned int*) (_LEDPORT0_BASE_ADDR + _PIO_SODR_OFFS))
#define _LEDPORT0_CODR  (*(volatile unsigned int*) (_LEDPORT0_BASE_ADDR + _PIO_CODR_OFFS))
#define _LEDPORT0_STATE (*(volatile unsigned int*) (_LEDPORT0_BASE_ADDR + _PIO_ODSR_OFFS))

#define _LEDPORT1_PER   (*(volatile unsigned int*) (_LEDPORT1_BASE_ADDR + _PIO_PER_OFFS))
#define _LEDPORT1_OER   (*(volatile unsigned int*) (_LEDPORT1_BASE_ADDR + _PIO_OER_OFFS))
#define _LEDPORT1_SODR  (*(volatile unsigned int*) (_LEDPORT1_BASE_ADDR + _PIO_SODR_OFFS))
#define _LEDPORT1_CODR  (*(volatile unsigned int*) (_LEDPORT1_BASE_ADDR + _PIO_CODR_OFFS))
#define _LEDPORT1_STATE (*(volatile unsigned int*) (_LEDPORT1_BASE_ADDR + _PIO_ODSR_OFFS))

#define _LEDMASK0_ALL   (1 << _LED0_BIT)
#define _LEDMASK1_ALL   (1 << _LED1_BIT)

/*********************************************************************
*
*       Static const
*
**********************************************************************
*/
typedef struct {
  volatile unsigned int * pSODR;
  volatile unsigned int * pCODR;
  volatile unsigned int * pSTATE;
  char                    Id;
} LED_TYPE;

static const LED_TYPE _aLED[] = {
  {&_LEDPORT0_SODR, &_LEDPORT0_CODR, &_LEDPORT0_STATE, _LED0_BIT},
  {&_LEDPORT0_SODR, &_LEDPORT0_CODR, &_LEDPORT0_STATE, _LED1_BIT}
};

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
  _PMC_PCER     |= (1 << _LEDPORT0_ID)  /* Enable peripheral clock for LED-Ports    */
                |  (1 << _LEDPORT1_ID)
                 ;
  _LEDPORT0_PER   = _LEDMASK0_ALL;       /* enable Port           */
  _LEDPORT0_OER   = _LEDMASK0_ALL;       /* switch to output mode */
  _LEDPORT0_SODR |= _LEDMASK0_ALL;       /* Initially clear LEDs  */
  _LEDPORT1_PER   = _LEDMASK1_ALL;       /* enable Port           */
  _LEDPORT1_OER   = _LEDMASK1_ALL;       /* switch to output mode */
  _LEDPORT1_SODR |= _LEDMASK1_ALL;       /* Initially clear LEDs  */
}

/*********************************************************************
*
*       LED switching routines
*       LEDs are switched on with low level on port lines
*/
void BSP_SetLED(int Index) {
  *_aLED[Index].pCODR = (1 << _aLED[Index].Id);         /* Switch on LED 0  */
}

void BSP_ClrLED(int Index) {
  *_aLED[Index].pSODR = (1 << _aLED[Index].Id);         /* Switch on LED 0  */
}

void BSP_ToggleLED(int Index) {
  if (*_aLED[Index].pSTATE & (1 << _aLED[Index].Id)) {  /* LED is switched off */
    BSP_SetLED(Index);
  } else {
    BSP_ClrLED(Index);
  }
}

/****** EOF *********************************************************/

