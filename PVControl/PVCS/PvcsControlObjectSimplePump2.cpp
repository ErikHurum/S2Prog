#include "StdAfx.h"
#include ".\pvcscontrolobjectsimplepump2.h"
#include "pvcscontrolobjectinfo.h"
#include "pvcswagocontrol.h"
#include "DxfLayout.h"
#include <queue>
#undef MAX
#define MAX(a,b)	((a) > (b) ? (a) : (b))
#undef MIN
#define MIN(a,b)	((a) < (b) ? (a) : (b))
// Handle to the timer
HANDLE PumpTimer2;
extern VOID CALLBACK BVTimerCallback(PVOID, BOOLEAN);

CPvcsControlObjectSimplePump2::CPvcsControlObjectSimplePump2(void)
    : m_hTimerQ2(CreateTimerQueue()) {
}


CPvcsControlObjectSimplePump2::~CPvcsControlObjectSimplePump2(void) {
    DeleteTimerQueueEx(m_hTimerQ2, NULL);
}


// The container to queue the timed digital signal off requests
//std::queue<PvcsControlObjectTypes::DigitalSignal> g_DigSigQ;




// Function name   : CPvcsControlObjectSimplePump2::GetColor
// Description     : Get the deafault color
// Return type     : const COLORREF&
// Argument        : const CPvcsControlObjectInfo& param_info

const Gdiplus::ARGB& CPvcsControlObjectSimplePump2::GetColor(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2) {
    //COLORREF tmpCol = param_info.GetStatusColor(GetStatus(param_info,pSubIndex2),pSubIndex2);
    return param_info.GetStatusColor(GetStatus(param_info, pSubIndex2), pSubIndex2);
//	static Gdiplus::ARGB StatCol = Gdiplus::Color::Red;

//	return StatCol++;

}


// Function name   : CPvcsControlObjectSimplePump2::GetInText
// Description     : Get the Intext
// Return type     : const CString&
// Argument        : const CPvcsControlObjectInfo& param_info

const CString& CPvcsControlObjectSimplePump2::GetInText(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2) {
    return param_info.GetStatusInText(GetStatus(param_info), pSubIndex2);
}

// Function name   : CPvcsControlObjectBallastPump::GetValueString
// Description     : Not implemented
// Return type     : CString
// Argument        : const CPvcsControlObjectInfo& param_info

CString CPvcsControlObjectSimplePump2::GetValueString(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2) {
    CString strValue;
    bool bValue = false;
    UINT uiValue = 0;

    // The value string is determined as follows:
    // Default: Value = Analog Input%
    try {
        switch (pSubIndex2) {
        case 0:
            if (CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputAnalogSignalList().at(0), uiValue, param_info.GetWagoUnitType())){
				double InVal =  AnalogScaleWagoToObjectD(param_info.GetInputAnalogSignalList().at(0).Value.Limit.MinValue, param_info.GetInputAnalogSignalList().at(0).Value.Limit.MaxValue, uiValue, param_info.GetWagoUnitType());
				if (InVal < 10.0) InVal = 0.0;
				strValue.Format("%4.0f",InVal);
			}
            break;
        case 1:
            //if (CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputAnalogSignalList().at(1), uiValue, param_info.GetWagoUnitType())) strValue.Format("%4.1f A", AnalogScaleWagoToObjectD(param_info.GetInputAnalogSignalList().at(1).Value.Limit.MinValue, param_info.GetInputAnalogSignalList().at(1).Value.Limit.MaxValue, uiValue, param_info.GetWagoUnitType()));
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


// Function name   : CPvcsControlObjectSimplePump2::OnButton
// Description     : Not Implemented
// Return type     : bool
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nButton
// Argument        : const bool& param_bIsPressed
#define MAX_DIG_OP  10
bool CPvcsControlObjectSimplePump2::OnButton(const CPvcsControlObjectInfo &param_info, const int &param_nButton, const bool &param_bIsPressed) {
    bool bResult = false;
    unsigned PulsDuration = param_info.GetDigitalOutputPulseDuration(param_nButton);
    int NumberOfDigOP = param_info.GetOutputDigitalSignalList().size();
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

        // If button is pressed
        if (param_bIsPressed) {

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

                    CreateTimerQueueTimer(&PumpTimer2, m_hTimerQ2, BVTimerCallback, (PVOID)(ptempInfo),
                                          PulsDuration, 0, WT_EXECUTEINTIMERTHREAD);

                    ASSERT(PumpTimer2);
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

bool CPvcsControlObjectSimplePump2::OnSetSpin(const CPvcsControlObjectInfo &param_info, const int &param_nSpin, const UINT &param_uiValue) {
    bool bResult = true;

    if (param_info.GetOutputDigitalSignalList().size() >= 1) {
        bResult =
            CPvcsWagoControl::theWagoUnit().SetValue(param_info.GetOutputAnalogSignalList().at(0),
                                   AnalogScaleObjectToWago(param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MinValue,
                                                           param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MaxValue, param_uiValue, param_info.GetWagoUnitType()));

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

void CPvcsControlObjectSimplePump2::GetSpinInitInfo(const CPvcsControlObjectInfo &param_info, UINT &param_uiMinValue, UINT &param_uiMaxValue, UINT &param_uiStep, CString &param_strValue) {
    if (param_info.GetOutputAnalogSignalList().empty()) return;

    try {
        param_uiMinValue = param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MinValue;
        param_uiMaxValue = param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MaxValue;
        param_uiStep = param_info.GetOutputAnalogSignalList().at(0).Value.Step;

        CString strValue;
        bool bValue = false;
        UINT uiValue = 0;

        if (CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputAnalogSignalList().at(0), uiValue, param_info.GetWagoUnitType())) {
            uiValue = AnalogScaleWagoToObject(param_uiMinValue, param_uiMaxValue, uiValue, param_info.GetName(), param_info.GetWagoUnitType());
            /*
            if(param_info.GetOutputAnalogSignalList().at(0).Value.bIsInverted)
            {
                Value = param_info.GetObjectMaxStop() - uiValue;
            }
            else
                Value = uiValue;

            */
			int Value = uiValue;

            strValue.Format("%d", Value);
            param_info.SetValueToBeSet(strValue);
            CDxfLayout::SetValueToBeSet(param_info.GetIndex(), param_info.GetSubIndex(), strValue);
        }
        param_strValue = strValue;
    } catch (std::out_of_range &e) {
        //TRACE("*****CPvcsControlObjectSimplePump2-getspininitinfo*std::out range******");
        XmlLogError("Probable error: Analog Input count is less than Spin box count.");
        throw e;
    } catch (exception &e) {
        //TRACE("*****CPvcsControlObjectSimplePump2-getspininitinfo*std::out range******");
        XmlLogError(e.what());
    }
}




// Function name   : CPvcsControlObjectSimplePump2::GetStatus
// Description     : Get a status
// Return type     : int
// Argument        : const CPvcsControlObjectInfo& param_info

int CPvcsControlObjectSimplePump2::GetStatus(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2) {
    return GetObjStatus(param_info, pSubIndex2);
}

// Function name   : CPvcsControlObjectCargoValve::GetStatus
// Description     : Returns the current status of the control object
// Return type     : int
// Argument        : const CPvcsControlObjectInfo& param_info
int CPvcsControlObjectSimplePump2::GetObjStatus(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2) {
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
        if (pSubIndex2 < int(NumberOfDI)) {
            bool Status = false;
            bool Success = CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputDigitalSignalList().at(pSubIndex2), Status, param_info.GetWagoUnitType());
            if (Status) {
                nStatus = 0;
            } else {
                nStatus = 1;
            }
        } else {
            nStatus = 0;
        }
        break;
    case 100:
    case 101:
    case 102:
    case 103:
    case 104:
    case 105:
    case 106:
    case 107:
    case 108:
    case 109:
    case 110:
        {
            unsigned LocSubIndex2 = pSubIndex2 - 100;
            unsigned NumberOfDO = param_info.GetOutputDigitalSignalList().size();

            if (LocSubIndex2 < NumberOfDO) {
                bool Status = false;
                bool Success = CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetOutputDigitalSignalList().at(LocSubIndex2), Status, param_info.GetWagoUnitType(), CControlWago750::OffsetDigitalOut);
                if (Status) {
                    nStatus = 0;
                } else {
                    nStatus = 1;
                }
            } else {
                nStatus = 0;
            }
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
            nStatus = MAX(nStatus, param_info.GetStatusOr(State));
            nStatus = MAX(nStatus, param_info.GetStatusOrNot(State));
            nStatus = MAX(nStatus, param_info.GetStatusAnd(State));
            nStatus = MAX(nStatus, param_info.GetStatusAndNot(State));
            if (!nStatus) nStatus++;
        }
        break;
    }


    return nStatus;
}


bool CPvcsControlObjectSimplePump2::CheckAlarm(DigitalSignal DigitalInput, CString WagoUnitType) {
    bool Status = false;
    bool Success = CPvcsWagoControl::theWagoUnit().GetValue(DigitalInput, Status, WagoUnitType);
    return Status;
}
