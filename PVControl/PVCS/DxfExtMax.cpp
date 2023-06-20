#include "StdAfx.h"
#include ".\DxfExtMax.h"


// Function name   : CDxfExtMax::CDxfExtMax
// Description     : Default constructor
// Return type     :
// Argument        : void

CDxfExtMax::CDxfExtMax(CDxfFile& param_dxfFile)
: m_dxfFile( param_dxfFile ), m_MaxX(0.0), m_MaxY(0.0), m_MaxZ(0.0)
{
}



// Function name   : CDxfExtMax::~CDxfExtMax
// Description     : Destructor
// Return type     :
// Argument        : void

CDxfExtMax::~CDxfExtMax(void)
{
}


// Function name   : CDxfExtMax::SetX
// Description     : Sets the X-Coordinate of point
// Return type     : void
// Argument        : const double& param_dXVal

void CDxfExtMax::SetX(const double& param_MaxX)
{
	m_MaxX = param_MaxX;
	MakeValid();
}


// Function name   : CDxfExtMax::SetY
// Description     : Sets the Y-Cordinate of the point
// Return type     : void
// Argument        : const double& param_dYVal

void CDxfExtMax::SetY(const double& param_MaxY)
{
	m_MaxY = param_MaxY;
	MakeValid();
}

// Function name   : CDxfExtMax::SetZ
// Description     : Sets the Z-Cordinate of the point
// Return type     : void
// Argument        : const double& param_dZVal

void CDxfExtMax::SetZ(const double& param_MaxZ)
{
	m_MaxZ = param_MaxZ;
	MakeValid();
}



// Function name   : CDxfExtMax::GetX
// Description     : Retrives the X-Coordinate of the point
// Return type     : const double&
// Argument        : void

const double& CDxfExtMax::GetX(void) const
{
	return m_MaxX;
}


// Function name   : CDxfExtMax::GetY
// Description     : Retrives the Y-Coordinate of the point
// Return type     : const double&
// Argument        : void

const double& CDxfExtMax::GetY(void) const
{
	return m_MaxY;
}
// Function name   : CDxfExtMax::GetZ
// Description     : Retrives the Z-Coordinate of the point
// Return type     : const double&
// Argument        : void

const double& CDxfExtMax::GetZ(void) const
{
	return m_MaxZ;
}
// Function name   : CDxfEntitiesSection::Parse
// Description     : Parses the entities section
// Return type     : DxfErrorCodes::DxfError
// Argument        : void

DxfErrorCodes::DxfError CDxfExtMax::Parse(void)
{
	using namespace DxfErrorCodes;
	using namespace DxfExtLimitGroupCodes;


    DxfError		enumErrorCode = NoError;
    CDxfValue		dxfValue;
    bool            MoreData = true ;


	do
	{// Loop until input and code is valid
        m_dxfFile >> dxfValue; // Input first value
		switch( dxfValue.Code() )
		{
		case XCoord	: SetX( dxfValue ); break;
		case YCoord	: SetY( dxfValue ); break;
		case ZCoord	:
            SetZ( dxfValue );
            MoreData = false;
            break;
		} // switch( dxfValue.Code() )
	} while( MoreData && static_cast <bool> ( dxfValue ) );

	if( enumErrorCode == NoError ) // If everything is OK
		MakeValid();	// Make this a valid Entity section

	return enumErrorCode;
}

