#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AlarmTXUComFailure::~AlarmTXUComFailure(void)
{
}

unsigned AlarmTXUComFailure::NumberOfAlarmSettings=0;

AlarmTXUComFailure::AlarmTXUComFailure(PRogramObjectBase *PROPtr, float Lim):AlarmBasic(PROPtr)
{
    NumberOfAlarmSettings++;
    PROPointer      = PROPtr;
    Name            = PROPointer->Name;
    IDNumber        = (ID_AL_TDU_COM_ERROR << 16)+NumberOfAlarmSettings;
    Type            = ID_AL_TDU_COM_ERROR;
    Limit           = Lim;
    MessageKey      = L_WORD516;    // ComFault
    TPCMessageKey   = L_WORD771;    // TDUce
    IsHWAlarm       = true;
}

void AlarmTXUComFailure::Check(void)
{
    int FailCnt = ((PROTanksystemUnit *)PROPointer)->SysInfoRxFailCnt;
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

int AlarmTXUComFailure::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
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

int  AlarmTXUComFailure::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
        case SVT_AL_LIMIT:
            MyRetValue = (float)Limit;
            DecPnt     = 0;
            Unit       = NO_UNIT;
            break;
    case SVT_AL_VALUE:
            MyRetValue = (float)((PROTanksystemUnit *)PROPointer)->SysInfoRxFailCnt;
            DecPnt     = 0;
            Unit       = NO_UNIT;
            break;
        default:
            Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
            break;
    }
    return(Status);
}


int AlarmTXUComFailure::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    int Status = GETVAL_NO_ERR;
    //switch ( ValueId ) {
    //  default:
    Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
    //      break;
    //}
    return(Status);
}

int AlarmTXUComFailure::PutFloatValue( int ValueId, float NewValue)
{
    int Status= E_NO_ERR;
    //switch ( ValueId ) {
    //   default:
    Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
    //     break;
    //}
    return(Status);
}

