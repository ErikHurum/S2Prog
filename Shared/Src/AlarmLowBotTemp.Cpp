#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

unsigned AlarmLowBotTemp::NumberOfAlarmSettings = 0;
AlarmLowBotTemp::AlarmLowBotTemp(PRogramObjectBase *PROPtr):AlarmLowTemp(PROPtr){
    NumberOfAlarmSettings++;
    IDNumber 		    = ( ID_AL_LOW_BOT_TEMP << 16 ) + NumberOfAlarmSettings;
    Type 			    = ID_AL_LOW_BOT_TEMP;
    MessageKey          = L_WORD1061;   // LoBotTemp
    TPCMessageKey       = L_WORD1063;   // LBTmp
}

void AlarmLowBotTemp::Check(void) {
    float Val     = PROTmpPtr->BottomTemp;
    bool  HasTemp = PROTmpPtr->BottomTempOK;
    int   Status  = AL_STAT_IN_DEADBAND;
    if (HasTemp) {
        if (Val > Limit + Deadband) {
            Status = AL_STAT_IN_NORMAL;
        } else if (Val <= Limit) {
            Status = AL_STAT_IN_ALARM;
        }
    } else {
        Status = AL_STAT_IN_NORMAL;
    }
    UpdateAlarm( Status );
}

int  AlarmLowBotTemp::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_AL_LIMIT:
        MyRetValue = Limit;
        DecPnt     = 1;
        Unit       = TEMP_UNIT;
        if (!Enable) {
            Status     = GETVAL_DISABLED;
        }
        break;
    case SVT_AL_VALUE:
        MyRetValue = ( (PROTemperature *)PROPointer )->BottomTemp;
        DecPnt     = 1;
        Unit       = TEMP_UNIT;
        break;
    default:
        Status = AlarmBasic::GetValue( ValueId, Index, MyRetValue, DecPnt, Unit );
        break;
    }
    return (Status);
}

