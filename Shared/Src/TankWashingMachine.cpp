#include "TSNIncludes.h"
//---------------------------------------------------------------------------

#pragma hdrstop
#include <functional>				// used for the compare binary function struct
#include "TankWashingMachine.h"
//---------------------------------------------------------------------------
#ifdef ANWIN
#pragma package(smart_init)
#endif


TankWashingMachine::TankWashingMachine()
{
    IDNumber = 0;
	TankId = 0;
	//Identifier = AnsiString("");
	NozzleDiameter_mm 			= 0;
	RunningTimeSinceLastService = 0.0;
	LifeRunningTime 			= 0.0;
	MachineTypeId 				= 0;
	NumberOfNozzles 			= 1;
	GearRatio                   = 370; // Default to the value for T30 machine with 370 pulses for 1 rotation;


}


/// Copy data from other TankWashingMachine object
///
void TankWashingMachine::CopyData(TankWashingMachine& other)
{
	IDNumber            = other.IDNumber;
	Identifier          = other.Identifier;
	NozzleDiameter_mm   = other.NozzleDiameter_mm;
	GearRatio           = other.GearRatio;
	TankId              = other.TankId;
	TankName			= other.TankName;
	MachineTypeId		= other.MachineTypeId;
	NumberOfNozzles		= other.NumberOfNozzles;
}


/// Update service time counters
///
void TankWashingMachine::ResetAfterService()
{
	RunningTimeSinceLastService = 0.0;
}


/// Append string representation of this object to the "dest" string
///
void TankWashingMachine::ToString(AnsiString& dest)
{
	dest.cat_sprintf("TankWashingMachine ID=%d, Ident=\"%s\", TankId=%d, Nozzle.mm=%d", IDNumber, Identifier.c_str(), TankId, NozzleDiameter_mm);
}
