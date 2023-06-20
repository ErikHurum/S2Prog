/*******************
 *
 * Copyright 1998-2003 IAR Systems. All rights reserved.
 *
 * $Revision: 1.7 $
 *
 * This is the default implementation of the "abort" function of the
 * standard library.  It can be replaced with a system-specific
 * implementation.
 *
 * The abort function is called when an abnormal program termination
 * should occur.
 *
 ********************/

#include <stdlib.h>
#include <yfuns.h>

_STD_BEGIN

#pragma module_name = "?abort"

void abort(void)
{
  __exit(EXIT_FAILURE);
}

_STD_END
