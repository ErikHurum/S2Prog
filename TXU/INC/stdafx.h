// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#ifdef WIN32




#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <stdio.h>
#include <tchar.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

#define WINVER	0x0501	// Target Windows XP and Windows .NET Server

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Control
#endif // _AFX_NO_AFXCMN_SUPPORT


//#include <atlbase.h>


// TODO: reference additional headers your program requires here
#include <search.h>
#include <winsock2.h>
#include <iostream>
#include <fstream>
#endif
#include <GUI.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#include <string>
#include <ctype.h>
#include <math.h>

extern "C" {
	#include "GUI_X.h"
	#include "BUTTON.h"
	#include "EDIT.h"
	#include "FRAMEWIN.h"
	#include "LISTBOX.h"
	#include "DIALOG.h"
	#include "DROPDOWN.h"
	#include "TEXT.h"
	#include "HEADER.h"
	#include "LISTVIEW.h"
    //	#include "LCD_ConfDefaults.h"      /* valid LCD configuration */
	#include "MESSAGEBOX.h"
    #include "MULTIPAGE.h"

}

#ifdef ANTDUSIM
	using namespace std ;
#endif


