#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
vector<PRogramObjectBase*>PROVoidSpace::AllObjVector;
vector<PRogramObjectBase*>PROVoidSpace::ObjVector;
set<PRogramObjectBase*>PROVoidSpace::ObjectSet;
bool PROVoidSpace::Redundancy = false;
const float &PROVoidSpace::NoiseLimitB = PROProjectInfo::NoiseLimVoidSpace;

PROVoidSpace::PROVoidSpace(void)
{
	ObjectSet.insert(this);
	AllObjVector.push_back(this);
	IDNumber = (C_PRO_VOIDSPACE << 16 )+ObjectSet.size();
	TankType = TANKTYPE_VOIDSPACE;
}

PROVoidSpace::PROVoidSpace(int Number, int LNumber):PROTank(C_PRO_VOIDSPACE,Number, LNumber)
{
	ObjectSet.insert(this);
	AllObjVector.push_back(this);
}

PROVoidSpace::~PROVoidSpace(void)
{
	ObjectSet.erase(this);
	EraseFromVector(ObjVector,this);
	EraseFromVector(AllObjVector,this);
}
//---------------------------------------------------------------------------
bool PROVoidSpace::IsLevelInsideWindow(float NewValue, float OldValue)
{
	return true; // No delay
}


ValueList *PROVoidSpace::GetValueInfoTableStatic(int &Entries, int Index)
{
    return PROTank::GetValueInfoTableStatic(Entries,Index,PROVoidSpace::Redundancy);
}

ValueList *PROVoidSpace::GetServiceValueInfoTableStatic(int &Entries) {
    return PROTank::GetServiceValueInfoTableStatic(Entries);
}


void PROVoidSpace::Calculate(void)
{
	PROTank::Calculate();
}
void PROVoidSpace::SetState(TankState newState) {
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
            { (AlarmBasic *)LoLoLevelPtr    , { EnableTrue  , EnableFalse   , EnableTrue    , EnableFalse } },
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

