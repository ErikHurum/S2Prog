//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ModbusExchangeDataThread.h"
#include "TSNIncludes.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ModbusExchangeDataThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall ModbusExchangeDataThread::ModbusExchangeDataThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	OnTerminate = OnTerminateThread;
}
//---------------------------------------------------------------------------
void __fastcall ModbusExchangeDataThread::Execute()
{
	NameThreadForDebugging(System::String(L"ModbusExchangeDataThread"));
	//---- Place thread code here ----
	TSN_Delay(10000); // For debug
	try {
		while(!Terminated){
			set<ModbusObject*>::iterator pBIt;
			for ( pBIt=ModbusObject::ModbusSet.begin(); pBIt!=ModbusObject::ModbusSet.end(); pBIt++ ) {
				(*pBIt)->Update();
			}

			if (Terminated) {
				break;
			}
			else {
				TSN_Delay(1000);
			}
		}


		//---- Place thread code here ----
	}
	catch (...) {
	}
	return;
}
//---------------------------------------------------------------------------



void __fastcall ModbusExchangeDataThread::OnTerminateThread(TObject* Sender)
{
}
