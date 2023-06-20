//---------------------------------------------------------------------------

#include <vcl.h>
#include <queue>
#include "TXUFlashProgMain.h"
#include "TSNVersion.h"
#include <stdlib.h>
#pragma hdrstop

#include "CommunicationThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall CommunicationThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall CommunicationThread::CommunicationThread(bool CreateSuspended,TTXUFlashProg *MyOwner)
	: TThread(CreateSuspended)
{
	MyForm 	  = MyOwner;
	FreeOnTerminate = false;
  	Priority        = tpHigher;
}
//---------------------------------------------------------------------------
void CommunicationThread::SetName()
{
	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = "ANPRO10 Receive";
	info.dwThreadID = -1;
	info.dwFlags = 0;

	__try
	{
		RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD),(DWORD*)&info );
	}
	__except (EXCEPTION_CONTINUE_EXECUTION)
	{
	}
}
//---------------------------------------------------------------------------
void __fastcall CommunicationThread::Execute()
{
	SetName();
		//---- Place thread code here ----
	U8 *RxBuf = new U8[3*MAX_ANPRO10_SIZE+P_START_SIZE+sizeof(ANPRO10_PacketTail)+P_COMMAND_SIZE];
	while (!Terminated ){
		try{
			ANPRO10_Receive(MyForm->WinUartPtr,1000,RxBuf);
		}
		catch(...){
			//MyForm->NetReceiveRestartTimer->Enabled = true;
		}

	}
	delete [] RxBuf;
}
//---------------------------------------------------------------------------
