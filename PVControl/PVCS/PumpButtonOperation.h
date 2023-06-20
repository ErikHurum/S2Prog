#pragma once
#include <vector>
#include ".\PvcsControlObjectInfo.h"
using namespace PvcsControlObjectTypes;
class CPumpButtonOperation
{
public:
	struct pair_struct {
		bool Inserted;
		DigitalSignal mDigitalSignal;
	};
	typedef map<int, DigitalSignal>Functions;
	CPumpButtonOperation(void);
	~CPumpButtonOperation(void);
	static pair_struct InsertInMap(Functions &pFunctionMap, int pFunction, DigitalSignal pDigitalSignal);
	static bool FindObject(Functions &pFunctionMap,int pFunction, DigitalSignal &pDigitalSignal);
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
		bool bButtonState;
		bool bIsOperationGoing;
		bool bIsPumpLightON;
		vector<DigitalSignal>DigitalIn;
		vector<DigitalSignal>DigitalOut;
		vector<AnalogSignal>AnalogIn;
		map<int, DigitalSignal>FunctionMap;
	};

	static vector <CPumpButtonOperation::ButtonInfo *> m_PumpButtonInfo;

};
