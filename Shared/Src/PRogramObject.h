#pragma once
//---------------------------------------------------------------------------
#ifndef PRogramObjectH
#define PRogramObjectH

class PRogramObject :
    public PRogramObjectBase {
protected:
    float SimulatorSign;
    set<AnalogInput *>ModbusSensorSet;
public:
    PRogramObject(bool AddToList = true);
    ~PRogramObject(void);
    AnsiString LongName;
    volatile bool IsNewData;
    set<AlarmBasic *>AlarmSet;
    set<AlarmBasic *>CompleteAlarmInfoList;
    set<AlarmBasic *>ExternalAlarmList;

    static set<PRogramObject *>ObjectSet;
    static vector<PRogramObject *>IOObjectVector;
    static vector<PRogramObjectBase *>ScratchPageVector;
    static set<PRogramObject *>TaskUniquePROSet;
    vector<AnalogInput *>AnalogInList;
    vector<AnalogInput *>AllAnalogInList;
    bool DataFromOther;

// Routines for the Configuration
    virtual AnsiString MakeConfigString(int ExtraTabs = 0);
    virtual bool LoadConfigString(TSNConfigString &ConfigString);
    virtual void SortAnalogInputs(void);
    void CopyAnalogList(void);
    void AddToIOObjectList(void);
    void AddToScratchPageVector(void);
// Routines for Saving of Settings
    virtual void SaveSettings(TSNConfigString *SettingsString);
    virtual bool RestoreSettings(TSNConfigString *SettingsString);
    AnalogInput* FindAIFromIDNumber(unsigned AIIDNumber);

// Routines for the librarian
    AnalogInput* FindAnalogInput(int Location);
    AnalogInput* FindAnalogInput(int Location, int BasicSensorType);
    AnalogInput* FindAllAnalogInput(int Location, int BasicSensorType);
    int         FindTypeNumberOfSensors(int BasicSensorType);
    int         FindTypeNumberOfAllSensors(int BasicSensorType);
    virtual int GetValue(int ValueId, int Index, float &MyValue, int &DecPnt, int &Unit);
    virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    virtual int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
    virtual int PutFloatValue(int ValueId, float NewValue);

    // Misc Routines
    virtual void Calculate(void);


    void AddAlarms(set<AlarmBasic *> &AlInfoList);
    void AddToExternalAlarms(set<AlarmBasic *> &AlInfoList);
    void AddCompleteList(set<AlarmBasic *> &AlInfoList);
    void AddSensorAlarms(void);
    virtual void CreateAlarms(void);

    virtual int WriteXML(char *StrBuf, bool IncAlarms);
    void RemoveAnalogInI(int Index, bool DeleteAI = true);
    void RemoveAnalogInP(AnalogInput *AIPtr, bool DeleteAI = true);
    void AddAnalogIn(AnalogInput *AIPtr);
    void SetChildUserRights(void);
    void SetChildUserRights(PRogramObject *Child);
    void MergeChildUserRights(PRogramObject *Child);
    virtual int LCWriteXML(char *StrBuf);
    AnsiString GetHWAlarms(void);
    AnsiString GetAlarms(void);
    AnsiString GetWarnings(void);
    int        GetNumberOfHWAlarms(void);
    int        GetNumberOfAlarms(void);
    int        GetNumberOfWarnings(void);
    virtual void RefreshData(int ValueKey=0);
    void SetOffline(int ValueKey);

    set<AnalogInput *>GetModBusSensorList(void);
    virtual bool IsStaticValue(int ValueKey);
};

//---------------------------------------------------------------------------
#endif
