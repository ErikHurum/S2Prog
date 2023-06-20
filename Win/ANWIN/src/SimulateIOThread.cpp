//---------------------------------------------------------------------------

#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop

#include "SimulateIOThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall SimulateIOThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall SimulateIOThread::SimulateIOThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	NameThreadForDebugging(System::String(L"SimulateIOThread"));
}
//---------------------------------------------------------------------------
void __fastcall SimulateIOThread::Execute()
{
	//NameThreadForDebugging("SimulateIO");
	//---- Place thread code here ----
	Sleep(5000);
	while(!Terminated){
		if ( ConfigWarningsString.IsEmpty() ) {
			if ( !Terminated && PROAtmReference::PROAtmRefPtr ) {
				PROAtmReference::PROAtmRefPtr->SimCalculate();
				TSN_Delay(10);
			}
			// Water ingress
			for ( set<PRogramObjectBase*>::iterator pBIt=PROWaterIngress::ObjectSet.begin(); !Terminated && pBIt!=PROWaterIngress::ObjectSet.end(); pBIt++ ) {
				PROWaterIngress *TElement = (PROWaterIngress*)(*pBIt);
				TElement->SimCalculate();
				CheckAlarms(TElement->AlarmSet);
				TSN_Delay(10);
			}

			// Temp
			for ( set<PRogramObjectBase*>::iterator pBIt=PROTemperature::ObjectSet.begin(); !Terminated && pBIt!=PROTemperature::ObjectSet.end(); pBIt++ ) {
				PROTemperature *TElement = (PROTemperature*)(*pBIt);
				TElement->SimCalculate();
				CheckAlarms(TElement->AlarmSet);
				TSN_Delay(10);
			}
			// Tanks
			for ( set<PRogramObjectBase*>::iterator pBIt=PROTank::ObjectSet.begin(); !Terminated && pBIt!=PROTank::ObjectSet.end(); pBIt++ ) {
				PROTank *TElement = (PROTank*)(*pBIt);
				TElement->SimCalculate();
				CheckAlarms(TElement->AlarmSet);
				TSN_Delay(10);
			}
			// TankPress
			for ( set<PRogramObjectBase*>::iterator pBIt=PROTankPressure::ObjectSet.begin(); !Terminated && pBIt!=PROTankPressure::ObjectSet.end(); pBIt++ ) {
				PROTankPressure *TElement = (PROTankPressure*)(*pBIt);
				TElement->SimCalculate();
				CheckAlarms(TElement->AlarmSet);
				TSN_Delay(10);
			}
			for ( set<PRogramObjectBase*>::iterator pBIt=PROLinePressure::ObjectSet.begin(); !Terminated && pBIt!=PROLinePressure::ObjectSet.end(); pBIt++ ) {
				PROLinePressure *TElement = (PROLinePressure*)(*pBIt);
				TElement->SimCalculate();
				CheckAlarms(TElement->AlarmSet);
				TSN_Delay(10);
			}
			for ( set<PRogramObjectBase*>::iterator pBIt=PROLevelSwitch::ObjectSet.begin(); !Terminated && pBIt!=PROLevelSwitch::ObjectSet.end(); pBIt++ ) {
				PROLevelSwitch *TElement = (PROLevelSwitch*)(*pBIt);
				TElement->SimCalculate();
				CheckAlarms(TElement->AlarmSet);
				TSN_Delay(10);
			}

		}
		Sleep(1000);
	}
}
//---------------------------------------------------------------------------
