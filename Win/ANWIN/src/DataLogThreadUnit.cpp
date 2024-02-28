//---------------------------------------------------------------------------

#include "DataLogThreadUnit.h"
#include <System.hpp>
#include "ANWinInc.h"
#pragma hdrstop
#include "ChildUnit.h"
#include "Anpro_Net.h"
//#include "MainUnit.h"


#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall DataLogThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall DataLogThread::DataLogThread(bool CreateSuspended,int pDelay)
	: TThread(CreateSuspended),Delay(pDelay)
{
    Priority 		= tpLower;
}
//---------------------------------------------------------------------------
void __fastcall DataLogThread::Execute()
{
	NameThreadForDebugging(System::String(L"DataLogThread"));
	//---- Place thread code here ----
	try {
		unsigned NumberOfTanks = PROCargoTank::ObjVector.size();
		if (  NumberOfTanks ){
			int NextCleanTime = time(NULL) + NEXT_CLEAN_TIME; // Clean once every day
			while (!Terminated) {
				const unsigned rDelay         = Delay / NumberOfTanks;
				PROCargoTank::LogData(TChildForm::LiteQueryDataLog, Terminated,rDelay);
				PROSystemData::LogData(TChildForm::LiteQueryDataLog);
				int timeNow = time(NULL);
				if (NextCleanTime <= timeNow) {
					NextCleanTime = timeNow + NEXT_CLEAN_TIME;
					PROSystemData::CleanLogData(TChildForm::LiteQueryDataLog,TChildForm::DataLogDays);
					PROCargoTank::CleanLogDataFromTank(TChildForm::LiteQueryDataLog,TChildForm::DataLogDays);
				}
			}
		}
	}
	catch (...) {
	}

}
//---------------------------------------------------------------------------
void __fastcall DataLogThread::SetDelay(int pDelay)
{
	if ( pDelay < 10) {
		pDelay = 10;
	}
	Delay = pDelay;
}

