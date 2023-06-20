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
Purpose : BSP for OKI M69Q6203 CPU and ML69Q6203 CPU Board
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

#define	PIOD_PATTERN		0x0018
#define	PIOF_PATTERN		0x003F
#define	PIOD_MASK_PATTERN	0x00E7
#define	PIOF_MASK_PATTERN	0x00C0
#define	INPUT_PIOD_PATTERN	0x00C0

#define PCR_BASE3 0xB7A03000    /* base address */
#define PO3     (PCR_BASE3+0x00)  /* port3(PD) output register */
#define PM3     (PCR_BASE3+0x08)  /* port3(PD) Mode register */

#define PCR_BASE5 0xB7A05000    /* base address */
#define PO5     (PCR_BASE5+0x00)  /* port5(PF) output register */
#define PM5     (PCR_BASE5+0x08)  /* port5(PF) Mode register */

typedef unsigned char   UBYTE;  /* unsigned byte */

#define get_value(n)    (*((volatile UBYTE *)(n)))          /* byte input */
#define put_value(n,c)  (*((volatile UBYTE *)(n)) = (c))    /* byte output */

/****** constants for led_on() **************************************/

#define LED_START_PATTERN   0x0063  /* light upper 4 segments */
#define LED_NORMAL_END_PATTERN  0x005C  /* light lower 4 segments */
#define LED_0   0x003F  /* light "0" */
#define LED_1   0x0006  /* light "1" */
#define LED_2   0x005B  /* light "2" */
#define LED_3   0x004F  /* light "3" */
#define LED_4   0x0066  /* light "4" */
#define LED_5   0x006D  /* light "5" */
#define LED_6   0x007D  /* light "6" */
#define LED_7   0x0027  /* light "7" */
#define LED_8   0x007F  /* light "8" */
#define LED_9   0x006F  /* light "9" */
#define LED_A   0x0077  /* light "A" */
#define LED_b   0x007C  /* light "b" */
#define LED_C   0x0039  /* light "C" */
#define LED_d   0x005E  /* light "d" */
#define LED_E   0x0079  /* light "E" */
#define LED_F   0x0071  /* light "F" */
#define LED_all 0x00FF  /* light all LEDs */
#define LED_off 0x0000  /* turn off all LEDs */

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static char _LEDStat0;
static char _LEDStat1;

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
  UBYTE  gppo_data;
  UBYTE  set_data;

  /* LED-control(set output mode) LOW-6bits */
  gppo_data = get_value(PM5);
  set_data = ((gppo_data & PIOF_MASK_PATTERN) | PIOF_PATTERN);
  put_value(PM5, set_data);

  /* LED-control(set output mode) HI-2bits */
  gppo_data = get_value(PM3);
  set_data = ((gppo_data & PIOD_MASK_PATTERN) | PIOD_PATTERN);
  put_value(PM3, set_data);
}

void BSP_LED(UBYTE pattern);
void BSP_LED(UBYTE pattern) {
  UBYTE gppo_data;
  UBYTE set_data;
  /************************************************/
  /***  Attention!! : Do not change this I/F !  ***/
  /************************************************/
  gppo_data = get_value(PO3);
  set_data = ((gppo_data & PIOD_MASK_PATTERN) | ((pattern & INPUT_PIOD_PATTERN) >> 3 ) );
  put_value(PO3, set_data);

  gppo_data = get_value(PO5);
  set_data = ((gppo_data & PIOF_MASK_PATTERN) | (pattern & PIOF_PATTERN));
  put_value(PO5, set_data);
}

/*********************************************************************
*
*       LED switching routines
*       LEDs are switched on with low level on port lines
*/
void BSP_SetLED(int Index) {
  if(Index == 0) {
    _LEDStat0 = 1;
    BSP_LED(LED_0);
  } else {
    _LEDStat1 = 1;
    BSP_LED(LED_1);
  }
}

void BSP_ClrLED(int Index) {
  if(Index == 0) {
    _LEDStat0 = 0;
    BSP_LED(LED_off);
  } else {
    _LEDStat1 = 0;
    BSP_LED(LED_off);
  }
}

void BSP_ToggleLED(int Index) {
  if(Index == 0) {
    if(_LEDStat0) {
      BSP_ClrLED(0);
    } else {
      BSP_SetLED(0);
    }
  } else {
    if(_LEDStat1) {
      BSP_ClrLED(1);
    } else {
      BSP_SetLED(1);
    }
  }
}

/****** EOF *********************************************************/


