
#include <exception>
#include <string>

class ArgumentException : public exception
{
private:
	string exceptionReason;
	
public:
	ArgumentException(string& reason)
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

