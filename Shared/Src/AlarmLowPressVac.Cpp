#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
unsigned AlarmLowPressVac::NumberOfAlarmSettings = 0;
AlarmLowPressVac::AlarmLowPressVac(PRogramObjectBase *PROPtr){
    Init(PROPtr);
}


AlarmLowPressVac::AlarmLowPressVac(PRogramObjectBase *PROPtr, float Lim, bool Visible) {
    Init(PROPtr);
    IsVisible         = Visible;
    Limit             = Lim;
}

void AlarmLowPressVac::Init(PRogramObjectBase *PROPtr) {
    NumberOfAlarmSettings++;
    IDNumber          = (ID_AL_LOW_PRESS_VAC << 16) + NumberOfAlarmSettings;
    Type              = ID_AL_LOW_PRESS_VAC;
    Locked            = true;
    IsExtraAlarm      = true;
    PROPointer        = PROPtr;
    PROTPressPtr      = (PROTankPressure *)PROPtr;
    Limit             = PROTPressPtr->LowPressVacLimit;
    MessageKey        = L_WORD1052;  // LoPressVac
    TPCMessageKey     = L_WORD1054;  // LPVac
    PROTankPressure::hasPressVacAlarms = true;
}

