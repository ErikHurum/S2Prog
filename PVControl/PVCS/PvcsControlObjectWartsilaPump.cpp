#include "StdAfx.h"
#include ".\PvcsControlObjectWartsilaPump.h"
#include "pvcscontrolobjectinfo.h"
#include "pvcswagocontrol.h"
#include "DxfLayout.h"
#include <queue>
#undef MAX
#define MAX(a,b)	((a) > (b) ? (a) : (b))
#undef MIN
#define MIN(a,b)	((a) < (b) ? (a) : (b))
// Handle to the timer
HANDLE WartsilaPumpTimer;
extern VOID CALLBACK BVTimerCallback(PVOID, BOOLEAN);
CPvcsControlObjectWartsilaPump::CPvcsControlObjectWartsilaPump(void)
	: m_hTimerQ2(CreateTimerQueue()) {
}


CPvcsControlObjectWartsilaPump::~CPvcsControlObjectWartsilaPump(void) {
	DeleteTimerQueueEx(m_hTimerQ2, NULL);
}


// The container to queue the timed digital signal off requests
//std::queue<PvcsControlObjectTypes::DigitalSignal> g_DigSigQ;




// Function name   : CPvcsControlObjectWartsilaPump::GetColor
// Description     : Get the deafault color
// Return type     : const COLORREF&
// Argument        : const CPvcsControlObjectInfo& param_info

const Gdiplus::ARGB& CPvcsControlObjectWartsilaPump::GetColor(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2) {
	//COLORREF tmpCol = param_info.GetStatusColor(GetStatus(param_info,pSubIndex2),pSubIndex2);
	return param_info.GetStatusColor(GetStatus(param_info, pSubIndex2), pSubIndex2);
//	static Gdiplus::ARGB StatCol = Gdiplus::Color::Red;

//	return StatCol++;

}


// Function name   : CPvcsControlObjectWartsilaPump::GetInText
// Description     : Get the Intext
// Return type     : const CString&
// Argument        : const CPvcsControlObjectInfo& param_info

const CString& CPvcsControlObjectWartsilaPump::GetInText(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2) {
	return param_info.GetStatusInText(GetStatus(param_info), pSubIndex2);
}

// Function name   : CPvcsControlObjectBallastPump::GetValueString
// Description     : Not implemented
// Return type     : CString
// Argument        : const CPvcsControlObjectInfo& param_info

CString CPvcsControlObjectWartsilaPump::GetValueString(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2) {
	CString strValue;
	bool bValue = false;
	UINT uiValue = 0;

	// The value string is determined as follows:
	// Default: Value = Analog Input%
	try {
		switch (pSubIndex2) {
		case 0xffffffff:
			if (CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputAnalogSignalList().at(0), uiValue, param_info.GetWagoUnitType())) {
				if (uiValue < 10) uiValue = 0;
				strValue.Format("%4d", uiValue);
			}
			break;
		case 0:
			if (CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputAnalogSignalList().at(0), uiValue, param_info.GetWagoUnitType())) {
				strValue.Format("%4d", uiValue);
			}
			break;
		case 1:
			if (CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputAnalogSignalList().at(1), uiValue, param_info.GetWagoUnitType())) {
				strValue.Format("%4d", uiValue);
			}
			break;
		case 2:
			if (CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputAnalogSignalList().at(2), uiValue, param_info.GetWagoUnitType())) {
				strValue.Format("%4d", uiValue);
			}
			break;
		case 3:
			if (CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputAnalogSignalList().at(3), uiValue, param_info.GetWagoUnitType())) {
				strValue.Format("%4d", uiValue);
			}
			break;
		case 4: // Pump active mode
			if (GetObjStatus(param_info, 20)) {
				strValue = "Remote";
			} else if (GetObjStatus(param_info, 1)) { // Check if pump running
				if (CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputAnalogSignalList().at(4), uiValue, param_info.GetWagoUnitType())) {
					switch (uiValue) {
					case 0:
						strValue = "Discharge"; break;
					case 1:
						strValue = "Stripping"; break;
					case 2:
						strValue = "Wash"; break;
					case 3:
						strValue = "Circulation"; break;
					}
				}
			} else if (GetObjStatus(param_info, 0)) {
				strValue = "Ready";
			} else {
				strValue = "Stopped";
			}
			break;
		case 7: // Pump state, active mode, only numeric value
			if (GetObjStatus(param_info, 20)) {
				strValue = "3";
			} else if (GetObjStatus(param_info, 0)) {
				strValue = "0";
			} else if (GetObjStatus(param_info, 1)) {
				strValue = "1";
			} else {
				strValue = "2";
			}
			break;
		case 8: // Pump active mode, only numeric value
			if (CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputAnalogSignalList().at(4), uiValue, param_info.GetWagoUnitType())) {
				strValue.Format("%d", uiValue);
			}
			break;
		case 5: // Frequency converter
			if (CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputAnalogSignalList().at(5), uiValue, param_info.GetWagoUnitType())) {
				strValue.Format("FreqCnv %4d", uiValue);
			}
			break;
		case 6: // Pump active mode
			if (CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputAnalogSignalList().at(6), uiValue, param_info.GetWagoUnitType())) {
				switch (uiValue) {
				case 0:
					strValue = "No heating"; break;
				case 1:
					strValue = "Energized"; break;
				case 2:
					strValue = "Fault"; break;
				}
			}
			break;
		case 9:
			// Speed setpoint
			if (CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputAnalogSignalList().at(7), uiValue, param_info.GetWagoUnitType())) {
				strValue.Format("%4d", uiValue);
			}
			break;
		}
	} catch (std::out_of_range &e) {   //TRACE("*****CPvcsControlObjectTempSetPoint-getvaluestring*std::out range******");
		XmlLogError("Probable error: Input signal count is mismatched in config.");
		throw e;
	} catch (exception &e) {
		//TRACE("*****CPvcsControlObjectTempSetPoint-getvaluestring*******");
		XmlLogError(e.what());
	}
	return strValue;
}


// Function name   : CPvcsControlObjectWartsilaPump::OnButton
// Description     : Not Implemented
// Return type     : bool
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nButton
// Argument        : const bool& param_bIsPressed
#define MAX_DIG_OP  10
#define MAX_ANA_OP   10
bool CPvcsControlObjectWartsilaPump::OnButton(const CPvcsControlObjectInfo &param_info, const int &param_nButton, const bool &param_bIsPressed) {
	bool bResult = false;
	unsigned PulsDuration = param_info.GetDigitalOutputPulseDuration(param_nButton);
	int NumberOfDigOP = param_info.GetOutputDigitalSignalList().size();
	int NumberOfAnaOP = param_info.GetOutputAnalogSignalList().size();
	int ExtraFunction = param_info.GetDigitalOutputExtraFunction(param_nButton);
	if (NumberOfDigOP > 1) {
		DigitalSignal DigOp[MAX_DIG_OP];
		try {
			for (int i = 0; i < NumberOfDigOP; i++) {
				DigOp[i] = param_info.GetOutputDigitalSignalList().at(i);
			}
		} catch (exception &e) {
			//TRACE("*****CPvcsControlObjectCargoValve2-GetSpinInitInfo*******");
			XmlLogError(e.what());
		}


		CDxfLayout::SetControlOperationState(param_info.GetIndex(), param_info.GetSubIndex(), false);

		AnalogSignal AnaOp[MAX_ANA_OP];
		try {
			for (int i = 0; i < NumberOfAnaOP; i++) {
				AnaOp[i] = param_info.GetOutputAnalogSignalList().at(i);
			}
		} catch (exception &e) {
			//TRACE("*****CPvcsControlObjectCargoValve2-GetSpinInitInfo*******");
			XmlLogError(e.what());
		}
		// If button is pressed
		if (param_bIsPressed) {
			switch (ExtraFunction) {
			case 0:
				CPvcsWagoControl::theWagoUnit().SetValue(AnaOp[ExtraFunction], AnaOp[ExtraFunction].Value.Limit.MinValue);
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			}
			//if output is not of pulse type, then set output to true
			if (PulsDuration == 0) {

				CPvcsWagoControl::theWagoUnit().SetValue(DigOp[param_nButton], true);
			}
			//else if output is of pulse type, then send true signal for the specified time period
			else {
				// Initialize the timer
				ASSERT(m_hTimerQ2);

				if (m_hTimerQ2) {
					// Push the output into the timer queue
					//g_DigSigQ.push(param_info.GetOutputDigitalSignalList().at( param_nButton ));
					using namespace PvcsControlObjectTypes;

					DigitalSignal *ptempInfo = new DigitalSignal(DigOp[param_nButton]);

					CreateTimerQueueTimer(&WartsilaPumpTimer, m_hTimerQ2, BVTimerCallback, (PVOID)(ptempInfo),
										  PulsDuration, 0, WT_EXECUTEINTIMERTHREAD);

					ASSERT(WartsilaPumpTimer);
				}
				CPvcsWagoControl::theWagoUnit().SetValue(DigOp[param_nButton], true);
				//bResult = CPvcsWagoControl::theWagoUnit().SetValue(param_info.GetOutputDigitalSignalList().at(param_nButton),true);
			} // if( param_info.GetDigitalOutputPulseDuration( param_nButton ) > 0 )
			bResult = true;
		} else { //if(param_bIsPressed)
				 //if button released
			//if output is of pulse type, then send true signal for the specified time period

			//if output is not of pulse type, then set output to true
			if (PulsDuration == 0) {
				CPvcsWagoControl::theWagoUnit().SetValue(DigOp[param_nButton], false);
				bResult = true;
			}
		} //else if(!param_bIsPressed)

		CDxfLayout::SetControlOperationState(param_info.GetIndex(), param_info.GetSubIndex(), true);
	} //if( param_info.GetOutputDigitalSignalList().size() > 1 )

	return bResult;
}


// Function name   : CPvcsControlObjectBallastPump::OnSetSpin
// Description     : Outputs control signals according to the spin box status
// Return type     : bool
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nSpin
// Argument        : const UINT& param_uiValue

bool CPvcsControlObjectWartsilaPump::OnSetSpin(const CPvcsControlObjectInfo &param_info, const int &param_nSpin, const UINT &param_uiValue) {
	bool bResult = true;

	if (param_info.GetOutputDigitalSignalList().size() >= 5) {
		UINT uiValue;
		if (CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputAnalogSignalList().at(4), uiValue, param_info.GetWagoUnitType())) {
			int RegNo;
			switch (uiValue) {
			default:
			case 0:
			case 1:
				RegNo = 0; break;
			case 2:
				RegNo = 1; break;
			case 3:
				RegNo = 2; break;
			}
			bResult = CPvcsWagoControl::theWagoUnit().SetValue(param_info.GetOutputAnalogSignalList().at(RegNo), param_uiValue);
		}
		

	}

	return bResult;
}


// Function name   : CPvcsControlObjectBallastPump::GetSpinInitInfo
// Description     : Initializes the spinbox with the current status of the objects
// Return type     : void
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : UINT& param_uiMinValue
// Argument        : UINT& param_uiMaxValue
// Argument        : UINT& param_uiStep
// Argument        : CString& param_strValue

void CPvcsControlObjectWartsilaPump::GetSpinInitInfo(const CPvcsControlObjectInfo &param_info, UINT &param_uiMinValue, UINT &param_uiMaxValue, UINT &param_uiStep, CString &param_strValue) {
	if (param_info.GetOutputAnalogSignalList().empty()) return;

	try {
		param_uiMinValue = param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MinValue;
		param_uiMaxValue = param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MaxValue;
		param_uiStep = param_info.GetOutputAnalogSignalList().at(0).Value.Step;

		CString strValue;
		bool bValue = false;
		UINT uiValue = 0;

		if (CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputAnalogSignalList().at(7), uiValue, param_info.GetWagoUnitType())) {

			int Value = uiValue;
			strValue.Format("%d", Value);
			param_info.SetValueToBeSet(strValue);
			CDxfLayout::SetValueToBeSet(param_info.GetIndex(), param_info.GetSubIndex(), strValue);
		}
		param_strValue = strValue;
	} catch (std::out_of_range &e) {
		//TRACE("*****CPvcsControlObjectWartsilaPump-getspininitinfo*std::out range******");
		XmlLogError("Probable error: Analog Input count is less than Spin box count.");
		throw e;
	} catch (exception &e) {
		//TRACE("*****CPvcsControlObjectWartsilaPump-getspininitinfo*std::out range******");
		XmlLogError(e.what());
	}
}




// Function name   : CPvcsControlObjectWartsilaPump::GetStatus
// Description     : Get a status
// Return type     : int
// Argument        : const CPvcsControlObjectInfo& param_info

int CPvcsControlObjectWartsilaPump::GetStatus(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2) {
	return GetObjStatus(param_info, pSubIndex2);
}

// Function name   : CPvcsControlObjectCargoValve::GetStatus
// Description     : Returns the current status of the control object
// Return type     : int
// Argument        : const CPvcsControlObjectInfo& param_info
int CPvcsControlObjectWartsilaPump::GetObjStatus(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2) {
	volatile unsigned nStatus = 0;
	bool bValue = false;

	unsigned NumberOfDI = param_info.GetInputDigitalSignalList().size();
	switch (pSubIndex2) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
		if (pSubIndex2 < int(NumberOfDI)) {
			bool Status = false;
			bool Success = CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputDigitalSignalList().at(pSubIndex2), Status, param_info.GetWagoUnitType());
			nStatus = unsigned(Status);
		} else {
			nStatus = 0;
		}
		break;
	case -1:
	default:
		{
			UINT State = 0;
			for (UINT i = 0; i < NumberOfDI; i++) {
				bool Status = false;
				bool Success = CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputDigitalSignalList().at(i), Status, param_info.GetWagoUnitType());
				if (Status) {
					State |= 1 << i;
				}
			}
			//First Check for remote control
			if (param_info.GetStatusAnd(State, 0)) {
				nStatus = 1;
			}
			//check for alarm
			else if (param_info.GetStatusAnd(State, 3)) {
				nStatus = 4;
			}
			//Check for warning
			else if (param_info.GetStatusAnd(State, 2)) {
				nStatus = 3;
			}
			//Check for Stripping
			else if (param_info.GetStatusAnd(State, 5)) {
				nStatus = 6;
			}
			//Check for Wash
			else if (param_info.GetStatusAnd(State, 6)) {
				nStatus = 7;
			}
			//Check for Circulation
			else if (param_info.GetStatusAnd(State, 7)) {
				nStatus = 8;
			}
			//After alternative running modes, Check for Discharge
			else if (param_info.GetStatusAnd(State, 4)) {
				nStatus = 5;
			}
			//Finally Check for Ready
			else if (param_info.GetStatusAnd(State, 1)) {
				nStatus = 2;
			}
	}
		break;
	}


	return nStatus;
}


bool CPvcsControlObjectWartsilaPump::CheckAlarm(DigitalSignal DigitalInput, CString WagoUnitType) {
	bool Status = false;
	bool Success = CPvcsWagoControl::theWagoUnit().GetValue(DigitalInput, Status, WagoUnitType);
	return Status;
}
