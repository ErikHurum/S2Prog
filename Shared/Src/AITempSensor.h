//---------------------------------------------------------------------------
#ifndef AITempSensorH
#define AITempSensorH

class AITempSensor:
public AnalogInput {
protected:
    float CableLengthShip;
    float CableLengthSensor;
    float CableResistanceShip;
    float CableResistanceSensor;
    float CableMsrdResistance;
    float CableOffset;
    float DistJunctionBoxToBot;
    bool  hasCableResistanceShip;
    bool  hasCableResistanceSensor;
    bool  hasCableLengthSensor;
    TSNTable1Degree *CalData;
public:
    AITempSensor(void);
    AITempSensor(int SnsType);
    ~AITempSensor(void);
    void Init(void);
    virtual void CalculateCableCorrection(void);
    float GetCableCorrection(void);

// Routines for the Configuration
    virtual AnsiString MakeConfigString(int ExtraTabs=0);
    bool LoadConfigString(TSNConfigString &ConfigString);

// Routines for the librarian
    virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
    virtual int PutFloatValue( int ValueId, float NewValue);
    int CheckInput(float Operator_Val, int &Action);
    // Misc Routines
    virtual bool IsHWError(void);
    virtual float Calculate(void);
    bool temp_PRTResistanceValue(double aTemp, double R0, double &Resistance);
    bool temp_PRTTemperatureValue(double aResistance, double R0, double &Temperature);
    float GetTempFromR(double R);
};

//---------------------------------------------------------------------------
#endif
