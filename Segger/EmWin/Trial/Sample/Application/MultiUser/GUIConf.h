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
Purpose     : Configuration file for emWin, using all features
----------------------------------------------------------------------
*/

#ifndef GUICONF_H
#define GUICONF_H

#define BUTTON_REACT_ON_LEVEL 1
#define GUI_SUPPORT_MULTIUSER 1
#define GUI_SELECT_ALLOC      1

#define GUI_OS                    1  /* Multitasking support */
#define GUI_WINSUPPORT            1  /* Use window manager if true (1)  */
#define GUI_SUPPORT_TOUCH         1  /* Support a touch screen */
#define GUI_SUPPORT_MOUSE         1  /* Support a mouse */
#define GUI_SUPPORT_MEMDEV        1  /* Support for memory devices */
#define GUI_SUPPORT_AA            1  /* Support for antialiasing */
#define GUI_NUM_LAYERS            3
#define WM_SUPPORT_NOTIFY_VIS_CHANGED 1

#define GUI_DEFAULT_FONT    &GUI_Font6x8   /* This font is used as default */

#endif /* GUICONF_H */
