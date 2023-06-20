#include "StdAfx.h"
#include ".\pvcscontrolobjectinfo.h"
#include ".\pvcs v1.0.h"
#include "pvcsconfiguration.h"
#include ".\emgbuttonoperation.h"


// Function name   : CPvcsControlObjectInfo::CPvcsControlObjectInfo
// Description     : Default constructor
// Return type     :
// Argument        : void

CPvcsControlObjectInfo::CPvcsControlObjectInfo(void)
    : m_iIndex( 0 )
    , m_iSubIndex( 0 )
    , m_iSubIndex2( -1 )
    , m_strName( _T( "No Info" ) )
    , m_strClassName( _T( "No Info" ) )
    , m_strToolTip( _T( "No Info" ) )
    , m_nSpinBox( 0 )
    , m_lTimeOut( 1000 )
    , m_iScreenNumber( -1 )
    , m_bThreadRunning( false )
    , m_bThreadExit( false )
    , m_bThreadExited( true )
    , m_bThreadBusy( false )
    , m_hasPassword( false ) {
    vector<COLORREF> tmpStatusColor;
    vector<CString>  tmpstatusTextIn;
    m_statusColor.push_back( 0 );
    //m_statusColor.push_back( 0xff );
    m_statusTextIn.push_back( _T( "Unknown Status" ) );
    SubStatusColor.push_back( m_statusColor );
    SubStatusTextIn.push_back( m_statusTextIn );
}


// Function name   : CPvcsControlObjectInfo::CPvcsControlObjectInfo
// Description     : Constructor
// Return type     :
// Argument        : const int& param_iIndex
// Argument        : const int& param_iSubIndex

CPvcsControlObjectInfo::CPvcsControlObjectInfo(const int &param_iIndex, const int &param_iSubIndex, const int &param_iSubIndex2)
    : m_iIndex( param_iIndex )
    , m_iSubIndex( param_iSubIndex )
    , m_iSubIndex2( param_iSubIndex2 ) {
    m_iScreenNumber = -1;
}


// Function name   : CPvcsControlObjectInfo::~CPvcsControlObjectInfo
// Description     : Destructor
// Return type     :
// Argument        : void

CPvcsControlObjectInfo::~CPvcsControlObjectInfo(void) {
}


// Function name   : operator<
// Description     : definition for Less than operator,
//					 so that the objects can be stored in STL set
// Return type     : bool
// Argument        : const CPvcsControlObjectInfo& lhsInfo
// Argument        : const CPvcsControlObjectInfo& rhsInfo

bool operator<(const CPvcsControlObjectInfo &lhsInfo, const CPvcsControlObjectInfo &rhsInfo) {
    if (( lhsInfo.GetSubIndex2() == -1 ) && ( lhsInfo.GetSubIndex2() == -1 )) {
        return lhsInfo.GetIndex() == rhsInfo.GetIndex() ?
               lhsInfo.GetSubIndex() < rhsInfo.GetSubIndex()
               : lhsInfo.GetIndex() < rhsInfo.GetIndex();
    } else {
        // EHSMark Possible bug!
        return lhsInfo.GetSubIndex2() < rhsInfo.GetSubIndex2();
    }
}


// Function name   : CPvcsControlObjectInfo::LoadInfo
// Description     : Loads the information about the corresponding object
// Return type     : bool
// Argument        : const int& param_iIndex
// Argument        : const int& param_iSubIndex

bool CPvcsControlObjectInfo::LoadInfo(const int &param_iIndex, const int &param_iSubIndex, const int& param_iSubIndex2) {
    bool           bSuccess        = false;
    using namespace PvcsControlObjectTypes;

    CObjectDetails objObjectDetail;
    CConvertData   obj_ConvertData;

    m_iIndex     = param_iIndex;
    m_iSubIndex  = param_iSubIndex;
    m_iSubIndex2 = param_iSubIndex2;

    // Load the configuration file
    if (objObjectDetail.LoadXMLFile( XML_OBJECT_CONFIGURATION_FILE )
        && objObjectDetail.LocateTank( param_iIndex, param_iSubIndex )) {

        m_strName = objObjectDetail.GetObjectName( obj_ConvertData.IntToCStr( param_iIndex ), obj_ConvertData.IntToCStr( param_iSubIndex ) );

        WagoUnitType = objObjectDetail.ReadWagoUnitType( param_iIndex, param_iSubIndex );
        m_lTimeBetweenPulses = objObjectDetail.GetTimeBetweenPulses( param_iIndex, param_iSubIndex );
        m_iPercentageToStop = objObjectDetail.GetPercentagetoStop( param_iIndex, param_iSubIndex );

        CString strTipRef = objObjectDetail.GetToolTipRef( param_iIndex, param_iSubIndex );
        CString strTipTxt = objObjectDetail.GetToolTipText( param_iIndex, param_iSubIndex );


        UINT tmp_iObjectStopCount = objObjectDetail.GetObjectStopCount( param_iIndex, param_iSubIndex );
		if (tmp_iObjectStopCount ) {
			for (UINT i=0; i < tmp_iObjectStopCount; i++) {
				UINT tmp_iObjectMinStop = objObjectDetail.GetObjectMinStop(param_iIndex, param_iSubIndex, i);
				UINT tmp_iObjectMaxStop = objObjectDetail.GetObjectMaxStop( param_iIndex, param_iSubIndex, i);
				m_iObjectMinStop.push_back(tmp_iObjectMinStop);
				m_iObjectMaxStop.push_back(tmp_iObjectMaxStop);
			}
		} else {
			UINT tmp_iObjectMinStop = objObjectDetail.GetObjectMinStop(param_iIndex, param_iSubIndex);
			UINT tmp_iObjectMaxStop = objObjectDetail.GetObjectMaxStop( param_iIndex, param_iSubIndex );
			m_iObjectMinStop.push_back(tmp_iObjectMinStop);
			m_iObjectMaxStop.push_back(tmp_iObjectMaxStop);
		}
        if (!strTipRef.IsEmpty()  && !strTipTxt.IsEmpty()) m_strToolTip.Format( "%s - %s", strTipRef, strTipTxt );

        m_strClassName = objObjectDetail.GetObjControllerClass( param_iIndex, param_iSubIndex );
        m_strStatusTextOut = objObjectDetail.GetOutputStatusText( param_iIndex, param_iSubIndex );


        CString TankName = theConfiguration().GetTankName( param_iIndex );

        //Code for emergency button information

        //if their is any emergency button
        if (!CEmgButtonOperation::m_EmgButtonInfo.empty()) {

            UINT uiEmgButtonCount = CEmgButtonOperation::m_EmgButtonInfo.size();

            for (unsigned i = 0; i < uiEmgButtonCount; i++) {
                int     iActionOfButton = -1;
                CString strEmgAction    = "";
                strEmgAction = objObjectDetail.GetEmgAction( param_iIndex, param_iSubIndex, i );

                //if Action defined in the control for the particular (i) button
                if (!strEmgAction.IsEmpty()) {
                    strEmgAction.TrimLeft( "ObjButtonText" );
                    iActionOfButton = atoi( strEmgAction );

                    CString EmgActionOfButton = "";
                    EmgActionOfButton = objObjectDetail.GetButtonText( param_iIndex, param_iSubIndex, iActionOfButton );

                    if (EmgActionOfButton != " ") {
                        CEmgButtonOperation::m_EmgButtonInfo[i]->iTotalOperation++;

                        CEmgButtonOperation::ControlInfo *pControlInfo;
                        pControlInfo =  new CEmgButtonOperation::ControlInfo;

                        pControlInfo->strControlName = m_strName;
                        pControlInfo->uiControlIndex = param_iIndex;
                        pControlInfo->uiControlSubIndex = param_iSubIndex;
                        pControlInfo->uiActionOfButton = iActionOfButton;
                        pControlInfo->Next_ControlInfo = NULL;

                        CEmgButtonOperation::ControlInfo *pTempControlInfo;
                        pTempControlInfo = CEmgButtonOperation::m_EmgButtonInfo[i]->Next_ControlInfo;

                        //for the first entry into the vector
                        if (pTempControlInfo == NULL) {
                            CEmgButtonOperation::m_EmgButtonInfo[i]->Next_ControlInfo = pControlInfo;
                        } else {
                            bool IsInsertEntry = false;
                            //Traverse the list, while not reach to the last node
                            while (pTempControlInfo->Next_ControlInfo != NULL) {
                                //if already having entry about the control, then do not insert it.
                                if (int( pTempControlInfo->uiControlIndex ) == param_iIndex && int( pTempControlInfo->uiControlSubIndex ) == param_iSubIndex) break;

                                pTempControlInfo = pTempControlInfo->Next_ControlInfo;
                            }

                            //if already having entry about the control, then do not insert it.
                            if (int( pTempControlInfo->uiControlIndex ) == param_iIndex && int( pTempControlInfo->uiControlSubIndex ) == param_iSubIndex) IsInsertEntry = false;
                            else IsInsertEntry = true;

                            if (IsInsertEntry) pTempControlInfo->Next_ControlInfo = pControlInfo;
                            else { //delete the control information pointer
                                CEmgButtonOperation::m_EmgButtonInfo[i]->iTotalOperation--;
                                delete pControlInfo;
                                pControlInfo = NULL;
                            }
                        }
                    }
                }
            }
        }


        //Code for emergency button information

        int                               TotalInputCount     = 0;
        int                               TotalOutputCount    = 0;

        CCalibrateChannels::CalibrateData *objCalibrationData;

        objCalibrationData = new CCalibrateChannels::CalibrateData;

        objCalibrationData->ObjectName = m_strName;
        objCalibrationData->ObjectToolTip = m_strToolTip;
        objCalibrationData->TankName = TankName;
        objCalibrationData->WagoUnitType = objObjectDetail.ReadWagoUnitType( param_iIndex, param_iSubIndex );
        objCalibrationData->StartText = "0";
        objCalibrationData->StopText = "0";
        objCalibrationData->ptrStartListButton = NULL;
        objCalibrationData->ptrStopListButton = NULL;
        objCalibrationData->StartButtonClicked = false;
        objCalibrationData->uiControlIndex = param_iIndex;
        objCalibrationData->uiControlSubIndex = param_iSubIndex;

        TotalInputCount = objObjectDetail.GetTotalInputCount( param_iIndex, param_iSubIndex );

        for (int j = 0; j < TotalInputCount; j++) {
            objCalibrationData->Channel = objObjectDetail.GetWagoInputChannel( param_iIndex, param_iSubIndex, j );
            objCalibrationData->Type = objObjectDetail.GetObjectInputType( param_iIndex, param_iSubIndex, j );
            objCalibrationData->WagoUnitNumber = objObjectDetail.GetObjectInputWagoUnitNumber( param_iIndex, param_iSubIndex, j );
            CCalibrateChannels::m_CalibrationData.push_back( *objCalibrationData );
        }

        TotalOutputCount = objObjectDetail.GetTotalOutputCount( param_iIndex, param_iSubIndex );

        for (int j = 0; j < TotalOutputCount; j++) {
			CString tmpStr = objObjectDetail.GetWagoOutputChannel( param_iIndex, param_iSubIndex, j );
            objCalibrationData->Channel = objObjectDetail.GetWagoOutputChannel( param_iIndex, param_iSubIndex, j );
            objCalibrationData->Type = objObjectDetail.GetObjectOutputType( param_iIndex, param_iSubIndex, j );
            objCalibrationData->WagoUnitNumber = objObjectDetail.GetObjectOutputWagoUnitNumber( param_iIndex, param_iSubIndex, j );
            CCalibrateChannels::m_CalibrationData.push_back( *objCalibrationData );
        }

        if (TotalInputCount == 0 && TotalOutputCount == 0) {
            objCalibrationData->Channel = "Not Controlled";
            objCalibrationData->Type = "Not Controlled";
            objCalibrationData->WagoUnitNumber = "Not Controlled";
            CCalibrateChannels::m_CalibrationData.push_back( *objCalibrationData );
        }

        delete objCalibrationData;

        int nCount, i;

        // Get the timeout value
        m_lTimeOut = objObjectDetail.GetObjectTimeout( param_iIndex, param_iSubIndex );

        // Get number of buttons
        nCount = objObjectDetail.GetButtonCount( param_iIndex, param_iSubIndex );

        for (i = 0; i < nCount; i++) m_strButtonCaption.push_back( objObjectDetail.GetButtonText( param_iIndex, param_iSubIndex, i + 1 ) );

        // Get number of spin boxes
        m_nSpinBox    = objObjectDetail.GetObjSpinCount( param_iIndex, param_iSubIndex );
        // Get info about password
        m_hasPassword = objObjectDetail.GetPassword( param_iIndex, param_iSubIndex );

        // Get the input status text and color
        nCount = objObjectDetail.GetInputStatusTextCount( param_iIndex, param_iSubIndex );

        for (i = 0; i < nCount; i++) {
            m_statusTextIn.push_back( objObjectDetail.GetStatusTextInput( param_iIndex, param_iSubIndex, i ) );

            CString  strtemp   = objObjectDetail.GetStatusColor( param_iIndex, param_iSubIndex, i );

            COLORREF tempColor;
            if (strtemp != "") sscanf_s( strtemp, "%x", &tempColor );
            else tempColor = RGB( 255, 255, 255 );

            m_statusColor.push_back( tempColor );
            StatusOr.push_back( objObjectDetail.GetObjectStatusOr( param_iIndex, param_iSubIndex, i ) );
            StatusOrNot.push_back( objObjectDetail.GetObjectStatusOrNot( param_iIndex, param_iSubIndex, i ) );
            StatusAnd.push_back( objObjectDetail.GetObjectStatusAnd( param_iIndex, param_iSubIndex, i ) );
            StatusAndNot.push_back( objObjectDetail.GetObjectStatusAndNot( param_iIndex, param_iSubIndex, i ) );
        } // for(i=0; i<nCount; i++)



        // Get the input status text and color for sub-elements
        int nCount2 = objObjectDetail.GetSubStatusCount( param_iIndex, param_iSubIndex );
        for (i = 0; i < nCount2; i++) {
            vector<CString>  tmpSubStatusText;
            vector<COLORREF> tmpStatusColor;
            for (int j = 0; j < 2; j++) {
                tmpSubStatusText.push_back( objObjectDetail.GetStatusTextInput( param_iIndex, param_iSubIndex, i, j ) );

                CString  strtemp   = objObjectDetail.GetStatusColor( param_iIndex, param_iSubIndex, i, j );

                COLORREF tempColor;
				if ( !strtemp.IsEmpty() ) {
					sscanf_s(strtemp, "%x", &tempColor);
				}
				else {
					tempColor = RGB(255, 255, 255);
				}

                tmpStatusColor.push_back( tempColor );
            }
            SubStatusTextIn.push_back( tmpSubStatusText );
            SubStatusColor.push_back( tmpStatusColor );
        } // for(i=0; i<nCount2; i++)

        // Get the input channels
        nCount = objObjectDetail.GetObjectInputCount( param_iIndex, param_iSubIndex );

        for (i = 0; i < nCount; i++) {
            int iConnType = objObjectDetail.GetInputConnType( param_iIndex, param_iSubIndex, i );
            switch (iConnType) {
            case INP_DIGITAL : // Digital input
                {
                    DigitalSignal tempDigitalSignal;

                    tempDigitalSignal.Port.WagoUnit    = objObjectDetail.GetObjectInputWagoUint( param_iIndex, param_iSubIndex, i );
                    tempDigitalSignal.Port.WagoChannel = objObjectDetail.GetInputChannel( param_iIndex, param_iSubIndex, i );
                    tempDigitalSignal.IsInverted       = objObjectDetail.GetInputInvert( param_iIndex, param_iSubIndex, i );
                    tempDigitalSignal.BitNo            = -1;
                    m_sigDigitalInput.push_back( tempDigitalSignal );
                }
                break;
            case INP_DIG_REG:
                {
                    DigitalSignal tempDigitalSignal;

                    tempDigitalSignal.Port.WagoUnit    = objObjectDetail.GetObjectInputWagoUint( param_iIndex, param_iSubIndex, i );
                    tempDigitalSignal.Port.WagoChannel = objObjectDetail.GetInputChannel( param_iIndex, param_iSubIndex, i, &tempDigitalSignal.BitNo );
                    tempDigitalSignal.IsInverted       = objObjectDetail.GetInputInvert( param_iIndex, param_iSubIndex, i );
                    m_sigDigitalInput.push_back( tempDigitalSignal );
                }
                break;
            case INP_ANALOG: // Analog input
                {
                    AnalogSignal tempAnalogSignal;

                    tempAnalogSignal.Port.WagoUnit        = objObjectDetail.GetObjectInputWagoUint( param_iIndex, param_iSubIndex, i );
                    tempAnalogSignal.Port.WagoChannel     = objObjectDetail.GetInputChannel( param_iIndex, param_iSubIndex, i );
                    tempAnalogSignal.Value.Limit.MinValue = objObjectDetail.GetAnalogIObjMinValue( param_iIndex, param_iSubIndex, i );
                    tempAnalogSignal.Value.Limit.MaxValue = objObjectDetail.GetAnalogIObjMaxValue( param_iIndex, param_iSubIndex, i );
                    tempAnalogSignal.Value.Step           = objObjectDetail.GetAnalogIObjSteps( param_iIndex, param_iSubIndex, i );
                    //This invert for Throttle Valve only for Wago uint 461
                    if (atoi( WagoUnitType ) == 461) tempAnalogSignal.Value.IsInverted = objObjectDetail.GetInputInvert( param_iIndex, param_iSubIndex, i );
                    else tempAnalogSignal.Value.IsInverted = false;

                    m_sigAnalogInput.push_back( tempAnalogSignal );
                }
                break;
            }
        } // for(i=0; i<nCount; i++)

        // Get the output channels
        nCount = objObjectDetail.GetObjectOutputCount( param_iIndex, param_iSubIndex );

        for (i = 0; i < nCount; i++) {
            int iConnType = objObjectDetail.GetOutputConnType( param_iIndex, param_iSubIndex, i );
            switch (iConnType) {
            case INP_DIGITAL:
                {
                    // Digital output
                    DigitalSignal tempDigitalSignal;

                    tempDigitalSignal.Port.WagoUnit    = objObjectDetail.GetObjectOutputWagoUint( param_iIndex, param_iSubIndex, i );
                    tempDigitalSignal.Port.WagoChannel = objObjectDetail.GetOutputChannel( param_iIndex, param_iSubIndex, i );
                    tempDigitalSignal.IsInverted       = objObjectDetail.GetOutputInvert( param_iIndex, param_iSubIndex, i );
                    tempDigitalSignal.BitNo            = -1;

                    m_sigDigitalOutput.push_back( tempDigitalSignal );
                    m_uiPulseDuration.push_back( objObjectDetail.GetOutputPluse( param_iIndex, param_iSubIndex, i ) );
                    m_ButtonExtraFunction.push_back( objObjectDetail.GetOutputFunction( param_iIndex, param_iSubIndex, i ) );
                    
                }
                break;
            case INP_DIG_REG:
                {
                    // Digital output
                    DigitalSignal tempDigitalSignal;

                    tempDigitalSignal.Port.WagoUnit    = objObjectDetail.GetObjectOutputWagoUint( param_iIndex, param_iSubIndex, i );
                    tempDigitalSignal.Port.WagoChannel = objObjectDetail.GetOutputChannel( param_iIndex, param_iSubIndex, i, &tempDigitalSignal.BitNo );
                    tempDigitalSignal.IsInverted       = objObjectDetail.GetOutputInvert( param_iIndex, param_iSubIndex, i );

                    m_sigDigitalOutput.push_back( tempDigitalSignal );
                    m_uiPulseDuration.push_back( objObjectDetail.GetOutputPluse( param_iIndex, param_iSubIndex, i ) );
                    m_ButtonExtraFunction.push_back( objObjectDetail.GetOutputFunction( param_iIndex, param_iSubIndex, i ) );
                }
                break;
            case INP_ANALOG:
                {
                    // Analog output
                    AnalogSignal tempAnalogSignal;

                    tempAnalogSignal.Port.WagoUnit        = objObjectDetail.GetObjectOutputWagoUint( param_iIndex, param_iSubIndex, i );
                    tempAnalogSignal.Port.WagoChannel     = objObjectDetail.GetOutputChannel( param_iIndex, param_iSubIndex, i );
                    tempAnalogSignal.Value.Limit.MinValue = objObjectDetail.GetAnalogObjMinValue( param_iIndex, param_iSubIndex, i );
                    tempAnalogSignal.Value.Limit.MaxValue = objObjectDetail.GetAnalogObjMaxValue( param_iIndex, param_iSubIndex, i );
                    tempAnalogSignal.Value.Step           = objObjectDetail.GetAnalogObjSteps( param_iIndex, param_iSubIndex, i );

                    m_sigAnalogOutput.push_back( tempAnalogSignal );
                }
                break;
            }
        } // for(i=0; i<nCount; i++)


        // Now make this a valid container
        MakeValid();
        bSuccess = true;
    }

    return bSuccess;
}


// Function name   : CPvcsControlObjectInfo::GetName
// Description     : Returns the Name of object
// Return type     : const CString&
// Argument        : void

const CString& CPvcsControlObjectInfo::GetName(void) const {
    return m_strName;
}


// Function name   : CPvcsControlObjectInfo::GetIndex
// Description     : Returns the Index of Object
// Return type     : const int&
// Argument        : void

const int& CPvcsControlObjectInfo::GetIndex(void) const {
    return m_iIndex;
}


// Function name   : CPvcsControlObjectInfo::GetSubIndex
// Description     : Returns the SubIndex of object
// Return type     : const int&
// Argument        : void

const int& CPvcsControlObjectInfo::GetSubIndex(void) const {
    return m_iSubIndex;
}
// Function name   : CPvcsControlObjectInfo::GetSubIndex
// Description     : Returns the second SubIndex of object
// Return type     : const int&
// Argument        : void

const int& CPvcsControlObjectInfo::GetSubIndex2(void) const {
    return m_iSubIndex2;
}


// Function name   : CPvcsControlObjectInfo::GetToolTip
// Description     : Gets the Tool-tip string for the object
// Return type     : const CString&
// Argument        : void

const CString& CPvcsControlObjectInfo::GetToolTip(void) const {
    return m_strToolTip;
}



// Function name   : CPvcsControlObjectInfo::GetClassName
// Description     : Retrives the controlller class name
// Return type     : const CString&
// Argument        : void

const CString& CPvcsControlObjectInfo::GetClassName(void) const {
    return m_strClassName;
}


// Function name   : CPvcsControlObjectInfo::GetStatusColor
// Description     : Retrieves the status color
// Return type     : const COLORREF&
// Argument        : const UINT& param_nStatus

const Gdiplus::ARGB& CPvcsControlObjectInfo::GetStatusColor(const UINT &param_nStatus, int SubIndex2) const {
    //volatile Gdiplus::ARGB StatCol2;
    static Gdiplus::ARGB StatCol;
    if (SubIndex2 != -1) {
        SubIndex2++;

		if (SubIndex2 < int(SubStatusColor.size()) && param_nStatus < SubStatusColor[SubIndex2].size()) {
			StatCol = SubStatusColor[SubIndex2][param_nStatus];
		}
        else {
            if (SubIndex2 >= 100) {
                SubIndex2 -= 100;
                if (param_nStatus) {
                    StatCol = 0x008000;
                } else {
                    StatCol = Gdiplus::ARGB( Gdiplus::Color::Red );
                }
            } else {
                StatCol = SubStatusColor[0][0];
                //StatCol = AFX_IDC_COLOR_MAGENTA;
            }
        }
    } else {
        if (param_nStatus < m_statusColor.size()) StatCol = m_statusColor[param_nStatus];
        else StatCol = m_statusColor[0];
    }
    //StatCol2 = StatCol;
    return StatCol;

}


// Function name   : CPvcsControlObjectInfo::GetStatusInText
// Description     : Retrieves the object intext
// Return type     : const CString&
// Argument        : const UINT& param_nStatus

const CString& CPvcsControlObjectInfo::GetStatusInText(const UINT &param_nStatus, int SubIndex2) const {
    if (SubIndex2 != -1) {
        SubIndex2++;
        if (SubIndex2 < int( SubStatusTextIn.size() ) && param_nStatus < int( SubStatusTextIn[SubIndex2].size() )) return SubStatusTextIn[SubIndex2][param_nStatus];
        else return SubStatusTextIn[0][0];
    } else {
        if (param_nStatus < m_statusTextIn.size()) return m_statusTextIn[param_nStatus];
        else return m_statusTextIn[0];
    }

}



// Function name   : CPvcsControlObjectInfo::GetOutputAnalogSignalList
// Description     : Retrieves the analog outputs
// Return type     : const PvcsControlObjectTypes::AnalogSignalList& 
// Argument        : void

const PvcsControlObjectTypes::AnalogSignalList& CPvcsControlObjectInfo::GetOutputAnalogSignalList(void) const {
    return m_sigAnalogOutput;
}


// Function name   : CPvcsControlObjectInfo::GetInputAnalogSignalList
// Description     : Retrieves the analog inputs
// Return type     : const PvcsControlObjectTypes::AnalogSignalList&
// Argument        : void

const PvcsControlObjectTypes::AnalogSignalList& CPvcsControlObjectInfo::GetInputAnalogSignalList(void) const {
    return m_sigAnalogInput;
}


// Function name   : CPvcsControlObjectInfo::GetInputDigitalSignalList
// Description     : Retrieves the digital inputs
// Return type     : const PvcsControlObjectTypes::DigitalSignalList&
// Argument        : void

const PvcsControlObjectTypes::DigitalSignalList& CPvcsControlObjectInfo::GetInputDigitalSignalList(void) const {
    return m_sigDigitalInput;
}


// Function name   : CPvcsControlObjectInfo::GetOutputDigitalSignalList
// Description     : Retrieves the digital outputs
// Return type     : const PvcsControlObjectTypes::DigitalSignalList&
// Argument        : void

const PvcsControlObjectTypes::DigitalSignalList& CPvcsControlObjectInfo::GetOutputDigitalSignalList(void) const {
    return m_sigDigitalOutput;
}


// Function name   : CPvcsControlObjectInfo::GetNumberOfButtons
// Description     : Retrieves the number of buttons
// Return type     : const UINT
// Argument        : void

const UINT CPvcsControlObjectInfo::GetNumberOfButtons(void) const {
    // The number of buttons will be equal to the number of button captions
    return(UINT)m_strButtonCaption.size();
}


// Function name   : CPvcsControlObjectInfo::GetButtonCaption
// Description     : Retrieves the button caption
// Return type     : const CString&
// Argument        : const UINT& param_nIndex

const CString& CPvcsControlObjectInfo::GetButtonCaption(const UINT &param_nIndex) const {
    return m_strButtonCaption.at( param_nIndex );
}


// Function name   : CPvcsControlObjectInfo::GetNumberOfSpinBox
// Description     : Retrieves the number of spin box controls
// Return type     : const UINT
// Argument        : void

const UINT CPvcsControlObjectInfo::GetNumberOfSpinBox(void) {
    return m_nSpinBox;
}

// Function name   : CPvcsControlObjectInfo::GetNumberOfSpinBox
// Description     : Retrieves the number of spin box controls
// Return type     : const UINT
// Argument        : void

const bool CPvcsControlObjectInfo::GetPassword(void) {
    return m_hasPassword;
}



// Function name   : CPvcsControlObjectInfo::GetStatusCount
// Description     : Retrieves the nimber of status of the object
// Return type     : UINT
// Argument        : void

UINT CPvcsControlObjectInfo::GetStatusCount(void) const {
    return(UINT)m_statusTextIn.size();
}


// Function name   : CPvcsControlObjectInfo::GetOutText
// Description     : Retrieves the out text
// Return type     : const CString&
// Argument        : void

const CString& CPvcsControlObjectInfo::GetOutText(void) const {
    return m_strStatusTextOut;
}


// Function name   : CPvcsControlObjectInfo::GetDigitalOutputPulseDuration
// Description     : Retrieves the pulse duration
// Return type     : const UINT&
// Argument        : const UINT& param_nIndex

const UINT& CPvcsControlObjectInfo::GetDigitalOutputPulseDuration(const UINT &param_nIndex) const {
    return m_uiPulseDuration.at( param_nIndex );
}
// Function name   : CPvcsControlObjectInfo::GetDigitalOutputExtraFunction
// Description     : Retrieves the extra function if any is defined
// Return type     : const UINT&
// Argument        : const UINT& param_nIndex

const int CPvcsControlObjectInfo::GetDigitalOutputExtraFunction(const UINT &param_nIndex) const {
    return m_ButtonExtraFunction.at( param_nIndex );
}


// Function name   : CPvcsControlObjectInfo::GetTimeOut
// Description     : Retrieves the time out duration for the control object
// Return type     : const long&
// Argument        : void

const long& CPvcsControlObjectInfo::GetTimeOut(void) const {
    return m_lTimeOut;
}
// Function name   : CPvcsControlObjectInfo::GetTimeOut
// Description     : Retrieves the screen number to which control object belongs
// Return type     : int
// Argument        : void

int CPvcsControlObjectInfo::GetScreenNumber(void) const {
    return m_iScreenNumber;
}

// Function name   : CPvcsControlObjectInfo::GetTimeOut
// Description     : Set the screen number to which control object belongs
// Return type     : void
// Argument        : int

void CPvcsControlObjectInfo::SetScreenNumber(int ScreenNumber) const {
    m_iScreenNumber = ScreenNumber;
}
// , to get percentage to stop for throttle valve
int CPvcsControlObjectInfo::GetPercentagetoStop(void) {
    return m_iPercentageToStop;
}

// , to get time between pulses for throttle valve
long CPvcsControlObjectInfo::GetTimeBetweenPulses(void) {
    return m_lTimeBetweenPulses;
}

CString CPvcsControlObjectInfo::GetWagoUnitType(void) const {
    return WagoUnitType;

}

//Function to get wanted value to be set
CString CPvcsControlObjectInfo::GetValueToBeSet(void) const {
    return m_strValueToBeSet;
}

//Function to set new value to be set or wanted by the user
void CPvcsControlObjectInfo::SetValueToBeSet(CString pstrValuetoset) const {
    m_strValueToBeSet = pstrValuetoset;
}

void CPvcsControlObjectInfo::SetThreadRunningState(bool pState) const {
    m_bThreadRunning = pState;
}

void CPvcsControlObjectInfo::SetThreadExitState(bool pState) const {
    m_bThreadExit = pState;
}

void CPvcsControlObjectInfo::SetThreadExitedState(bool pState) const {
    m_bThreadExited = pState;
}

void CPvcsControlObjectInfo::SetThreadBusyState(bool pState) const {
    m_bThreadBusy = pState;
}

bool CPvcsControlObjectInfo::GetThreadRunningState(void) const {
    return m_bThreadRunning;
}

bool CPvcsControlObjectInfo::GetThreadExitState(void) const {
    return m_bThreadExit;
}

bool CPvcsControlObjectInfo::GetThreadExitedState(void) const {
    return m_bThreadExited;
}

bool CPvcsControlObjectInfo::GetThreadBusyState(void) const {
    return m_bThreadBusy;
}

UINT CPvcsControlObjectInfo::GetObjectMinStop(int SubIndex2) const {
    return m_iObjectMinStop[SubIndex2];
}

UINT CPvcsControlObjectInfo::GetObjectMaxStop(int SubIndex2) const {
    return m_iObjectMaxStop[SubIndex2];
}


bool CPvcsControlObjectInfo::GetTimeOutState(void) const {
    return m_bTimeOutState;
}

void CPvcsControlObjectInfo::SetTimeOutState(bool pState) const {
    m_bTimeOutState = pState;
}

void CPvcsControlObjectInfo::SetControlOperationState(bool bState) const {
    m_bIsOperationOver = bState;
}

bool CPvcsControlObjectInfo::GetControlOperationState(void) const {
    return m_bIsOperationOver;
}

UINT CPvcsControlObjectInfo::GetStatusOr(UINT State) const {
    UINT tmpState = 0;
    for (unsigned i = 0; i < StatusOr.size(); i++) {
        if (StatusOr.at( i ) & State) {
            tmpState = i + 1;
        }
    }
    return tmpState;
}

UINT CPvcsControlObjectInfo::GetStatusOrNot(UINT State) const {
    UINT tmpState = 0;
    for (unsigned i = 0; i < StatusOrNot.size(); i++) {
        if (StatusOrNot.at( i ) & ~State) {
            tmpState = i + 1;
        }
    }
    return tmpState;
}

UINT CPvcsControlObjectInfo::GetStatusAnd(UINT State, int Index) const {
    UINT tmpState = 0;
	if (Index >= 0) {
		if (unsigned(Index) < StatusAnd.size()) {
            tmpState = State & StatusAnd.at( Index );
		}
	} else {
        for (unsigned i = 0; i < StatusAnd.size(); i++) {
            if (!( StatusAnd.at( i ) ^ State )) {
                tmpState = i + 1;
            }
        }
    }
    return tmpState;
}

UINT CPvcsControlObjectInfo::GetStatusAndNot(UINT State) const {
    UINT tmpState = 0;
    for (unsigned i = 0; i < StatusAndNot.size(); i++) {
        if (!( StatusAnd.at( i ) ^ ~State )) {
            tmpState = i + 1;
        }
    }
    return tmpState;
}


