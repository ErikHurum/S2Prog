#pragma once
#ifndef PROWaterHeaterH
#define PROWaterHeaterH

#if defined(ANTDUSIM) || defined(ANWIN)
using namespace std;
#endif


class PROWaterHeater 
    : public PROXRefObject {

public:
	PROWaterHeater(int idNumber=0, bool addToList=true);
	~PROWaterHeater(void);

    static vector<PRogramObjectBase*>AllObjVector;
    static set<PRogramObjectBase*>ObjectSet;
    static vector<PROWaterHeater*>ObjectVector;
    
    float MaxPressureRange;
    
    bool  HasPressure;
    float PressureValue;
    float ManualPressure    ;
    float ManualInputTemp   ;
    float ManualOutputTemp  ;

    bool  HasInputTemperature;
    float InputTemperatureValue;
    bool  HasOutputTemperature;
    float OutputTemperatureValue;

    float MDO_Efficiency;
    float MDO_kWh_per_ton;

    //bool IsAvailableNewData(void);
    virtual void Calculate(void);
    virtual void WriteConfigToFile(TSNConfigString &ConfigString);
    virtual int LoadConfigFromFile(TSNConfigString &ConfigString);
    void SaveSettings(TSNConfigString *SettingsString);
    bool RestoreSettings(TSNConfigString *SettingsString);

    
    int SendData(U16 cmd = CMD_GENERIC_REALTIME_DATA);
    int ReceiveData(U8* data);

private:
    AIPressSensor* ptrPipePressure;
    AITempSensor* ptrInputTempSensor;
    AITempSensor* ptrOutputTempSensor;

    void Initiate(int idNumber, bool addToList);
// Routines for the librarian
    virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
};

#endif

