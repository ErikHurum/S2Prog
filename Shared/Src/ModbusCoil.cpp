#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
set<PRogramObjectBase*>ModbusCoil::ModbusSet;

ModbusCoil::ModbusCoil(void)
{
	ModbusSet.insert(this);
	AlarmDelay = 0;
    NormalState= 0;

}

ModbusCoil::~ModbusCoil(void)
{
	ModbusSet.erase(this);
}
//---------------------------------------------------------------------------


int ModbusCoil::GetAlarmDelay(void)
{
	return AlarmDelay;
}


