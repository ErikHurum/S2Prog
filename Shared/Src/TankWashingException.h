//---------------------------------------------------------------------------

#ifndef TankWashingExceptionH
#define TankWashingExceptionH
//---------------------------------------------------------------------------

#include <stdexcept>
#include <string>
#if defined(ANWIN) || defined(ANTDUSIM)
using namespace std;
#endif
class TankWashingException : public runtime_error
{
public:
	TankWashingException(const char *message);
};

#endif
