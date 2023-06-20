/*******************
 *
 * Copyright 1998-2003 IAR Systems. All rights reserved.
 *
 * $Revision: 1.3 $
 *
 * This is the default implementation of the "exit" function of the
 * standard library.  It can be replaced with a system-specific
 * implementation.
 *
 * The "exit" function is called when the system performs a normal
 * termination.
 *
 ********************/

#include <yfuns.h>

void exit(int arg)
{
  _exit(arg);
}
