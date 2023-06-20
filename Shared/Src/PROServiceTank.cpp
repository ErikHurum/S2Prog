#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
vector<PRogramObjectBase*>PROServiceTank::AllObjVector;
vector<PRogramObjectBase*>PROServiceTank::AllHeavyFuelOilVector;
vector<PRogramObjectBase*>PROServiceTank::AllDieselVector;
vector<PRogramObjectBase*>PROServiceTank::AllLubricantsVector;
vector<PRogramObjectBase*>PROServiceTank::AllFreshWaterVector;
vector<PRogramObjectBase*>PROServiceTank::AllMiscVector;
vector<PRogramObjectBase*>PROServiceTank::ObjVector;
vector<PRogramObjectBase*>PROServiceTank::HeavyFuelOilVector;
vector<PRogramObjectBase*>PROServiceTank::DieselVector;
vector<PRogramObjectBase*>PROServiceTank::LubricantsVector;
vector<PRogramObjectBase*>PROServiceTank::FreshWaterVector;
vector<PRogramObjectBase*>PROServiceTank::MiscVector;

set<PRogramObjectBase*>PROServiceTank::ObjectSet;
bool PROServiceTank::Redundancy = false;


PROServiceTank::PROServiceTank(int TType,int number, int LNumber):PROTank(TType,number, LNumber)
{
	ObjectSet.insert(this);
	AllObjVector.push_back(this);
	switch ( TType ) {
	case C_PRO_HFO:
		AllHeavyFuelOilVector.push_back(this);
		break;
	case C_PRO_DO:
		AllDieselVector.push_back(this);
		break;
	case C_PRO_LUB:
		AllLubricantsVector.push_back(this);
		break;
	case C_PRO_FW:
		AllFreshWaterVector.push_back(this);
		break;
	case C_PRO_MISC:
		AllMiscVector.push_back(this);
		break;
	}
}

PROServiceTank::~PROServiceTank(void)
{
	ObjectSet.erase(this);
	EraseFromVector(ObjVector,this);
	EraseFromVector(AllObjVector,this);
	switch ( Type ) {
	case C_PRO_HFO:
		EraseFromVector(HeavyFuelOilVector,this);
		EraseFromVector(AllHeavyFuelOilVector,this);
		break;
	case C_PRO_DO:
		EraseFromVector(DieselVector,this);
		EraseFromVector(AllDieselVector,this);
		break;
	case C_PRO_LUB:
		EraseFromVector(LubricantsVector,this);
		EraseFromVector(AllLubricantsVector,this);
		break;
	case C_PRO_FW:
		EraseFromVector(FreshWaterVector,this);
		EraseFromVector(AllFreshWaterVector,this);
		break;
	case C_PRO_MISC:
		EraseFromVector(MiscVector,this);
		EraseFromVector(AllMiscVector,this);
		break;
	}
}
//---------------------------------------------------------------------------
float PROServiceTank::GetNoiseLimitB(void)
{
	return PROProjectInfo::NoiseLimServiceB;
}
float PROServiceTank::GetNoiseLimitU(void)
{
	return PROProjectInfo::NoiseLimServiceU;
}

ValueList *PROServiceTank::GetValueInfoTableStatic(int &Entries, int Index)
{
    return PROTank::GetValueInfoTableStatic(Entries,Index,PROServiceTank::Redundancy);
}

ValueList *PROServiceTank::GetServiceValueInfoTableStatic(int &Entries) {
    return PROTank::GetServiceValueInfoTableStatic(Entries);
}

void PROServiceTank::SetState(TankState newState) {
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
            { (AlarmBasic *)LevelChangeAPtr , { EnableFalse , EnableFalse   , EnableFalse   , EnableFalse } },
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

