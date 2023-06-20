#include "StdAfx.h"
#include ".\dxfvalue.h"


// Function name   : CDxfValue::CDxfValue
// Description     : Default Constructor
// Return type     : 
// Argument        : void

CDxfValue::CDxfValue(void)
: m_iCode(0)
{
}


// Function name   : CDxfValue::CDxfValue
// Description     : Constructor with values
// Return type     : 
// Argument        : const int& param_iCode
// Argument        : const string& param_strValue

CDxfValue::CDxfValue(const int& param_iCode, const string& param_strValue)
: m_iCode( param_iCode )
, m_strValue( param_strValue )
{
	MakeValid();
}


// Function name   : CDxfValue::~CDxfValue
// Description     : Destructor
// Return type     : 
// Argument        : void

CDxfValue::~CDxfValue(void)
{
}


// Function name   : CDxfValue::Code
// Description     : Returns the Group code 
// Return type     : const int& 
// Argument        : void

const int& CDxfValue::Code(void) const
{
	return m_iCode;
}


// Function name   : CDxfValue::Value
// Description     : Returns the value
// Return type     : const string& 
// Argument        : void

const string& CDxfValue::Value(void) const
{
	return m_strValue;
}


// Function name   : CDxfValue::operator==
// Description     : Overload operator == so that m_bIsValid object of parent class
//					 CDxfValid is not checked
// Return type     : bool 
// Argument        : const CDxfValue& param_dxfValue

bool CDxfValue::operator==(const CDxfValue& param_dxfValue)
{
	return ( ( m_iCode == param_dxfValue.m_iCode )
		  && ( m_strValue == param_dxfValue.m_strValue ) );
}


// Function name   : CDxfValue::operator!=
// Description     : Overload operator !=
// Return type     : bool 
// Argument        : const CDxfValue& param_dxfValue

bool CDxfValue::operator!=(const CDxfValue& param_dxfValue)
{
	return !( *this == param_dxfValue );
}


// Function name   : operator>>
// Description     : Extracts group code and corresponding value from the file stream
// Return type     : ifstream& 
// Argument        : ifstream& param_fin
// Argument        : CDxfValue& param_dxfValue

ifstream& operator>>( ifstream& param_fin, CDxfValue& param_dxfValue )
{
	string strTemp;

	getline( param_fin, strTemp );	// Get the Group code integer
	param_dxfValue.m_iCode = atoi( strTemp.c_str() );

	getline( param_fin, param_dxfValue.m_strValue ); // Get the corresponding value

	if( param_fin.good() ) // Ensure that input was proper 
		param_dxfValue.MakeValid();
	else
		param_dxfValue.MakeValid( false );

	return param_fin;
}
