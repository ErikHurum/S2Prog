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
Purpose : BSP for ADuC702x Eval Boards
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

#define GP0CON    (*(volatile unsigned long *) 0xFFFFF404)
#define GP4DAT    (*(volatile unsigned long *) 0xFFFFF460)
#define GP4SET    (*(volatile unsigned long *) 0xFFFFF464)
#define GP4CLR    (*(volatile unsigned long *) 0xFFFFF468)

/****** Assign LEDs to Ports ****************************************/

#define GPIO_DAT (GP4DAT)
#define GPIO_SET (GP4SET)
#define GPIO_CLR (GP4CLR)

#define GPIO_LED1_BIT   (2)
#define GPIO_LED1_MASK  (1 << GPIO_LED1_BIT )

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
  GP0CON = 0x00;
  GPIO_DAT = (GPIO_LED1_MASK << 24);    /* Configure Port as output */
}

/*********************************************************************
*
*       LED switching routines
*       LEDs are switched on by low level on port lines
*/

void BSP_SetLED(int Index) {
  if (Index == 1) {
    GPIO_CLR = (GPIO_LED1_MASK << 16);   /* Switch on LED 1 */
  }
}

void BSP_ClrLED(int Index) {
  if (Index == 1) {
    GPIO_SET = (GPIO_LED1_MASK << 16);   /* Switch off LED 1 */
  }
}

void BSP_ToggleLED(int Index) {
  if (Index == 0) {
    GPIO_DAT ^= (GPIO_LED1_MASK << 16);  /* Toggle LED */
  }
}

/****** EOF *********************************************************/

