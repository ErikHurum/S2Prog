//---------------------------------------------------------------------------
#ifndef PROVOCTrackH
	#define PROVOCTrackH

class PROVOCTrack :
public PROXRefObject {
private:
	static ValueList VOCTrackValueList[];
public:
    enum VOCTrackState {
        VOC_Start, VOC_Stop, VOC_Active, VOC_Venting, VOC_IGSRunning,
    };
	static vector<PRogramObjectBase*>AllObjVector;
	static vector<PRogramObjectBase*>ObjVector;
	static set<PRogramObjectBase*>ObjectSet;
	PROVOCTrack(bool AddToList=true);
	PROVOCTrack(int IdNum,PROXRefObject *CreatedFromTank, bool AddToList=true);
	void Initiate();
	~PROVOCTrack(void);

	bool  IGSRunning;
    float IGSVolume;
	float Temperature;
    float StartPress, StopPress,StartVol, StopVol, StartTemp, StopTemp;
    float TotalVolume;
    float HiPressSetPoint, LoPressSetPoint;
    bool IsOpenVent;
    bool IGSRunning;
    float IGSVolume;
    float IGSStartVolume;
    float IGSFinalVolume;

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
	ValueList *GetValueInfoTable(int &Entries, int Index);
	static ValueList *GetValueInfoTableStatic(int &Entries, int Index=0);
	void Calculate(void);
	void SimCalculate(void);
	void SetState(TankState newState);
	// Routines for object internode communication
	virtual int ReceiveData(U8* data);
	virtual int SendData(U16 CommandNo=CMD_GENERIC_REALTIME_DATA);
};

//---------------------------------------------------------------------------
#endif
