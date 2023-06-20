#include "StdAfx.h"
#include "pvcscontrolobjectinfo.h"
#include ".\PvcsControlObjectPowerPack.h"

#include "pvcswagocontrol.h"
#include "DxfLayout.h"
#include <queue>
#undef MAX
#define MAX(a,b)	((a) > (b) ? (a) : (b))
#undef MIN
#define MIN(a,b)	((a) < (b) ? (a) : (b))

set<int>CPvcsControlObjectPowerPack::AlarmSet;
set<int>CPvcsControlObjectPowerPack::WarningSet;
bool CPvcsControlObjectPowerPack::IsFirstTime = true;
bool CPvcsControlObjectPowerPack::HasErasedAlarms = false;
bool CPvcsControlObjectPowerPack::HasNewAlarms  = false;
bool CPvcsControlObjectPowerPack::HasErasedWarnings = false;
bool CPvcsControlObjectPowerPack::HasNewWarnings  = false;
unsigned CPvcsControlObjectPowerPack::AlarmBits = 0;
unsigned CPvcsControlObjectPowerPack::prevAlarmBits = 0xffffffff;

unsigned CPvcsControlObjectPowerPack::WarningBits = 0;
unsigned CPvcsControlObjectPowerPack::prevWarningBits = 0xffffffff;
vector<DigitalSignal>CPvcsControlObjectPowerPack::DigOp;
// Handle to the timer
HANDLE PowerPackTimer;
extern VOID CALLBACK BVTimerCallback(PVOID, BOOLEAN);

CPvcsControlObjectPowerPack::CPvcsControlObjectPowerPack(void)
    : m_hTimerQ2(CreateTimerQueue()) {
}


CPvcsControlObjectPowerPack::~CPvcsControlObjectPowerPack(void) {
    DeleteTimerQueueEx(m_hTimerQ2, NULL);
	// Don't include the Buzzer silence
	/*
    for (unsigned i = 1; i < DigOp.size(); i++) {
        CPvcsWagoControl::theWagoUnit(false).SetValue(DigOp[i], true);
    }
	*/

}


// The container to queue the timed digital signal off requests
//std::queue<PvcsControlObjectTypes::DigitalSignal> g_DigSigQ;




// Function name   : CPvcsControlObjectPowerPack::GetColor
// Description     : Get the deafault color
// Return type     : const COLORREF&
// Argument        : const CPvcsControlObjectInfo& param_info

const Gdiplus::ARGB& CPvcsControlObjectPowerPack::GetColor(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2) {
    //COLORREF tmpCol = param_info.GetStatusColor(GetStatus(param_info,pSubIndex2),pSubIndex2);
    return param_info.GetStatusColor(GetStatus(param_info, pSubIndex2), pSubIndex2);
//	static Gdiplus::ARGB StatCol = Gdiplus::Color::Red;

//	return StatCol++;

}


// Function name   : CPvcsControlObjectPowerPack::GetInText
// Description     : Get the Intext
// Return type     : const CString&
// Argument        : const CPvcsControlObjectInfo& param_info

const CString& CPvcsControlObjectPowerPack::GetInText(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2) {
    return param_info.GetStatusInText(GetStatus(param_info), pSubIndex2);
}

// Function name   : CPvcsControlObjectBallastPump::GetValueString
// Description     : Not implemented
// Return type     : CString
// Argument        : const CPvcsControlObjectInfo& param_info

CString CPvcsControlObjectPowerPack::GetValueString(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2) {
    CString strValue;
    //bool bValue = false;
    UINT uiValue = 0;

    // The value string is determined as follows:
    // Default: Value = Analog Input%
    try {
        switch (pSubIndex2) {
        case 0:
            if (CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputAnalogSignalList().at(0), uiValue, param_info.GetWagoUnitType())) {
                double InVal = AnalogScaleWagoToObjectD(param_info.GetInputAnalogSignalList().at(0).Value.Limit.MinValue, param_info.GetInputAnalogSignalList().at(0).Value.Limit.MaxValue, uiValue, param_info.GetWagoUnitType());
                if (InVal < 10.0) InVal = 0.0;
                strValue.Format("%4.0f", InVal);
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


// Function name   : CPvcsControlObjectPowerPack::OnButton
// Description     : Not Implemented
// Return type     : bool
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nButton
// Argument        : const bool& param_bIsPressed
#define MAX_DIG_OP  10
bool CPvcsControlObjectPowerPack::OnButton(const CPvcsControlObjectInfo &param_info, const int &param_nButton, const bool &param_bIsPressed) {
    bool bResult = false;
    unsigned PulsDuration = param_info.GetDigitalOutputPulseDuration(param_nButton);
    int NumberOfDigOP = param_info.GetOutputDigitalSignalList().size();
    if (!DigOp.empty()) {
        CDxfLayout::SetControlOperationState(param_info.GetIndex(), param_info.GetSubIndex(), false);

        // If button is pressed
        if (param_bIsPressed) {

            //if output is not of pulse type, then set output to true
            if (PulsDuration == 0) {
                CPvcsWagoControl::theWagoUnit().SetValue(DigOp[param_nButton], false);
                HasNewWarnings = false;
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

                    CreateTimerQueueTimer(&PowerPackTimer, m_hTimerQ2, BVTimerCallback, (PVOID)(ptempInfo),
                                          PulsDuration, 0, WT_EXECUTEINTIMERTHREAD);

                    ASSERT(PowerPackTimer);
                }
                CPvcsWagoControl::theWagoUnit().SetValue(DigOp[param_nButton], true);
                //bResult = CPvcsWagoControl::theWagoUnit().SetValue(param_info.GetOutputDigitalSignalList().at(param_nButton),true);
            } // if( param_info.GetDigitalOutputPulseDuration( param_nButton ) > 0 )
            bResult = true;
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

bool CPvcsControlObjectPowerPack::OnSetSpin(const CPvcsControlObjectInfo &param_info, const int &param_nSpin, const UINT &param_uiValue) {
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

void CPvcsControlObjectPowerPack::GetSpinInitInfo(const CPvcsControlObjectInfo &param_info, UINT &param_uiMinValue, UINT &param_uiMaxValue, UINT &param_uiStep, CString &param_strValue) {
    if (param_info.GetOutputAnalogSignalList().empty()) return;

    try {
        param_uiMinValue = param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MinValue;
        param_uiMaxValue = param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MaxValue;
        param_uiStep = param_info.GetOutputAnalogSignalList().at(0).Value.Step;

        CString strValue;
        bool bValue = false;
        UINT uiValue = 0;
        int Value;

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
            Value = uiValue;
            if (Value < (int)param_info.GetObjectMinStop()) Value = 0;
            if (Value > (int)param_info.GetObjectMaxStop()) Value = 100;

            strValue.Format("%d", Value);
            param_info.SetValueToBeSet(strValue);
            CDxfLayout::SetValueToBeSet(param_info.GetIndex(), param_info.GetSubIndex(), strValue);
        }
        param_strValue = strValue;
    } catch (std::out_of_range &e) {
        //TRACE("*****CPvcsControlObjectPowerPack-getspininitinfo*std::out range******");
        XmlLogError("Probable error: Analog Input count is less than Spin box count.");
        throw e;
    } catch (exception &e) {
        //TRACE("*****CPvcsControlObjectPowerPack-getspininitinfo*std::out range******");
        XmlLogError(e.what());
    }
}




// Function name   : CPvcsControlObjectPowerPack::GetStatus
// Description     : Get a status
// Return type     : int
// Argument        : const CPvcsControlObjectInfo& param_info

int CPvcsControlObjectPowerPack::GetStatus(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2) {
    int ObjStat = GetObjStatus(param_info, pSubIndex2);
    return ObjStat;
}

// Function name   : CPvcsControlObjectCargoValve::GetStatus
// Description     : Returns the current status of the control object
// Return type     : int
// Argument        : const CPvcsControlObjectInfo& param_info
int CPvcsControlObjectPowerPack::GetObjStatus(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2) {
    volatile unsigned nStatus = 0;
    bool bValue = false;
    pair<set<int>::iterator,bool> Ret;

   // bool IsServer = theApp.IsServerMachine();
    if (IsFirstTime) {
        IsFirstTime = false;
        int NumberOfDigOP = param_info.GetOutputDigitalSignalList().size();
        try {
            for (int i = 0; i < NumberOfDigOP; i++) {
                DigOp.push_back(param_info.GetOutputDigitalSignalList().at(i));
            }
        } catch (exception &e) {
            //TRACE("*****CPvcsControlObjectCargoValve2-GetSpinInitInfo*******");
            XmlLogError(e.what());
        }
    }else if ( DigOp.size() >= 3){// The power pack must minimum have 3 outputs
        // Index:
        // 0: Buzzer
        // 1: Common alarm output
        // 2: Common warning output
        if (AlarmBits != prevAlarmBits) {
            prevAlarmBits = AlarmBits;
            if (!AlarmSet.empty()) {
                CPvcsWagoControl::theWagoUnit().SetValue(DigOp[1], true);  // Second output is for Alarm
            }else{
                CPvcsWagoControl::theWagoUnit().SetValue(DigOp[1], false);  // Second output is for Alarm
            }
        }
        if (WarningBits != prevWarningBits) {
            prevWarningBits = WarningBits;
            if (!WarningSet.empty()) {
                if (HasNewWarnings) {
                    CPvcsWagoControl::theWagoUnit().SetValue(DigOp[0], true);  // 0 output is for Warnings, to activate buzzer
                }
                CPvcsWagoControl::theWagoUnit().SetValue(DigOp[2], true);  // Second output is for Warnings
            }else{
                CPvcsWagoControl::theWagoUnit().SetValue(DigOp[2], false);  // Second output is for Warnings
            }
        }
    }
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
        if (pSubIndex2 < int(NumberOfDI)) {
            bool Status = false;
            bool Success = CPvcsWagoControl::theWagoUnit().GetValue(param_info.GetInputDigitalSignalList().at(pSubIndex2), Status, param_info.GetWagoUnitType());
            if (Status) {
                nStatus = 0;
            } else {
                nStatus = 1;
            }
            switch (pSubIndex2) {
            case 0:
            case 1:
                break;
            case 2: // Only these shall activate alarms
            case 3:
            case 5:
            case 6:
                if (!Status) {
                    AlarmSet.erase(pSubIndex2);
                    AlarmBits &= ~(1 <<pSubIndex2 );
                } else {
                    Ret = AlarmSet.insert(pSubIndex2);
                    if (Ret.second) {
                        HasNewAlarms = true;
                        AlarmBits |= 1 << pSubIndex2;
                    }
                }
                break;
            case 4: // Pressure prsent
                break;
            case 7: // Pump1 standby
            case 8: // Pump2 standby
                break;
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
                if (Status) {
                    WarningSet.erase(pSubIndex2);
                    WarningBits &= ~(1 <<pSubIndex2 );
                } else {
                    Ret = WarningSet.insert(pSubIndex2);
                    if (Ret.second) {
                        HasNewWarnings = true;
                        WarningBits |= 1 << pSubIndex2;
                    }
                }
                break;
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
    case 111:
    case 112:
    case 113:
    case 114:
    case 115:
    case 116:
    case 117:
    case 118:
    case 119:
    case 120:
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


bool CPvcsControlObjectPowerPack::CheckAlarm(DigitalSignal DigitalInput, CString WagoUnitType) {
    bool Status = false;
    bool Success = CPvcsWagoControl::theWagoUnit().GetValue(DigitalInput, Status, WagoUnitType);
    return Status;
}
