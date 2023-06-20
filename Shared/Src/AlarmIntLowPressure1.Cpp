#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
unsigned AlarmIntLowPressure1::NumberOfAlarmSettings=0;

AlarmIntLowPressure1::AlarmIntLowPressure1(PRogramObjectBase *PROPtr, float Lim, bool Visible)
{
	NumberOfAlarmSettings++;
	IDNumber     = (ID_AL_X_LOW_T_PRESS1 << 16)+NumberOfAlarmSettings;
	Type         = ID_AL_X_LOW_T_PRESS1;
	IsExtraAlarm = true;
	IsVisible    = Visible;
    PROPointer   = PROPtr;
    PROTPressPtr = (PROTankPressure*)PROPtr;
	Limit        = Lim;
    Locked       = true;
	if (PROProjectInfo::IsInlandVessel) {
		 MessageKey      = L_WORD775;	// LowPressure1
		 char Buf[BUF_SIZE];
		 sprintf(Buf,"%s %3.0fkPa",FindDictionaryWord(MessageKey).c_str(),Limit*MH2O_TO_KPA);
		 Description = AnsiString(Buf);
	 }else{
		 MessageKey      = L_WORD514;	// LowPressureX1
	 }
	TPCMessageKey       = L_WORD515;	// LPrX1
}

