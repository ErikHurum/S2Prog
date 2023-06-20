class LCTankData:public LCLocationData {
private:
    static ValueList SelectLCTankValueList[];
    float Temperature;
    float Density;
    float UllageRef,UllageFC;
    float LevelFC,Sounding,LevelAtRef;
    float Volume,VolumePercent;
    float MeasuredDns;
    float LoadRate;
    float RemainingTime;
    float TFS_Moment;
    float TFreeSurf;

    bool  HasMeasuredDensity;
    bool  DBU_IsConfigured;
    volatile bool  HWFailure;
    CargoTypeObject CargoType;
    TSNTableCenterOfGravity     *CG_Table;
    TSNTableCenterOfGravity     *CG_UllTable;
    TSNTable1Degree             *TFS_Table;
    TSNTable1Degree             *TFS_UllTable;
    TSNTable1Degree             *LevVolumeTab;
    TSNTable1Degree             *UllVolumeTab;
    TSNTable1Degree             *VolumeTab;
    TSNTable1Degree             *SoundingTab;
    TSNTableCenterOfFlotation   *CenterOfFlotTab;
    PROTank                     *OnlineTank;

    float cDLR;
    float cDTR;
    float cDLFC;
    float cDTFC;
    float LevelOffset;
    float TableOffset;



    float LDist;
    float TDist;
    float DBotUllRefPnt;
    float DManMsrPntToMid;
    float DManMsrPntToCL;
    float DFltCntToMid;
    float DFltCntToCL;
    float MaxWeight;
    float MaxDensity;
    bool  HasMaxWeight;
public:
    bool    IsOnline;
    static vector<LCLocationData*>OnlineTable;
    static vector<LCLocationData*>OfflineTable;
    static vector<LCTankData*>LCTankVector;
    LCTankData(int TType);
    ~LCTankData();
    void Initialize(void);
    void SetOnlineTank(PROTank *TankPtr);
    void LoadConditionString(TSNConfigString &ConfigString, int &ErrorLine);
    AnsiString SaveConditionString(int ExtraTabs);
    bool LoadConfigString(TSNConfigString &ConfigString);
    void SetCargoType(void);
    void CalculateMoments(float *LMoment, float *TMoment, float *VMoment,float *TFSMoment);
    void GetOnlineValues(void);
// Routines for the librarian
    int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
    int PutFloatValue( int ValueId, float NewValue);
    void InputLevelFC(float Level);
    void InputUllageFC(float Level);
    void InputLevelAtRef(float Level);
    void InputUllageAtRef(float UllageRef);
    void InputUllageAtFC(float Ullage);

    void InputWeight(float Wgt);
    void InputVolume(float Vol);
    void InputVolumePercent(float VolPercent);
    void GetCargoTypeSettings(int Key);
    float VolumeAtRefTmp(void);
    virtual ValueList *GetValueInfoTable(int &Entries, int Index=0);
    static ValueList *GetValueInfoTableStatic(int &Entries, int Index=0, bool Redundancy=false);
    static float GetFSMoments(int TType);
    TColor GetCargoColor(void);
    bool IsOnlineTank(void);

};

