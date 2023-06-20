//---------------------------------------------------------------------------
#include "TSNIncludes.h"
#ifdef ANWIN
	#include "LiteCall.hpp"
    #include "LiteAccess.hpp"
    #pragma hdrstop
    #include "MainUnit.h"
#endif

#pragma hdrstop

#include "TWMRepository.h"
#include "TankWashingException.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


/// ***************************************************
/// Public functions
/// ***************************************************

TWMRepository::TWMRepository(void)
{
    LiteQuery = new TLiteQuery(NULL);
	LiteTable = new TLiteTable(NULL);
	try {
		MainForm->WashTrackLiteConnection->Connected = true;
		LiteQuery->Connection = MainForm->WashTrackLiteConnection;
		LiteTable->Connection = MainForm->WashTrackLiteConnection;

		LiteTable->TableName = "WashingMachines";
		LiteTable->Options->QueryRecCount = true;
		LiteTable->ReadOnly = true;
		LiteTable->OrderFields = "Id";
		LiteTable->Active = true;
	}
	__finally{
	}
}
TWMRepository::~TWMRepository(void)
{
	try {
		LiteQuery->Free();
		LiteTable->Free();
	}
	__finally{
	}
}


/// Check if a tank washing machine object exists in the database
/// Returns true if all OK, false otherwise
///
bool TWMRepository::ExistsById(int id, bool& exists)
{
	AnsiString Query("SELECT Count(*) AS Count FROM WashingMachines WHERE Id=");
	Query.cat_sprintf("%d", id);

    try {
        LiteQuery->SQL->Text = Query;
        LiteQuery->Open();
		exists = bool( LiteQuery->FieldByName("Count")->AsInteger);
		LiteQuery->Close();
	}
	__finally{
	}
	return true;

}



/// Check if a cargo tank has washing machines mounted (according to the DB data).
/// Returns true if all OK, false otherwise
///
bool TWMRepository::ExistsByTankId(int tankId, bool& exists)
{
	AnsiString Query("SELECT COUNT(*) AS Count FROM WashingMachines WHERE TankId=");
	Query.cat_sprintf("%d", tankId);

	try {
		LiteQuery->SQL->Text = Query;
		LiteQuery->Open();
		//AnsiString Result = LiteQuery->FieldByName("Count")->AsString;
		exists = bool( LiteQuery->FieldByName("Count")->AsInteger);
		LiteQuery->Close();
	}
	__finally{
	}

	return true;
}


/// Returns true if all OK, false otherwise
///
bool TWMRepository::Create(TankWashingMachine& twm)
{
	AnsiString Query("SELECT * FROM WashingMachines");


    try {
		LiteQuery->SQL->Text = Query;
        LiteQuery->Open();
		LiteQuery->Append();
		LiteQuery->FieldByName("Id")->AsAnsiString							= twm.IDNumber;
		LiteQuery->FieldByName("Identifier")->AsAnsiString					= twm.Identifier;
		LiteQuery->FieldByName("SerialId")->AsAnsiString					= twm.SerialId;
		LiteQuery->FieldByName("NozzleDiameterMM")->AsInteger				= twm.NozzleDiameter_mm;
		LiteQuery->FieldByName("NumberOfNozzles")->AsInteger				= twm.NumberOfNozzles;
		LiteQuery->FieldByName("GearRatio")->AsFloat						= twm.GearRatio;
		LiteQuery->FieldByName("TankId")->AsInteger							= twm.TankId;
		LiteQuery->FieldByName("TankName")->AsAnsiString					= twm.TankName;
		LiteQuery->FieldByName("RunningTimeSinceLastService")->AsFloat 		= twm.RunningTimeSinceLastService;
		LiteQuery->FieldByName("LifeRunningTime")->AsFloat					= twm.LifeRunningTime;
		LiteQuery->FieldByName("MachineTypeId")->AsInteger					= twm.MachineTypeId;
		LiteQuery->Post();
		LiteQuery->Close();
	}
	__finally{
	}
	return true;
}


/// Returns true if all OK, false otherwise
///
bool TWMRepository::ReadById(int id, TankWashingMachine& twm)
{
	if (id < 1) {
		throw TankWashingException("Read error: Tank Washing Machine's Id property cannot be zero or lower");
	}

	AnsiString Query("SELECT * FROM WashingMachines WHERE Id = ");
	Query.cat_sprintf("%d", id);
    try {
        LiteQuery->SQL->Text  = Query;
        LiteQuery->Open();
		ParseOneTankWashingMachine(&twm, LiteQuery);
		LiteQuery->Close();
	}
	__finally{
	}


	return true;
}



/// Returns true if all OK, false otherwise
///
bool TWMRepository::Update(TankWashingMachine& twm)
{
	AnsiString Query("SELECT * FROM WashingMachines ");
	Query.cat_sprintf("WHERE Id = %d", twm.IDNumber);


    try {
		LiteQuery->SQL->Text = Query;
        LiteQuery->Open();
		LiteQuery->Edit();
		LiteQuery->FieldByName("RunningTimeSinceLastService")->AsInteger 	= twm.RunningTimeSinceLastService;
		LiteQuery->FieldByName("LifeRunningTime")->AsInteger				= twm.LifeRunningTime;
		LiteQuery->Post();
		LiteQuery->Close();
	}
	__finally{
	}
	return true;
}


/// Same as update, except it only updates fields which can be specified in the configuration file.
/// Service related timespans etc. are not updated.
///
bool TWMRepository::UpdateFromConfiguration(TankWashingMachine& twm)
{
	AnsiString Query("SELECT * FROM WashingMachines ");
    // Can not update Id      . Must delete database to update Id
	Query.cat_sprintf(" WHERE Id = %d", twm.IDNumber);

    try {
		LiteQuery->SQL->Text = Query;
        LiteQuery->Open();
		LiteQuery->Edit();
		LiteQuery->FieldByName("Identifier")->AsAnsiString					= twm.Identifier;
		LiteQuery->FieldByName("SerialId")->AsAnsiString					= twm.SerialId;
		LiteQuery->FieldByName("NozzleDiameterMM")->AsInteger				= twm.NozzleDiameter_mm;
		LiteQuery->FieldByName("NumberOfNozzles")->AsInteger				= twm.NumberOfNozzles;
		LiteQuery->FieldByName("GearRatio")->AsFloat						= twm.GearRatio;
		LiteQuery->FieldByName("TankId")->AsInteger							= twm.TankId;
		LiteQuery->FieldByName("TankName")->AsAnsiString					= twm.TankName;
		LiteQuery->Post();
		LiteQuery->Close();
	}
	__finally{
	}
	return true;
}





/// Returns true if all OK, false otherwise
///
bool TWMRepository::Delete(int id)
{
	if (id < 1) {
		throw TankWashingException("Delete error: Tank Washing Machine's Id property cannot be zero or lower");
	}

	AnsiString Query;
	Query.cat_sprintf("SELECT *FROM WashingMachines WHERE Id = %d", id);
    try {
		LiteQuery->SQL->Text = Query;
        LiteQuery->Open();
		LiteQuery->Delete();
	}
	__finally{
	}
	return true;
}


/// Returns true if all OK, false otherwise
///
bool TWMRepository::ReadAllTankWashingMachineIDs(std::vector<int>& tankWashingMachineIDs)
{
    try {
		LiteTable->First();
		while (!LiteTable->Eof) {
			AnsiString IdStr = LiteTable->FieldByName("Id")->AsString;
			if (!IdStr.IsEmpty()) {
				int Id = IdStr.ToInt();
				tankWashingMachineIDs.push_back(Id);
			}
			LiteTable->Next();
		}
	}
	__finally{
	}
	return true;
}


/// Get all tank washing machines mounted in a single cargo tank, ordered by their ID number
///
bool TWMRepository::ReadAllTankWashingMachinesInTank(int tankId, TankWashingMachineCollection& dest)
{
	if (tankId < 1) {
		throw TankWashingException("Read error: Tank ID must be set and cannot be zero or lower");
	}

	AnsiString Query("SELECT Id, Identifier, SerialId, NozzleDiameterMM, NumberOfNozzles, GearRatio, TankId, RunningTimeSinceLastService, LifeRunningTime, MachineTypeId ");
	Query += "FROM WashingMachines WHERE TankId = ";
	Query.cat_sprintf("%d", tankId);
	Query.cat_sprintf(" ORDER BY Id");


    try {
		LiteQuery->SQL->Text = Query;
		LiteQuery->Open();
		while (!LiteQuery->Eof) {
			TankWashingMachine* twmPtr = new TankWashingMachine();
			ParseOneTankWashingMachine(twmPtr, LiteQuery);
			dest.Add(twmPtr);
			LiteQuery->Next();
		}
	}
	__finally{
	}
	return true;

}


/// ***************************************************
/// Private functions
/// ***************************************************

/// Used for simply determining if a tank washing machine is in the database
/// or not.
///

/// Get the values for one tank washing machine, given that they are selected in the correct order.
/// The correct order is the same order as the columns are defined in the WashingMachines table in database.
///
void TWMRepository::ParseOneTankWashingMachine(TankWashingMachine* twmPtr, TLiteQuery *LiteQuery)
{
	twmPtr->IDNumber 					= LiteQuery->FieldByName("Id")->AsInteger;
	twmPtr->Identifier 					= LiteQuery->FieldByName("Identifier")->AsAnsiString;
	twmPtr->SerialId 					= LiteQuery->FieldByName("SerialId")->AsAnsiString;
	twmPtr->NozzleDiameter_mm 			= LiteQuery->FieldByName("NozzleDiameterMM")->AsInteger;
	twmPtr->NumberOfNozzles 			= LiteQuery->FieldByName("NumberOfNozzles")->AsInteger;
	twmPtr->GearRatio 					= LiteQuery->FieldByName("GearRatio")->AsFloat;
	twmPtr->TankId 						= LiteQuery->FieldByName("TankId")->AsInteger;
	twmPtr->RunningTimeSinceLastService = LiteQuery->FieldByName("RunningTimeSinceLastService")->AsFloat;
	twmPtr->LifeRunningTime 			= LiteQuery->FieldByName("LifeRunningTime")->AsFloat;
	twmPtr->MachineTypeId 				= LiteQuery->FieldByName("MachineTypeId")->AsInteger;
}
