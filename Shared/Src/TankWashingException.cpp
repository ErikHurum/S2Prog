//---------------------------------------------------------------------------

#pragma hdrstop

#include "TankWashingException.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

TankWashingException::TankWashingException(const char* message)
	: std::runtime_error(std::string(message))
{
}
