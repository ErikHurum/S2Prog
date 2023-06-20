/*******************
 *
 * Copyright 1998-2003 IAR Systems. All rights reserved.
 *
 * $Revision: 1.6 $
 *
 * This is the default implementation of the "raise" function of the
 * standard library.  It can be replaced with a system-specific
 * implementation.
 *
 * The "raise" function should call the signal handler for the raised
 * signal, or terminate and possibly report an error.
 *
 ********************/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
_STD_BEGIN

int (raise)(int sig)
{	/* raise a signal */
  _Sigfun *const s = signal(sig, SIG_IGN);

  if (s == SIG_ERR)
    return (-1);	/* bad signal */
  else if (s == SIG_IGN)
    ;
  else if (s != SIG_DFL)
  {	/* revert and call handler */
    signal(sig, SIG_DFL);
    (*s)(sig);
  }
  else
  {	/* default handling */
    exit(EXIT_FAILURE);
  }
  return 0;
}

_STD_END

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
