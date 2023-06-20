//---------------------------------------------------------------------------

#ifndef TWMRunH
#define TWMRunH
#if defined(ANWIN)
#include <System.hpp>
#else
#include "TSNIncludes.h"
#endif
//---------------------------------------------------------------------------

enum TankWashingMachineRun_Statuses { twmr_idle = 0, twmr_completed, twmr_running, twmr_error, twmr_aborted  };

enum TankWashingMachineRun_Type { twmr_type_unknown = 0, twmr_type_prewash, twmr_type_wash };


class TankWashingMachineRun
{
public:
	int Id;
	int WashingMachineId;

	/// Status is the current operational status of the machine, idle, running ..
	int Status;

	/// WashType specifies whether a prewash or washing program is being run on the machine
	int WashType;

	int CleaningMediaId;

	double startDateTime;
	double endDateTime;

	AnsiString BatchGUID;

	int SystemCargoId;
	AnsiString CargoDisplayName;

	double WaterConsumption;
	double EnergyConsumption;
	double FuelConsumption;
    double Flow;
    int    RunningTime;
	AnsiString RunTime;

	TankWashingMachineRun();
	~TankWashingMachineRun();

	void InitializeIdle(int twmId, AnsiString GUIIdStr="");
	void Start();
	void Completed(bool force = false);
	void Aborted(bool force = false);
	void Error();

	static AnsiString StatusToString(int status);
	static AnsiString WashTypeToString(int status);

	double GetElapsedTime(double nowTime=0.0);
};

#endif

