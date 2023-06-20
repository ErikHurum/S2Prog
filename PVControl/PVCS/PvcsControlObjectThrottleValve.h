
#pragma once
#include "pvcscontrolobject.h"
#include "PvcsControlObjectInfo.h"

//Thread to set Throttle Valve value
UINT SetThrottleValueThread(LPVOID pParam);
UINT SetThrottleButtonThread(LPVOID pParam);

// Class: CPvcsControlObjectThrottleValve
// Description: Class to control the Throttle valves
class CPvcsControlObjectThrottleValve :
	public CPvcsControlObject
{

private:
	virtual int GetStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);

public:
	virtual ~CPvcsControlObjectThrottleValve(void);

	virtual const Gdiplus::ARGB& GetColor(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
	virtual const CString& GetInText(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
	
	virtual CString GetValueString(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);

	virtual bool OnButton(const CPvcsControlObjectInfo& param_info, const int& param_nButton, const bool& param_bIsPressed);
	virtual bool OnSetSpin(const CPvcsControlObjectInfo& param_info, const int& param_nSpin, const UINT& param_uiValue);
	virtual void GetSpinInitInfo(const CPvcsControlObjectInfo& param_info, UINT& param_uiMinValue, UINT& param_uiMaxValue, UINT& param_uiStep, CString& param_strValue);
};

