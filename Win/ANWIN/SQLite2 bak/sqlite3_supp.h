//	sqlite3_supp.h : supplement header file for sqlite3.dll
//	Author: DLL to Lib version 3.00
//	Date: Wednesday, February 24, 2021
//	Description: The declaration of the sqlite3.dll's entry-point function.
//	Prototype: BOOL WINAPI xxx_DllMain(HINSTANCE hinstance, DWORD fdwReason, LPVOID lpvReserved);
//	Parameters: 
//		hinstance
//		  Handle to current instance of the application. Use AfxGetInstanceHandle()
//		  to get the instance handle if your project has MFC support.
//		fdwReason
//		  Specifies a flag indicating why the entry-point function is being called.
//		lpvReserved 
//		  Specifies further aspects of DLL initialization and cleanup. Should always
//		  be set to NULL;
//	Comment: Please see the help document for detail information about the entry-point 
//		 function
//	Homepage: http://www.binary-soft.com
//	Technical Support: support@binary-soft.com
/////////////////////////////////////////////////////////////////////

#if !defined(D2L_SQLITE3_SUPP_H__5E797C4F_20B7_7623_6B2E_1D0E565613F3__INCLUDED_)
#define D2L_SQLITE3_SUPP_H__5E797C4F_20B7_7623_6B2E_1D0E565613F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef __cplusplus
extern "C" {
#endif


#include <windows.h>

/* This is sqlite3.dll's entry-point function. You should call it to do necessary
 initialization and finalization. */

BOOL WINAPI SQLITE3_DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);


#ifdef __cplusplus
}
#endif

#endif // !defined(D2L_SQLITE3_SUPP_H__5E797C4F_20B7_7623_6B2E_1D0E565613F3__INCLUDED_)