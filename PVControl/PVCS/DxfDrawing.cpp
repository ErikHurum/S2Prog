#include "StdAfx.h"
#include ".\dxfdrawing.h"


// Function name   : CDxfDrawing::CDxfDrawing
// Description     : Constructor
// Return type     :
// Argument        : void

CDxfDrawing::CDxfDrawing(void)
: m_dxfHeader( m_dxfFile )
, m_dxfTable( m_dxfFile )
, m_dxfEntities( m_dxfFile )
{
}


// Function name   : CDxfDrawing::~CDxfDrawing
// Description     : Destructor
// Return type     :
// Argument        : void

CDxfDrawing::~CDxfDrawing(void)
{
}


// Function name   : CDxfDrawing::Load
// Description     : Loads a dxf file into the container
// Return type     : DxfErrorCodes::DxfError
// Argument        : const string& param_strFileName

DxfErrorCodes::DxfError CDxfDrawing::Load(const string& param_strFileName)
{
	using namespace DxfErrorCodes;

	DxfError enumErrorCode = NoError;

	if( !m_dxfFile.Open( param_strFileName ) ) // Open the file
		enumErrorCode = CannotOpenFile;
	else
		enumErrorCode = Parse(); // Parse and load

	if( enumErrorCode == NoError )	// If Everything was OK
		MakeValid();				// Make this a valid Drawing

	return enumErrorCode;
}


// Function name   : CDxfDrawing::Parse
// Description     : Parse the complete drawing
// Return type     : DxfErrorCodes::DxfError
// Argument        : void

DxfErrorCodes::DxfError CDxfDrawing::Parse(void)
{
	using namespace DxfErrorCodes;
	using namespace DxfCommonSectionCodes;

	DxfError enumErrorCode = NoError;

	CDxfValue dxfValue;

	m_dxfFile >> dxfValue;

	while( dxfValue )
	{// Loop throgh the file
		if( dxfValue == SectionBegin ) // If a new section is found
		{
			m_dxfFile >> dxfValue;

			if( dxfValue == SectionHeaderBegin ) // Its a Header section
			{
				enumErrorCode = m_dxfHeader.Parse(); // Parse the header

			} // if( dxfValue == SectionHeaderBegin )


			if( dxfValue == SectionTablesBegin ) // Its a table section
			{
				enumErrorCode = m_dxfTable.Parse(); // Parse the tables

			} // if( dxfValue == SectionTablesBegin )

			if( dxfValue == SectionEntitiesBegin ) // Its an Entities section
			{
				enumErrorCode = m_dxfEntities.Parse(); // Parse the entities

			} // if( dxfValue == SectionEntitiesBegin )

		} // if( dxfValue == SectionBegin )

		m_dxfFile >> dxfValue;

	} // while( dxfValue )

	return enumErrorCode;
}


// Function name   : CDxfDrawing::Entity
// Description     : Retrieves the Entities section
// Return type     : const CDxfEntitiesSection&
// Argument        : void

const CDxfEntitiesSection& CDxfDrawing::Entity(void) const
{
	return m_dxfEntities;
}


// Function name   : CDxfDrawing::Table
// Description     : Retrieves the Table section
// Return type     : const CDxfTableSection&
// Argument        : void

const CDxfTableSection& CDxfDrawing::Table(void) const
{
	return m_dxfTable;
}


const double CDxfDrawing::GetMaxX(void)
{
    return m_dxfHeader.GetMaxX();
}
const double CDxfDrawing::GetMaxY(void)
{
    return m_dxfHeader.GetMaxY();
}
const double CDxfDrawing::GetMinX(void)
{
    return m_dxfHeader.GetMinX();
}
const double CDxfDrawing::GetMinY(void)
{
    return m_dxfHeader.GetMinY();
}

