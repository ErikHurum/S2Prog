//---------------------------------------------------------------------------

#ifndef ModbusComUnitH
#define ModbusComUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class ModbusComThread : public TThread
{
protected:
	void __fastcall Execute();
public:
	__fastcall ModbusComThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
