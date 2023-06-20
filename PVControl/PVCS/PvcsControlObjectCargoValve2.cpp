#include "StdAfx.h"
#include ".\pvcscontrolobjectcargovalve2.h"
#include "pvcsobjectcontroldlg.h"
#include "pvcscontrolobjecttimeoutinfo.h"
#include "pvcswagocontrol.h"
#include <time.h>
#include ".\pvcs v1.0.h"
#include "DxfLayout.h"

//global var


// Function name   : CPvcsControlObjectCargoValve2::~CPvcsControlObjectCargoValve2
// Description     : Destructor
// Return type     :
// Argument        : void

CPvcsControlObjectCargoValve2::~CPvcsControlObjectCargoValve2(void) {
}


// Function name   : CPvcsControlObjectCargoValve2::GetStatus
// Description     : Returns the current status of the control object
// Return type     : int
// Argument        : const CPvcsControlObjectInfo& param_info

int CPvcsControlObjectCargoValve2::GetStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2) {
	int nStatus = 0;
	bool bValue = false;

	// The status is determined as follows:
	// Digital input 1 true: Status = 1
	// Digital input 2 true: Status = 2
	// Digital input 1 false and 2 false: Status = 4
	// Digital input 1 true and 2 true: Status = 3

	if ( param_info.GetInputDigitalSignalList().size() > 1 ) {
		if ( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 0 ), bValue ,param_info.GetWagoUnitType()) ) {
			if ( bValue )
				nStatus = 1;

			if ( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 1 ), bValue ,param_info.GetWagoUnitType()) ) {
				if ( bValue )
					nStatus |= 2;

				if ( !nStatus ) {
					nStatus = 4;
				} // switch( nStatus )

			}// if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 1 ), bValue ) )

		} // if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( 0 ), bValue ) )

	} // if( param_info.GetInputDigitalSignalList().size() > 1 )

	return nStatus;
}


// Function name   : CPvcsControlObjectCargoValve2::GetColor
// Description     : Returns the object color corresponding to the current status
// Return type     : const COLORREF&
// Argument        : const CPvcsControlObjectInfo& param_info

const Gdiplus::ARGB& CPvcsControlObjectCargoValve2::GetColor(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2) {
    return param_info.GetStatusColor(GetStatus(param_info));
}


// Function name   : CPvcsControlObjectCargoValve2::GetInText
// Description     : Returns the Intext corresponding to the current status
// Return type     : const CString&
// Argument        : const CPvcsControlObjectInfo& param_info

const CString& CPvcsControlObjectCargoValve2::GetInText(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2) {
    return param_info.GetStatusInText( GetStatus( param_info ) );
}


// Function name   : CPvcsControlObjectCargoValve2::GetValueString
// Description     : Returns the value string to be displayed
// Return type     : CString
// Argument        : const CPvcsControlObjectInfo& param_info
#pragma warning (disable: 4101)
CString CPvcsControlObjectCargoValve2::GetValueString(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2) {
    CString strValue;
    bool bValue = false;
    UINT uiValue = 0;

	DigitalSignal DigOp1, DigOp2;
    DigitalSignal DigIp1, DigIp2;
    AnalogSignal AnaIp1,AnaIp2;
    AnalogSignal AnaOp1,AnaOp2;
    try{
        //DigOp1  = param_info.GetOutputDigitalSignalList().at( 0 );
        //DigOp2  = param_info.GetOutputDigitalSignalList().at( 1 );
        DigIp1  = param_info.GetInputDigitalSignalList().at( 0 );
        DigIp2  = param_info.GetInputDigitalSignalList().at( 1 );
        AnaIp1  = param_info.GetInputAnalogSignalList().at( 0 );
        AnaOp1  = param_info.GetOutputAnalogSignalList().at( 0 );
        //AnaIp1  = param_info.GetInputAnalogSignalList().at( 0 );
    }
    catch( exception &e )
    {
        //TRACE("*****CPvcsControlObjectCargoValve2-GetValueString*******");
        XmlLogError( e.what() );
        return false;
    }


    // The value string is determined as follows:
    // Digital input 1 true: Value = Max%
    // Digital input 2 true: Value = Min%
    // Default: Value = Analog Input%
    try {
        if ( CPvcsWagoControl::theWagoUnit().GetValue( DigIp1, bValue,param_info.GetWagoUnitType() ) && bValue )
            strValue.Format("%d %%", AnaIp1.Value.Limit.MaxValue );
        else if ( CPvcsWagoControl::theWagoUnit().GetValue( DigIp2, bValue,param_info.GetWagoUnitType() ) && bValue )
            strValue.Format("%d %%", AnaIp1.Value.Limit.MinValue );
        else if ( CPvcsWagoControl::theWagoUnit().GetValue( AnaIp1, uiValue,param_info.GetWagoUnitType() ) )
            strValue.Format("%d %%", AnalogScaleWagoToObject(AnaIp1.Value.Limit.MinValue, AnaIp1.Value.Limit.MaxValue, uiValue,param_info.GetName(),param_info.GetWagoUnitType()) );
    } catch ( std::out_of_range &e ) {
        //TRACE("*******pvcscontrolobjectcargovale-getvaluestring* error - std::out range****");
        XmlLogError( "Probable error: Input signal count is mismatched in config." );
        throw e;
    } catch ( exception &e ) {
        //TRACE("*******pvcscontrolobjectcargovale-getvaluestring*****");
        XmlLogError( e.what() );
    }
    return strValue;
}


// Function name   : CPvcsControlObjectCargoValve2::OnButton
// Description     : Not Implemented
// Return type     : bool
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nButton
// Argument        : const bool& param_bIsPressed

bool CPvcsControlObjectCargoValve2::OnButton(const CPvcsControlObjectInfo& param_info, const int& param_nButton, const bool& param_bIsPressed) {
    bool bResult = true;

    if ( param_bIsPressed && !param_info.GetInputAnalogSignalList().empty() && !param_info.GetOutputAnalogSignalList().empty() && param_info.GetInputDigitalSignalList().size() > 1 ) {
       CPvcsControlObjectInfo ObjControlObject = param_info;

        int iIndex, iSubIndex;
        iIndex = ObjControlObject.GetIndex();
        iSubIndex = ObjControlObject.GetSubIndex();

		AnalogSignal AnaIp1;
		AnalogSignal AnaOp1;
		try{
			AnaIp1  = param_info.GetInputAnalogSignalList().at( 0 );
			AnaOp1  = param_info.GetOutputAnalogSignalList().at( 0 );
		}
		catch( exception &e )
		{
			//TRACE("*****CPvcsControlObjectCargoValve2-GetValueString*******");
			XmlLogError( e.what() );
			return false;
		}


        TRACE("\n\n\nButton - wait for Access\n\n\n");

        CString strButtonCaption = ObjControlObject.GetButtonCaption(param_nButton);
        unsigned SetPoint = atoi(strButtonCaption);
        strButtonCaption.Format("%d",SetPoint);
        CDxfLayout::SetValueToBeSet(iIndex, iSubIndex,strButtonCaption);

        bResult =    CPvcsWagoControl::theWagoUnit().SetValue( param_info.GetOutputAnalogSignalList().at( 0 ),
                                             AnalogScaleObjectToWago( AnaOp1.Value.Limit.MinValue,
                                                                      AnaOp1.Value.Limit.MaxValue, SetPoint,param_info.GetWagoUnitType() ) );
		if ( bResult ){
			bResult = false;
			// Wait for feedback
			clock_t begin_tick = clock();
			clock_t cur_tick;

 			// The "wait" loop
			while( !bResult && CPVCSApp::m_bIsAlive)
			{
				cur_tick = clock() - 100;//100ms for Sleep time

				long time_elapsed = ( ( cur_tick - begin_tick ) * 1000 ) / CLOCKS_PER_SEC;
				if( ( time_elapsed  > param_info.GetTimeOut() ) )
				{
					// The "wait" timed out
					// ie the object failed to respond
                    string tStr = "WARNING\n"+param_info.GetName()+" TimeOut";
                    AfxMessageBox(tStr.c_str(),MB_SETFOREGROUND|MB_ICONERROR,0);

					bResult = false;
					break;
				} // if( ( time_elapsed  > param_info.GetTimeOut() ) )
				unsigned	CurrentRawPos;
				CPvcsWagoControl::theWagoUnit().GetValue( AnaIp1, CurrentRawPos,0 );
				unsigned CurrentPos = AnalogScaleWagoToObject(AnaIp1.Value.Limit.MinValue, AnaIp1.Value.Limit.MaxValue, CurrentRawPos,param_info.GetName(),param_info.GetWagoUnitType());
				//UINT CPvcsControlObject::AnalogScaleWagoToObject(const UINT& param_uiMin, const UINT& param_uiMax, const UINT& param_uiValue,CString param_psObjectName,CString param_psWagoUnitType)
				float Limit       = float(AnaIp1.Value.Limit.MaxValue - float(AnaIp1.Value.Limit.MinValue)/5.0);
				bResult = (abs(float(SetPoint) - float(CurrentPos)) <= Limit );
				Sleep(100);
			} // while( !bResult )
		}
    } //if( param_bIsPressed && param_info.GetInputAnalogSignalList().size() > 0 && param_info.GetOutputDigitalSignalList().size() > 1 )
    else {
        TRACE("\n\n\nButton - UP event\n\n\n");
    }
    return bResult;

}


// Function name   : CPvcsControlObjectCargoValve2::OnSetSpin
// Description     : Outputs control signals according to the spin box status
// Return type     : bool
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nSpin
// Argument        : const UINT& param_uiValue

bool CPvcsControlObjectCargoValve2::OnSetSpin(const CPvcsControlObjectInfo& param_info, const int& param_nSpin, const UINT& param_uiValue) {
    bool bResult = false;
	AnalogSignal AnaIp1;
	AnalogSignal AnaOp1;
	try{
		AnaIp1  = param_info.GetInputAnalogSignalList().at( 0 );
		AnaOp1  = param_info.GetOutputAnalogSignalList().at( 0 );
	}
	catch( exception &e )
	{
		//TRACE("*****CPvcsControlObjectCargoValve2-GetValueString*******");
		XmlLogError( e.what() );
		return false;
	}
    // Set the output
    if ( param_nSpin == 0 && param_info.GetOutputAnalogSignalList().size() != 0 )
        bResult =
        CPvcsWagoControl::theWagoUnit().SetValue( AnaOp1,
                                AnalogScaleObjectToWago( AnaOp1.Value.Limit.MinValue,
                                                         AnaOp1.Value.Limit.MaxValue, param_uiValue,0 ) );

	if ( bResult ){
		bResult = false;
		// Wait for feedback
		clock_t begin_tick = clock();
		clock_t cur_tick;

		// Change the cursor shape
		HCURSOR hCurs;
		hCurs = LoadCursor(NULL, IDC_WAIT);
		SetCursor( hCurs );

 		// The "wait" loop
		while( !bResult && CPVCSApp::m_bIsAlive)
		{
			cur_tick = clock() - 100;//100ms for Sleep time

			long time_elapsed = ( ( cur_tick - begin_tick ) * 1000 ) / CLOCKS_PER_SEC;
			if( ( time_elapsed  > param_info.GetTimeOut() ) )
			{
				// The "wait" timed out
				// ie the object failed to respond
				bResult = false;
				break;
			} // if( ( time_elapsed  > param_info.GetTimeOut() ) )
			unsigned	CurrentPos;
			CPvcsWagoControl::theWagoUnit().GetValue( AnaIp1, CurrentPos,0 );
			int Difference = int(param_uiValue)-int(CurrentPos);
            float DiffP = float(AnalogScaleObjectToWago( AnaIp1.Value.Limit.MinValue,AnaIp1.Value.Limit.MaxValue, unsigned(Difference),0 ));

			bResult = abs(DiffP) < 1;
			Sleep(100);
		} // while( !bResult )
	}

    return true;
}


// Function name   : CPvcsControlObjectCargoValve2::GetSpinInitInfo
// Description     : Initializes the spinbox with the current status of the objects
// Return type     : void
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : UINT& param_uiMinValue
// Argument        : UINT& param_uiMaxValue
// Argument        : UINT& param_uiStep
// Argument        : CString& param_strInitValue

void CPvcsControlObjectCargoValve2::GetSpinInitInfo(const CPvcsControlObjectInfo& param_info, UINT& param_uiMinValue, UINT& param_uiMaxValue, UINT& param_uiStep, CString& param_strValue)
{
	DigitalSignal DigOp1, DigOp2;
    DigitalSignal DigIp1, DigIp2;
    AnalogSignal AnaIp1,AnaIp2;
    AnalogSignal AnaOp1,AnaOp2;
    try{
        //DigOp1  = param_info.GetOutputDigitalSignalList().at( 0 );
        //DigOp2  = param_info.GetOutputDigitalSignalList().at( 1 );
        DigIp1  = param_info.GetInputDigitalSignalList().at( 0 );
        DigIp2  = param_info.GetInputDigitalSignalList().at( 1 );
        AnaIp1  = param_info.GetInputAnalogSignalList().at( 0 );
        AnaOp1  = param_info.GetOutputAnalogSignalList().at( 0 );
        //AnaIp1  = param_info.GetInputAnalogSignalList().at( 0 );
    }
    catch( exception &e )
    {
        //TRACE("*****CPvcsControlObjectCargoValve2-GetSpinInitInfo*******");
        XmlLogError( e.what() );
    }

    try {
        param_uiMinValue = AnaOp1.Value.Limit.MinValue;
        param_uiMaxValue = AnaOp1.Value.Limit.MaxValue;
        param_uiStep     = AnaOp1.Value.Step;


        UINT SetPoint = 0;
        CString strValue;

		// Change from reading the output to reading the current position
        if ( !param_info.GetInputAnalogSignalList().empty()
             && CPvcsWagoControl::theWagoUnit().GetValue( AnaOp1, SetPoint,0 ) ) {
            strValue.Format("%d", AnalogScaleWagoToObject( AnaOp1.Value.Limit.MinValue,
                                                           AnaOp1.Value.Limit.MaxValue, SetPoint ,param_info.GetName(),0) );
            param_info.SetValueToBeSet(strValue);
            CDxfLayout::SetValueToBeSet(param_info.GetIndex(),param_info.GetSubIndex(),strValue);
            param_strValue = strValue;
        }

    } catch ( std::out_of_range &e ) {
        //TRACE("*****CPvcsControlObjectTempSetPoint-getvaluestring***std::out range****");
        XmlLogError( "Probable error: Analog output count is less than Spin box count." );
        XmlLogError( e.what() );
    } catch ( exception &e ) {
        //TRACE("*****CPvcsControlObjectTempSetPoint-getvaluestring*******");
        XmlLogError( e.what() );
    }

}

