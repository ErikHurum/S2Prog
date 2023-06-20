#include "StdAfx.h"
#include ".\dxfentitiessection.h"


// Function name   : CDxfEntitiesSection::CDxfEntitiesSection
// Description     : Constructor
// Return type     :
// Argument        : CDxfFile& param_dxfFile

CDxfEntitiesSection::CDxfEntitiesSection(CDxfFile& param_dxfFile)
: m_dxfFile( param_dxfFile )
, m_dxfPolyLine( param_dxfFile )
, m_dxfHatch( param_dxfFile )
, m_dxfText( param_dxfFile )
, m_dxfMText( param_dxfFile )
{
}


// Function name   : CDxfEntitiesSection::~CDxfEntitiesSection
// Description     : Destructor
// Return type     :
// Argument        : void

CDxfEntitiesSection::~CDxfEntitiesSection(void)
{
}


// Function name   : CDxfEntitiesSection::Parse
// Description     : Parses the entities section
// Return type     : DxfErrorCodes::DxfError
// Argument        : void

DxfErrorCodes::DxfError CDxfEntitiesSection::Parse(void)
{
	using namespace DxfErrorCodes;
	using namespace DxfEntitiesSectionCodes;

	DxfError enumErrorCode = NoError;

	CDxfValue dxfValue;

	m_dxfFile >> dxfValue;

	while( static_cast <bool> ( dxfValue ) && ( dxfValue != EntitiesSectionEnd ) )
	{// Loop through the section
		if( dxfValue == LineBegin ) // if found polyline
		{
            CDxfLine m_dxfLine(m_dxfPolyLine.GetDxfFile());
			m_dxfLine.Parse(); // parse polyline
            m_dxfPolyLine.AddPolyLineVector(m_dxfLine.GetPolyLineVector());
			dxfValue = m_dxfFile.GetLastValue();
            continue;
		} // if( dxfValue == LineBegin )
        if( dxfValue == PolylineBegin ) // if found polyline
        {
            m_dxfPolyLine.Parse(); // parse polyline
            dxfValue = m_dxfFile.GetLastValue();
            continue;
        } // if( dxfValue == PolyLineBegin )
        if( dxfValue == HatchBegin ) // if found polyline
        {
            m_dxfHatch.Parse(); // parse polyline
            dxfValue = m_dxfFile.GetLastValue();
            continue;
        } // if( dxfValue == PolyLineBegin )

		if( dxfValue == TextBegin ) // if found text
		{
			m_dxfText.Parse(); // parse text
			dxfValue = m_dxfFile.GetLastValue();
            continue;
		} // if( dxfValue == TextBegin )

		if( dxfValue == MTextBegin ) // if found multiline text
		{
			m_dxfMText.Parse(); // parse multiline text
			dxfValue = m_dxfFile.GetLastValue();
			continue;
		} // if( dxfValue == MTextBegin )


		m_dxfFile >> dxfValue;
	} // while( static_cast <bool> ( dxfValue ) && ( dxfValue != EntitiesSectionEnd ) )

	if( enumErrorCode == NoError ) // If everything is OK
		MakeValid();	// Make this a valid Entity section

	return enumErrorCode;
}


// Function name   : CDxfEntitiesSection::Polyline
// Description     : Retrieves the set of polylines in the entity
// Return type     : const CDxfPolyLine&
// Argument        : void

const CDxfPolyLine& CDxfEntitiesSection::Polyline(void) const
{
	return m_dxfPolyLine;
}
// Function name   : CDxfEntitiesSection::Hatch
// Description     : Retrieves the set of Hatches in the entity
// Return type     : const CDxfHatch&
// Argument        : void

const CDxfHatch& CDxfEntitiesSection::Hatch(void) const
{
	return m_dxfHatch;
}


// Function name   : CDxfEntitiesSection::Text
// Description     : Retrieves the set of text in the entity
// Return type     : const CDxfText&
// Argument        : void

const CDxfText& CDxfEntitiesSection::Text(void) const
{
	return m_dxfText;
}


// Function name   : CDxfEntitiesSection::MText
// Description     : Retrieves the set of multiline text in the entity
// Return type     : const CDxfMText&
// Argument        : void

const CDxfMText& CDxfEntitiesSection::MText(void) const
{
	return m_dxfMText;
}
