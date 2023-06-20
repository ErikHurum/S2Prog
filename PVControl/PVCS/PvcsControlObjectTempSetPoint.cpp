#include "StdAfx.h"
#include ".\pvcsControlObjectTempSetPoint.h"
#include "pvcscontrolobjectinfo.h"
#include "pvcswagocontrol.h"

// The default color for the temp set objects
COLORREF CPvcsControlObjectTempSetPoint::m_Color = 0x339999;


// Function name   : CPvcsControlObjectTempSetPoint::~CPvcsControlObjectTempSetPoint
// Description     : Destructor
// Return type     : 
// Argument        : void

CPvcsControlObjectTempSetPoint::~CPvcsControlObjectTempSetPoint(void)
{
}


// Function name   : CPvcsControlObjectTempSetPoint::GetColor
// Description     : Get the deafault color
// Return type     : const COLORREF& 
// Argument        : const CPvcsControlObjectInfo& param_info

const COLORREF& CPvcsControlObjectTempSetPoint::GetColor(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
    return m_Color;
}


// Function name   : CPvcsControlObjectTempSetPoint::GetInText
// Description     : Get the Intext
// Return type     : const CString& 
// Argument        : const CPvcsControlObjectInfo& param_info

const CString& CPvcsControlObjectTempSetPoint::GetInText(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
    return param_info.GetStatusInText( 1 );
}


// Function name   : CPvcsControlObjectTempSetPoint::GetValueString
// Description     : Returns the value string to be displayed
// Return type     : CString 
// Argument        : const CPvcsControlObjectInfo& param_info

CString CPvcsControlObjectTempSetPoint::GetValueString(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
    CString strValue;
    bool bValue = false;
    UINT uiValue = 0;

    // The value string is determined as follows:
    // Default: Value = Analog Input%
    try{
        if( CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetInputAnalogSignalList().at( 0 ), uiValue,param_info.GetWagoUnitType() ) )
            strValue.Format("%4.1f °C", AnalogScaleWagoToObjectD(param_info.GetInputAnalogSignalList().at( 0 ).Value.Limit.MinValue, param_info.GetInputAnalogSignalList().at( 0 ).Value.Limit.MaxValue, uiValue,param_info.GetWagoUnitType()));
    }
    catch( std::out_of_range &e )
    {   //TRACE("*****CPvcsControlObjectTempSetPoint-getvaluestring*std::out range******");
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


// Function name   : CPvcsControlObjectTempSetPoint::OnButton
// Description     : Not Implemented
// Return type     : bool 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nButton
// Argument        : const bool& param_bIsPressed

bool CPvcsControlObjectTempSetPoint::OnButton(const CPvcsControlObjectInfo& param_info, const int& param_nButton, const bool& param_bIsPressed)
{
    return false;
}


// Function name   : CPvcsControlObjectTempSetPoint::OnSetSpin
// Description     : Sets the analog output
// Return type     : bool 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : const int& param_nSpin
// Argument        : const UINT& param_uiValue

bool CPvcsControlObjectTempSetPoint::OnSetSpin(const CPvcsControlObjectInfo& param_info, const int& param_nSpin, const UINT& param_uiValue)
{
    bool bResult = false;
    
    // Set the output
    if( param_nSpin == 0 && !param_info.GetOutputAnalogSignalList().empty() )
        bResult = 
            CPvcsWagoControl::theWagoUnit().SetValue( param_info.GetOutputAnalogSignalList().at( 0 ), 
                AnalogScaleObjectToWago( param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MinValue, 
                                                        param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MaxValue, param_uiValue,param_info.GetWagoUnitType() ) );

    return true;
}


// Function name   : CPvcsControlObjectTempSetPoint::GetStatus
// Description     : Not Implemented
// Return type     : int 
// Argument        : const CPvcsControlObjectInfo& param_info

int CPvcsControlObjectTempSetPoint::GetStatus(const CPvcsControlObjectInfo& param_info, const int& pSubIndex2)
{
    return 0;
}


// Function name   : CPvcsControlObjectTempSetPoint::GetSpinInitInfo
// Description     : Initializes the spin box
// Return type     : void 
// Argument        : const CPvcsControlObjectInfo& param_info
// Argument        : UINT& param_uiMinValue
// Argument        : UINT& param_uiMaxValue
// Argument        : UINT& param_uiStep
// Argument        : CString& param_strValue

void CPvcsControlObjectTempSetPoint::GetSpinInitInfo(const CPvcsControlObjectInfo& param_info, UINT& param_uiMinValue, UINT& param_uiMaxValue, UINT& param_uiStep, CString& param_strValue)
{
    try{
        param_uiMinValue = param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MinValue;
        param_uiMaxValue = param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MaxValue;
        param_uiStep     = param_info.GetOutputAnalogSignalList().at(0).Value.Step;
        
        CString strValue;
        UINT uiValue = 0; 

        if( param_info.GetOutputAnalogSignalList().size() != 0 
            && CPvcsWagoControl::theWagoUnit().GetValue( param_info.GetOutputAnalogSignalList().at( 0 ), uiValue,param_info.GetWagoUnitType() ) )
            strValue.Format("%d", AnalogScaleWagoToObject( param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MinValue, 
                                                            param_info.GetOutputAnalogSignalList().at(0).Value.Limit.MaxValue, uiValue ,param_info.GetName(),param_info.GetWagoUnitType()) );

        param_strValue = strValue;
}
    catch( std::out_of_range &e )
    {
        //TRACE("*****CPvcsControlObjectTempSetPoint-getvaluestring***std::out range****");
        XmlLogError( "Probable error: Analog output count is less than Spin box count." );
        XmlLogError( e.what() );
    }
    catch( exception &e )
    {
        //TRACE("*****CPvcsControlObjectTempSetPoint-getvaluestring*******");
        XmlLogError( e.what() );
    }
}
