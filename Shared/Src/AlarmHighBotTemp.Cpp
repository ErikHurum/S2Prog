#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
unsigned AlarmHighBotTemp::NumberOfAlarmSettings = 0;


AlarmHighBotTemp::AlarmHighBotTemp(PRogramObjectBase *PROPtr):AlarmHighTemp(PROPtr){
    NumberOfAlarmSettings++;
    IDNumber 		    = ( ID_AL_HIGH_BOT_TEMP << 16 ) + NumberOfAlarmSettings;
    Type 			    = ID_AL_HIGH_BOT_TEMP;
    MessageKey          = L_WORD1060;   // HiBotTemp
    TPCMessageKey       = L_WORD1062;   // HBTmp
}


void AlarmHighBotTemp::Check(void) {
    float Val     = PROTmpPtr->BottomTemp;
    bool  HasTemp = PROTmpPtr->BottomTempOK;
    int   Status  = AL_STAT_IN_DEADBAND; 
    if (HasTemp) {
        if (Val < Limit - Deadband) {
            Status = AL_STAT_IN_NORMAL;
        } else if (Val >= Limit) {
            Status = AL_STAT_IN_ALARM;
        }
    } else {
        Status = AL_STAT_IN_NORMAL;
    }
    UpdateAlarm( Status );
}

int  AlarmHighBotTemp::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
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


