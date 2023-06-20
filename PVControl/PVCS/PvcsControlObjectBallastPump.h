#pragma once
#include "pvcscontrolobject.h"


// Class: CPvcsControlObjectBallastPump
// Descreption: Class to control the Ballast Pumps
class CPvcsControlObjectBallastPump :
	public CPvcsControlObject
{

	virtual int GetStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
	HANDLE m_hTimerQ; // The handle to the timer queue implemented by the controller

public:
	CPvcsControlObjectBallastPump();
	virtual ~CPvcsControlObjectBallastPump(void);

	virtual const COLORREF& GetColor(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2);
	virtual const CString& GetInText(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);
	
	virtual CString GetValueString(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2=-1);

	virtual bool OnButton(const CPvcsControlObjectInfo& param_info, const int& param_nButton, const bool& param_bIsPressed);
	virtual bool OnSetSpin(const CPvcsControlObjectInfo& param_info, const int& param_nSpin, const UINT& param_uiValue);
	virtual void GetSpinInitInfo(const CPvcsControlObjectInfo& param_info, UINT& param_uiMinValue, UINT& param_uiMaxValue, UINT& param_uiStep, CString& param_strValue);
};

VOID CALLBACK TimerCallback( PVOID, BOOLEAN );

