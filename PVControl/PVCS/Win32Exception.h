#pragma once

#include "windows.h"
#include <exception>

class CWin32Exception :
	public std::exception
{
public:
    typedef const void* Address; // OK on Win32 platform
	//~CWin32Exception(void);

	static void install_handler(void)
	{
		_set_se_translator(CWin32Exception::translate);
	}
    virtual const char* what() const { return mWhat; };
    Address where() const { return mWhere; };
    unsigned code() const { return mCode; };

protected:
	CWin32Exception(const EXCEPTION_RECORD& info);
private:
    const char* mWhat;
    Address mWhere;
    unsigned mCode;
public:
	static void translate(unsigned int code, EXCEPTION_POINTERS* info);
};
