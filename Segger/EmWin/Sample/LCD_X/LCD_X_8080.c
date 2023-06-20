/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2009  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.00 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCD_X_8080.c
Purpose     : Port routines 8080 interface, 8 bit data bus
----------------------------------------------------------------------
*/

/*********************************************************************
*
*           Hardware configuration
*
**********************************************************************
  Needs to be adapted to your target hardware.
*/

/* Configuration example:

#define Chip_30600
#include <IOM16C.H>

#define LCD_CLR_A0()      P8 &= ~(1<<0)
#define LCD_SET_A0()      P8 |=  (1<<0)
#define LCD_CLR_WR()      P8 &= ~(1<<1)
#define LCD_SET_WR()      P8 |=  (1<<1)
#define LCD_CLR_RD()      P8 &= ~(1<<2)
#define LCD_SET_RD()      P8 |=  (1<<2)
#define LCD_CLR_RESET()   P8 &= ~(1<<3)
#define LCD_SET_RESET()   P8 |=  (1<<3)
#define LCD_CLR_CS()      P8 &= ~(1<<4)
#define LCD_SET_CS()      P8 |=  (1<<4)
#define LCD_DATA_IN       P7
#define LCD_DATA_OUT      P7
#define LCD_SET_DIR_IN()  P7D = 0
#define LCD_SET_DIR_OUT() P7D = 0xff
#define LCD_DELAY(ms)     GUI_Delay(ms)
*/

/*********************************************************************
*
*           High level LCD access macros
*
**********************************************************************
  Usually, there is no need to modify these macros.
  It should be sufficient ot modify the low-level macros
  above.
*/

#define LCD_X_READ(c)     \
  LCD_SET_DIR_IN();       \
  LCD_CLR_CS();           \
  LCD_CLR_RD();           \
  c = LCD_DATA_IN;        \
  LCD_SET_RD();           \
  LCD_SET_CS();           \
  LCD_SET_DIR_OUT()


#define LCD_X_WRITE(data) \
  LCD_DATA_OUT = data;    \
  LCD_CLR_CS();           \
  LCD_CLR_WR();           \
  LCD_SET_WR();           \
  LCD_SET_CS()

/*********************************************************************
*
*           Initialisation
*
**********************************************************************
  This routine should be called from your application program
  to set port pins to their initial values
*/

void LCD_X_Init(void) {
  LCD_SET_CS();
  LCD_SET_RD();
  LCD_SET_WR();
  LCD_CLR_RESET();
  LCD_DELAY(20);
  LCD_SET_RESET();
  LCD_DELAY(20);
  LCD_SET_DIR_OUT();
}

void LCD_X_Sync(void) {
  LCD_CLR_CS();
  LCD_SET_RD();
  LCD_CLR_A0();
  LCD_CLR_WR();
  LCD_DELAY(1);
  LCD_SET_WR();
  LCD_DELAY(1);
  LCD_CLR_WR();
  LCD_DELAY(1);
  LCD_SET_WR();
  LCD_DELAY(1);
  LCD_CLR_WR();
  LCD_DELAY(1);
  LCD_SET_WR();
  LCD_DELAY(1);
  LCD_CLR_WR();
  LCD_DELAY(1);
  LCD_SET_WR();
  LCD_DELAY(1);
  LCD_SET_A0();
  LCD_SET_CS();
  LCD_DELAY(50);
}

/*********************************************************************
*
*           Access routines
*
**********************************************************************
  Usually, there is no need to modify these routines.
  It should be sufficient ot modify the low-level macros
  above.
*/

/* Write to controller, with A0 = 0 */
void LCD_X_Write00(unsigned char c) {
  LCD_CLR_A0();
  LCD_X_WRITE(c);
}

/* Write to controller, with A0 = 1 */
void LCD_X_Write01(unsigned char c) {
  LCD_SET_A0();
  LCD_X_WRITE(c);
}

/* Write multiple bytes to controller, with A0 = 1 */
void LCD_X_WriteM01(unsigned char * pData, int NumBytes) {
  LCD_SET_A0();
  for (; NumBytes; NumBytes--) {
    LCD_X_WRITE(*pData++);
  }
}

/* Write multiple bytes to controller, with A0 = 0 */
void LCD_X_WriteM00(unsigned char * pData, int NumBytes) {
  LCD_CLR_A0();
  for (; NumBytes; NumBytes--) {
    LCD_X_WRITE(*pData++);
  }
}

/* Read from controller, with A0 = 0 */
unsigned char LCD_X_Read00(void) {
  unsigned char c;
  LCD_CLR_A0();
  LCD_X_READ(c);
  return c;
}

/* Read from controller, with A0 = 1 */
unsigned char LCD_X_Read01(void) {
  unsigned char c;
  LCD_SET_A0();
  LCD_X_READ(c);
  return c;
}

/* Read multiple bytes from controller, with A0 = 1 */
void LCD_X_ReadM01(unsigned char * pData, int NumBytes) {
  LCD_SET_A0();
  for (; NumBytes; NumBytes--) {
    LCD_X_READ(*pData);
    pData++;
  }
}
