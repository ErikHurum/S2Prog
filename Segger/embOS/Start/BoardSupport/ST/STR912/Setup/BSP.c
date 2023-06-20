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
Purpose : BSP for ST STR912-EVAL board
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

/****** SFRs used for LED-Port **************************************/

#define _APB0_BASE_ADDR    0x58000000

#define _GPIO0_BASE_ADDR   (_APB0_BASE_ADDR + 0x6000)
#define _GPIO1_BASE_ADDR   (_APB0_BASE_ADDR + 0x7000)
#define _GPIO2_BASE_ADDR   (_APB0_BASE_ADDR + 0x8000)
#define _GPIO3_BASE_ADDR   (_APB0_BASE_ADDR + 0x9000)
#define _GPIO4_BASE_ADDR   (_APB0_BASE_ADDR + 0xA000)
#define _GPIO5_BASE_ADDR   (_APB0_BASE_ADDR + 0xB000)
#define _GPIO6_BASE_ADDR   (_APB0_BASE_ADDR + 0xC000)
#define _GPIO7_BASE_ADDR   (_APB0_BASE_ADDR + 0xD000)
#define _GPIO8_BASE_ADDR   (_APB0_BASE_ADDR + 0xE000)
#define _GPIO9_BASE_ADDR   (_APB0_BASE_ADDR + 0xF000)

#define _APB1_BASE_ADDR     0x5C000000
#define _SCU_BASE_ADDR      (_APB1_BASE_ADDR + 0x2000)

#define _SCU_PCGR1    *(volatile unsigned int*)(_SCU_BASE_ADDR + 0x18)
#define _SCU_PRR1     *(volatile unsigned int*)(_SCU_BASE_ADDR + 0x20)
#define _SCU_EMI      *(volatile unsigned int*)(_SCU_BASE_ADDR + 0xAC)
#define _SCU_GPIOOUT6 *(volatile unsigned int*)(_SCU_BASE_ADDR + 0x5C)

#define _DIR_OFFS     0x400
#define _SEL_OFFS     0x420

/****** Assign LEDs to Ports ****************************************/

#ifdef STR910_EK
  #define _LEDPORT_BASE_ADDR     _GPIO9_BASE_ADDR
  #define _LED_PORT_CLK_BIT 23          // used to enable GPIO port clock

  #define _LED0_BIT  0  // LD2 on EVAL board
  #define _LED1_BIT  1  // LD3 on EVAL board

  #define _LEDPORT_DIR   *(volatile unsigned char*)(_LEDPORT_BASE_ADDR + _DIR_OFFS)
  #define _LEDPORT_SEL   *(volatile unsigned char*)(_LEDPORT_BASE_ADDR + _SEL_OFFS)
  #define _LEDPORT0_DATA *(volatile unsigned char*)(_LEDPORT_BASE_ADDR + ((1 << _LED0_BIT) << 2))
  #define _LEDPORT1_DATA *(volatile unsigned char*)(_LEDPORT_BASE_ADDR + ((1 << _LED1_BIT) << 2))

#else
  #define _LEDPORT_BASE_ADDR     _GPIO6_BASE_ADDR
  #define _LED_PORT_CLK_BIT 20          // used to enable GPIO port clock

  #define _LED0_BIT  7  // LED16 on EVAL board
  #define _LED1_BIT  6  // LED15 on EVAL board

  #define _LEDPORT_DIR   *(volatile unsigned char*)(_LEDPORT_BASE_ADDR + _DIR_OFFS)
  #define _LEDPORT_SEL   *(volatile unsigned char*)(_LEDPORT_BASE_ADDR + _SEL_OFFS)
  #define _LEDPORT0_DATA *(volatile unsigned char*)(_LEDPORT_BASE_ADDR + ((1 << _LED0_BIT) << 2))
  #define _LEDPORT1_DATA *(volatile unsigned char*)(_LEDPORT_BASE_ADDR + ((1 << _LED1_BIT) << 2))
#endif

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
#ifdef STR910_EK
  _SCU_EMI   &= ~(1 << 0);                     // Switch port mode of P9 to GPIO function
#endif
  _SCU_PCGR1    |= (1 << _LED_PORT_CLK_BIT);   // Activate GPIO clock for LED port
  _SCU_PRR1     |= (1 << _LED_PORT_CLK_BIT);   // Clear reset for LED port
#ifndef STR910_EK
  _SCU_GPIOOUT6 |= (1 << 14) | ( 1 << 12);     // Normal Ouput mode LED0, LED1
#endif
  /* Setup port mode: GPIO used, output */
  _LEDPORT_DIR  |=  ((1 << _LED0_BIT) | (1 << _LED1_BIT));  // Set to output
  _LEDPORT_SEL  &= ~((1 << _LED0_BIT) | (1 << _LED1_BIT));
  /* Initially switch off LEDs */
  _LEDPORT0_DATA = (1 << _LED0_BIT);
  _LEDPORT1_DATA = (1 << _LED1_BIT);
}

/*********************************************************************
*
*       LED switching routines
*       LEDs are switched on by low level on port lines
*/
void BSP_SetLED(int Index) {
  if (Index == 0) {
    _LEDPORT0_DATA = 0;                  /* Switch on LED 0  */
  } else if (Index == 1) {
    _LEDPORT1_DATA = 0;                  /* Switch on LED1  */
  }
}

void BSP_ClrLED(int Index) {
  if (Index == 0) {
    _LEDPORT0_DATA = (1 << _LED0_BIT);   /* Switch off LED 0 */
  } else if (Index == 1) {
    _LEDPORT1_DATA = (1 << _LED1_BIT);   /* Switch off LED1 */
  }
}

void BSP_ToggleLED(int Index) {
  if (Index == 0) {
    _LEDPORT0_DATA ^= (1 << _LED0_BIT);  /* LED is switched off */
  } else if (Index == 1) {
    _LEDPORT1_DATA ^= (1 << _LED1_BIT);  /* LED is switched on */
  }
}

/****** EOF *********************************************************/

