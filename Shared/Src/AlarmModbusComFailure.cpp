#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AlarmModbusComFailure::~AlarmModbusComFailure(void)
{
}

unsigned AlarmModbusComFailure::NumberOfAlarmSettings=0;

AlarmModbusComFailure::AlarmModbusComFailure(PRogramObjectBase *PROPtr, float Lim):AlarmBasic(PROPtr,Lim)
{
    NumberOfAlarmSettings++;
    IDNumber        = (ID_AL_MODBUS_COM_ERROR << 16)+NumberOfAlarmSettings;
    Type            = ID_AL_MODBUS_COM_ERROR;
    MessageKey      = L_WORD516;    // ComFault
    TPCMessageKey   = L_WORD517;    // IOErr
    IsHWAlarm       = true;
}

void AlarmModbusComFailure::Check(void)
{
    int FailCnt = ((ModbusUnit*)PROPointer)->GetFailCount();
    int Status = AL_STAT_IN_DEADBAND;
    if ( FailCnt < Limit ) {
        Status = AL_STAT_IN_NORMAL;
    } else /*if ( FailCnt >= Limit ) */{
        Status = AL_STAT_IN_ALARM;
    }
    UpdateAlarm(Status);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////

int AlarmModbusComFailure::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
        case SVT_AL_LIMIT:
            Status = E_NOT_ADJUSTABLE;
            break;
        default:
            Status = AlarmBasic::PutValue(ValueId, Index,NewValue,Local,&ValUnitId);
            break;
    }
    if ( Status==E_NO_ERR){
            SetModifiedFlag();
    }
    if (UnitId) {
        *UnitId = ValUnitId;
    }
    return(Status);
}

int  AlarmModbusComFailure::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
        case SVT_AL_LIMIT:
            MyRetValue = (float)Limit;
            DecPnt     = 0;
            Unit       = NO_UNIT;
            break;
        case SVT_AL_VALUE:
			MyRetValue = (float)((ModbusUnit *)PROPointer)->GetFailCount();
            DecPnt     = 0;
            Unit       = NO_UNIT;
            break;
        default:
            Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
            break;
    }
    return(Status);
}


int AlarmModbusComFailure::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    int Status = GETVAL_NO_ERR;
    //switch ( ValueId ) {
    //  default:
    Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
    //      break;
    //}
    return(Status);
}

int AlarmModbusComFailure::PutFloatValue( int ValueId, float NewValue)
{
    int Status= E_NO_ERR;
    //switch ( ValueId ) {
    //   default:
    Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
    //     break;
    //}
    return(Status);
}


