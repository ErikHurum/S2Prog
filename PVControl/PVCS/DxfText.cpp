#include "StdAfx.h"
#include ".\dxftext.h"


// Function name   : CDxfText::CDxfText
// Description     : Constructor
// Return type     :
// Argument        : CDxfFile& param_dxfFile

CDxfText::CDxfText(CDxfFile& param_dxfFile)
: m_dxfFile( param_dxfFile )
{
}


// Function name   : CDxfText::~CDxfText
// Description     : Destructor
// Return type     :
// Argument        : void

CDxfText::~CDxfText(void)
{
}


// Function name   : CDxfText::Parse
// Description     : Parses all the text entities in dxf
// Return type     : DxfErrorCodes::DxfError
// Argument        : void

DxfErrorCodes::DxfError CDxfText::Parse(void)
{
	using namespace DxfErrorCodes;
	using namespace DxfTextGroupCodes;

	DxfError	enumErrorCode = NoError;
	CDxfValue	dxfValue;
	CAcDbText	tempText;

	m_dxfFile >> dxfValue; // Input first value

	while( static_cast <bool> ( dxfValue ) && ( dxfValue.Code() != 0 ) )
	{// Loop until input and code is valid
		switch( dxfValue.Code() )
		{
		case XCoord	        : tempText.SetX( dxfValue ); break;
		case YCoord	        : tempText.SetY( dxfValue ); break;
		case Height	        : tempText.SetHeight( dxfValue ); break;
		case Width	        : tempText.SetWidth( dxfValue ); break;
        case Layer	        : tempText.SetLayer( dxfValue.Value() ); break;
        case TextStyle      : tempText.SetFont( dxfValue.Value() ); break;
		case Value	        : tempText.SetValue( dxfValue.Value() ); break;
		case DrawDir        : tempText.SetDrawDir( dxfValue ); break;
        case LineSpace		: tempText.SetLSpace( dxfValue ); break;
        case AttachPnt      : tempText.SetAttachPnt( dxfValue ); break;
        case XAngle         : tempText.SetXAngle(dxfValue); break;
        case YAngle         : tempText.SetYAngle(dxfValue); break;
        case ZAngle         : tempText.SetZAngle(dxfValue); break;
		} // switch( dxfValue.Code() )

		m_dxfFile >> dxfValue;
	} // while( static_cast <bool> ( dxfValue ) && ( dxfValue.Code() != 0 ) )

	m_acdbText.push_back( tempText ); // Store the text

	if( enumErrorCode == NoError )	// If every thing was OK
		MakeValid();				// Make this a valid text

	return enumErrorCode;
}


// Function name   : CDxfText::GetCount
// Description     : Returns the number of text in this container
// Return type     : int
// Argument        : void

int CDxfText::GetCount(void) const
{
	return static_cast<int> ( m_acdbText.size() );
}


// Function name   : CDxfText::operator[]
// Description     : Returns the indexed text entity
// Return type     : const CAcDbText&
// Argument        : const int& param_nIndex

const CAcDbText& CDxfText::operator[](const int& param_nIndex) const
{
		return m_acdbText[param_nIndex];
}

