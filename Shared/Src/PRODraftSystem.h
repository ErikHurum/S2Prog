//---------------------------------------------------------------------------
#ifndef PRODraftSystemH
	#define PRODraftSystemH
class PRODraftSystem :
public PRogramObject {
public:
	enum DraftSys {
		DftFwdAft,DftFwdMidShipAft,DftFwdAPortAStbd,DftFromOther, DftCorners, DftFwdOnly, DftAftOnly,DftFwdMidShipAftPS, DftNoDef
	};

private:
	int StatusDftFwd;
	int StatusDftAft;
	int StatusDftP;
	int StatusDftS;
	int StatusDftAftP;
	int StatusDftAftS;
	int StatusDftFwdP;
	int StatusDftFwdS;
    int StatusDftMean;
	static ValueList DraftSystemValueList[];


public:
	static set<PRogramObjectBase*>ObjectSet;
	static PRODraftSystem *PRODraftSysPtr;
	static int NumberOfPRO;
	static float MaxSummerDraft;
	static bool Has2ndMark;
	PRODraftSystem(void);
	PRODraftSystem(int IdNum);
	void Initiate();
	~PRODraftSystem(void);
	DraftSys DraftSystem;
	PRODraft *DFPtr;
	PRODraft *DPPtr;
	PRODraft *DSPtr;
	PRODraft *DAPtr;
	PRODraft *DAPPtr;
	PRODraft *DASPtr;
	PRODraft *DFPPtr;
	PRODraft *DFSPtr;
    set<PRogramObjectBase*>DraftList;
	bool GlobalRefSystem;
	bool HasTrimValue;
	bool HasListValue;
	bool HasDeflection;
	float TrimValue;
	float ListValue;
	float DftFwdMark;
	float DftAftMark;
	float DftFwd;
	float DftAft;
	float DftP;
	float DftS;
    float DftAftP    ;
    float DftAftS    ;
    float DftFwdP    ;
    float DftFwdS    ;
    float DftFwdMarkP;
    float DftFwdMarkS;
    float DftAftMarkP;
    float DftAftMarkS;
	float Deflection;
	float MaxDraft;
	float MeanDraft;
	bool DraftIndicationAtPP;

	void WriteConfigToFile(TSNConfigString &ConfigString);
	int LoadConfigFromFile(TSNConfigString &ConfigString);
// Routines for Saving of Settings
	void SaveSettings(TSNConfigString *SettingsString);
	bool RestoreSettings(TSNConfigString *SettingsString);

	void Calculate(void);
// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    int GetFloatValue(int ValueId, int Index, float &MyValue);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
	static ValueList *GetValueInfoTableStatic(int &Entries, int Index=0);

	int ReceiveData(U8* data);
	int SendData(U16 cmd=CMD_GENERIC_REALTIME_DATA);

    virtual ValueList *GetValueInfoTable(int &Entries, int Index=0);
	int LCWriteXML(char *StrBuf);
    int WriteXMLSingle(char *StrBuf, bool IncAlarms, int pValKey, PRODraft *DftPtr);
    int WriteXML(char *StrBuf, bool IncAlarms);
    int GetStatus(int ValueKey);
    TColor GetColor(int ValueKey);
    static TColor GetStatusColor(int Status);

};

//---------------------------------------------------------------------------
#endif
