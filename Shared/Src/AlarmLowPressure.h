//---------------------------------------------------------------------------
#ifndef AlarmLowPressureH
#define AlarmLowPressureH
class PROTankPressure;
class AlarmLowPressure : public AlarmBasic {
protected:
    PROTankPressure *PROTPressPtr;

public:
    static unsigned NumberOfAlarmSettings;
    AlarmLowPressure(void);
    AlarmLowPressure(PRogramObjectBase *PROPtr);
    virtual AnsiString Get_Message(void);
    void Check(void);
    bool RestoreSettings(TSNConfigString *SettingsString);
// Routines for the librarian
    int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    virtual int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
    int PutFloatValue(int ValueId, float NewValue);
};

//---------------------------------------------------------------------------
#endif
