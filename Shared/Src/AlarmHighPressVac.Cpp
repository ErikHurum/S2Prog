#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmHighPressVac::NumberOfAlarmSettings = 0;
AlarmHighPressVac::AlarmHighPressVac(PRogramObjectBase *PROPtr)  {
	Init(PROPtr);
}

AlarmHighPressVac::AlarmHighPressVac(PRogramObjectBase *PROPtr, float Lim, bool Visible){
	Init(PROPtr);
	IsVisible    	  = Visible;
	Limit        	  = Lim;
}

void AlarmHighPressVac::Init(PRogramObjectBase *PROPtr){
	NumberOfAlarmSettings++;
	IDNumber          = (ID_AL_HIGH_PRESS_VAC << 16) + NumberOfAlarmSettings;
	Type              = ID_AL_HIGH_PRESS_VAC;
	Locked            = true;
	IsExtraAlarm      = true;
    PROPointer        = PROPtr;
    PROTPressPtr      = (PROTankPressure*)PROPtr;
    Limit             = PROTPressPtr->HighPressVacLimit;
	MessageKey        = L_WORD1051;  // HiPressVac
	TPCMessageKey     = L_WORD1053;  // HPVac
    PROTankPressure::hasPressVacAlarms = true;
}
