//---------------------------------------------------------------------------

#include <System.hpp>
#include "ANWinInc.h"
#pragma hdrstop
#include "MainUnit.h"

#include "SensorLogUnit.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall SensorLogThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall SensorLogThread::SensorLogThread(bool CreateSuspended, int pDelay)
	: TThread(CreateSuspended),Delay(pDelay)
{
}
//---------------------------------------------------------------------------
void __fastcall SensorLogThread::Execute()
{
	NameThreadForDebugging(System::String(L"SensorLog"));
	//---- Place thread code here ----
	try {
		int NextCleanTime = time(NULL) + NEXT_CLEAN_TIME; // Clean once every day
		unsigned NumberOfSensors = AIPressSensor_mA::ObjectSet.size();
		unsigned rDelay         = Delay / NumberOfSensors;
		while (!Terminated) {
			AIPressSensor_mA::LogData(MainForm->LiteQuerySensorLog, Terminated,rDelay);
			int timeNow = time(NULL);
			if (NextCleanTime <= timeNow) {
				NextCleanTime = timeNow + NEXT_CLEAN_TIME;
				AIPressSensor_mA::CleanLogDataFromSensor(MainForm->LiteQuerySensorLog,MainForm->SensorLogDays);
			}
		}
	}
	catch (...) {
	}
}
//---------------------------------------------------------------------------
void __fastcall SensorLogThread::SetDelay(int pDelay)
{
	Delay = pDelay;
}
//---------------------------------------------------------------------------