//---------------------------------------------------------------------------
#ifndef AIInclinometerN2H
#define AIInclinometerN2H

class AIInclinometerN2 :
    public AIInclinometer {
private:
public:
    AIInclinometerN2(int SnsType);
    ~AIInclinometerN2(void);

    volatile float RawValue;
    
// Routines for the Configuration
    AnsiString MakeConfigString(int ExtraTabs = 0);
    bool LoadConfigString(TSNConfigString &ConfigString);
    float Calculate(void);
    float CalculateRaw(void);
    void NewValue(float NewVal);

    AnsiString GetName(void);
// Routines for the librarian
    int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
    int PutFloatValue(int ValueId, float NewValue);
    int CheckInput(float Operator_Val, int &Action);
    int ReceiveData(U8 *data);
    int SendData(U16 cmd = CMD_GENERIC_REALTIME_DATA);


};
//---------------------------------------------------------------------------
#endif
