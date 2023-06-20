#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmIntHighPressure2::NumberOfAlarmSettings=0;
AlarmIntHighPressure2::AlarmIntHighPressure2(PRogramObjectBase *PROPtr, float Lim, bool Visible)
{
	NumberOfAlarmSettings++;
	IDNumber 	        = (ID_AL_X_HIGH_T_PRESS2 << 16)+NumberOfAlarmSettings;
	Type 		        = ID_AL_X_HIGH_T_PRESS2;
	IsExtraAlarm        = true;
	IsVisible           = Visible;
    PROPointer          = PROPtr;
    PROTPressPtr        = (PROTankPressure*)PROPtr;
	Limit               = Lim;
    Locked              = true;
	MessageKey          = L_WORD1018; // X Hi Press2
	TPCMessageKey       = L_WORD1020;	// XHiP2
    PROTankPressure::hasExtraAlarm2 = true;
}
AnsiString AlarmIntHighPressure2::Get_Message(void)
{
	return AlarmBasic::Get_Message();
}


