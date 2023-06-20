//---------------------------------------------------------------------------
#ifndef PROAtmReferenceH
#define PROAtmReferenceH

class PROAtmReference :
public PRogramObject {
private:
    bool IsConfigured;
public:
    static PROAtmReference *PROAtmRefPtr;
    PROAtmReference(bool IsConfig);
    ~PROAtmReference(void);
    vector<AIPressSensor*>AtmRefSensors;
    bool IsOutOfRange;
    bool SensorOnTCU;
//  bool AtmRefEnable;
    bool UseManual;
    float ManualPressure;
// Routines for the Configuration
//
#ifdef ANCONF
    AnalogInput *ReplaceSensor(AnalogInput *AIPtr, int CurrentSnsType);
    void RemoveSensors(void);
#endif
    void WriteConfigToFile(TSNConfigString &ConfigString);
    int LoadConfigFromFile(TSNConfigString &ConfigString);

// Routines for Saving of Settings
    void SaveSettings(TSNConfigString *SettingsString);
    bool RestoreSettings(TSNConfigString *SettingsString);

// Routines for Calculation of values
    void Calculate(void);
    void SimCalculate(void);

// Routines for the librarian
    virtual int GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit);
    virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    virtual int GetFloatValue(int ValueId, int Index, float &MyValue);

    virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
    virtual int PutFloatValue( int ValueId, float NewValue);
    static ValueList *GetValueInfoTableStatic(int &Entries, int Index=0);

    int ReceiveData(U8* data);
    int SendData(U16 cmd=CMD_GENERIC_REALTIME_DATA);
    void RefreshData(int ValueKey=0);


};
//---------------------------------------------------------------------------
#endif
