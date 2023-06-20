//---------------------------------------------------------------------------
#ifndef AIInclinometer_mAH
#define AIInclinometer_mAH

class AIInclinometer_mA :
    public AIInclinometer {
private:
    float  a,b;   // Constants used for linear interpolation
public:
    AIInclinometer_mA(int SnsType);
    ~AIInclinometer_mA(void);

// Routines for the Configuration
    AnsiString MakeConfigString(int ExtraTabs = 0);
    bool LoadConfigString(TSNConfigString &ConfigString);
    float Get_Angle(float Amp);
    float Calculate(void);
    void NewValue(float NewVal);
    void MakeConstants(void);


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
