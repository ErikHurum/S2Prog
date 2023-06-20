#include "StdAfx.h"
#include ".\pvcscontrolobjectsimplepump.h"
#include "pvcscontrolobjectinfo.h"
#include "pvcswagocontrol.h"
#include "DxfLayout.h"
#undef MAX
#define MAX(a,b)	((a) > (b) ? (a) : (b))
#undef MIN
#define MIN(a,b)	((a) < (b) ? (a) : (b))

CPvcsControlObjectSimplePump::CPvcsControlObjectSimplePump(void)
{
}


CPvcsControlObjectSimplePump::~CPvcsControlObjectSimplePump(void)
{
}

// Function name   : CPvcsControlObjectSimplePump::GetColor
// Description     : Get the deafault color
// Return type     : const COLORREF& 
// Argument        : const CPvcsControlObjectInfo& param_info

const Gdiplus::ARGB& CPvcsControlObjectSimplePump::GetColor(const CPvcsControlObjectInfo &param_info, const int &pSubIndex2)
{
	//COLORREF tmpCol = param_info.GetStatusColor(GetStatus(param_info,pSubIndex2),pSubIndex2);
	return param_info.GetStatusColor(GetStatus(param_info,pSubIndex2),pSubIndex2);
}


// Function name   : CPvcsControlObjectSimplePump::GetInText
// Description     : Get the Intext
// Return type     : const CString& 
// Argument        : const CPvcsControlObjectInfo& param_info

const CString& CPvcsControlObjectSimplePump::GetInText(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	return param_info.GetStatusInText( GetStatus( param_info ),pSubIndex2 );
}

// Function name   : CPvcsControlObjectBallastPump::GetValueString
// Description     : Not implemented
// Return type     : CString 
// Argument        : const CPvcsControlObjectInfo& param_info

CString CPvcsControlObjectSimplePump::GetValueString(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	CString strValue;
	UINT uiValue = 0;

	// The value string is determined as follows:
	// Default: Value = Analog Input%
	try{
		switch(pSubIndex2){
		case 0:
			if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputAnalogSignalList().at( 0 ), uiValue,param_info.GetWagoUnitType() ) )
				strValue.Format("%4.1f %%", AnalogScaleWagoToObjectD(param_info.GetInputAnalogSignalList().at( 0 ).Value.Limit.MinValue, param_info.GetInputAnalogSignalList().at( 0 ).Value.Limit.MaxValue, uiValue,param_info.GetWagoUnitType()));
			break;
		case 1:
			if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputAnalogSignalList().at( 1 ), uiValue,param_info.GetWagoUnitType() ) )
				strValue.Format("%4.1f A", AnalogScaleWagoToObjectD(param_info.GetInputAnalogSignalList().at( 1 ).Value.Limit.MinValue, param_info.GetInputAnalogSignalList().at( 1 ).Value.Limit.MaxValue, uiValue,param_info.GetWagoUnitType()));
		}
	}
	catch( std::out_of_range &e )
	{	//TRACE("*****CPvcsControlObjectTempSetPoint-getvaluestring*std::out range******");
		XmlLogError( "Probable error: Input signal count is mismatched in config." );
		throw e;
	}
	catch( exception &e)
	{
		//TRACE("*****CPvcsControlObjectTempSetPoint-getvaluestring*******");
		XmlLogError( e.what() );
	}
	return strValue;
}


// Function name   : CPvcsControlObjectSimplePump::OnButton
// Description     : Not Implemented
// Return type     : bool 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nButton
// Argument        : const bool& param_bIsPressed

bool CPvcsControlObjectSimplePump::OnButton(const CPvcsControlObjectInfo& param_info, const int& param_nButton, const bool& param_bIsPressed)
{
	//bool bResult = false;
	//CString tmpStr = param_info.GetButtonCaption(param_nButton);
	if ( !param_info.GetOutputDigitalSignalList().empty() ) {
		if ( !param_bIsPressed ) {
			int Index     = param_info.GetIndex();
			int SubIndex1 = param_info.GetSubIndex();
			//int SubIndex2 = param_info.GetSubIndex2();
			CDxfLayout::SetControlOperationState(Index,SubIndex1,false);
			UINT State = GetObjStatus(param_info, -1);
			switch ( param_nButton ) {
			case 0:
				if ( State == 1 ) {
					if ( !param_info.GetOutputAnalogSignalList().empty() ) {
						UINT MaxValue = param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MaxValue;
						CPvcsWagoControl::theWagoUnit().SetValue( param_info.GetOutputAnalogSignalList().at( 0 ), MaxValue);
						CString strValue;
						strValue.Format("%d", MaxValue);
						//param_info.SetValueToBeSet(strValue);
						CDxfLayout::SetValueToBeSet(Index,SubIndex1,strValue);
					}		
					if ( param_info.GetOutputDigitalSignalList().size() >= 2 ) {
						CPvcsWagoControl::theWagoUnit().SetValue( param_info.GetOutputDigitalSignalList().at(1), false );
						CPvcsWagoControl::theWagoUnit().SetValue( param_info.GetOutputDigitalSignalList().at(0), true  );
					} else {
						CPvcsWagoControl::theWagoUnit().SetValue( param_info.GetOutputDigitalSignalList().at(0), true );
					}
				}
				break;
			case 1: // If not remote, we can stop regardless of alarms
				if ( ( State == 2) || ( State == 4 )) {
					if ( !param_info.GetOutputAnalogSignalList().empty() ) {
						UINT MinValue = param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MinValue;
						CPvcsWagoControl::theWagoUnit().SetValue( param_info.GetOutputAnalogSignalList().at( 0 ), MinValue);
						CString strValue;
						strValue.Format("%d", MinValue);
					}
					if ( param_info.GetOutputDigitalSignalList().size() >= 2 ) {
						CPvcsWagoControl::theWagoUnit().SetValue( param_info.GetOutputDigitalSignalList().at(0), false );
						CPvcsWagoControl::theWagoUnit().SetValue( param_info.GetOutputDigitalSignalList().at(1), true  );
					} else {
						CPvcsWagoControl::theWagoUnit().SetValue( param_info.GetOutputDigitalSignalList().at(0), false );
					}
				}
				break;
			}
			CDxfLayout::SetControlOperationState(Index,SubIndex1,true);

		}
	}
	return true;
}

// Function name   : CPvcsControlObjectBallastPump::OnSetSpin
// Description     : Outputs control signals according to the spin box status
// Return type     : bool 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nSpin
// Argument        : const UINT& param_uiValue

bool CPvcsControlObjectSimplePump::OnSetSpin(const CPvcsControlObjectInfo& param_info, const int& param_nSpin, const UINT& param_uiValue)
{
  	bool bResult = true;

	if(  param_info.GetOutputDigitalSignalList().size() >= 1 )
	{
		bResult = 
			CPvcsWagoControl::theWagoUnit().SetValue( param_info.GetOutputAnalogSignalList().at( 0 ), 
				AnalogScaleObjectToWago( param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MinValue, 
														param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MaxValue, param_uiValue,param_info.GetWagoUnitType() ) );

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

void CPvcsControlObjectSimplePump::GetSpinInitInfo(const CPvcsControlObjectInfo& param_info, UINT& param_uiMinValue, UINT& param_uiMaxValue, UINT& param_uiStep, CString& param_strValue)
{ 
	if ( param_info.GetOutputAnalogSignalList().empty()) return;

	try{
		param_uiMinValue = param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MinValue;
		param_uiMaxValue = param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MaxValue;
		param_uiStep	 = param_info.GetOutputAnalogSignalList().at(0).Value.Step;

		CString strValue;
		UINT uiValue = 0;
		int Value; 

		if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputAnalogSignalList().at( 0 ), uiValue,param_info.GetWagoUnitType() ) )
		{
			uiValue = AnalogScaleWagoToObject(param_uiMinValue, param_uiMaxValue, uiValue,param_info.GetName(),param_info.GetWagoUnitType());
			/*
            if(param_info.GetOutputAnalogSignalList().at(0).Value.bIsInverted)
			{
				Value = param_info.GetObjectMaxStop() - uiValue;
			}
			else
				Value = uiValue;

			*/
			Value = uiValue;
			if(Value < (int)param_info.GetObjectMinStop())
				Value = 0;
			if(Value > (int)param_info.GetObjectMaxStop())
				Value = 100;
			
			strValue.Format("%d", Value);
			param_info.SetValueToBeSet(strValue);
			CDxfLayout::SetValueToBeSet(param_info.GetIndex(),param_info.GetSubIndex(),strValue);
		}
		param_strValue = strValue;
	}
	catch( std::out_of_range &e )
	{
		//TRACE("*****CPvcsControlObjectSimplePump-getspininitinfo*std::out range******");
		XmlLogError( "Probable error: Analog Input count is less than Spin box count." );
		throw e;
	}
	catch( exception &e )
	{
		//TRACE("*****CPvcsControlObjectSimplePump-getspininitinfo*std::out range******");
		XmlLogError( e.what() );
	}
}




// Function name   : CPvcsControlObjectSimplePump::GetStatus
// Description     : Get a status
// Return type     : int 
// Argument        : const CPvcsControlObjectInfo& param_info

int CPvcsControlObjectSimplePump::GetStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	return GetObjStatus(param_info, pSubIndex2);
}

// Function name   : CPvcsControlObjectCargoValve::GetStatus
// Description     : Returns the current status of the control object
// Return type     : int 
// Argument        : const CPvcsControlObjectInfo& param_info
int CPvcsControlObjectSimplePump::GetObjStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
	unsigned nStatus = 0;
	bool bValue = false;

	int NumberOfDI = int(param_info.GetInputDigitalSignalList().size());
	switch ( pSubIndex2 ) {
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
		if ( pSubIndex2 < NumberOfDI ) {
			bool Status=false;
			bool Success = CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( pSubIndex2 ), Status,param_info.GetWagoUnitType() );
			if ( Status ) {
				nStatus = 0;
			} else {
				nStatus = 1;
			}
		} else {
			nStatus=0;
		}
		break;
	case -1:
	default:
		{
			UINT State=0;
			for ( int i=0; i < NumberOfDI; i++ ) {
				bool Status=false;
				bool Success = CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputDigitalSignalList().at( i ), Status,param_info.GetWagoUnitType() );
				if ( Status ) {
					State |= 1 << i;
				}
			}
			nStatus = MAX(nStatus,param_info.GetStatusOr(State));
			nStatus = MAX(nStatus,param_info.GetStatusOrNot(State));
			nStatus = MAX(nStatus,param_info.GetStatusAnd(State));
			nStatus = MAX(nStatus,param_info.GetStatusAndNot(State));
			if ( !nStatus ) nStatus++;
		}
		break;
	}


	return nStatus;
}


bool CPvcsControlObjectSimplePump::CheckAlarm(DigitalSignal DigitalInput,CString WagoUnitType)
{
	bool Status=false;
	bool Success = CPvcsWagoControl::theWagoUnit().GetValue( DigitalInput, Status,WagoUnitType );
	return Status;
}
