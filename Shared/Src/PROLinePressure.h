//---------------------------------------------------------------------------
#ifndef PROLinePressureH
	#define PROLinePressureH

class PROLinePressure:
public PROXRefObject {
public:
	static vector<PRogramObjectBase*>ObjVector;
	static vector<PRogramObjectBase*>AllObjVector;
	static set<PRogramObjectBase*>ObjectSet;
	PROLinePressure(int LNumber=0, bool AddToList=true);
	PROLinePressure(int number, int LNumber=0, bool AddToList=true);
	void Initiate();
	~PROLinePressure(void);
	int PROIDNumber;
	bool HasPressure;

	PROXRefObject *PROPtr;
	AIPressSensor *LinePressSensor;
	vector<AIPressSensor*>LinePressures;

	float Pressure;
	AlarmHiHiLinePressure *HiHiPressurePtr;
	AlarmHighLinePressure *HighPressurePtr;
	AlarmLowLinePressure  *LowPressurePtr;
	float HiHiPressLimit;
	float HighPressLimit;
	float LowPressLimit;
    bool HighLinePressLocked;
    bool LowLinePressLocked;

	void SetAlarmLimits(float HHLineLim,float HLineLim,float LowLineLim);
// Routines for the Configuration
	void WriteConfigToFile(TSNConfigString &ConfigString);
	int LoadConfigFromFile(TSNConfigString &ConfigString);
// Routines for Saving of Settings
	void SaveSettings(TSNConfigString *SettingsString);
	bool RestoreSettings(TSNConfigString *SettingsString);
// Adjust sensors
	AnsiString ZeroSetLinePressureSensor(bool Local);

// Routines for the librarian
	virtual int FindPROStatus(AnsiString &MyString);
	virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	virtual int PutFloatValue( int ValueId, float NewValue);
	ValueList *GetValueInfoTable(int &Entries, int Index);
	static ValueList *GetValueInfoTableStatic(int &Entries, int Index=0);
	void Calculate(void);
	void SimCalculate(void);

	virtual int ReceiveData(U8* data);
	virtual int SendData(U16 cmd=CMD_GENERIC_REALTIME_DATA);
	int WriteXML(char *StrBuf, bool IncAlarms);
	static AnsiString ZeroSetAllLinePressureSensors(bool Local);
	float GetHiHiPressLimit(void);

};

//---------------------------------------------------------------------------
#endif
