#pragma once
//---------------------------------------------------------------------------
#ifndef PROWaterIngressH
#define PROWaterIngressH

class PROWaterIngress :
public PROXRefObject {
private:
    static ValueList TempValueList[];
public:
	static vector<PRogramObjectBase*>ObjVector;
	static vector<PRogramObjectBase*>AllObjVector;
	static set<PRogramObjectBase*>ObjectSet;
	PROWaterIngress(int number=0,bool AddToList=true);
	void Initiate(bool AddToList);
	~PROWaterIngress(void);
	bool  DisableOverride;
	float SimulatorLevel;
	bool  Override;
	bool  HasProtection;
	bool  MainAlarmValue;
	bool  PreAlarmValue;
	AIWaterIngressSensor  *MainWaterIngrSensor;
	AIWaterIngressSensor  *PreWaterIngrSensor;

    AlarmMainWaterIngress *MainWaterIngressPtr;
	AlarmPreWaterIngress  *PreWaterIngressPtr;
	PROTemperature  	  *TemperaturePtr;


// Routines for the Configuration
	void WriteConfigToFile(TSNConfigString &ConfigString);
	int LoadConfigFromFile(TSNConfigString &ConfigString);

	PROTemperature *AddTemperature(void);

// Routines for Saving of Settings
	void SaveSettings(TSNConfigString *SettingsString);
	bool RestoreSettings(TSNConfigString *SettingsString);

// Routines for the librarian
	int FindPROStatus(AnsiString &MyString);
	virtual int GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit);
	virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	virtual int PutFloatValue( int ValueId, float NewValue);
	static ValueList *GetValueInfoTableStatic(int &Entries, int Index=0);
	void Calculate(void);
	void SimCalculate(void);

	virtual int ReceiveData(U8* data);
	virtual int SendData(U16 cmd=CMD_GENERIC_REALTIME_DATA);

};

//---------------------------------------------------------------------------
#endif
