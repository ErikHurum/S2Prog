//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop
#include "MainUnit.h"

#include "ANPRO10ThreadUnit.h"
#pragma package(smart_init)

extern volatile bool IsReadyToReceive;
extern char MyRxBuf[UNPACK_BLOCK_SIZE];
extern WinUart *myWinUartPtr;
extern void ANPRO10_Receive(TSNUart *Port, int StartTimeOut, U8 *RxBuf, const volatile bool &Terminated);


//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ANPR10Receive::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall ANPR10ReceiveThread::ANPR10ReceiveThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
/*
		try {
			nrComm1->Active = true;
		} catch ( ... ) {
			int ComPort = 0;
			for ( int i = 1; !ComPort && i < 32; i++ ) {
				if ( WinUart::ComIsAvailable(i) ) {
					ComPort = i;
					nrComm1->ComPortNo = i;
					nrComm1->Active = true;
					AnsiString ComName = "Com" + AnsiString(ComPort);
					DataSourceName = ComName;
				}
			}
		}

		ANPRO10_SendReqSysInfo(WinUartPtr, CurrentDeviceAddress,
							   CurrentDeviceId);
		AlarmTimer->Enabled = true;

		ANPRO10_SendSysInfo(WinUartPtr, CurrentDeviceAddress,
							CurrentDeviceId);
*/
}
//---------------------------------------------------------------------------
void __fastcall ANPR10ReceiveThread::Execute()
{
	NameThreadForDebugging(System::String(L"ANPR10ReceiveThread"));
	//---- Place thread code here ----
	U8  *RxBuf = new U8[2*MAX_ANPRO10_SIZE+P_START_SIZE+sizeof(ANPRO10_PacketTail)+P_COMMAND_SIZE];
    Sleep(10000);
	ANPRO10_Receive(MainForm->WinUartPtr, 10000, RxBuf, Terminated);
	delete RxBuf;
}
//---------------------------------------------------------------------------
void __fastcall ANPR10ReceiveThread::ANPRO10Receive(void){
	//ANPRO10_Receive(myWinUartPtr, &MyRxBuf[4]);
}

