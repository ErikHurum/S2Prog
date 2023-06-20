#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
unsigned AlarmIntLowPressure2::NumberOfAlarmSettings=0;

AlarmIntLowPressure2::AlarmIntLowPressure2(PRogramObjectBase *PROPtr, float Lim, bool Visible)
{
	NumberOfAlarmSettings++;
	IDNumber            = (ID_AL_X_LOW_T_PRESS2 << 16)+NumberOfAlarmSettings;
	Type                = ID_AL_X_LOW_T_PRESS2;
	IsExtraAlarm        = true;
	IsVisible           = Visible;
    PROPointer          = PROPtr;
    PROTPressPtr        = (PROTankPressure*)PROPtr;
	Limit               = Lim;
    Locked              = true;
    MessageKey          = L_WORD1019;    // X Lo Press2
	TPCMessageKey       = L_WORD1021;	// XLoP2
    PROTankPressure::hasExtraAlarm2 = true;
}

AnsiString AlarmIntLowPressure2::Get_Message(void)
{
	return AlarmBasic::Get_Message();
}

