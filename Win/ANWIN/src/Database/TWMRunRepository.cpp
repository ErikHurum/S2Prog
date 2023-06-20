//---------------------------------------------------------------------------
#include "TSNIncludes.h"
#ifdef ANWIN
	#include "LiteCall.hpp"
    #include "LiteAccess.hpp"
    #pragma hdrstop
    #include "MainUnit.h"
#endif

#pragma hdrstop


#include "TWMRunRepository.h"
#include "SQLiteAccessor.h"
#include "TankWashingException.h"
#include "TankWashingCompoundLogObject.h"
#include <string>
#include <System.SysUtils.hpp>
//---------------------------------------------------------------------------

#pragma package(smart_init)


/// ***************************************************
/// Public functions
/// ***************************************************

TWMRunRepository::TWMRunRepository(void)
{
    LiteQuery = new TLiteQuery(NULL);
	LiteTable = new TLiteTable(NULL);
    //LiteQuery->CheckMode = cmNone;
	try {
		MainForm->WashTrackLiteConnection->Connected = true;
		LiteQuery->Connection = MainForm->WashTrackLiteConnection;
		LiteTable->Connection = MainForm->WashTrackLiteConnection;

		LiteTable->TableName = "WashingRuns";
		LiteTable->Options->QueryRecCount = true;
		LiteTable->ReadOnly = true;
		LiteTable->OrderFields = "Id";
		LiteTable->Active = true;
	}
	__finally{
	}
}

TWMRunRepository::~TWMRunRepository(void) {
	try {
		LiteQuery->Free();
		LiteTable->Free();
	}
	__finally{
	}
}

/// Return true if one or more runs exist for a tank washing machine, false otherwise.
///
bool TWMRunRepository::ExistsByWashingMachineId(int twmId, bool& exists)
{
	AnsiString Query("SELECT Count(*) AS Count FROM WashingRuns WHERE WashingMachineId=");
	Query.cat_sprintf("%d", twmId);
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


/// Return true if a specific run exists, false otherwise.
///
bool TWMRunRepository::ExistsById(int Id, bool& exists)
{
	AnsiString Query("SELECT Count(*) AS Count FROM WashingRuns WHERE Id=");
	Query.cat_sprintf("%d", Id);
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


/// Get a specific run by its Id
///
bool TWMRunRepository::ReadById(int id, TankWashingMachineRun& dest)
{
	AnsiString Query("SELECT Id, WashingMachineId, Status, StartDateTime, EndDateTime, WashType, CleaningMediaId, BatchGUID, SystemCargoId, CargoDisplayName, WaterConsumption, EnergyConsumption, FuelConsumption, Flow, RunningTime FROM WashingRuns WHERE ");
	Query.cat_sprintf("Id=%d", id);

    try {
		LiteQuery->SQL->Text = Query;
		LiteQuery->Open();
		ParseDataRow(LiteQuery, &dest );
	}
	__finally{
	}
	return true;
}


/// Gets the single newest run for a single tank washing machine
///
bool TWMRunRepository::ReadLatestByWashingMachineId(int twmId, TankWashingMachineRun& dest)
{
	AnsiString Query("SELECT Id, WashingMachineId, Status, StartDateTime, EndDateTime, WashType, CleaningMediaId, BatchGUID, SystemCargoId, CargoDisplayName, WaterConsumption, EnergyConsumption, FuelConsumption, Flow, RunningTime FROM WashingRuns ");
	Query.cat_sprintf("WHERE WashingMachineId=%d ORDER BY Id DESC LIMIT 1", twmId);

    try {
		LiteQuery->SQL->Text = Query;
		LiteQuery->Open();
		ParseDataRow(LiteQuery, &dest);
	}
	__finally{
	}
	return true;
}



bool TWMRunRepository::ReadMultipleLatestByListOfWashingMachineIds(vector<int>& twmIDs, TankWashingMachineRunCollection& dest)
{
	AnsiString QueryStr("SELECT Id, WashingMachineId, Status, StartDateTime, EndDateTime, WashType, CleaningMediaId, BatchGUID, SystemCargoId, CargoDisplayName, WaterConsumption, EnergyConsumption, FuelConsumption, Flow, RunningTime ");
	QueryStr += "FROM WashingRuns ";
	QueryStr += "WHERE WashingMachineId IN (";

	std::vector<int>::iterator iter = twmIDs.begin();
	std::vector<int>::iterator endIter = twmIDs.end();

	while (iter != endIter) {
		QueryStr += (*iter);
		++iter;
		if (iter != endIter) {
			QueryStr += ",";
		}
	}
	QueryStr += ") ";
	QueryStr.cat_sprintf("GROUP BY WashingMachineId HAVING MAX(Id) ");
	QueryStr += "ORDER BY WashingMachineId DESC ";

    try {
		LiteQuery->SQL->Text = QueryStr;
		LiteQuery->Open();
		while (!LiteQuery->Eof) {
			TankWashingMachineRun* twmRun = new TankWashingMachineRun();
			ParseDataRow(LiteQuery, twmRun );
			dest.Add(twmRun);
			LiteQuery->Next();
		}
	}
	__finally{
	}
	return true;
}

AnsiString TWMRunRepository::PrepareQueryMultipleLatestByListOfWashingMachineIds(vector<int>& twmIDs)
{
	AnsiString queryStr("SELECT Id, WashingMachineId, Status, StartDateTime, EndDateTime, WashType, CleaningMediaId, BatchGUID, SystemCargoId, CargoDisplayName, WaterConsumption, EnergyConsumption, FuelConsumption, Flow, RunningTime ");
	queryStr += "FROM WashingRuns ";
	queryStr += "WHERE WashingMachineId IN (";

	std::vector<int>::iterator iter = twmIDs.begin();
	std::vector<int>::iterator endIter = twmIDs.end();

	while (iter != endIter) {
		queryStr += (*iter);
		++iter;
		if (iter != endIter) {
			queryStr += ",";
		}
	}
	queryStr += ") ";
	queryStr.cat_sprintf("GROUP BY WashingMachineId HAVING MAX(Id) ");
	queryStr += "ORDER BY WashingMachineId DESC ";

	return queryStr;
}



/// Reads the latest runs for all tank washing machines in the vector (one run per washing machine id)
///
bool TWMRunRepository::ReadMultipleLatestByListOfTWMIds(vector<int>& tankWashingMachineIDs, TankWashingMachineRunCollection& dest)
{
	AnsiString query;
	query += "SELECT Id, WashingMachineId, Status, StartDateTime, EndDateTime, WashType, CleaningMediaId, BatchGUID, SystemCargoId, CargoDisplayName, WaterConsumption, EnergyConsumption, FuelConsumption, Flow, RunningTime ";
	query += "FROM WashingRuns WHERE WashingMachineId IN (";

	std::vector<int>::iterator iter = tankWashingMachineIDs.begin();
	std::vector<int>::iterator endIter = tankWashingMachineIDs.end();

	while (iter != endIter) {
		query += (*iter);

		++iter;
		if (iter != endIter) {
			query += ",";
		}
	}
	query += ") GROUP BY WashingMachineId HAVING MAX(Id) ";
	query += " ORDER BY Id";
    try {
		LiteQuery->SQL->Text = query;
		LiteQuery->Open();
		while (!LiteQuery->Eof) {
			TankWashingMachineRun* twmRun = new TankWashingMachineRun();
			ParseDataRow(LiteQuery, twmRun );
			dest.Add(twmRun);
			LiteQuery->Next();
		}
	}
	__finally{
	}
	return true;
}




/// Reads the latest runs for all tank washing machines in a specified tank
///
bool TWMRunRepository::ReadMultipleLatestByTankId(int tankId, TankWashingMachineRunCollection& dest)
{
	AnsiString query;
	query += "SELECT r.Id, r.WashingMachineId, r.Status, r.StartDateTime, r.EndDateTime, r.WashType, r.CleaningMediaId, r.BatchGUID, r.SystemCargoId, r.CargoDisplayName, r.WaterConsumption, r.EnergyConsumption, r.FuelConsumption, r.Flow, r.RunningTime ";
	query += "FROM WashingRuns r INNER JOIN WashingMachines m ON r.WashingMachineId = m.Id ";
	query.cat_sprintf("WHERE m.TankId = %d ", tankId);
	query += "GROUP BY r.WashingMachineId HAVING MAX(r.Id) ";
	query += "ORDER BY r.Id";
    try {
		LiteQuery->SQL->Text = query;
		LiteQuery->Open();
		while (!LiteQuery->Eof) {
			TankWashingMachineRun* twmRun = new TankWashingMachineRun();
			ParseDataRow(LiteQuery, twmRun );
			dest.Add(twmRun);
			LiteQuery->Next();
		}
	}
	__finally{
	}
	return true;
}




bool TWMRunRepository::ReadMultipleLogObjects(vector<int>& tankIDs, double startDate, double endDate, AnsiString& nullStringReplacement, vector<TankWashingCompoundLogObject*>& dest)
{
	AnsiString Query;
	Query += "SELECT MAX(m.TankId), MAX(r.Status), MAX(r.WashType), MAX(r.CleaningMediaId), MAX(r.BatchGUID), MIN(r.StartDateTime) as startDT, MAX(r.EndDateTime) as endDT, "; 
	Query += "MAX(SystemCargoId), SUM(r.WaterConsumption), SUM(r.EnergyConsumption), SUM(r.FuelConsumption), SUM(r.Flow), MAX(r.RunningTime)";
	Query += "(r.RunningTime/3600) || ':' || strftime('%M:%S',MAX(r.RunningTime)/86400.0) AS RunTime, ";
	Query.cat_sprintf(" IFNULL(MAX(CargoDisplayName), '%s') ", nullStringReplacement.c_str());

	Query += "FROM WashingRuns r INNER JOIN WashingMachines m ON r.WashingMachineId = m.Id ";
	Query += "WHERE m.TankId IN ( ";

	std::vector<int>::iterator iter = tankIDs.begin();
	std::vector<int>::iterator endIter = tankIDs.end();

	while (iter != endIter) {
		Query += (*iter);

		++iter;
		if (iter != endIter) {
			Query += ",";
		}
	}
	Query += ") GROUP BY r.BatchGUID ";
	Query += "HAVING (MAX(r.Status) == 1 OR MAX(r.Status) == 3) ";
	Query.cat_sprintf("AND (MIN(r.StartDateTime) >= %0.0f AND MAX(r.EndDateTime) <= %0.0f) ", startDate, endDate);
	Query += "ORDER BY startDT DESC";

    try {
		LiteQuery->SQL->Text = Query;
		LiteQuery->Open();
		while (!LiteQuery->Eof) {
			TankWashingCompoundLogObject* pLogObj = new TankWashingCompoundLogObject();
			ParseCompoundLogObject(LiteQuery,pLogObj);
			dest.push_back(pLogObj);
			LiteQuery->Next();
		}
	}
	__finally{
	}
	return true;
}



bool TWMRunRepository::ReadLogObject(AnsiString batchId, AnsiString& nullStringReplacement, TankWashingCompoundLogObject& dest)
{
	AnsiString query;
	query += "SELECT MAX(m.TankId) AS TankId, MAX(r.Status) AS Status, MAX(r.WashType) AS WashType, MAX(r.CleaningMediaId) AS CleaningMediaId, MAX(r.BatchGUID) AS BatchGUID, ";
	query += "MIN(r.StartDateTime) as startDT, MAX(r.EndDateTime) as endDT, MAX(SystemCargoId) AS SystemCargoId, ";
	query.cat_sprintf(" IFNULL(CargoDisplayName, '%s') AS CargoDisplayName, ", nullStringReplacement.c_str());
	query += "SUM(r.WaterConsumption) AS WaterConsumption, SUM(r.EnergyConsumption) AS EnergyConsumption, SUM(r.FuelConsumption) AS FuelConsumption, ";
    query += "SUM(r.Flow) AS Flow, ";
	query += "(r.RunningTime/3600) || ':' || strftime('%M:%S',MAX(r.RunningTime)/86400.0) AS RunningTime ";

	query += "FROM WashingRuns r INNER JOIN WashingMachines m ON r.WashingMachineId = m.Id ";
	query.cat_sprintf("WHERE UPPER(r.BatchGUID) LIKE UPPER('%s') ", batchId.c_str());

	try {
		LiteQuery->SQL->Text = query;
		LiteQuery->Open();
		while (!LiteQuery->Eof) {
			ParseCompoundLogObject(LiteQuery,&dest);
			LiteQuery->Next();
		}
	}
	__finally{
	}
	return true;
}




bool TWMRunRepository::Create(TankWashingMachineRun& twmRun)
{
	AnsiString Query("SELECT * FROM WashingRuns, CleaningMediaTypes, WashingMachines");
    try {
		LiteQuery->SQL->Text = Query;
        LiteQuery->Open();
		LiteQuery->Append();

		LiteQuery->FieldByName("WashingMachineId")->AsInteger		= twmRun.WashingMachineId ;
		LiteQuery->FieldByName("Status")->AsInteger					= twmRun.Status           ;
		LiteQuery->FieldByName("startDateTime")->AsInteger			= twmRun.startDateTime    ;
		LiteQuery->FieldByName("endDateTime")->AsInteger			= twmRun.endDateTime      ;
		LiteQuery->FieldByName("WashType")->AsInteger				= twmRun.WashType         ;
		LiteQuery->FieldByName("CleaningMediaId")->AsInteger		= twmRun.CleaningMediaId  ;
		LiteQuery->FieldByName("BatchGUID")->AsAnsiString			= twmRun.BatchGUID        ;
		LiteQuery->FieldByName("SystemCargoId")->AsInteger			= twmRun.SystemCargoId    ;
		LiteQuery->FieldByName("CargoDisplayName")->AsAnsiString	= twmRun.CargoDisplayName ;
		LiteQuery->FieldByName("WaterConsumption")->AsFloat			= twmRun.WaterConsumption ;
		LiteQuery->FieldByName("EnergyConsumption")->AsFloat		= twmRun.EnergyConsumption;
		LiteQuery->FieldByName("FuelConsumption")->AsFloat			= twmRun.FuelConsumption  ;
		LiteQuery->FieldByName("Flow")->AsFloat						= twmRun.Flow             ;
		LiteQuery->FieldByName("RunningTime")->AsInteger			= twmRun.RunningTime      ;

		LiteQuery->Post();
		LiteQuery->Close();
	}
	__finally{
	}
	return true;
}


bool TWMRunRepository::Update(TankWashingMachineRun& twmRun)
{

	if (twmRun.Id <= 0) {
		AnsiString errorMsg = __FUNC__;
		errorMsg += ": TankWashingMachineRun object must have Id member set before an update";
		throw TankWashingException(errorMsg.c_str());
	}

	AnsiString Query("SELECT * FROM WashingRuns ");
	Query.cat_sprintf("WHERE Id = %d ", twmRun.Id);
	try {
		LiteQuery->SQL->Text = Query;
		LiteQuery->Open();
		LiteQuery->Edit();

		LiteQuery->FieldByName("Status")->AsInteger					= twmRun.Status           ;
		LiteQuery->FieldByName("startDateTime")->AsInteger			= twmRun.startDateTime    ;
		LiteQuery->FieldByName("endDateTime")->AsInteger			= twmRun.endDateTime      ;
		LiteQuery->FieldByName("WashType")->AsInteger				= twmRun.WashType         ;
		LiteQuery->FieldByName("CleaningMediaId")->AsInteger		= twmRun.CleaningMediaId  ;
		LiteQuery->FieldByName("BatchGUID")->AsAnsiString			= twmRun.BatchGUID        ;
		LiteQuery->FieldByName("SystemCargoId")->AsInteger			= twmRun.SystemCargoId    ;
		LiteQuery->FieldByName("CargoDisplayName")->AsAnsiString	= twmRun.CargoDisplayName ;
		LiteQuery->FieldByName("WaterConsumption")->AsFloat			= twmRun.WaterConsumption ;
		LiteQuery->FieldByName("EnergyConsumption")->AsFloat		= twmRun.EnergyConsumption;
		LiteQuery->FieldByName("FuelConsumption")->AsFloat			= twmRun.FuelConsumption  ;
		LiteQuery->FieldByName("Flow")->AsFloat						= twmRun.Flow             ;
		LiteQuery->FieldByName("RunningTime")->AsInteger			= twmRun.RunningTime      ;

		LiteQuery->Post();
		LiteQuery->Close();
	}
	__finally{
	}
	return true;
}



bool TWMRunRepository::CreateOrUpdate(TankWashingMachineRun& twmRun)
{
	bool opSuccess = false;

	if (twmRun.Id > 0) {
		bool existsInDb = false;
		opSuccess = ExistsById(twmRun.Id, existsInDb);

		if (opSuccess) {
			if (existsInDb) {

				opSuccess = Update(twmRun);
			}
			else {

				opSuccess = Create(twmRun);
			}
		}
	}
	else
	{
		opSuccess = Create(twmRun);
	}

	return opSuccess;
}


bool TWMRunRepository::Delete(int id)
{
	// Not implemented yet
	return false; 
}



/// ***************************************************
/// Protected functions
/// ***************************************************


/// Parse the current data row and fill in an object
void TWMRunRepository::ParseDataRow(TLiteQuery *LiteQuery, TankWashingMachineRun* twmRun)
{
	twmRun->Id 					= LiteQuery->FieldByName("Id")->AsInteger;
	twmRun->WashingMachineId 	= LiteQuery->FieldByName("WashingMachineId")->AsInteger;
	twmRun->Status 				= LiteQuery->FieldByName("Status")->AsInteger;
	twmRun->startDateTime 		= LiteQuery->FieldByName("startDateTime")->AsInteger;
	twmRun->endDateTime 		= LiteQuery->FieldByName("endDateTime")->AsInteger;
	twmRun->WashType 			= LiteQuery->FieldByName("WashType")->AsInteger;
	twmRun->CleaningMediaId 	= LiteQuery->FieldByName("CleaningMediaId")->AsInteger;
	twmRun->BatchGUID 			= LiteQuery->FieldByName("BatchGUID")->AsAnsiString;
	twmRun->SystemCargoId 		= LiteQuery->FieldByName("SystemCargoId")->AsInteger;
	twmRun->CargoDisplayName 	= LiteQuery->FieldByName("CargoDisplayName")->AsAnsiString;
	twmRun->WaterConsumption 	= LiteQuery->FieldByName("WaterConsumption")->AsFloat;
	twmRun->EnergyConsumption 	= LiteQuery->FieldByName("EnergyConsumption")->AsFloat;
	twmRun->FuelConsumption 	= LiteQuery->FieldByName("FuelConsumption")->AsFloat;
	twmRun->Flow 				= LiteQuery->FieldByName("Flow")->AsFloat;
	twmRun->RunTime 			= LiteQuery->FieldByName("RunningTime")->AsAnsiString;
}


/// Parse a compound log object
void TWMRunRepository::ParseCompoundLogObject(TLiteQuery *LiteQuery, TankWashingCompoundLogObject* pLogObj)
{
	pLogObj->TankIdNumber 			= LiteQuery->FieldByName("TankId")->AsInteger;
	pLogObj->CompoundStatus			= LiteQuery->FieldByName("Status")->AsInteger;
	pLogObj->EarliestStartDateTime	= LiteQuery->FieldByName("startDT")->AsInteger;
	pLogObj->LatestEndDateTime		= LiteQuery->FieldByName("endDT")->AsInteger;
	pLogObj->WashType 				= LiteQuery->FieldByName("WashType")->AsInteger;
	pLogObj->CleaningMediaId 		= LiteQuery->FieldByName("CleaningMediaId")->AsInteger;
	pLogObj->BatchGUID 				= LiteQuery->FieldByName("BatchGUID")->AsAnsiString;
	pLogObj->SystemCargoId 			= LiteQuery->FieldByName("SystemCargoId")->AsInteger;
	pLogObj->CargoDisplayName 		= LiteQuery->FieldByName("CargoDisplayName")->AsAnsiString;
	pLogObj->WaterConsumption 		= LiteQuery->FieldByName("WaterConsumption")->AsFloat;
	pLogObj->EnergyConsumption 		= LiteQuery->FieldByName("EnergyConsumption")->AsFloat;
	pLogObj->FuelConsumption 		= LiteQuery->FieldByName("FuelConsumption")->AsFloat;
	pLogObj->Flow 					= LiteQuery->FieldByName("Flow")->AsFloat;
	pLogObj->RunTime 				= LiteQuery->FieldByName("RunningTime")->AsString;
}

