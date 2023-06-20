//---------------------------------------------------------------------------
#ifndef PROSystemDataH
#define PROSystemDataH



//enum UnitSystems {SISystem,USUnitSystem, UserUnitSystem};
class PROSystemData:
public PRogramObject {
private:
    void InputLatitude(float NewLatitude);
    static ValueList ServiceReportSystemValueList[];
    static ValueList SelectSystemValueList[];
public:
    static PROSystemData *TXUSystemData;
    static volatile bool HasConfigWritePermission;
    PROSystemData(void);
//Global Density variables
    static float BallastDensity;
    static float SeaWaterDensity;
    static float FreshWaterDensity;
    static float HeavyFuelDensity;
    static float DieselDensity;
    static float LubricantsDensity;
    static float SeaWaterTemp;
    static float AmbientTemp;
    static int TimeFromGMT;
    static int DaylightSaving;
    static float Latitude;
    float CargoVolume;
    float BallastVolume;
    float HeavyFuelVolume;
    float DieselOilVolume;
    float LubricantsVolume;
    float FreshWaterVolume;
    float MiscVolume;
    float CargoWeight;
    float BallastWeight;
    float HeavyFuelWeight;
    float DieselOilWeight;
    float LubricantsWeight;
    float FreshWaterWeight;
    float MiscWeight;
    static bool ReceiveWeightVolume;
    static int CurrentUnitSystem;
    static int CurrentLanguage;
    char MyTypeId;
    char MyAddress;
    static int TrimSource;
    static int ListSource;
    static float ManualTrim;
    static float ManualList;
    static float TrimValue;
    static float ListValue;

    static int AlarmOffDelay;
    static int AlarmOnDelay;
    static int LogTime;
    static bool LogToFile;
    static bool LogAlarms;
    static bool LogBallastExchange;
    static bool LogCargo;
    static bool LogService;
    static bool LogTemperature;
    static bool LogTankPressure;
    static bool PrinterOnThisTXU;
    time_t LastTimeModified;
    AnsiString UserPinCode;


// Routines for Saving of Settings
    void SaveSettings(TSNConfigString *SettingsString);
    bool RestoreSettings(TSNConfigString *SettingsString);
    void CalcTotals(vector<PRogramObjectBase*>&ObjectSet, float *Volume, float *Weight);
    void Calculate(void);
    static void  SetTimeZone(int NewZone);
    static int   GetTimeZone(void);
    static void  SetDST(int NewDST);
    static float TrimListCorrection(float LongitudinalDist, float TransverceDist);

    int GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit);
    int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    int GetFloatValue(int ValueId, int Index, float &MyValue);
    int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
    int PutFloatValue( int ValueId, float NewValue);
	int PutBitValue(int ValueId, int Index, bool NewValue);

    virtual ValueList *GetValueInfoTable(int &Entries, int Index=0);
    static ValueList* GetValueInfoTableStatic(int& Entries, int Index = 0);


    int ReceiveData(U8* data);
    int SendData(U16 cmd=CMD_GENERIC_REALTIME_DATA);
    TankState GetOpModeState(int ValueKey=SVT_TANK_STATE_STR);
    void SetOpModeState(TankState newState, int ValueKey=SVT_TANK_STATE_STR,int Index=0);
    int LCWriteXML(char *StrBuf);
#ifdef ANWIN    
	static void LogData(TLiteQuery *LiteQuery);
	static void CleanLogData(TLiteQuery *LiteQuery, int MaxAge);
#endif


};

//---------------------------------------------------------------------------
#endif
