//---------------------------------------------------------------------------
#ifndef PROInclinometerH
	#define PROInclinometerH

class PROInclinometer :
public PRogramObject {
private:
	double HeelLog[ROL_LIST_ENTRIES];
	float MaxListS;
	float MaxListP;
	double MaxBufListS;
	double MaxBufListP;
	float ListRollFilter;
	float AvgRollingPeriod;
	float AvgFrequency;
	int   RollingTimeStart;
    ANCriticalSection *ListSema;

public:
	static PROInclinometer *PROInclinPtr;
#ifdef S2TXU
	static TSN_STACKPTR int TaskStack[2][256];
	static TSN_TASK TaskHandle[2];
#endif
	PROInclinometer(void);
	~PROInclinometer(void);

	AIInclinometer *Inc1Sensor;
	AIInclinometer *Inc2Sensor;

	AIInclinometer *TrimSensor;
	AIInclinometer *ListSensor;

	int MountedOn;
	static float TrimValue;
	static float ListValue;
	static bool  HasTrimValue;
	static bool  HasListValue;
    bool FrequencyCalc;


// Routines for the Configuration
	void WriteConfigToFile(TSNConfigString &ConfigString);
	int LoadConfigFromFile(TSNConfigString &ConfigString);
// Routines for Saving of Settings
	void SaveSettings(TSNConfigString *SettingsString);
	bool RestoreSettings(TSNConfigString *SettingsString);

// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit);
    int GetFloatValue(int ValueId, int Index, float &MyValue);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
	static ValueList *GetValueInfoTableStatic(int &Entries, int Index=0);
	void Calculate(void);
	int ReceiveData(U8* data);
	int SendData(U16 cmd=CMD_GENERIC_REALTIME_DATA);
#ifdef S2TXU
	void LogList(void);
	static void LogListTask(void);

	void RecIncData(void);
	static void RecIncDataTask(void);
#endif

};

//---------------------------------------------------------------------------
#endif
