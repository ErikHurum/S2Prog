#ifdef ANWIN
	#include "LiteCall.hpp"
#endif
#include "TSNIncludes.h"
#ifdef ANWIN
	#include "MainUnit.h"
#endif
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

bool PROCargoTank::Redundancy =false;
vector<PRogramObjectBase*>PROCargoTank::AllObjVector;
vector<PRogramObjectBase*>PROCargoTank::ObjVector;
set<PRogramObjectBase*>PROCargoTank::ObjectSet;

PROCargoTank::PROCargoTank(int TType,int number, int LNumber):PROTank(TType,number, LNumber)
{
	ObjectSet.insert(this);
	AllObjVector.push_back(this);
    SetIdNumber(this, number,C_PRO_TANK/*C_PRO_CARGO*/,AllObjVector);
}

PROCargoTank::~PROCargoTank(void)
{
	ObjectSet.erase(this);
	EraseFromVector(ObjVector,this);
	EraseFromVector(AllObjVector,this);
}
//---------------------------------------------------------------------------
float PROCargoTank::GetNoiseLimitB(void)
{
	return PROProjectInfo::NoiseLimCargoB;
}
float PROCargoTank::GetNoiseLimitU(void)
{
	return PROProjectInfo::NoiseLimCargoU;
}

ValueList *PROCargoTank::GetValueInfoTableStatic(int &Entries, int Index)
{
    return PROTank::GetValueInfoTableStatic(Entries,Index,PROCargoTank::Redundancy);
}

ValueList *PROCargoTank::GetServiceValueInfoTableStatic(int &Entries) {
    return PROTank::GetServiceValueInfoTableStatic(Entries);
}


#ifdef ANWIN

void PROCargoTank::PrepareDatabase(TLiteQuery *LiteQuery)
{
	//LogSema.Acquire();

	//TLiteQuery *LiteQuery = new TLiteQuery(NULL);
	try {
		// LiteConnection is either TLiteConnection already set up
		//LiteQuery->Connection = MainForm->DataLogLiteConnection;
		// retrieve data
		LiteQuery->SQL->Text = "SELECT * FROM Tanks";
		LiteQuery->Execute();

		for(unsigned i=0; i < ObjVector.size(); i++){
			((PROCargoTank*)ObjVector[i])->AddTankRecord(LiteQuery);
		}
	}
	__finally{
		//LiteQuery->Free();

	}
	//LogSema.Release();
}
void PROCargoTank::LogData(TLiteQuery *LiteQuery, const volatile bool &Terminated, int Delay)
{
	//LogSema.Acquire();

	//TLiteQuery *LiteQuery1 = new TLiteQuery(NULL);
	try {
		//LiteQuery1->CachedUpdates = true;
		// LiteConnection is either TLiteConnection already set up
		//LiteQuery1->Connection = MainForm->DataLogLiteConnection;

		// retrieve data
		LiteQuery->SQL->Text = "SELECT * FROM DataLog";
		LiteQuery->Execute();


		for(unsigned i=0; !Terminated && i < ObjVector.size(); i++){
			((PROCargoTank*)ObjVector[i])->LogDataFromTank(MainForm->LiteQueryDataLog);
			Sleep(Delay);
		}
	}
	__finally{
		//LiteQuery1->Free();
	}
	//LogSema.Release();

}

void PROCargoTank::AddTankRecord(TLiteQuery *LiteQuery)
{

	//LogSema.Acquire();
	if ( !IsallreadyAdded()){
		try {

			// append record
			LiteQuery->Append();
			LiteQuery->FieldByName("Id")->AsInteger        = IDNumber;
			LiteQuery->FieldByName("Name")->AsString       = Name;
			LiteQuery->Post();
		}
		__finally{

		}
	}
	//LogSema.Release();

}


void PROCargoTank::LogDataFromTank(TLiteQuery *LiteQuery) {

	time_t rawtime = GetGMT();
	try {
		AnsiString MyStatusString;

		// append record
		LiteQuery->Append();


		LiteQuery->FieldByName("TankId")->AsInteger     = IDNumber;
		LiteQuery->FieldByName("LogTimeGMT")->AsInteger = rawtime;
		LiteQuery->FieldByName("DataOK")->AsInteger     = FindPROStatus(MyStatusString) ;
		if ( PressurePtr ){
			LiteQuery->FieldByName("Pressure")->AsFloat     = Pressure*MH2O_TO_MBAR ;       // EHS
		}
		if ( TemperaturePtr ){
			bool hasTemp[3];
			float Temp[3];
			int UnitId, DecimalPnt, Status[3];

			LiteQuery->FieldByName("Temperature")->AsFloat  = Temperature;

			Status[0] = TemperaturePtr->GetValue(SVT_T1, 0, Temp[0],  DecimalPnt, UnitId);
			Status[1] = TemperaturePtr->GetValue(SVT_T2, 0, Temp[1],  DecimalPnt, UnitId);
			Status[2] = TemperaturePtr->GetValue(SVT_T3, 0, Temp[2],  DecimalPnt, UnitId);
			if ( Status[0] == GETVAL_NO_ERR ) LiteQuery->FieldByName("BotTemp")->AsFloat  = Temp[0];
			if ( Status[1] == GETVAL_NO_ERR ) LiteQuery->FieldByName("MidTemp")->AsFloat  = Temp[1];
			if ( Status[2] == GETVAL_NO_ERR ) LiteQuery->FieldByName("UppTemp")->AsFloat  = Temp[2];
		}
		LiteQuery->FieldByName("Ullage")->AsFloat  		= UllageRef;
		LiteQuery->FieldByName("Level")->AsFloat  		= LevelAtRef;
		LiteQuery->FieldByName("Volume")->AsFloat  		= Volume;
		LiteQuery->FieldByName("LoadRate")->AsFloat  	= LoadRate;

		LiteQuery->Post();
	}
	__finally{

	}

}

void PROCargoTank::CleanLogDataFromTank(TLiteQuery *LiteQuery, int MaxAge) {

	try {
		if (MaxAge < 2) {
			MaxAge = 2;
		}
		AnsiString MaxAgeStr = MaxAge;
		LiteQuery->SQL->Text = "DELETE FROM DataLog WHERE LogTimeGMT < strftime('%s', datetime('now', '-"+MaxAgeStr+" day'))";
		LiteQuery->Execute();
		LiteQuery->SQL->Clear();
	}
	__finally{

	}

}


bool PROCargoTank::IsallreadyAdded(void){
	bool AlreadyAdded = true;

	//LogSema.Acquire();
	TLiteQuery *LiteQuery = new TLiteQuery(NULL);
    try {
		LiteQuery->Connection = MainForm->DataLogLiteConnection;
		LiteQuery->SQL->Text = "SELECT * FROM Tanks";
        LiteQuery->Open();
		TField *tmpFiledPtr1 = LiteQuery->FindField("Id");

		LiteQuery->Close();
		if (tmpFiledPtr1 ) {
			AnsiString SQLText = "SELECT * FROM Tanks";
			SQLText += " WHERE Id=" + AnsiString(IDNumber);
			// retrieve data
			LiteQuery->SQL->Text = SQLText;

			LiteQuery->Open();
			// retrieve data
			//	ShowMessage("Records of this alarm= "+IntToStr(LiteQuery->FetchRows));

			AlreadyAdded =  bool(LiteQuery->RecordCount);
		}
	}
	__finally{
		LiteQuery->Free();
	}
	//LogSema.Release();

	return AlreadyAdded;
}

#endif
void PROCargoTank::SetState(TankState newState) {
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
            { (AlarmBasic *)OverfillPtr     , { EnableFalse , EnableTrue    , EnableFalse   , EnableFalse } }, //Note: Overfill also enabled for discharge to detect backflow
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

