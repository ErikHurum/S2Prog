/*******************
 *
 * Copyright 1998-2003 IAR Systems. All rights reserved.
 *
 * $Revision: 1.5 $
 *
 * This is the default implementation of the "signal" function of the
 * standard library.  It can be replaced with a system-specific
 * implementation.
 *
 * The "signal" function handles signal handlers for all signals.  It
 * should return the current signal handler and keep "func" as the
 * current signal handler for signal "sig".
 *
 * The typical reason to modify this is if the environment supports
 * some kind of asynchronous signals.
 *
 ********************/

/* signal function */
#include <signal.h>
_STD_BEGIN

static _Sigfun *sigtable[_NSIG] = {0};

_Sigfun *(signal)(int sig, _Sigfun *func)
{	/* specify handling for a signal */
  _Sigfun *s;

  if (sig <= 0 || _NSIG <= sig || func == SIG_ERR)
    return (SIG_ERR);	/* bad signal */

  /* add machine-dependent handling here */

  _Locksyslock(_LOCK_MALLOC);
  s = sigtable[sig], sigtable[sig] = func;
  _Unlocksyslock(_LOCK_MALLOC);
  return (s);
}

_STD_END

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
