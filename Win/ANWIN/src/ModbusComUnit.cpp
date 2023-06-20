//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ModbusComUnit.h"
#pragma package(smart_init)
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
}
//---------------------------------------------------------------------------
void __fastcall ModbusComThread::Execute()
{
	NameThreadForDebugging(System::String(L"ModbusComThread"));
	//---- Place thread code here ----
}
//---------------------------------------------------------------------------
