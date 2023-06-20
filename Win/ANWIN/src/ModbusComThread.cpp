//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "def.h"
#include "ModbusComThread.h"
#include "TSNIncludes.h"
#include "ANWinException.h"
//#include "lib\MBTError.h"
//#pragma package(smart_init)

//#pragma link "lib\\BTInit.obj"
//#pragma link "BTExit.obj"
//#pragma link "BTConnect.obj"

// function signature for the MBT void functions






unsigned m_lWagoReturnStatus;
#ifdef __cplusplus
extern "C"
{
#endif
long _stdcall MBTInit();

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ModbusComThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall ModbusComThread::ModbusComThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	NameThreadForDebugging(System::String(L"ModbusComThread"));

	const char* dllPath = "MBT.dll";
	HMODULE hm = LoadLibrary(dllPath);

	if (hm != NULL) {
		pMBTInit           = (mbtVoidFunc          ) GetProcAddress(hm, "MBTInit");
		pMBTExit           = (mbtVoidFunc          ) GetProcAddress(hm, "MBTExit");
		pMBTConnect        = (mbtConnectFunc       ) GetProcAddress(hm, "MBTConnect");
		pMBTDisconnect     = (mbtDisconnectFunc    ) GetProcAddress(hm, "MBTDisconnect");
		pMBTReadRegisters  = (mbtReadRegistersFunc ) GetProcAddress(hm, "MBTReadRegisters");
		pMBTWriteRegisters = (mbtWriteRegistersFunc) GetProcAddress(hm, "MBTWriteRegisters");
		pMBTReadCoils      = (mbtReadCoilsFunc  	) GetProcAddress(hm, "MBTReadCoils");
		pMBTWriteCoils     = (mbtWriteCoilsFunc    ) GetProcAddress(hm, "MBTWriteCoils");

		pMBTInit();
		m_hWagoSocketHandle = 0;
	 }
	 else
	 {
		AnsiString errorMsg;
		errorMsg.cat_sprintf("%s not found", dllPath);
		throw ANWinException(errorMsg);
	 }

     OnTerminate = OnTerminateThread;
}
//---------------------------------------------------------------------------
void __fastcall ModbusComThread::Execute()
{
	U16 InRegisterBuf[100];
	U16   InRegs[10];
	float InRegsF[5];
	bool LittleEndian = false;
	NameThreadForDebugging(System::String(L"ModbusComThread"));
	ModbusUnit::SetToMaster();

	//---- Place thread code here ----
	Sleep(500);

	int Cnt=0;
	while ( !Terminated ) {
		try {
			// Connect if not connected
			if (m_hWagoSocketHandle == 0) {
				m_lWagoReturnStatus = pMBTConnect("192.168.227.200", 502, true, 2000, &m_hWagoSocketHandle);
			}
			bool success = ModbusObject::ThreadModBusHandle(m_hWagoSocketHandle,pMBTReadRegisters,pMBTWriteRegisters,pMBTReadCoils,pMBTWriteCoils);

			if (!success) {
				pMBTDisconnect(m_hWagoSocketHandle);
				m_hWagoSocketHandle = 0;				// Trigger a reconnect
			}
		}
		catch (...) {
		}
		Cnt++;

		if (Terminated) {
			break;
		}
		else
		{
			Sleep(500);
		}
	}
	return;
}

//---------------------------------------------------------------------------
__fastcall ModbusComThread::~ModbusComThread(void)
{

}


//---------------------------------------------------------------------------
void __fastcall ModbusComThread::OnTerminateThread(TObject* Sender)
{
    pMBTExit();
}
