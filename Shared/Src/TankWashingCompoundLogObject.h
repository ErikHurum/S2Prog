//---------------------------------------------------------------------------

#ifndef TankWashingCompoundLogObjectH
#define TankWashingCompoundLogObjectH

#include "TSNIncludes.h"

//---------------------------------------------------------------------------

/// Used for presenting compound log information for multiple machines mounted in the same tank
///
class TankWashingCompoundLogObject
{
public:
	inline TankWashingCompoundLogObject()
	{
	}

	int TankIdNumber;

	int CompoundStatus;
	int WashType;
	int CleaningMediaId;
	AnsiString BatchGUID;
	double EarliestStartDateTime;
	double LatestEndDateTime;
	int SystemCargoId;
	AnsiString CargoDisplayName;
	double WaterConsumption;
	double EnergyConsumption;
    double FuelConsumption;
    double Flow;
    AnsiString RunTime;
};


#endif
