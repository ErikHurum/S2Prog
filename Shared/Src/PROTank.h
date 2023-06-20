//---------------------------------------------------------------------------
#ifndef PROTankH
#define PROTankH

#include "TSNIncludes.h"
#ifdef ANWIN
    #include "TankWashingMachineCollection.h"
#endif
// forward declarations
class TankWashingMachineCollection;

#define LEVEL_HISTORY_ENTRIES   5
#define LEVEL_HISTORY_INTERVAL 30  // Seconds

class PROTank :  public PROXRefObject {
private:
    static ValueList TankValueList[];
    static ValueList RedTankValueList[];
    static ValueList AllTankValueList[];
    static ValueList AllTankValueList2[];
    static ValueList TankAlarmValueList[];
    static ValueList TankCargoValueList[];
    static ValueList TankSensorValueList[];
    bool HasRedundancy;
    bool HasRadarAndPressure;
    int MyIndex;
    float LR_Buffer[LR_BUFSIZE];
    float Prev_Volume;
    float LR_Volume;
    float LR_Weight;
    float LR_Limit;
    int   LR_Cnt;

    bool  LrCalcFlag;
    clock_t LrCalcTime;

    float SMid,SCl;
    float AdjustedDBU;
    float SteelExp;
    bool  UsePrevCalcDns;
    bool HasDVManMsrPntToSns;
    bool HasDVSnsToUTI;

    float FilteredMsrdDns;
    float StartLevelMsrdDns;
    AIWaterIngressSensor *WaterSns;
    vector<AnalogInput *>RadarSensors;
    AIMetriTapeSensor *MetriTapeSns;
    AILNGFloat        *HSH_FloatSns;
    vector<AIPressSensor *>LevelPressures;
    vector<AIPressSensor *>tankPressures;
    int LevelPressureSnsCnt;
    float cDLR;
    float cDTR;
    float cDLFC;
    float cDTFC;
    // For hybrid systems, trim and list correction
    float cRadarDLR;
    float cRadarDTR;

    float LevelOffset;
    float TableOffset;
    bool DBU_IsConfigured;
    int  OutsideCnt;
    bool  NotEmptyTank;
    float NoiseLimitR;
    float VolumeOffset;
    float VolCorrFactor;


    bool CalculateHSH_LNG_Float(void);
    bool CalculateMetriTape(void);
    bool CalculateRadarUllage(void);
    bool CalculateOtherSns(void);
    void FindLevelPressSns(float &PrevMaxDB, float &MaxDB, float &PrevMaxDBSnsPress,  float &MaxDBSnsPress, int &NumberOfSubmergedSensors, int &NumberOfUseableSensors);
    void LoadTDUTankPlanPosition(TSNConfigString &ConfigString);

protected:
    float CompDns;
    virtual float GetNoiseLimitB(void);
    virtual float GetNoiseLimitU(void);

public:
    static vector<PROTank *>SortedTankVector;
    static vector<PROTank *>TankVector;
    static set<PRogramObjectBase *>ObjectSet;
    static float GravityCorrection;
    static int LevelDifferenceFilterDegree;
    static int LevelChangeFilterDegree;
    static bool HasTankWashingMachines;
    vector<PROTankWashingMachine *> TankWashingMachineVector;

    static ValueList ServiceReportTankValueList[];

#ifdef ANWIN
	TankWashingMachineCollection *WashingMachines;
#endif
    float LoadRate;
    float MeasuredDns;
    bool  UseMeasuredDensity;
    bool  HasMeasuredDensity;
    bool  HasLevelSensors;
    int   UseTempFromOtherId;
    int   UsePressFromOtherId;

    struct {
        unsigned xpos;
        unsigned ypos;
        unsigned page;
        bool initialized;
    } TDUTankPlacement;


    PROTank(int LNumber = 0, bool AddToList = true);
    PROTank(int number, int LNumber, bool AddToList = true);
    PROTank(int TType, int number, int LNumber, bool AddToList = true);
    void Initiate(bool AddToList);
    ~PROTank(void);

//  int RefSystem;
    bool GlobalRefSystem;
    bool UseCFTable;


    float DBotUllRefPnt;        // DBU
    float DBotManMsrPnt;        // DB1Ref Distance bottom at manual reference point
                                // to bottom at sensor location
    float DSnsToMid;
    float DSnsToCL;
    float DManMsrPntToMid;
    float DManMsrPntToCL;
    float DFltCntToMid;
    float DFltCntToCL;

    float DLManMsrPntToSns;
    float DTManMsrPntToSns;
    float DVManMsrPntToSns;
    float DVSnsToUTI;
    float DLFltCntToSns;
    float DTFltCntToSns;
    float TableType;
    float Temperature;
    float Pressure;
    float Density;
    float UllageRef,UllageFC,UllageAtSns;
    float Level,LevelFC,Sounding,LevelAtRef;
    float Volume,VolumePercent,Weight,LevelDifference;
    float RemainingTime;
    float RemainingVolume;
    float LCWeight,LCVolume;
    float StartVolPercent;
    time_t LCDataTime;
    float *TempLog[5]; //[MAX_TEMP_SENSORS+1];
    float *VapourLog;
    PROTankPressure *PressurePtr;
    PROTemperature  *TemperaturePtr;
    PROLinePressure *LPressurePtr;
    char HasWater;
    CargoTypeObject         *CargoType;

    AlarmOverfill           *OverfillPtr;
    AlarmHighLevel          *HighLevelPtr;
    AlarmLowLevel           *LowLevelPtr;
    AlarmLoLoLevel          *LoLoLevelPtr;
    AlarmVoidSpace          *VoidSpaceAPtr;
    AlarmLevelDifference    *LevelDiffAPtr;
    AlarmLevelChange        *LevelChangeAPtr;
    AlarmWaterDetect        *AlarmWaterDetectPtr;

    float VoidSpaceLimit;
    float LevelDiffLimit;
    float OverfillLimit;
    float HighLevelLimit;
    float LowLevelLimit;
    float LoLoLevelLimit;
    float HighTempLimit;
    float LowTempLimit;
    float HighTankPressLimit;
    float LowTankPressLimit;
    float LowPressVacLimit;
    float HighPressVacLimit;
    float LowIGP_Limit;
    float HighIGP_Limit;
    float LowVapourReturnLimit;
    float HighVapourReturnLimit;
    float IntHighTankPressLimit1;
    float IntLowTankPressLimit1;
    float IntHighTankPressLimit2;
    float IntLowTankPressLimit2;

    bool  hasLowPressVacLimit;
    bool  hasHighPressVacLimit;
    bool  hasLowIGP_Limit;
    bool  hasHighIGP_Limit;
    bool  hasLowVapourReturnLimit;
    bool  hasHighVapourReturnLimit;
    bool  HasIntHighTankPressLimit1;
    bool  HasIntLowTankPressLimit1;
    bool  HasIntHighTankPressLimit2;
    bool  HasIntLowTankPressLimit2;
    bool  hasLoLoLevelLimit;

    bool OverfillLocked;
    bool HighLevelLocked;
    bool LowLevelLocked;
    bool LowLowLevelLocked;
    bool HighTempLocked;
    bool LowTempLocked;
    bool HighTankPressLocked;
    bool LowTankPressLocked;
    bool HighIGP_Locked;
    bool LowIGP_Locked;

    TSNTable1Degree *LevVolumeTab,
    *UllVolumeTab,
    *VolumeTab,
    *SoundingTab,   // Volume table based on the sounding pipe
    *DensityCorrectionTab;
    TSNTableCenterOfFlotation *CenterOfFlotTab; // Instead of fixed point
    TSNTableLevelCorrection  *TrimCorrectionTable;
    TSNTableLevelCorrection  *ListCorrectionTable;
    TSNTableLevelCorrection  *TempCorrectionTable;

    float FilteredVolPercent;
    float LevelHistory[LEVEL_HISTORY_ENTRIES];

    int  GetTankType(void);
    void SetTankType(int TType);
    void CheckForTPAndTemp(void);

// Routines for the Configuration
    void WriteConfigToFile(TSNConfigString &ConfigString);
    int LoadConfigFromFile(TSNConfigString &ConfigString);
    void SetProList(void);
    static void SetAllProList(void);

// Routines for Saving of Settings
    void SaveSettings(TSNConfigString *SettingsString);
    bool RestoreSettings(TSNConfigString *SettingsString);

    AnsiString ZeroSetTankPressureSensor(bool Local);
    AnsiString ZeroSetLevelSensors(bool Local);

// Routines for the librarian
    bool HasLCData(void);
    virtual int FindPROStatus(AnsiString &MyString);
    virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    virtual int GetBitValue(int ValueId, int Index, bool &MyBit);
    virtual int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
    virtual int PutFloatValue(int ValueId, float NewValue);
    virtual int PutBitValue(int ValueId, int Index, bool NewValue);
    int ReceiveData(U8 *data);
    int SendData(U16 cmd = CMD_GENERIC_REALTIME_DATA);

    virtual ValueList* GetValueInfoTable(int &Entries, int Index = 0);
    virtual ValueList* GetServiceValueInfoTable(int &Entries);
    static ValueList* GetValueInfoTableStatic(int &Entries, int Index = 0, bool Redundancy = false);
    static ValueList* GetServiceValueInfoTableStatic(int &Entries);

    float VolumeAtRefTmp(void);
    float NetVolumeAtRefTmp(void);

    void InputSounding(float Snd);
    void CalculateSounding(void);

    void LR_Calc(float LRTime);
    float CalcRemainingVolume(void);
    void  CalcRemainingTime(void);
    void SetOutsideCountToMax(void);
    virtual bool IsLevelInsideWindow(float NewValue, float OldValue);

    virtual void Calculate(void);
    void SimCalculate(void);
    void GetHorisontalDistances(float *LDist, float *TDist);
    bool GetOnlineValues(float *PtrLevelFC, float *PtrSounding, float *PtrLevelAtRef, float *PtrUllage, float *PtrUllageFC, float *PtrVolume, float *PtrVolumePercent, float *PtrDensity, float *PtrTemperature);
    void GetCargoTypeSettings(int Key);
    int WriteXML(char *StrBuf, bool IncAlarms);
    virtual void SetState(TankState newState);
    int LCWriteXML(char *StrBuf);
    float GetCorrectWeight(void);
    //float ConverToWeightInVac(float Wgt);
    bool HasInstalledLevelPressureSensors(void);
    static AnsiString ZeroSetAllTankPressureSensor(set<PRogramObjectBase *>TankSet, bool Local);
    static AnsiString ZeroSetAllLevelSensors(set<PRogramObjectBase *>TankSet, bool Local);
    void CalcSteelCorrection(void);
    float GetTemperature(void);
    void SetTemperature(float NewTemp);
    float GetPressure(void);
    void SetPressure(float NewPress);
    float GetWeightFromLPG(void);
    float GetWeightFromGas(void);
    static PROTank* FindTankById(int tankId);
    //static void FilterTankWashingMachinesByTank(PROTank* tank, vector<PROTankWashingMachine *> &destination);
    bool IsStaticValue(int ValueKey);
    bool UTIUllageAvailable(void);

    static ANCriticalSection LogSema;
    int GetSensorEEPROM_Status(int ValueKey);

    /*---------------------------------------------------------------------------------------------
      From the loading calculator
    */

    void InputLevelFC(float pLevel);
    void InputUllageFC(float pLevel);
    void InputLevelAtRef(float pLevel);
    void InputLevelAtSensor(float pLevel);
    void InputUllageAtRef(float UllageRef);
    void InputUllageAtSensor(float pUllageAtSns);
    void InputUllageAtFC(float pUllageFC);

    void InputWeight(float Wgt);
    void InputVolume(float Vol);
    void InputVolumePercent(float VolPercent);


};

//---------------------------------------------------------------------------
#endif
