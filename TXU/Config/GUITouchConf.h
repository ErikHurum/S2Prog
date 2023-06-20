/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2004  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

***** emWin - Graphical user interface for embedded applications *****
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUITouch.Conf.h
Purpose     : Configures touch screen module
----------------------------------------------------------------------
*/


#ifndef GUITOUCH_CONF_H
#define GUITOUCH_CONF_H

// TDU Rev 1
#define GUI_TOUCH_AD_LEFT1       69   
#define GUI_TOUCH_AD_RIGHT1      926  
#define GUI_TOUCH_AD_TOP1        178  
#define GUI_TOUCH_AD_BOTTOM1     937  
// TDU Rev 2
#define GUI_TOUCH_AD_LEFT2       20
#define GUI_TOUCH_AD_RIGHT2      970
#define GUI_TOUCH_AD_TOP2        90
#define GUI_TOUCH_AD_BOTTOM2     990  



#define GUI_TOUCH_SWAP_XY    	0

#define GUI_TOUCH_MIRROR_X   	1
#define GUI_TOUCH_MIRROR_Y      1

#endif /* GUITOUCH_CONF_H */
#ifdef __cplusplus
  extern "C" {
#endif
	extern void GUI_TOUCH_SetCalData(int Coord, int pMin,int pMax);
#ifdef __cplusplus
  }
#endif

