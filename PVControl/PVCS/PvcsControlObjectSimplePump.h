#pragma once
#include "pvcscontrolobject.h"

class CPvcsControlObjectSimplePump :
	public CPvcsControlObject
{
private:
	virtual int GetStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);

public:
	CPvcsControlObjectSimplePump(void);
	~CPvcsControlObjectSimplePump(void);
	virtual const COLORREF& GetColor(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
	virtual const CString& GetInText(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
	
	virtual CString GetValueString(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
	virtual bool OnButton(const CPvcsControlObjectInfo& param_info, const int& param_nButton, const bool& param_bIsPressed);
	virtual bool OnSetSpin(const CPvcsControlObjectInfo& param_info, const int& param_nSpin, const UINT& param_uiValue);
	virtual void GetSpinInitInfo(const CPvcsControlObjectInfo& param_info, UINT& param_uiMinValue, UINT& param_uiMaxValue, UINT& param_uiStep, CString& param_strValue);
	static int GetObjStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
	virtual bool CheckAlarm(DigitalSignal DigitalInput,CString WagoUnitType);
};
