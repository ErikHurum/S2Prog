#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmHiHiLinePressure::NumberOfAlarmSettings=0;

AlarmHiHiLinePressure::AlarmHiHiLinePressure(PRogramObjectBase *PROPtr)
{
	NumberOfAlarmSettings++;
	IDNumber            = (ID_AL_HIGHHIGH_LINE_PRESS << 16)+NumberOfAlarmSettings;
	Type                = ID_AL_HIGHHIGH_LINE_PRESS;
    PROPointer          = PROPtr;
    PROLPressPtr        = (PROLinePressure*)PROPtr;
	Locked              = true;
	Limit               = PROLPressPtr->HiHiPressLimit;
	MessageKey          = L_WORD1104; // HiHiLinePress
	TPCMessageKey       = L_WORD1105;  // HHLPr
}


