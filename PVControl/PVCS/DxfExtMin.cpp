#include "StdAfx.h"
#include ".\DxfExtMin.h"

// Function name   : CDxfExtMin::CDxfExtMin
// Description     : Default constructor
// Return type     :
// Argument        : void

CDxfExtMin::CDxfExtMin(CDxfFile& param_dxfFile)
: m_dxfFile( param_dxfFile ), m_MinX(0.0), m_MinY(0.0), m_MinZ(0.0)
{
}




// Function name   : CDxfExtMin::~CDxfExtMin
// Description     : Destructor
// Return type     :
// Argument        : void

CDxfExtMin::~CDxfExtMin(void)
{
}


// Function name   : CDxfExtMin::SetX
// Description     : Sets the X-Coordinate of point
// Return type     : void
// Argument        : const double& param_dXVal

void CDxfExtMin::SetX(const double& param_MinX)
{
	m_MinX = param_MinX;
	MakeValid();
}


// Function name   : CDxfExtMin::SetY
// Description     : Sets the Y-Cordinate of the point
// Return type     : void
// Argument        : const double& param_dYVal

void CDxfExtMin::SetY(const double& param_MinY)
{
	m_MinY = param_MinY;
	MakeValid();
}

// Function name   : CDxfExtMin::SetZ
// Description     : Sets the Z-Cordinate of the point
// Return type     : void
// Argument        : const double& param_dZVal

void CDxfExtMin::SetZ(const double& param_MinZ)
{
	m_MinZ = param_MinZ;
	MakeValid();
}




// Function name   : CDxfExtMin::GetX
// Description     : Retrives the X-Coordinate of the point
// Return type     : const double&
// Argument        : void

const double& CDxfExtMin::GetX(void) const
{
	return m_MinX;
}


// Function name   : CDxfExtMin::GetY
// Description     : Retrives the Y-Coordinate of the point
// Return type     : const double&
// Argument        : void

const double& CDxfExtMin::GetY(void) const
{
	return m_MinY;
}

// Function name   : CDxfExtMin::GetZ
// Description     : Retrives the Z-Coordinate of the point
// Return type     : const double&
// Argument        : void

const double& CDxfExtMin::GetZ(void) const
{
	return m_MinZ;
}

// Function name   : CDxfEntitiesSection::Parse
// Description     : Parses the entities section
// Return type     : DxfErrorCodes::DxfError
// Argument        : void

DxfErrorCodes::DxfError CDxfExtMin::Parse(void)
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
