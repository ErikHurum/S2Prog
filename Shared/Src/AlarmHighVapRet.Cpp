#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmHighVapRet::NumberOfAlarmSettings = 0;
AlarmHighVapRet::AlarmHighVapRet(PRogramObjectBase *PROPtr)  {
    Init(PROPtr);
}

AlarmHighVapRet::AlarmHighVapRet(PRogramObjectBase *PROPtr, float Lim, bool Visible) {
    Init(PROPtr);
    IsVisible         = Visible;
    Limit             = Lim;
}

void AlarmHighVapRet::Init(PRogramObjectBase *PROPtr){
    NumberOfAlarmSettings++;
    IDNumber          = (ID_AL_HIGH_VAPOUR_RETURN << 16) + NumberOfAlarmSettings;
    Type              = ID_AL_HIGH_VAPOUR_RETURN;
    Locked            = true;
	IsExtraAlarm      = true;
    PROPointer        = PROPtr;
	PROTPressPtr      = (PROTankPressure*)PROPtr;
    Deadband          = 10.0 / MH2O_TO_MBAR;
	Limit             = PROTPressPtr->HighVapourReturnLimit;
    MessageKey        = L_WORD1055;  // LoVapRet
    TPCMessageKey     = L_WORD1057;  // LVPRet
	PROTankPressure::hasVapRetAlarms = true;
}

