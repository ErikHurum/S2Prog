//---------------------------------------------------------------------------
#ifndef AlarmHighPressureH
#define AlarmHighPressureH

class PROTankPressure;
class AlarmHighPressure : public AlarmBasic {
protected:
    PROTankPressure *PROTPressPtr;
public:
    static unsigned NumberOfAlarmSettings;
    AlarmHighPressure(void);
    AlarmHighPressure(PRogramObjectBase *PROPtr, bool isParent=true);
    virtual AnsiString Get_Message(void);
    void Check(void);
    int GetOperationMode(void);
    bool RestoreSettings(TSNConfigString *SettingsString);
// Routines for the librarian
    int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
    int PutFloatValue(int ValueId, float NewValue);
};

//---------------------------------------------------------------------------
#endif
