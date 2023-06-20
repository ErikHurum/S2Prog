#include "StdAfx.h"
#include ".\win32exception.h"

CWin32Exception::CWin32Exception(const EXCEPTION_RECORD& info)
: mWhat("Win32 exception"), mWhere(info.ExceptionAddress), mCode(info.ExceptionCode)
{
    switch (info.ExceptionCode) 
	{
    case EXCEPTION_ACCESS_VIOLATION:
        mWhat = "Access violation";
        break;
    case EXCEPTION_FLT_DIVIDE_BY_ZERO:
    case EXCEPTION_INT_DIVIDE_BY_ZERO:
        mWhat = "Division by zero";
        break;
    }
}

void CWin32Exception::translate(unsigned int code, EXCEPTION_POINTERS* info)
{
	// suppress compiler warning
	code;

	throw CWin32Exception(*(info->ExceptionRecord));
}
