/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 2002         SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

**** emWin/GSC Grafical user interface for embedded applications ****
emWin is protected by international copyright laws. Knowledge of the
source code may not be used to write a similar product. This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUIConf.h
Purpose     : Configures emWins abilities, fonts etc.
----------------------------------------------------------------------
*/


#ifndef GUICONF_H
#define GUICONF_H

#define GUI_OS                    (1)  /* Compile with multitasking support */
#define GUI_SUPPORT_TOUCH         (1)  /* Support a touch screen (req. win-manager) */
#define GUI_SUPPORT_UNICODE       (1)  /* Support mixed ASCII/UNICODE strings */

#define GUI_DEFAULT_FONT          &GUI_Font6x8
#define GUI_NOT_COLOR 		  0xffffffe      /* Not set color */


#define BUTTON_REACT_ON_LEVEL				1


#define GUI_MAXTASK (10)
/*********************************************************************
*
*         Configuration of available packages
*/
#define GUI_SUPPORT_MOUSE             0    /* Support a mouse */
#define GUI_WINSUPPORT                1    /* Use window manager */
#define GUI_SUPPORT_MEMDEV            1    /* Memory device package available */
#define GUI_SUPPORT_AA                0    /* Antialiasing package not available */
#define GUI_ALLOC_SIZE                600000//(524288)  // Modified by EHS/RB 301003
    /* Size of dynamic memory ... For WM, cursor and memory devices*/
#endif  /* Avoid multiple inclusion */
