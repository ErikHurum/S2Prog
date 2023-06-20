/* localtime function */
#include <stdlib.h>
#include "xmtloc.h"
#include "xtime.h"
#include <yfuns.h>
_STD_BEGIN

#define MAXTZ	(100 * 13)	/* biggest valid HHMM offset from UTC */

typedef const char *_Localtime_old_t;

_TLS_DATA_DEF(static, _Localtime_old_t, _Localtime_oldzone, 0);
_TLS_DATA_DEF(static, long, _Localtime_tzoff, 0);

time_t _Tzoff(void)
{	/* determine local time offset */
	_Localtime_old_t *poldzone = _TLS_DATA_PTR(_Localtime_old_t,
                                                   _Localtime_oldzone);
	char const * * pzone = _TLS_DATA_PTR(char const *, _TzoneStr);
	long *ptzoff = _TLS_DATA_PTR(long, _Localtime_tzoff);

	if (*poldzone != *pzone)
		{	/* determine time zone offset (East is +) */
		const char *p, *pe;
		int n;

		if ( (*pzone)[0] == '\0' )
                        (*pzone) = __getzone();

		p = _Gettime(*pzone, 2, &n);
		*ptzoff = strtol(p, (char **)&pe, 10);
		if ( pe - p != n
				 || *ptzoff <= -MAXTZ || MAXTZ <= *ptzoff )
			*ptzoff = 0;
		*ptzoff -= (*ptzoff / 100) * 40;	/* HHMM -- changed for C9X */
		*ptzoff = -*ptzoff;	/* also change sense of offset for C9X */
		*poldzone = *pzone;
	}
	return(-*ptzoff * 60);
}

struct tm *(localtime)(const time_t *tod)
	{	/* convert to local time structure */
	return(_Ttotm(0, *tod + _Tzoff(), -1));
}

/*****************************************************************
*
* Added by EHS, Tanksystem Norway
*
*/
time_t *GetTimeZone(void)
{
	return(time_t*)_TLS_DATA_PTR(long, _Localtime_tzoff);
}

void SetTimeZone(int NewTZ)
{
	long *ptzoff = _TLS_DATA_PTR(long, _Localtime_tzoff);
	NewTZ /=60; // Convert to minutes
	if (NewTZ <= -12*60 ) {
		*ptzoff = 12*60;
	}else if ( NewTZ >= 12*60 ) {
		*ptzoff = -12*60;
	}else{
	  *ptzoff = NewTZ;
	}
}

_STD_END

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
