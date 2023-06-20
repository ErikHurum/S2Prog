/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2007  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V4.14 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : DROPDOWN_ItemDisabled.c
Purpose     : Implementation of dropdown widget
---------------------------END-OF-HEADER------------------------------
*/

#include <string.h>

#include "LISTBOX.h"
#include "DROPDOWN_Private.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Public routines
*
**********************************************************************
*/
/*********************************************************************
*
*       DROPDOWN_SetItemDisabled
*/
void DROPDOWN_SetItemDisabled(DROPDOWN_Handle hObj, unsigned Index, int OnOff) {
  DROPDOWN_Obj * pObj;
  if (hObj) {
    WM_LOCK();
    pObj = DROPDOWN_H2P(hObj);
    if (Index < (unsigned)pObj->Handles.NumItems) {
      int RequiredSize;
      RequiredSize = ((Index + 8) / 8) + sizeof(U16); /* One bit per entry + number of entries */
      if (pObj->hDisabled) {
        /* If handle already exists, check if size is sufficient */
        U16 NumItems;
        NumItems = *(U16 *)GUI_ALLOC_h2p(pObj->hDisabled); /* Current number of items */
        if ((unsigned)NumItems < (Index + 1)) {
          /* Enlarge memory block */
          WM_HMEM hNew;
          U8  * pNew;
          U8  * pOld;
          hNew = GUI_ALLOC_AllocZero(RequiredSize);
          if (hNew) {
            pNew = (U8 *)GUI_ALLOC_h2p(hNew);
            pOld = (U8 *)GUI_ALLOC_h2p(pObj->hDisabled);
            GUI_MEMCPY(pNew, pOld, ((NumItems + 7) / 8) + sizeof(U16));
            *(U16 *)pNew = Index + 1;        /* Save number of items */
            GUI_ALLOC_Free(pObj->hDisabled); /* Free old memory */
            pObj->hDisabled = hNew;          /* Use new handle */
          }
        }
      } else {
        /* Create memory block */
        pObj->hDisabled = GUI_ALLOC_AllocZero(RequiredSize);
        if (pObj->hDisabled) {
          *(U16 *)GUI_ALLOC_h2p(pObj->hDisabled) = Index + 1;
        }
      }
      /* Save disabled state of item */
      if (pObj->hDisabled) {
        U8 * pDisabled;
        pDisabled = (U8 *)GUI_ALLOC_h2p(pObj->hDisabled) + sizeof(U16);
        if (OnOff) {
          *(pDisabled + (Index >> 3)) |=  (1 << (Index & 7));
        } else {
          *(pDisabled + (Index >> 3)) &= ~(1 << (Index & 7));
        }
      }
    }
    WM_UNLOCK();
  }
}

/*********************************************************************
*
*       DROPDOWN_GetItemDisabled
*/
unsigned DROPDOWN_GetItemDisabled(DROPDOWN_Handle hObj, unsigned Index) {
  unsigned r;
  DROPDOWN_Obj * pObj;
  r = 0;
  if (hObj) {
    WM_LOCK();
    pObj = DROPDOWN_H2P(hObj);
    if (Index < (unsigned)pObj->Handles.NumItems && pObj->hDisabled) {
      U16 NumItems;
      NumItems = *(U16 *)GUI_ALLOC_h2p(pObj->hDisabled); /* Current number of items */
      if (Index < (unsigned)NumItems) {
        U8 * pDisabled;
        pDisabled = (U8 *)GUI_ALLOC_h2p(pObj->hDisabled) + sizeof(U16);
        r = *(pDisabled + (Index >> 3)) & (1 << (Index & 7)) ? 1 : 0;
      }
    }
    WM_UNLOCK();
  }
  return r;
}

#else                            /* Avoid problems with empty object modules */
  void DROPDOWN_ItemDisabled_C(void);
  void DROPDOWN_ItemDisabled_C(void) {}
#endif
