//---------------------------------------------------------------------------
#ifndef AlarmLowBotTempH
	#define AlarmLowBotTempH
class AlarmLowBotTemp : public AlarmLowTemp {
public:
    static unsigned NumberOfAlarmSettings;
    AlarmLowBotTemp(PRogramObjectBase *PROPtr);

    void Check(void);
    int  GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit);


    };

//---------------------------------------------------------------------------
#endif
