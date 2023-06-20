#pragma once
#include "pvcscontrolobject.h"
#define POWERPACK_ALARMS 20
class CPvcsControlObjectPowerPack :
	public CPvcsControlObject
{
private:
	virtual int GetStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
	HANDLE m_hTimerQ2; // The handle to the timer queue implemented by the controller
public:
    static set<int>AlarmSet;
    static set<int>WarningSet;
    static vector<DigitalSignal>DigOp;
    static bool IsFirstTime;
    static bool  HasErasedAlarms;
    static bool  HasNewAlarms;
    static bool  HasErasedWarnings;
    static bool  HasNewWarnings;
    static unsigned AlarmBits;
    static unsigned prevAlarmBits;
    static unsigned WarningBits;
    static unsigned prevWarningBits;

	CPvcsControlObjectPowerPack(void);
	~CPvcsControlObjectPowerPack(void);
	virtual const COLORREF& GetColor(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
	virtual const CString& GetInText(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
	
	virtual CString GetValueString(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
	virtual bool OnButton(const CPvcsControlObjectInfo& param_info, const int& param_nButton, const bool& param_bIsPressed);
	virtual bool OnSetSpin(const CPvcsControlObjectInfo& param_info, const int& param_nSpin, const UINT& param_uiValue);
	virtual void GetSpinInitInfo(const CPvcsControlObjectInfo& param_info, UINT& param_uiMinValue, UINT& param_uiMaxValue, UINT& param_uiStep, CString& param_strValue);
	static int GetObjStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
	virtual bool CheckAlarm(DigitalSignal DigitalInput,CString WagoUnitType);

};

//VOID CALLBACK BVTimerCallback( PVOID, BOOLEAN );
