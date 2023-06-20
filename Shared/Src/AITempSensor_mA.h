//---------------------------------------------------------------------------
#ifndef AITempSensor_mAH
#define AITempSensor_mAH

class AITempSensor_mA:public AITempSensor {
private:
    float  a,b;   // Constants used for linear interpolation

public:
    AITempSensor_mA(int SnsType);
//  AITempSensor_mA(AnalogInput *Sns);
    ~AITempSensor_mA(void);
    U8 GetFilter(void);
// Routines for the Configuration
  bool LoadConfigString(TSNConfigString &ConfigString);

  float CableLength;
 // Routines for the librarian
    int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
  int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
    int PutFloatValue( int ValueId, float NewValue);

    void MakeConstants(void);
    float Get_Temp(float Amp);
    float Calculate(void);

};

//---------------------------------------------------------------------------
#endif
