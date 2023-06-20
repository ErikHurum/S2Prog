/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2008  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V4.18 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCDConf.c
Purpose     : Display controller initialization
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "LCDConf.h"

/*********************************************************************
*
*       Define register contents
*
**********************************************************************
*/
#define LCD_REG04 0x00	// BUSCLK MEMCLK Config Register
#define LCD_REG05 0x42	// PCLK Config  Register
#define LCD_REG10 0x61	// PANEL Type Register
#define LCD_REG11 0x00	// MOD Rate Register
#define LCD_REG12 0x27	// Horizontal Total Register
#define LCD_REG14 ((LCD_XSIZE / 8) - 1)	// Horizontal Display Period Register
#define LCD_REG16 0x23	// Horizontal Display Period Start Pos Register 0
#define LCD_REG17 0x00	// Horizontal Display Period Start Pos Register 1
#define LCD_REG18 0x46	// Vertical Total Register 0 ; = 320
#define LCD_REG19 0x01	// Vertical Total Register 1
#define LCD_REG1C 0x3F	// Vertical Display Period Register 0
#define LCD_REG1D 0x01	// Vertical Display Period Register 1
#define LCD_REG1E 0x04	// Vertical Display Period Start Pos Register 0
#define LCD_REG1F 0x00	// Vertical Display Period Start Pos Register 1
#define LCD_REG20 0x04	// Horizontal Sync Pulse Width Register
#define LCD_REG22 0x13	// Horizontal Sync Pulse Start Pos Register 0
#define LCD_REG23 0x00	// Horizontal Sync Pulse Start Pos Register 1
#define LCD_REG24 0x01	// Vertical Sync Pulse Width Register
#define LCD_REG26 0x02	// Vertical Sync Pulse Start Pos Register 0
#define LCD_REG27 0x00	// Vertical Sync Pulse Start Pos Register 1
#define LCD_REG70 0x03	// Display Mode Register
#define LCD_REG71 0x00	// Special Effects Register
#define LCD_REG78 0x3C	// Main Window Address Offset Register 0
#define LCD_REG79 0x00	// Main Window Address Offset Register 1
#define LCD_REG80 0x00	// Sub Window (= PIP) Address Offset Register 0
#define LCD_REG81 0x00	// Sub Window Address Offset Register 1
#define LCD_REG8C 0x4F	// Sub Window X End Pos Register 0
#define LCD_REG8D 0x00	// Sub Window X End Pos Register 1
#define LCD_REG90 0xEF	// Sub Window Y End Pos Register 0
#define LCD_REG91 0x00	// Sub Window Y End Pos Register 1
#define LCD_REGA0 0x00	// Power Save Config Reg
#define LCD_REGA1 0x00	// reserved reg
#define LCD_REGA8 0x00	// GPIO Config Register 0
#define LCD_REGA9 0x80	// GPIO Config Register 1

#if !LCD_SWAP_BYTE_ORDER
  #define LCD_WRITE_REGLH(Adr, d0, d1) LCD_WRITE_REG(Adr, ((d0)<<8) | (d1))
#else
  #define LCD_WRITE_REGLH(Adr, d0, d1) LCD_WRITE_REG(Adr, ((d1)<<8) | (d0))
#endif  

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_InitController
*
* Purpose:
*   Initializes the display controller
*/
void LCD_X_InitController(unsigned LayerIndex) {
  GUI_USE_PARA(LayerIndex);
  LCD_WRITE_REGLH(0x04 >> 1, LCD_REG04, LCD_REG05);
  LCD_WRITE_REGLH(0x10 >> 1, LCD_REG10, LCD_REG11);
  LCD_WRITE_REGLH(0x12 >> 1, LCD_REG12, 0);
  LCD_WRITE_REGLH(0x14 >> 1, LCD_REG14, 0);
  LCD_WRITE_REGLH(0x16 >> 1, LCD_REG16, LCD_REG17);
  LCD_WRITE_REGLH(0x18 >> 1, LCD_REG18, LCD_REG19);
  LCD_WRITE_REGLH(0x1C >> 1, LCD_REG1C, LCD_REG1D);
  LCD_WRITE_REGLH(0x1E >> 1, LCD_REG1E, LCD_REG1F);
  LCD_WRITE_REGLH(0x20 >> 1, LCD_REG20, 0);
  LCD_WRITE_REGLH(0x22 >> 1, LCD_REG22, LCD_REG23);
  LCD_WRITE_REGLH(0x24 >> 1, LCD_REG24, 0);
  LCD_WRITE_REGLH(0x26 >> 1, LCD_REG26, LCD_REG27);
  LCD_WRITE_REGLH(0x70 >> 1, LCD_REG70, LCD_REG71);
  LCD_WRITE_REGLH(0x78 >> 1, LCD_REG78, LCD_REG79);
  LCD_WRITE_REGLH(0x80 >> 1, LCD_REG80, LCD_REG81);
  LCD_WRITE_REGLH(0x8C >> 1, LCD_REG8C, LCD_REG8D);
  LCD_WRITE_REGLH(0x90 >> 1, LCD_REG90, LCD_REG91);
  LCD_WRITE_REGLH(0xA0 >> 1, LCD_REGA0, LCD_REGA1);
  LCD_WRITE_REGLH(0xA8 >> 1, LCD_REGA8, LCD_REGA9);
}

/*************************** End of file ****************************/

