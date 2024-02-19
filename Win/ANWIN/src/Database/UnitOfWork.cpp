//---------------------------------------------------------------------------

#pragma hdrstop
#include "TSNIncludes.h"
#include "UnitOfWork.h"
#include <vector>
#include <cmath>
#include <Vcl.Forms.hpp>

#include "TankWashingException.h"
#include "SystemWarningUnit.h"
#include "ChildUnit.h"
#include "Anpro_Net.h"
#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

USEFORM("SystemWarningUnit.cpp", SystemWarningForm);



UnitOfWork::UnitOfWork()
{
	TWMRun_Repository 			= new TWMRunRepository();
	TWM_Repository 				= new TWMRepository();
	TWCleaningMedia_Repository 	= new TankWashingCleaningMediaRepository();
}



UnitOfWork::~UnitOfWork()
{
	delete TWCleaningMedia_Repository;
	delete TWMRun_Repository;
	delete TWM_Repository;
}




/// Convenience function for getting a tank's human readable name based on its Id.
/// Initially loops over all tanks to find the name, but caches the data for
/// faster consequitive searces.
///
void UnitOfWork::TankIdToTankName(unsigned tankId, AnsiString& dest)
{
	if (tankNameMap.count(tankId) == 1)
	{
		dest = *(tankNameMap[tankId]);
	}
	else
	{
		vector<PROTank*>::iterator iter = PROTank::TankVector.begin();

		while(iter != PROTank::TankVector.end())
		{
			PROTank* ptrTank = *iter;

			tankNameMap[ptrTank->IDNumber] = &(ptrTank->Name);
			++iter;
		}

		dest = *(tankNameMap[tankId]);
	}
}





/// Outputs 'message' together with last error message from the database.
///
void UnitOfWork::OutputWarning(AnsiString message)
{
	AnsiString outputMsg = message;
	string rawErrorMsg;
	//sqliteAccessor->GetErrorMessage(rawErrorMsg);

	outputMsg += ": ";
	outputMsg += rawErrorMsg.c_str();

	TSystemWarningForm *pForm = (TSystemWarningForm*)Application->FindComponent("SystemWarningForm");
	if ( pForm ) {
		pForm->BringToFront();
		pForm->AddFreeTextWarning(message);
	}
	else {
		Application->CreateForm(__classid(TSystemWarningForm), &SystemWarningForm);
		SystemWarningForm->AddFreeTextWarning(message);
	}
}




double UnitOfWork::DateTimeToUnixTimestamp(TDateTime& dt)
{
	// Unix timestamp is seconds since start of 1970
	TDateTime unixEpochDT(1970, 1, 1, 0, 0, 0, 0);

	return (double(dt - unixEpochDT) * UnitOfWork_SecInDay);
}
//---------------------------------------------------------------------------



/// Convert a double representing unix time (seconds since 1/1 1970) to TDateTime
/// @param toLocalTime Set to true to compensate for the current time zone time, otherwise will return UTC time (or whatever timezone the input param unixTimestamp has).
///
TDateTime UnitOfWork::TimestampToDateTime(double unixTimestamp, bool toLocalTime)
{
	TDateTime returnValue;

	if (toLocalTime == false)
	{
		double unixTSDays = (double)unixTimestamp / UnitOfWork_SecInDay;

		TDateTime unixEpochDT(1970, 1, 1, 0, 0, 0, 0);
		returnValue = TDateTime(double(unixEpochDT) + unixTSDays);
	}
	else
	{
		long assumedUTCTime = (long) unixTimestamp;
		tm *localTm = localtime(&assumedUTCTime);

		TDateTime convDT(localTm->tm_year + 1900,
						 localTm->tm_mon + 1,
						 localTm->tm_mday,
						 localTm->tm_hour,
						 localTm->tm_min,
						 localTm->tm_sec,
						 0);
		returnValue = convDT;
	}

	return returnValue;
}



double UnitOfWork::DateFloor(double unixTimestamp)
{

	return floor(unixTimestamp / UnitOfWork_SecInDay) * UnitOfWork_SecInDay;
}


double UnitOfWork::DateCeiling(double unixTimestamp)
{
	return (ceil(unixTimestamp / UnitOfWork_SecInDay) * UnitOfWork_SecInDay) /*+ (UnitOfWork_SecInDay - 1.0)*/;
}

