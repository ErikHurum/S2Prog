#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

IOSimulator *IOSimulator::IOSimulatorPtr = NULL;
IOSimulator::~IOSimulator(void)
{
}

IOSimulator::IOSimulator(void)
{
}

void IOSimulator::ExecSimulator(bool *pTerminate)
{
	if ( ConfigWarningsString.IsEmpty() ) {
		if ( !pTerminate && PROAtmReference::PROAtmRefPtr ) {
			PROAtmReference::PROAtmRefPtr->SimCalculate();
			TSN_Delay(10);
		}
		// Water ingress
		for ( set<PRogramObjectBase*>::iterator pBIt=PROWaterIngress::ObjectSet.begin(); !(*pTerminate) && pBIt!=PROWaterIngress::ObjectSet.end(); pBIt++ ) {
			PROWaterIngress *TElement = (PROWaterIngress*)(*pBIt);
			TElement->SimCalculate();
			CheckAlarms(TElement->AlarmSet);
			TSN_Delay(10);
		}

		// Temp
		for ( set<PRogramObjectBase*>::iterator pBIt=PROTemperature::ObjectSet.begin(); !pTerminate && pBIt!=PROTemperature::ObjectSet.end(); pBIt++ ) {
			PROTemperature *TElement = (PROTemperature*)(*pBIt);
			TElement->SimCalculate();
			CheckAlarms(TElement->AlarmSet);
			TSN_Delay(10);
		}
		// Tanks
		for ( set<PRogramObjectBase*>::iterator pBIt=PROTank::ObjectSet.begin(); !pTerminate && pBIt!=PROTank::ObjectSet.end(); pBIt++ ) {
			PROTank *TElement = (PROTank*)(*pBIt);
			TElement->SimCalculate();
			CheckAlarms(TElement->AlarmSet);
			TSN_Delay(10);
		}
		// TankPress
		for ( set<PRogramObjectBase*>::iterator pBIt=PROTankPressure::ObjectSet.begin(); !pTerminate && pBIt!=PROTankPressure::ObjectSet.end(); pBIt++ ) {
			PROTankPressure *TElement = (PROTankPressure*)(*pBIt);
			TElement->SimCalculate();
			CheckAlarms(TElement->AlarmSet);
			TSN_Delay(10);
		}
		for ( set<PRogramObjectBase*>::iterator pBIt=PROLinePressure::ObjectSet.begin(); !pTerminate && pBIt!=PROLinePressure::ObjectSet.end(); pBIt++ ) {
			PROLinePressure *TElement = (PROLinePressure*)(*pBIt);
            TElement->SimCalculate();
			CheckAlarms(TElement->AlarmSet);
            TSN_Delay(10);
		}
		for ( set<PRogramObjectBase*>::iterator pBIt=PROLevelSwitch::ObjectSet.begin(); !pTerminate && pBIt!=PROLevelSwitch::ObjectSet.end(); pBIt++ ) {
			PROLevelSwitch *TElement = (PROLevelSwitch*)(*pBIt);
            TElement->SimCalculate();
			CheckAlarms(TElement->AlarmSet);
            TSN_Delay(10);
		}

	}
}
