//---------------------------------------------------------------------------

#ifndef TankWashingCalcParametersH
#define TankWashingCalcParametersH
//---------------------------------------------------------------------------

struct TankWashingMachineWaterUseParams
{
public:
	int machineTypeId;
	int nozzleMM;
	double A_value;
	double K_value;
};



class TankWashingCalcResources
{
protected:
	static TankWashingMachineWaterUseParams TankWashingMachineParameterArray[];
	static const int TankWashingMachineParameterArray_Length;

public:
	TankWashingMachineWaterUseParams* FindParameters(int machineTypeId, int nozzleMM);
};


class TankWashingCalcParams
{
public:
	TankWashingMachineWaterUseParams *waterUseParams;
	double waterPressure_bar;
	int numberOfNozzles;
	double waterTemp1_c;
	double waterTemp2_c;
	double HeatCapacity;	// Energy used for heating 1 m3 water by 1 degree C/K
	double MDO_kWh_per_ton;			// Money cost per kWh of energy spent
};



#endif
