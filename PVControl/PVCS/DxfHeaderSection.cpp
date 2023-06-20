#include "StdAfx.h"
#include "dxfheadersection.h"


// Function name   : CDxfHeaderSection::CDxfHeaderSection
// Description     : Constructor
// Return type     :
// Argument        : CDxfFile& param_dxfFile

CDxfHeaderSection::CDxfHeaderSection(CDxfFile& param_dxfFile)
: m_dxfFile( param_dxfFile ),m_CDxfExtMax(param_dxfFile),m_CDxfExtMin(param_dxfFile)
{
}


// Function name   : CDxfHeaderSection::~CDxfHeaderSection
// Description     : Destructor
// Return type     :
// Argument        : void

CDxfHeaderSection::~CDxfHeaderSection(void)
{
}


// Function name   : CDxfHeaderSection::Parse
// Description     : Parses the header section
// Return type     : DxfErrorCodes::DxfError
// Argument        : void

DxfErrorCodes::DxfError CDxfHeaderSection::Parse(void)
{
	using namespace DxfErrorCodes;
	using namespace DxfHeaderSectionCodes;

	DxfError enumErrorCode = NoError;

	CDxfValue dxfValue;

	m_dxfFile >> dxfValue;

	while( static_cast <bool> ( dxfValue ) && ( dxfValue != HeaderSectionEnd ) && ( enumErrorCode == NoError ) )
	{
		if( dxfValue == ExtMinBegin ) // Its a ExtMinLimits section
		{
			enumErrorCode = m_CDxfExtMin.Parse(); // Parse the min limits

		} // if( dxfValue == ExtMinLimBegin )
		if( dxfValue == ExtMaxBegin ) // Its a ExtMaxLimits section
		{
			enumErrorCode = m_CDxfExtMax.Parse(); // Parse the max limits

		} // if( dxfValue == ExtMaxLimBegin )
		if( dxfValue == VersionVariable )
		{
			m_dxfFile >> dxfValue;

			string Value = dxfValue.Value();
			if( Value.find(SupportedVersion.Value()) == Value.npos){
                if( Value.find(SupportedVersion2.Value()) == Value.npos){
                    enumErrorCode = UnsupportedVersion;
                }
			}
		} // if( dxfValue == VersionVariable )

		m_dxfFile >> dxfValue;
	} // while( static_cast <bool> ( dxfValue ) && ( dxfValue != HeaderSectionEnd ) && ( enumErrorCode == NoError ) )

	if( enumErrorCode == NoError )	// If everything was OK
		MakeValid();				// Make this a valid Header

	return enumErrorCode;
}


const double CDxfHeaderSection::GetMaxX(void)
{
    return m_CDxfExtMax.GetX();
}
const double CDxfHeaderSection::GetMaxY(void)
{
	return m_CDxfExtMax.GetY();
}
const double CDxfHeaderSection::GetMinX(void)
{
	return m_CDxfExtMin.GetX();
}
const double CDxfHeaderSection::GetMinY(void)
{
	return m_CDxfExtMin.GetY();
}
