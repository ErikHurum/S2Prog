//---------------------------------------------------------------------------
#ifndef PRODraftH
#define PRODraftH

class PRODraft :
    public PROXRefObject {
private:
    static int DraftFilterDegree;
    bool HasMetriTapeSns;
    static ValueList DraftValueList[];
public:
    float DraftOffset;
    static int NumberOfPRO;
    float Draft;
#ifdef S2TXU
    static OS_TIMER FilterTimer;
#endif
//	PRODraft(void);
    PRODraft(int type);
    void Initiate();
    ~PRODraft(void);

    AnalogInput *DraftSensor;
    vector<AIPressSensor *>LevelPressures;

    float DraftAtMark;
    float DraftAtPP;
    int DraftStatus;

    float DLMark1;
    float DTMark1;
    float DLMark2;
    float DTMark2;
    float DLPerp;
    float DTPerp;

    float DSnsToMid;
    float DSnsToCL;
    float DMarkToMid1;
    float DMarkToCL1;
    float DMarkToMid2;
    float DMarkToCL2;

    float DLRef1;
    float DTRef1;
    float DLRef2;
    float DTRef2;
    float DLFCenter;
    float DTFCenter;
    float DPerpToMid;
    float DPerpToCL;


    TSNTableCenterOfFlotation *MarkTable; // Instead of fixed point
public:


// Routines for the Configuration
    AnsiString MakeConfigString(int ExtraTabs = 0);
    bool LoadConfigString(TSNConfigString &ConfigString);

// Routines for Saving of Settings
    void SaveSettings(TSNConfigString *SettingsString);
    bool RestoreSettings(TSNConfigString *SettingsString);

/*   bool LoadDraftSensor(int DraftType, TSNConfigString &ConfigString);
  int LoadConfigFromFile(TSNConfigString &ConfigString);
 */
    void Calculate(void);
    float TrimListCorrectionRef(void);
    float TrimListCorrectionFC(void);

    int GetCalcVal(float *DraftPP, float *DraftMark = NULL);


// Routines for the librarian
    virtual int GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit);
    virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    virtual int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
    virtual int PutFloatValue(int ValueId, float NewValue);
    static ValueList* GetValueInfoTableStatic(int &Entries, int Index = 0);
    static void SetDraftFilterTimer(int TempFilterDegree);
    static void SetDraftFilter(void);
    int ReceiveData(U8 *data);
    int SendData(U16 cmd = CMD_GENERIC_REALTIME_DATA);
    float GetLDistanceMarkToPP(void);
    AnsiString ZeroSetDraftSensors(bool Local);
    ValueList* GetValueInfoTable(int &Entries, int Index);
};

//---------------------------------------------------------------------------
#endif
