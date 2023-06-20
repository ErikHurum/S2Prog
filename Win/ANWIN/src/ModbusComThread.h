//---------------------------------------------------------------------------

#ifndef ModbusComThreadH
#define ModbusComThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "lib\MBT.h"
//---------------------------------------------------------------------------
class ModbusComThread : public TThread
{
private:
	mbtVoidFunc 			pMBTInit            ;
	mbtVoidFunc 			pMBTExit            ;
	mbtConnectFunc  		pMBTConnect         ;
	mbtDisconnectFunc 		pMBTDisconnect      ;
	mbtReadRegistersFunc 	pMBTReadRegisters   ;
	mbtWriteRegistersFunc   pMBTWriteRegisters  ;
	mbtReadCoilsFunc     	pMBTReadCoils       ;
	mbtWriteCoilsFunc		pMBTWriteCoils      ;

protected:


	void __fastcall Execute();
	HANDLE m_hWagoSocketHandle;
	unsigned WagoConnectionStatus;

	void __fastcall OnTerminateThread(TObject* Sender);

public:
	__fastcall ModbusComThread(bool CreateSuspended);
	__fastcall ~ModbusComThread(void);
};
//---------------------------------------------------------------------------
#endif
