//---------------------------------------------------------------------------

#ifndef TankWashingExceptionH
#define TankWashingExceptionH
//---------------------------------------------------------------------------

#include <stdexcept>
#include <string>
#if defined(ANWIN) || defined(ANTDUSIM)
class TankWashingException : public std::runtime_error
#else
class TankWashingException : public runtime_error
#endif
{
public:
	TankWashingException(const char *message);
};

#endif
