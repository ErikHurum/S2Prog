#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
unsigned AlarmLowVapRet::NumberOfAlarmSettings=0;
AlarmLowVapRet::AlarmLowVapRet(PRogramObjectBase *PROPtr) {
    Init(PROPtr);
}


AlarmLowVapRet::AlarmLowVapRet(PRogramObjectBase *PROPtr, float Lim, bool Visible)
{
    Init(PROPtr);
	IsVisible         = Visible;
	Limit             = Lim;
}

void AlarmLowVapRet::Init(PRogramObjectBase *PROPtr) {
    NumberOfAlarmSettings++;
	IDNumber          = (ID_AL_LOW_VAPOUR_RETURN << 16) + NumberOfAlarmSettings;
    Type              = ID_AL_LOW_VAPOUR_RETURN;
    Locked            = true;
    IsExtraAlarm      = true;
    PROPointer        = PROPtr;
    PROTPressPtr      = (PROTankPressure*)PROPtr;
    Limit             = PROTPressPtr->LowVapourReturnLimit;
    MessageKey        = L_WORD1056;  // LoVapRet
    TPCMessageKey     = L_WORD1058;  // LVPRet
    PROTankPressure::hasVapRetAlarms = true;
}

