//---------------------------------------------------------------------------
#ifndef AITempSensor_Pt100H
#define AITempSensor_Pt100H


class AITempSensor_Pt100:public AITempSensor {
private:
    ConfigPacket ADConfigData;
public:
    AITempSensor_Pt100(float pRadarDistance=0.0);
//  AITempSensor_Pt100(AnalogInput *Sns);
    ~AITempSensor_Pt100(void);
    void Initialize(AnalogInput *Sns);
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
