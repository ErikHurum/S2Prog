//---------------------------------------------------------------------------
#ifndef AIMetriTapeSensorH
#define AIMetriTapeSensorH

class AIMetriTapeSensor:public AnalogInput {
private:
    float  a,b;   // Constants used for linear interpolation
    float MaxR;
    float MinR;
    float Rk;
    float Ui;

public:
    AIMetriTapeSensor(void);
//  AIMetriTapeSensor(AnalogInput *Sns);
    ~AIMetriTapeSensor(void);
    U8 GetFilter(void);
    AnsiString MakeConfigString(int ExtraTabs);
    bool LoadConfigString(TSNConfigString &ConfigString);
// Routines for the librarian
    virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
    virtual int PutFloatValue( int ValueId, float NewValue);

 // Routines for the librarian

    void MakeConstants(void);
    void FilterValue(float NewVal,float FilterDegree);
    float Get_Resistance(float Uv);
    float Get_Distance(float Resistance);

    float Calculate(void);

};

//---------------------------------------------------------------------------
#endif
