//---------------------------------------------------------------------------
#ifndef InclinometerH
#define InclinometerH

class AIInclinometer :
    public AnalogInput {
private:
protected:
    float Sign;
public:
    AIInclinometer(int SnsType);
    ~AIInclinometer(void);

    float ScaleTempCoef;
    float Scale;

// Routines for the Configuration
    virtual AnsiString MakeConfigString(int ExtraTabs = 0);
    virtual bool LoadConfigString(TSNConfigString &ConfigString);
    void SetSign(float Sgn);

// Routines for the librarian
    virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    virtual int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
    virtual int PutFloatValue(int ValueId, float NewValue);
// Misc routines
    virtual float CalculateRaw(void);

};

//---------------------------------------------------------------------------
#endif
