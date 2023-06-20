//---------------------------------------------------------------------------
#ifndef ILevelSensorAirPurgeH
#define AIModbusDiffPressSensor_mAH

class AIModbusDiffPressSensor_mA:
    public AIDiffPressSensor_mA
{
public:
    AIModbusDiffPressSensor_mA(bool IsAtmRef=false);
    ~AIModbusDiffPressSensor_mA(void);
// Routines for the librarian
    int PutFloatValue( int ValueId, float NewValue);
};

//---------------------------------------------------------------------------
#endif
