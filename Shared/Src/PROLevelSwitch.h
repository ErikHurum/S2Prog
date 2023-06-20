#pragma once
//---------------------------------------------------------------------------
#ifndef PROLevelSwitchH
#define PROLevelSwitchH

class PROLevelSwitch :
	public PROXRefObject{
private:
	int Location;
public:
	static vector<PRogramObjectBase*>ObjVector;
	static vector<PRogramObjectBase*>AllObjVector;
	static set<PRogramObjectBase*>ObjectSet;
	static bool Adjustable;

	PROLevelSwitch(void);
	PROLevelSwitch(int number);
	void Initiate();
	~PROLevelSwitch(void);
	bool IsActive;
	bool IsFailure;

	AnalogInput 		*LevelSwitchSensor;
	AlarmLevelSwitch    *LevelSwitchAlPtr;
	int Page,XPos,YPos;
	bool IsWarning;

// Routines for the Configuration
	void WriteConfigToFile(TSNConfigString &ConfigString);
	int LoadConfigFromFile(TSNConfigString &ConfigString);
// Routines for Saving of Settings
	void SaveSettings(TSNConfigString *SettingsString);
	bool RestoreSettings(TSNConfigString *SettingsString);

// Routines for the librarian
	int FindPROStatus(AnsiString &MyString);
	virtual int GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit);
	virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	virtual int PutFloatValue( int ValueId, float NewValue);
	void Calculate(void);
	void SimCalculate(void);

	virtual int ReceiveData(U8* data);
	virtual int SendData(U16 cmd=CMD_GENERIC_REALTIME_DATA);
	void SetState(TankState newState);
	int WriteXML(char *StrBuf, bool IncAlarms);

};

//---------------------------------------------------------------------------
#endif
