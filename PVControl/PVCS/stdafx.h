// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0501		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
//#define _WIN32_WINNT 0x0500		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#define _WIN32_WINNT 0x501//JSD
#endif

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
//#define _WIN32_IE 0x0400	// Change this to the appropriate value to target IE 5.0 or later.
#define _WIN32_IE 0x0500//JSD
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "MBT.h"
#include <afxsock.h>		// MFC socket extensions

//#include <tmschema.h>
#include <uxtheme.h>
#pragma comment(lib, "uxtheme.lib")

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

#include "win32exception.h"
#include "writelog.h"

#define SCREENMENUID	4000
#define SCREENMENUFIRSTID	SCREENMENUID + 1
#define SCREENMENULASTID	SCREENMENUID + 30

#define NOTANK -1

#define WM_UPDATE_VALUES	WM_APP + 0x100	// Message ID for updating the values
#define WM_TIMEOUT			WM_APP + 0x101

#define UPDATE_DELAY_TIMER	1000	// The update interval

#define XML_OBJECT_CONFIGURATION_FILE	"XMLFILES\\detailconfig.xml" // The config file for objects
#define XML_MAIN_CONFIGURATION_FILE		"XMLFILES\\config.xml" // The main config file

#ifdef _DEBUG

#include <time.h>
#include <afxdhtml.h>
#include <afxcontrolbars.h>

#define BEGINTICK(location) CString _str_ = location; TRACE("Tick_"location": Begin\n"); clock_t start_tick = clock()

#define SHOWTICK(tag) {clock_t finish_tick = clock(); double duration_tick = (double)(finish_tick - start_tick) / CLOCKS_PER_SEC; TRACE("Tick_%s: Time elapsed at "tag": %2.3f sec\n", _str_, duration_tick);}


#define SETMEMCHECK		CMemoryState oldMemState, newMemState, diffMemState; oldMemState.Checkpoint();
#define CHECKMEM		newMemState.Checkpoint(); if( diffMemState.Difference( oldMemState, newMemState ) ){TRACE( "Memory leaked!\n" ); }
#define ToHex(n)	((BYTE) (((n) > 9) ? ((n) - 10 + 'A') : ((n) + '0')))



#endif
