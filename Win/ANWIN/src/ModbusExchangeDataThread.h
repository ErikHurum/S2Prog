//---------------------------------------------------------------------------

#ifndef ModbusExchangeDataThreadH
#define ModbusExchangeDataThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class ModbusExchangeDataThread : public TThread
{
protected:
	void __fastcall Execute();
	void __fastcall OnTerminateThread(TObject* Sender);
public:
	__fastcall ModbusExchangeDataThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
