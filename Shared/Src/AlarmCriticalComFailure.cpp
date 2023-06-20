#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
// ANPRO10
AlarmCriticalComFailure *AlarmCriticalComFailure::CriticalComAlarm=NULL;

bool AlarmCriticalComFailure::ComFailure = false;

AlarmCriticalComFailure::~AlarmCriticalComFailure(void)
{
}

unsigned AlarmCriticalComFailure::NumberOfAlarmSettings=0;

AlarmCriticalComFailure::AlarmCriticalComFailure(AnsiString Nam, float Lim):AlarmBasic(NULL)
{
    CriticalComAlarm = this;
    NumberOfAlarmSettings++;
    IDNumber   = (ID_AL_CRITICAL_COM_ERR << 16)+NumberOfAlarmSettings;
    Type       = ID_AL_CRITICAL_COM_ERR;
    Name       = Nam;
    Limit      = Lim;
    LastSyncTime = clock();
    MessageKey   = L_WORD501; //ComFault

}

void AlarmCriticalComFailure::AddAlarm(void)
{
    // Should use a semaphore??
    AlarmNo    = ++AlarmBasic::CurrentAlarmNo;
    State      = AlActive;
    Time_Rised = time(NULL);
    AlarmSilence = false;   // For Buzzer, Flash, Siren, ....
    PROActiveAlarmList.insertInOrder(this);
    //RBMARK program error log
}
void AlarmCriticalComFailure::RemoveAlarm(void)
{
    State            = AlIdle;
    Time_Disappeared = time(NULL);
    PROAcknowAlarmList.removeNode(this);
    //RBMARK program error log
}

void AlarmCriticalComFailure::Check(void)
{

    float ElapsedTime = float(TSNElapsedTicks(LastSyncTime));
    if ( ElapsedTime >= Limit ) {
        OutsideLimit = true;
    } else {
        OutsideLimit = false;
    }
    switch ( State ) {
    case AlActive       :
        ComFailure = true;
        // Only user action
        break;
    case AlAknowledged  :
        if ( ElapsedTime < Limit ) {
            RemoveAlarm();
        }
        ComFailure = true;
        break;
    case AlIdle         :
        if ( OutsideLimit ) {
            GiveRelayDutyMessage(0,RELAY_MSG_ON,0,0);
            AlarmSilence = false;
            AlarmBasic::SetAllToIdle();
            AddAlarm();
            ComFailure = true;
        } else {
            ComFailure = false;
        }
        break;
    }
}



void AlarmCriticalComFailure::SyncReceived(void)
{
    LastSyncTime = clock();
}


///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


AnsiString AlarmCriticalComFailure::Get_CompleteMessage(void)
{
    return(Name + " " + Get_Message());
}

AnsiString AlarmCriticalComFailure::Get_Location(void)
{
    return(Name);
}


int AlarmCriticalComFailure::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
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
    if ( Status==E_NO_ERR ) {
        SetModifiedFlag();
    }
    if ( UnitId ) {
        *UnitId = ValUnitId;
    }
    return(Status);
}

int  AlarmCriticalComFailure::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AL_LIMIT:
        MyRetValue = (float)Limit;
        DecPnt     = 1;
        Unit       = NO_UNIT;
        break;
    case SVT_AL_VALUE:
        // This does not work
        MyRetValue = TSNElapsedTicks(LastSyncTime)/MSEC_TO_SEC;
        DecPnt     = 1;
        Unit       = NO_UNIT;
        break;
    default:
        Status = AlarmBasic::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return(Status);
}


int AlarmCriticalComFailure::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    int Status = GETVAL_NO_ERR;
    //switch ( ValueId ) {
    //  default:
    Status = AlarmBasic::GetStringValue(ValueId,Index, MyString);
    //      break;
    //}
    return(Status);
}

int AlarmCriticalComFailure::PutFloatValue( int ValueId, float NewValue)
{
    int Status= E_NO_ERR;
    //switch ( ValueId ) {
    //   default:
    Status = AlarmBasic::PutFloatValue(ValueId, NewValue);
    //     break;
    //}
    return(Status);
}



int AlarmCriticalComFailure::ReceiveData(U8* data)
{
    return E_OK;
}

// This function is typically called from AddAlarm, RemoveAlarm and MoveAlarmToAcknovledge (on Master)
// every time alarmstate changes. In addition it is also called from cyclic alarmupdate routine.
int AlarmCriticalComFailure::SendData(U16 cmd)
{
    return(E_OK);
}


