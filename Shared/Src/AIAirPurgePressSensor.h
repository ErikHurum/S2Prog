//---------------------------------------------------------------------------
#ifndef ILevelSensorAirPurgeH
#define AIAirPurgePressSensorH
class AlarmAirPurgeSensorFailure;

class AIAirPurgePressSensor:
    public AIPressSensor
{
private:
	AlarmAirPurgeSensorFailure *AlAirPurgeSensorFailurePtr;
public:
    AIAirPurgePressSensor(void);
    ~AIAirPurgePressSensor(void);
// Routines for the librarian
    int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
    int PutFloatValue( int ValueId, float NewValue);

    float Calculate(void);
    int ReceiveData(U8* data);
    int SendData(U16 cmd);
};

//---------------------------------------------------------------------------
#endif
