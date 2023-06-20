//---------------------------------------------------------------------------

#pragma hdrstop

#include "TankWashingMachineRun.h"
#include "TankWashingException.h"
#include <ctime>
//---------------------------------------------------------------------------
#ifdef ANWIn
#pragma package(smart_init)
#endif
TankWashingMachineRun::TankWashingMachineRun()
{
	InitializeIdle(0);
}

TankWashingMachineRun::~TankWashingMachineRun()
{
}


void TankWashingMachineRun::InitializeIdle(int twmId, AnsiString GUIIdStr)
{
	Id = 0;
	WashingMachineId    = twmId;
	Status              = twmr_idle;
	WashType            = twmr_type_unknown;
	startDateTime       = 0.0;
	endDateTime         = 0.0;
	CleaningMediaId     = 0;
	BatchGUID           = GUIIdStr;
	SystemCargoId       = 0;
	//CargoDisplayName  = "";
	WaterConsumption    = 0.0;
	EnergyConsumption   = 0.0;
    FuelConsumption     = 0.0;
	Flow				= 0.0;
	RunningTime			= 0;
}



void TankWashingMachineRun::Start()
{
	if (Status == twmr_idle) {
		Status = twmr_running;
		startDateTime = (double)time(NULL);
		endDateTime = 0.0;
	}
	else {
		AnsiString errorMsg("Cannot start washing run with status=");
		//errorMsg.cat_sprintf("%d/\"%s\"", Status, TankWashingMachineRun::StatusToString(Status));
		throw TankWashingException(errorMsg.c_str());
	}
}



void TankWashingMachineRun::Completed(bool force)
{
	if (!force && Status != twmr_running) {
		AnsiString errorMsg("Cannot stop washing run with status=");
		errorMsg.cat_sprintf("%d/\"%s\"", Status, TankWashingMachineRun::StatusToString(Status));
		throw TankWashingException(errorMsg.c_str());
	}
	else
	{
		Status = twmr_completed;
		endDateTime = (double)time(NULL);
	}
}

void TankWashingMachineRun::Aborted(bool force)
{
	if (!force && Status != twmr_running) {
		AnsiString errorMsg("Cannot stop washing run with status=");
		errorMsg.cat_sprintf("%d/\"%s\"", Status, TankWashingMachineRun::StatusToString(Status));
		throw TankWashingException(errorMsg.c_str());
	}
	else
	{
		Status = twmr_aborted;
		endDateTime = (double)time(NULL);
	}
}



void TankWashingMachineRun::Error()
{
	if (Status != twmr_error) {
		Status = twmr_error;
		endDateTime = (double)time(NULL);
	}
}



/// Convert status int to english string.
/// Not internationalized.
AnsiString TankWashingMachineRun::StatusToString(int status)
{
	AnsiString retval;

	switch (status) {
	case twmr_idle:
		retval = "Idle";
		break;
	case twmr_running:
		retval = "Running";
		break;
	case twmr_completed:
		retval = "Completed";
		break;
	case twmr_aborted:
		retval = "Aborted";
		break;
	case twmr_error:
		retval = "Error";
		break;
	default:
		retval = "Unknown";
		break;
	}
	return retval;
}




AnsiString TankWashingMachineRun::WashTypeToString(int washType)
{
	AnsiString retval;

	switch (washType) {
	case twmr_type_unknown:
		retval = "Not Selected";
		break;
	case twmr_type_prewash:
		retval = "Prewash";
		break;
	case twmr_type_wash:
		retval = "Washing";
		break;
	default:
		retval = "Unknown";
		break;
	}
	return retval;
}



double TankWashingMachineRun::GetElapsedTime(double nowTime)
{
	double elapsedTime = 0;

	switch (Status) {
	case twmr_completed:
		elapsedTime = endDateTime - startDateTime;
		break;
	case twmr_running:
		elapsedTime = nowTime - startDateTime;
		break;
	case twmr_error:
		elapsedTime = endDateTime - startDateTime;
		break;
	case twmr_idle:
	default:
		elapsedTime = 0;
		break;
	}

	return elapsedTime;
}