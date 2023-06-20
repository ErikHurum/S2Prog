//---------------------------------------------------------------------------
#ifndef AiLevelSwitchSensor_mVH
#define AiLevelSwitchSensor_mVH




class AiLevelSwitchSensor_mV:public AnalogInput {
public:
	AiLevelSwitchSensor_mV(int SnsType);
	~AiLevelSwitchSensor_mV(void);
	bool ConvErr;
	bool CalErr;
	ConfigPacket ADConfigData;

// Routines for the Configuration
  AnsiString MakeConfigString(int ExtraTabs=0);
  bool LoadConfigString(TSNConfigString &ConfigString);

// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);

	void SetStatus(U8 *NewStatus);

	float Calculate(void);

};

//---------------------------------------------------------------------------
#endif
