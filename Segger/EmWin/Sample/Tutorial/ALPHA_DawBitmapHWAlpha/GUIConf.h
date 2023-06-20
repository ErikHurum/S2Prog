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
File        : GUIConf.h
Purpose     : Configures emWins abilities, fonts etc.
----------------------------------------------------------------------
*/

#ifndef GUICONF_H
#define GUICONF_H

/*********************************************************************
*
*         Configuration of desired functionality
*/
#define GUI_WINSUPPORT            1  /* Use window manager if true (1)  */
#define GUI_SUPPORT_TOUCH         1  /* Support a touch screen */
#define GUI_SUPPORT_MOUSE         1  /* Support a mouse */
#define GUI_SUPPORT_MEMDEV        1  /* Support for memory devices */
#define GUI_NUM_LAYERS            2
#define GUI_SUPPORT_MULTIUSER     1

/*********************************************************************
*
*         Configuration of  fonts (optional)
*
* If your create add. fonts (usually using the emWin FontConvert), these
* fonts need to be declared as extern in order to be able to use them.
* This would be a good place to do this.
*/
#define GUI_DEFAULT_FONT    &GUI_Font6x8   /* This font is used as default */

#endif /* GUICONF_H */
