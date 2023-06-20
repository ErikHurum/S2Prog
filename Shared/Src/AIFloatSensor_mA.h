//---------------------------------------------------------------------------
#ifndef AIFloatSensor_mAH
#define AIFloatSensor_mAH

class AIFloatSensor_mA:
    public AnalogInput
{
public:
	vector<float>AmpCal;
	vector<float>AmpPcnt;
    AIFloatSensor_mA(void);
    ~AIFloatSensor_mA(void);

// Routines for the Configuration
  virtual AnsiString MakeConfigString(int ExtraTabs=0);
  virtual bool LoadConfigString(TSNConfigString &ConfigString);

// Routines for the librarian
    virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
    virtual int PutFloatValue( int ValueId, float NewValue);
    float Calculate(void);
    float Get_Percent(float Amp);
    float Get_Level(float Amp);


};

//---------------------------------------------------------------------------
#endif