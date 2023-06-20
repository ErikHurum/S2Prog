class LCFrameData : public PRogramObjectBase {
private:
    bool IsCopy;
    static ValueList FrameValueList[];
public:
    static int StrengthFirstFrameNum;
    static int StrengthLastFrameNum;

    static bool SfSagSeaLimit;
    static vector<LCFrameData *>Table;
    static vector<LCFrameData *>FrameList;
    static LCFrameData *FwdPP;
    static LCFrameData *AftPP;
    float  Bm;      // Bending moment at frame, TM
    float  Sf;      // Shear force at frame, T
    float  CorrBm;  // Corrected BM at frame, TM
    float  DistToFrame0;      // the distance frame 0
    float  DistToPrevFrame;
    float  BmHrbPrcnt;
    float  BmSeaPrcnt;
    float  SfHrbPrcnt;
    float  SfSeaPrcnt;
    float  Limit[MAX_FRAME_LIMITS];
    bool   HasStrengthCheck;
    TSNTableCrossCurve *CrossCurve;
    TSNTable1Degree *AreaTable;
    LCFrameData(TSNConfigString& ConfigString,
                float BmHogHrbLim, float BmHogSeaLim, float BmSagHrbLim, float BmSagSeaLim,
                float SfHogHrbLim, float SfHogSeaLim, float SfSagHrbLim, float SfSagSeaLim, int& ErrorLine);
    ~LCFrameData();
    int LoadConfigFromFile(TSNConfigString& ConfigString);
// Routines for the librarian
    int GetValue(int ValueId, int Index, float& MyValue,  int& DecPnt, int& Unit);
    int GetStringValue(int ValueId, int Index, AnsiString& MyString);
    int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
    int PutFloatValue(int ValueId, float NewValue);
    static ValueList* GetValueInfoTableStatic(int& Entries, int Index = 0);
    virtual ValueList* GetValueInfoTable(int& Entries, int Index = 0);

    void CalcPercent(void);
    static void FixFrameLimits(void);
    static LCFrameData* FindFrame(AnsiString Name);

    static int FindFrameNum(AnsiString Name);
    static int FindFrameNum(float Position);
    static bool FrameInList(LCFrameData *FPtr);
    static float CrossArea(float DistToFrame0, float Draft);
};
