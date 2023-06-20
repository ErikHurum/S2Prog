/*********************************************************************
*               SEGGER MICROCONTROLLER SYSTEME GmbH                  *
*       Solutions for real time microcontroller applications         *
**********************************************************************
*                                                                    *
*       (C) 2006   SEGGER Microcontroller Systeme GmbH               *
*                                                                    *
*       www.segger.com     Support: support@segger.com               *
*                                                                    *
**********************************************************************
*                                                                    *
*       embOS * Real time operating system for microcontrollers      *
*                                                                    *
*                                                                    *
*       Please note:                                                 *
*                                                                    *
*       Knowledge of this file may under no circumstances            *
*       be used to write a similar product or a real-time            *
*       operating system for in-house use.                           *
*                                                                    *
*       Thank you for your fairness !                                *
*                                                                    *
**********************************************************************
*                                                                    *
*       embOS version: 3.32a                                         *
*                                                                    *
**********************************************************************

----------------------------------------------------------------------
File    : OS_DLIB.c 
Purpose : embOS specific implementation of thread safe
          system library support for IAR system libraries.
          Do not modify any entry here.

--------  END-OF-HEADER  ---------------------------------------------
*/

#include "RTOS.h"
#include "stdio.h"   /* Needed to determine _MAX_LOCK and FOPEN_MAX */

#if (_DLIB_THREAD_SUPPORT != 0) /* Needed with thread safe system library only */

/*********************************************************************
*
*       Configuration
*
*********************************************************************/

#define _MAX_SEMA (_MAX_LOCK + FOPEN_MAX)

/*********************************************************************
*
*       Static data
*
*********************************************************************/

static OS_RSEMA _aRSema[_MAX_SEMA];
static int _RSemaCnt = 0;

/*********************************************************************
*
*       Global functions
*
*********************************************************************/

/*********************************************************************
*
*       _Mtxinit()
*
* Function description:
*   Called once from within system library function before any
*   of the required locks is used.
*   Initilizes an embOS resource semaphore and returns a pointer
*   to the semaphore.
*/
void _Mtxinit(void** pMtx) {      /* Initailize a lock */
  if (_RSemaCnt < _MAX_SEMA) {
    OS_CreateRSema(&_aRSema[_RSemaCnt]);
    *pMtx = (void*) &_aRSema[_RSemaCnt];
    _RSemaCnt++;
  }
}

/*********************************************************************
*
*       _Mtxdst()
*
* Function description:
*   Deletes a resource semaphore.
*/
void _Mtxdst(void** pMtx) {       /* Destroy a lock */
  OS_DeleteRSema((OS_RSEMA*) *pMtx);
}

/*********************************************************************
*
*       _Mtxlock()
*
* Function description:
*   Called to lock any system function against multiple access
*/
void _Mtxlock(void** pMtx) {      /* Lock a lock */
  OS_Use((OS_RSEMA*) *pMtx);
}

/*********************************************************************
*
*       _Mtxunlock()
*
* Function description:
*   Releases semaphore to re-eanble access of protected resource
*/
void _Mtxunlock(void** pMtx) {    /* Unlock a lock */
  OS_Unuse((OS_RSEMA*) *pMtx);
}

/********************************************************************/

#endif  /* _DLIB_THREAD_SUPPORT != 0 */

/****** EOF *********************************************************/
