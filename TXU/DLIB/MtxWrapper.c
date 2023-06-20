/***************************************************
 *
 * Callback interface to the library threads manager.
 *
 * Copyright (C) 2006 IAR Systems.  All rights reserved.
 *
 * $Revision: 1.1.2.1 $
 *
 * This is an experimental interface to allow a RTOS kernel
 * to register thread safe support with the prebuilt libraries.
 *
 * System locking is enable (malloc/free).
 * File locking is not enabled.
 * TLS (locking of library static data) is not enabled.
 *
 ***************************************************/

#include <stddef.h>
#include <DLib_Threads.h>
#include <MtxWrapper.h>
#include "RTOS.h"
#include "stdio.h"   /* Needed to determine _MAX_LOCK and FOPEN_MAX */
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
#pragma diag_suppress=Pe550

static _MtxFuncPtr mtxinit;
static _MtxFuncPtr mtxdst;
static _MtxFuncPtr mtxlock;
static _MtxFuncPtr mtxunlock;
/* Call callback if registered */

void _Mtxinit(_Rmtx *pMtx)
{
  if (_RSemaCnt < _MAX_SEMA) {
    OS_CreateRSema(&_aRSema[_RSemaCnt]);
    *pMtx = (void*) &_aRSema[_RSemaCnt];
    _RSemaCnt++;
  }
}

void _Mtxdst(_Rmtx *pMtx)
{
  OS_DeleteRSema((OS_RSEMA*) *pMtx);
}

void _Mtxlock(_Rmtx *pMtx)
{
  OS_Use((OS_RSEMA*) *pMtx);
}

void _Mtxunlock(_Rmtx *pMtx)
{
  OS_Unuse((OS_RSEMA*) *pMtx);
}

/* Functions to register the callbacks */

void _MtxinitRegister(_MtxFuncPtr func)
{
  mtxinit = func;
}

void _MtxdstRegister(_MtxFuncPtr func)
{
  mtxdst = func;
}

void _MtxlockRegister(_MtxFuncPtr func)
{
  mtxlock = func;
}

void _MtxunlockRegister(_MtxFuncPtr func)
{
  mtxunlock = func;
}

