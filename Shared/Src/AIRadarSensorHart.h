//---------------------------------------------------------------------------
#ifndef AIRadarSensorHartH
#define AIRadarSensorHartH

class AIRadarSensorHart:
    public AIRadarSensor
{
private:
    float HartValue;

public:
    int   HartComErrorCnt;
    AIRadarSensorHart(void);
    ~AIRadarSensorHart(void);


// Routines for the Configuration
  virtual AnsiString MakeConfigString(int ExtraTabs=0);
  virtual bool LoadConfigString(TSNConfigString &ConfigString);
// Routines for the librarian
    int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
    int PutFloatValue( int ValueId, float NewValue);
    float Calculate(void);
	int ReceiveData(U8* data);
	int SendData(U16 cmd=CMD_GENERIC_REALTIME_DATA);
	void SetNewStatus(bool NewStatus);
    void NewValue(float NewValue);
};

//---------------------------------------------------------------------------
#endif
