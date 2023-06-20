//---------------------------------------------------------------------------
#ifndef PROTemperatureH
#define PROTemperatureH

class PROTemperature :
    public PROXRefObject {
private:
    int StatusTemp;
    unsigned OutsideCnt;
    static ValueList TempValueList1[];
    static ValueList TempValueList2[];
    static ValueList TempAlarmValueList[];
    static ValueList TempSensorValueList1[];
    static ValueList TempSensorValueList2[];
    static unsigned MaxTempCnt;
    static bool      UseTemperatureWindow;
public:
    static vector<PRogramObjectBase *>AllObjVector;
    static vector<PRogramObjectBase *> ObjVector;
    static set<PRogramObjectBase *>    ObjectSet;
    PROTemperature(bool AddToList = true, int LNumber=0);
    PROTemperature(int IdNum, PROXRefObject *CreatedFromTank, bool AddToList = true, int LNumber=0);
    void Initiate();
    void CreateAlarms(void);
    ~PROTemperature(void);

    bool             HasTemp;
    PROXRefObject    *CreatedFromThisTank;
    float            Temperature,Level;
    float            VaporTemp;
    float            BottomTemp;
    bool             BottomTempOK;
    bool			 NotEmptyTank;

    AlarmHighTemp    *HighTempPtr;
    AlarmLowTemp     *LowTempPtr;
    AlarmHighBotTemp *HighBotTempPtr;
    AlarmLowBotTemp  *LowBotTempPtr;
    float            HighTempLimit;
    float            LowTempLimit;
// Routines for the Configuration
    void SortAnalogInputs(void);
    void WriteConfigToFile(TSNConfigString &ConfigString);
    int LoadConfigFromFile(TSNConfigString &ConfigString);

// Routines for Saving of Settings
    void SaveSettings(TSNConfigString *SettingsString);
    bool RestoreSettings(TSNConfigString *SettingsString);

// Routines for the librarian
    virtual int FindPROStatus(AnsiString &MyString);
    virtual int GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit);
    virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    virtual int GetBitValue(int ValueId, int Index, bool &MyBit);
    virtual int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
    virtual int PutFloatValue(int ValueId, float NewValue);
    virtual int PutBitValue(int ValueId, int Index, bool NewValue);

    ValueList* GetValueInfoTable(int &Entries, int Index);
    static ValueList* GetValueInfoTableStatic(int &Entries, int Index = 0);
    virtual bool IsTemperatureInsideWindow(float NewValue, float OldValue);
    void Calculate(void);
    void SimCalculate(void);
    void SetState(TankState newState);
    // Routines for object internode communication
    virtual int ReceiveData(U8 *data);
    virtual int SendData(U16 CommandNo = CMD_GENERIC_REALTIME_DATA);
    float GetTemperature(void);
    void SetTemperature(float NewTemp);
    bool IsAvailableNewData(void);
    void UpdateLevelInfo(float pLevel, bool pEmpty);
    int WriteXML(char *StrBuf, bool IncAlarms);
    static int GetMaxTempSensors(void);
};

//---------------------------------------------------------------------------
#endif
