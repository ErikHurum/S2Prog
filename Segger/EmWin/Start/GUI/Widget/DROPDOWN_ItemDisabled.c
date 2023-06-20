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
  unsigned NumItems;
  GUI_ARRAY hDisabled;
  if (hObj) {
    WM_LOCK();
    pObj = DROPDOWN_LOCK_H(hObj);
    hDisabled = pObj->hDisabled;
    NumItems = GUI_ARRAY_GetNumItems(pObj->Handles);
    GUI_UNLOCK_H(pObj);
    if (Index < NumItems) {
      int RequiredSize;
      RequiredSize = ((Index + 8) / 8) + sizeof(U16); /* One bit per entry + number of entries */
      if (hDisabled) {
        /* If handle already exists, check if size is sufficient */
        U16 NumItems;
        U16 * pNumItems;
        pNumItems = (U16 *)GUI_LOCK_H(hDisabled);
        NumItems = *pNumItems;
        GUI_UNLOCK_H(pNumItems);
        if ((unsigned)NumItems < (Index + 1)) {
          /* Enlarge memory block */
          WM_HMEM hNew;
          U8  * pNew;
          U8  * pOld;
          hNew = GUI_ALLOC_AllocZero(RequiredSize);
          if (hNew) {
            pNew = (U8 *)GUI_LOCK_H(hNew);
            pOld = (U8 *)GUI_LOCK_H(hDisabled);
            GUI_MEMCPY(pNew, pOld, ((NumItems + 7) / 8) + sizeof(U16));
            *(U16 *)pNew = Index + 1;        /* Save number of items */
            GUI_ALLOC_Free(hDisabled); /* Free old memory */
            pObj = DROPDOWN_LOCK_H(hObj);
            pObj->hDisabled = hNew;          /* Use new handle */
            GUI_UNLOCK_H(pNew);
            GUI_UNLOCK_H(pOld);
            GUI_UNLOCK_H(pObj);
            hDisabled = hNew;
          }
        }
      } else {
        /* Create memory block */
        hDisabled = GUI_ALLOC_AllocZero(RequiredSize);
        if (hDisabled) {
          U16 * pNumItems;
          pNumItems = (U16 *)GUI_LOCK_H(hDisabled);
          *pNumItems = Index + 1;
          GUI_UNLOCK_H(pNumItems);
          pObj = DROPDOWN_LOCK_H(hObj);
          pObj->hDisabled = hDisabled;
          GUI_UNLOCK_H(pObj);
        }
      }
      /* Save disabled state of item */
      if (hDisabled) {
        U8 * pDisabled;
        pDisabled = (U8 *)GUI_LOCK_H(hDisabled) + sizeof(U16);
        if (OnOff) {
          *(pDisabled + (Index >> 3)) |=  (1 << (Index & 7));
        } else {
          *(pDisabled + (Index >> 3)) &= ~(1 << (Index & 7));
        }
        GUI_UNLOCK_H(pDisabled);
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
  unsigned NumItems;
  DROPDOWN_Obj * pObj;
  GUI_ARRAY hDisabled;
  r = 0;
  if (hObj) {
    WM_LOCK();
    pObj = DROPDOWN_LOCK_H(hObj);
    NumItems = GUI_ARRAY_GetNumItems(pObj->Handles);
    hDisabled = pObj->hDisabled;
    GUI_UNLOCK_H(pObj);
    if ((Index < NumItems) && hDisabled) {
      U16 NumItems;
      U16 * p;
      p = (U16 *)GUI_LOCK_H(hDisabled);
      NumItems = *p; /* Current number of items */
      GUI_UNLOCK_H(p);
      if (Index < (unsigned)NumItems) {
        U8 * pDisabled;
        pDisabled = (U8 *)GUI_LOCK_H(hDisabled) + sizeof(U16);
        r = *(pDisabled + (Index >> 3)) & (1 << (Index & 7)) ? 1 : 0;
        GUI_UNLOCK_H(pDisabled);
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
