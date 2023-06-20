#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmIntHighPressure1::NumberOfAlarmSettings = 0;
AlarmIntHighPressure1::AlarmIntHighPressure1(PRogramObjectBase *PROPtr, float Lim, bool Visible) {
    NumberOfAlarmSettings++;
    IDNumber 	    = (ID_AL_X_HIGH_T_PRESS1 << 16) + NumberOfAlarmSettings;
    Type 		    =  ID_AL_X_HIGH_T_PRESS1;
    IsExtraAlarm    = true;
    IsVisible       = Visible;
    Limit           = Lim;
    Locked          = true;
    PROPointer      = PROPtr;
    PROTPressPtr    = (PROTankPressure*)PROPtr;
    if ( PROProjectInfo::IsInlandVessel ) {
        MessageKey      = L_WORD774;    // High
        char Buf[BUF_SIZE];
        sprintf(Buf, "%s %3.0fkPa", FindDictionaryWord(MessageKey).c_str(), Limit * MH2O_TO_KPA);
        Description = AnsiString(Buf);
    } else {
        MessageKey      = L_WORD512;    // X Hi Press1
    }
    TPCMessageKey       = L_WORD513;    // XHiP1
}

float AlarmIntHighPressure1::Get_Limit(void) {
    return (Limit);
}

