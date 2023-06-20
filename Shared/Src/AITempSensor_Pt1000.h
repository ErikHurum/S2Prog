//---------------------------------------------------------------------------
#ifndef AITempSensor_Pt1000H
#define AITempSensor_Pt1000H

class AITempSensor_Pt1000:public AITempSensor {
private:
    bool  IsIntegrated; 
    ConfigPacket ADConfigData;
public:
    AITempSensor_Pt1000(float pRadarDistance=0.0);
    AITempSensor_Pt1000(AnalogInput *Sns);
    ~AITempSensor_Pt1000(void);
    void Initialize(AnalogInput *Sns);
    AnsiString MakeConfigString(int ExtraTabs=0);

    void CalculateCableCorrection(void);
// Routines for the librarian
    int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
    int PutFloatValue( int ValueId, float NewValue);
    void SetStatus(U8 *NewStatus);

};

//---------------------------------------------------------------------------
#endif
