#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AIRadarSensor_mA::AIRadarSensor_mA(void) : AIRadarSensor(C_AI_Radar_4_20mA) {

    AlarmmAmpShortCircuit *ShortCircuitPtr  = new AlarmmAmpShortCircuit(this);
    AlarmmAmpOpenLoop     *OpenLoopPtr      = new AlarmmAmpOpenLoop(this,10000); // Was 0
    AlarmSet.insert(ShortCircuitPtr);
    AlarmSet.insert(OpenLoopPtr);
    // Always assume that the radar is mounted on deck
    // or top of the tank

    // Init the other variables
    MaxRange    = 100.0;
    MinRange    = 0.0;
    float Percent[2] = { 0.0, 100.0 };
    float mAmp[2] = { 4.0, 20.0 };
    for (int i = 0; i < 2; i++) {
        mAPcnt.push_back(Percent[i] / 100.0);
        mACal.push_back(mAmp[i] / 1000.0);
    }

    MakeConstants();
}
//---------------------------------------------------------------------------

AIRadarSensor_mA::~AIRadarSensor_mA(void) {
}
//---------------------------------------------------------------------------
U8 AIRadarSensor_mA::GetFilter(void) {
    return (FILTER_MA_RADAR);
}
//---------------------------------------------------------------------------
bool AIRadarSensor_mA::LoadConfigString(TSNConfigString &ConfigString) {
    bool NoError = AIRadarSensor::LoadConfigString(ConfigString);
    MakeConstants();
    return (NoError);
}


///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////
int  AIRadarSensor_mA::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_AI_CAL_DATA_FRO:
        MyRetValue = mAPcnt[Index] * 100.0;
        Unit       = PERCENT_UNIT;
        DecPnt     = 1;
        break;
    case SVT_AI_CAL_DATA_G1 :
        MyRetValue = mACal[Index];
        Unit       = CURRENT_UNIT;
        DecPnt     = 1;
        break;
    case SVT_AI_CAL_DATA_ENTRIES:
        MyRetValue = mAPcnt.size();
        Unit       = NO_UNIT;
        DecPnt     = 0;
        break;
    case SVT_AI_OFFSET   :
    case SVT_AI_CALC_VAL :
    default:
        Status = AIRadarSensor::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return (Status);
}


//////////////////////////////////////////////////////////////////
//
// Sensor calculations
//
//////////////////////////////////////////////////////////////////
void AIRadarSensor_mA::MakeConstants(void) {
    a                       = (MaxRange - MinRange) / (0.02 - 0.004);
    b                       = MaxRange - a * 0.02;
}

float AIRadarSensor_mA::Get_Distance(float Amp) {
    float Temp = a * Amp + b;
    return (Temp);
}


float AIRadarSensor_mA::Calculate(void) {
    if (CanCalculate()) {
        // This value should be checked for alarm
        CalcValue = Gain * Get_Distance(FilteredValue) - Offset;
        ResultOK  = true;

    }
    return (CalcValue);

}

