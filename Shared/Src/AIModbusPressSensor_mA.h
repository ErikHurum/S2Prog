//---------------------------------------------------------------------------
#ifndef ILevelSensorAirPurgeH
#define AIModbusPressSensor_mAH

class AIModbusPressSensor_mA:
    public AIPressSensor_mA
{
public:
    AIModbusPressSensor_mA(bool IsAtmRef=false);
    ~AIModbusPressSensor_mA(void);
// Routines for the librarian
    int PutFloatValue( int ValueId, float NewValue);
};

//---------------------------------------------------------------------------
#endif
