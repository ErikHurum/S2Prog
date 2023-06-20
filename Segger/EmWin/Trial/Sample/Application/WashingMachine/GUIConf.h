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
              
ATTENTION

Do not modify this file. It will have no effect, since this
configuration has been used to compile the libraries.
You will need the GUI sources for changes in these settings to become
effective.
*/


#ifndef GUICONF_H
#define GUICONF_H

#define GUI_WINSUPPORT            1  /* Use window manager if true (1)  */
#define GUI_SUPPORT_TOUCH         1  /* Support a touch screen */
#define GUI_SUPPORT_MOUSE         1  /* Support a mouse */
#define GUI_SUPPORT_MEMDEV        1  /* Support for memory devices */
#define GUI_SUPPORT_AA            1  /* Support for antialiasing */

#define GUI_DEFAULT_FONT    &GUI_Font6x8

#endif /* GUICONF_H */
