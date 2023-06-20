//---------------------------------------------------------------------------

#ifndef ANWinExceptionH
#define ANWinExceptionH
//---------------------------------------------------------------------------

#include "TSNIncludes.h"
#include <exception>


class ANWinException : public exception
{
private:
	AnsiString exceptionReason;

public:
	ANWinException(AnsiString& reason)
	{
		exceptionReason = reason;
	}

	/// Method used for fetching the error message in the exception
	///
	virtual inline const char* what() const throw()
	{
		return (const char*) exceptionReason.c_str();
	}
};

#endif
