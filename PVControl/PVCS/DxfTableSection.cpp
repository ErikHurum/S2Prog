#include "StdAfx.h"
#include ".\dxftablesection.h"


// Function name   : CDxfTableSection::CDxfTableSection
// Description     : Constructor
// Return type     : 
// Argument        : CDxfFile& param_dxfFile

CDxfTableSection::CDxfTableSection(CDxfFile& param_dxfFile)
: m_dxfFile( param_dxfFile )
, m_dxfLayer( param_dxfFile )
{
}


// Function name   : CDxfTableSection::~CDxfTableSection
// Description     : Destructor
// Return type     : 
// Argument        : void

CDxfTableSection::~CDxfTableSection(void)
{
}


// Function name   : CDxfTableSection::Parse
// Description     : Parses the table section
// Return type     : DxfErrorCodes::DxfError 
// Argument        : void

DxfErrorCodes::DxfError CDxfTableSection::Parse(void)
{
	using namespace DxfErrorCodes;
	using namespace DxfTableSectionCodes;

	DxfError enumErrorCode = NoError;

	CDxfValue dxfValue;

	m_dxfFile >> dxfValue;

	while( static_cast <bool> ( dxfValue ) && ( dxfValue != TableSectionEnd ) )
	{	// Loop through the Table section
		if( dxfValue == TableBegin )
		{
			m_dxfFile >> dxfValue;

			if( dxfValue == TableLayer )// If its a layer information
			{
				m_dxfLayer.Parse(); // Parse the layer

			} // if( dxfValue == TableLayer )
		} // if( dxfValue == TableBegin )

		m_dxfFile >> dxfValue;
	} // while( static_cast <bool> ( dxfValue ) && ( dxfValue != TableSectionEnd ) )

	if( enumErrorCode == NoError )	// If everything is OK
		MakeValid();				// Make this a valid Table Section

	return enumErrorCode;
}


// Function name   : CDxfTableSection::Layer
// Description     : Retrieves the Layer table
// Return type     : const CDxfLayer& 
// Argument        : void

const CDxfLayer& CDxfTableSection::Layer(void) const
{
	return m_dxfLayer;
}
