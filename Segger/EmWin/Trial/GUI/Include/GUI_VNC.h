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
File        : GUI_VNC.h
Purpose     : Publics for the VNC server
---------------------------END-OF-HEADER------------------------------

Attention : Do not modify this file ! If you do, you will not
            be able do update to a later GUI version !

*/

#ifndef  GUI_VNC_H
#define  GUI_VNC_H

#include "GUI_Private.h"

#if GUI_SUPPORT_DEVICES


#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif


/*********************************************************************
*
*       defines
*
**********************************************************************
*/
#define GUI_VNC_NO_ERROR            0
#define GUI_VNC_ERROR_MISC          1
#define GUI_VNC_ERROR_WRONGFORMAT   2

/*********************************************************************
*
*       types
*
**********************************************************************
*/
typedef int (*GUI_tSend)   (const U8 * pData, int len, void* pConnectInfo);
typedef int (*GUI_tReceive)(      U8 * pData, int len, void* pConnectInfo);

typedef struct GUI_VNC_CONTEXT {
  struct GUI_VNC_CONTEXT * pNext;
  int LayerIndex;
  int BytesPerPixel;
  /* Connection related data */
  GUI_tSend    pfSend;
  GUI_tReceive pfReceive;
  void*        pConnectInfo;
  U16          ServerIndex;
  /* Display related info */
  const tLCDDEV_APIList* pLayerAPIOrig;
  tLCDDEV_APIList       VNC_LayerAPI;
  int x0Dirty, y0Dirty, x1Dirty, y1Dirty;
  int XSize, YSize;
  int xOrg, yOrg, xOrgNew, yOrgNew;
  int OrgLock;
  /* Status */
  char ClientSupportsHextile;
  char IsBigEndian;
} GUI_VNC_CONTEXT;

/*********************************************************************
*
*       functions
*
**********************************************************************
*/
int  GUI_VNC_Process      (GUI_VNC_CONTEXT* pContext, GUI_tSend pfSend, GUI_tReceive pfReceive, void* pConnectInfo);
void GUI_VNC_AttachToLayer(GUI_VNC_CONTEXT* pContext, int LayerIndex);
int  GUI_VNC_GetNumConnections(void);

/****  External routine to link the server to the system ... USER defined ! ****/
int  GUI_VNC_X_StartServer(int LayerIndex, int ServerIndex);

#if defined(__cplusplus)
  }
#endif

#endif   /* GUI_SUPPORT_DEVICES */
#endif   /* Avoid multiple inclusion */

/*************************** End of file ****************************/
