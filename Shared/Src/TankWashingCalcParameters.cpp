//---------------------------------------------------------------------------

#pragma hdrstop

#include "TankWashingCalcParameters.h"
#include <cstdlib>
//---------------------------------------------------------------------------
#ifdef ANWIN
#pragma package(smart_init)
#endif

TankWashingMachineWaterUseParams TankWashingCalcResources::TankWashingMachineParameterArray[] =
{
	{100, 6, 0.5, 0.25},
	{100, 7, 1.8, 0.28},
	{100, 8, 2.9, 0.31},
	{100, 9, 4.0, 0.36},
	{100, 10, 5.0, 0.40},
	{100, 11, 6.3, 0.55},
	{100, 12, 7.4, 0.68},

	{100, 18, 22.33, 1.75},
	{100, 20, 22.67, 2.75},
	{100, 22, 25.67, 3.25},
	{100, 24, 30.67, 3.50},
	{100, 26, 34.33, 4.00},
	{100, 28, 38.00, 4.50},
	{100, 30, 41.33, 5.00},

};
const int TankWashingCalcResources::TankWashingMachineParameterArray_Length = 13;



/// Find struct in array of tank washing machine parameters.
/// Does a binary search of the parameters array, which is fast, ~O(log N)
/// If no match is found then NULL is returned.
///
TankWashingMachineWaterUseParams*
TankWashingCalcResources::FindParameters(int machineTypeId, int nozzleMM)
{
	TankWashingMachineWaterUseParams *returnValue = NULL;

	int minIndex = 0;											// range min index inclusive
	int maxIndex = TankWashingMachineParameterArray_Length;		// range max index exclusive
	for (int i = 0; !returnValue && i <maxIndex; i++){
		TankWashingMachineWaterUseParams *cursor = &TankWashingMachineParameterArray[i];
		if (cursor->machineTypeId == machineTypeId && cursor->nozzleMM == nozzleMM){
			returnValue = cursor;
		}

	}
	return returnValue;
}

