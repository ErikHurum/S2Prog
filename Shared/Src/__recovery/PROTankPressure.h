//---------------------------------------------------------------------------
#ifndef PROTankPressureH
#define PROTankPressureH

class PROTankPressure :
    public PROXRefObject {
private:
    static ValueList TankPressValueList[];
public:
    static vector<PRogramObjectBase *>AllObjVector;
    static vector<PRogramObjectBase *>ObjVector;
    static set<PRogramObjectBase *>ObjectSet;
    PROTankPressure(bool AddToList = true, int LNumber = 0);
    PROTankPressure(int Idnum, PROXRefObject *CreatedFromTank, bool AddToList = true, int LNumber = 0);
    void Initiate();
    ~PROTankPressure(void);
    bool HasPressure;
    PROXRefObject *CreatedFromThisTank;

    vector<AIPressSensor *>tankPressures;
    float Pressure;
    LimitState  		VapourAlarmSet;
    AlarmHighPressure 	*HighPressurePtr;
    AlarmLowPressure  	*LowPressurePtr;
    AlarmHighPressVac 	*HighPressVacPtr;
    AlarmLowPressVac  	*LowPressVacPtr;
    AlarmHighIGP    	*HighIGPPtr;
    AlarmLowIGP     	*LowIGPPtr;
    AlarmHighVapRet 	*HighVapRetPtr;
    AlarmLowVapRet  	*LowVapRetPtr;


    AlarmIntHighPressure1 *IntHighPressurePtr1;
    AlarmIntHighPressure2 *IntHighPressurePtr2;
    AlarmIntLowPressure1  *IntLowPressurePtr1;
    AlarmIntLowPressure2  *IntLowPressurePtr2;
    bool HighTankPressLocked;
    bool LowTankPressLocked;
    bool HighIGP_Locked;
    bool LowIGP_Locked;

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

    static bool hasIGPAlarms;
    static bool hasPressVacAlarms;
    static bool hasVapRetAlarms;
    static bool hasExtraAlarm2;


    float MaxPressureRange;

    void SetAlarmLimits(float HVapLim, float LowVapLim, float HPVLim, float LPVLim, float HLim, float LLim);
    void AddHighPressInternalAlarm1(float Lim, bool IsVisible);
    void AddLowPressInternalAlarm1(float Lim, bool IsVisible);
    void AddHighPressInternalAlarm2(float Lim, bool IsVisible);
    void AddLowPressInternalAlarm2(float Lim, bool IsVisible);
    void AddHighPressVacAlarm(float Lim, bool IsVisible);
    void AddLowPressVacAlarm(float Lim, bool IsVisible);
    void AddHighIGP_Alarm(float Lim, bool IsVisible);
    void AddLowIGP_Alarm(float Lim, bool IsVisible);
    void AddHighPressVapRetAlarm(float Lim, bool IsVisible);
    void AddLowPressVapRetAlarm(float Lim, bool IsVisible);
// Routines for the Configuration
    void WriteConfigToFile(TSNConfigString &ConfigString);
    int LoadConfigFromFile(TSNConfigString &ConfigString);
// Routines for Saving of Settings
    void SaveSettings(TSNConfigString *SettingsString);
    bool RestoreSettings(TSNConfigString *SettingsString);
// Adjust sensors
    AnsiString ZeroSetTankPressureSensor(bool Local);

// Routines for the librarian
    virtual int FindPROStatus(AnsiString &MyString);
    void SetPressureAlarmMode(LimitState NewMode);
    virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    virtual int GetBitValue(int ValueId, int Index, bool &MyBit);
    virtual int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
    virtual int PutFloatValue(int ValueId, float NewValue);
    virtual int PutBitValue(int ValueId, int Index, bool NewValue);

    virtual ValueList* GetValueInfoTable(int &Entries, int Index = 0);
    static ValueList* GetValueInfoTableStatic(int &Entries, int Index = 0);
    void Calculate(void);
    void SimCalculate(void);

    virtual int ReceiveData(U8 *data);
    virtual int SendData(U16 cmd = CMD_GENERIC_REALTIME_DATA);
    int WriteXML(char *StrBuf, bool IncAlarms);
    void SetState(TankState newState);
    static AnsiString ZeroSetAllTankPressureSensors(bool Local);
    void SetHighPressure_Locked(bool Locked);
    void SetLowPressure_Locked(bool Locked);
    void SetHighIGP_Locked(bool Locked);
    void SetLowIGP_Locked(bool Locked);
    void GetMaxPresureLimits(float &MinInput, float &MaxInput);
};

//---------------------------------------------------------------------------
#endif
