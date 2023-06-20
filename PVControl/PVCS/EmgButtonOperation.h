#pragma once
#include <vector>

class CEmgButtonOperation
{
public:
	CEmgButtonOperation(void);
	~CEmgButtonOperation(void);

public:
	struct ControlInfo
	{
		CString strControlName;
		UINT uiControlIndex;
		UINT uiControlSubIndex;
		UINT uiActionOfButton;
		ControlInfo * Next_ControlInfo;
	};

	struct ButtonInfo
	{
		CString strButtonText;
		int iWagoUnit;
		int iWagoChNo;
		int iInputType;
		double dInputThreshold;
		bool bInvertInput;
		bool bButtonState;
		bool bIsOperationGoing;
		bool bIsEmgLightON;
		ControlInfo * Next_ControlInfo;
		int iTotalOperation;
		bool bResetAllOutputs;
		bool bRemoteControl;
	};

	static vector <CEmgButtonOperation::ButtonInfo *> m_EmgButtonInfo;

};
