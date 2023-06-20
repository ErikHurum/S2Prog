#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
vector<PRogramObjectBase*>PROBallastTank::AllObjVector;
vector<PRogramObjectBase*>PROBallastTank::ObjVector;
set<PRogramObjectBase*>PROBallastTank::ObjectSet;
bool PROBallastTank::Redundancy = false;

PROBallastTank::PROBallastTank(int TType,int number, int LNumber):PROTank(TType, number, LNumber)
{
	AllObjVector.push_back(this);
	ObjectSet.insert(this);
}

PROBallastTank::~PROBallastTank(void)
{
	ObjectSet.erase(this);
	EraseFromVector(ObjVector,this);
	EraseFromVector(AllObjVector,this);
}
//---------------------------------------------------------------------------
float PROBallastTank::GetNoiseLimitB(void)
{
	return PROProjectInfo::NoiseLimBallastB;
}
float PROBallastTank::GetNoiseLimitU(void)
{
	return PROProjectInfo::NoiseLimBallastU;
}

ValueList *PROBallastTank::GetValueInfoTableStatic(int &Entries, int Index)
{
	return PROTank::GetValueInfoTableStatic(Entries,Index,PROBallastTank::Redundancy);
}

ValueList *PROBallastTank::GetServiceValueInfoTableStatic(int &Entries) {
	return PROTank::GetServiceValueInfoTableStatic(Entries);
}

void PROBallastTank::SetState(TankState newState) {
    switch ( newState ) {
    case tSeaGoing :
    case tLoad :
    case tDischarge :
    case tTankCleaning :
    case tUndefined :
        State = newState;
        break;
    default:
        break;
    }
    if ( !ExcludeState && newState != tUndefined ) {
        const AlarmBasic::StateAlarmTable myAlarmSet[] = { 
            //tSeaGoing  , tLoad        , tDischarge    , tTankCleaning, tUndefined
            { (AlarmBasic *)OverfillPtr     , { EnableFalse , EnableTrue    , EnableFalse   , EnableFalse } },
            { (AlarmBasic *)HighLevelPtr    , { EnableFalse , EnableTrue    , EnableFalse   , EnableFalse } },
            { (AlarmBasic *)LowLevelPtr     , { EnableFalse , EnableFalse   , EnableTrue    , EnableFalse } },
            { (AlarmBasic *)LoLoLevelPtr    , { EnableFalse , EnableFalse   , EnableTrue    , EnableFalse } },
            { (AlarmBasic *)LevelChangeAPtr , { EnableTrue  , EnableFalse   , EnableFalse   , EnableFalse } },
        };
        for ( unsigned i = 0; i < NELEMENTS(myAlarmSet); i++ ) {
            AlarmBasic *AlPtr = myAlarmSet[i].AlarmPtr;
            if ( AlPtr && !AlPtr->Locked ) {
                myAlarmSet[i].AlarmPtr->SetEnable(myAlarmSet[i].Enable[State]);
            }
        }
        if ( PressurePtr ) {
            PressurePtr->SetState(newState);
        }
        if ( TemperaturePtr ) {
            TemperaturePtr->SetState(newState);
        }
    }
}

