//---------------------------------------------------------------------------
#ifndef AiCoilInSensorH
#define AiCoilInSensorH




class AiCoilInSensor:public AnalogInput {
public:
	AiCoilInSensor(int SnsType);
	~AiCoilInSensor(void);


// Routines for the Configuration
  AnsiString MakeConfigString(int ExtraTabs=0);
  bool LoadConfigString(TSNConfigString &ConfigString);

// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);

	void SetNewStatus(bool NewStatus);

	float Calculate(void);

};

//---------------------------------------------------------------------------
#endif
