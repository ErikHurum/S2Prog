//---------------------------------------------------------------------------
#ifndef AITempSensor_HartH
#define AITempSensor_HartH

class AITempSensor_Hart : public AITempSensor {
private:
    float HartValue;

public:
    int   HartComErrorCnt;
    AITempSensor_Hart(void);
//  AITempSensor_Hart(AnalogInput *Sns);
    ~AITempSensor_Hart(void);
// Routines for the Configuration
    bool LoadConfigString(TSNConfigString &ConfigString);

    float CableLength;
    // Routines for the librarian
    int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
    int PutFloatValue(int ValueId, float NewValue);
    float Calculate(void);
	void SetNewStatus(bool NewStatus);
    void NewValue(float NewValue);

};

//---------------------------------------------------------------------------
#endif
