//---------------------------------------------------------------------------
#ifndef AlarmHighBotTempH
	#define AlarmHighBotTempH
class PROTemperature;
class AlarmHighBotTemp : public AlarmHighTemp {
public:
    static unsigned NumberOfAlarmSettings;
    AlarmHighBotTemp(PRogramObjectBase *PROPtr);

    void Check(void);
    int  GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit);
 };

//---------------------------------------------------------------------------
#endif

