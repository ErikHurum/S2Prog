#include "StdAfx.h"
#include ".\dxfpoint.h"


// Function name   : CDxfPoint::CDxfPoint
// Description     : Default constructor
// Return type     :
// Argument        : void

CDxfPoint::CDxfPoint(void)
: m_dXCoord(0.0)
, m_dYCoord(0.0)
, m_dBulge(0.0)
{
}


// Function name   : CDxfPoint::CDxfPoint
// Description     : Constructor
// Return type     :
// Argument        : const double& param_dXVal
// Argument        : const double& param_dYVal
// Argument        : const double& param_dBulge

CDxfPoint::CDxfPoint(const double& param_dXVal, const double& param_dYVal, const double& param_dBulge)
{
	m_dXCoord = param_dXVal;
	m_dYCoord = param_dYVal;

	m_dBulge = param_dBulge;

	MakeValid();
}


// Function name   : CDxfPoint::~CDxfPoint
// Description     : Destructor
// Return type     :
// Argument        : void

CDxfPoint::~CDxfPoint(void)
{
}


// Function name   : CDxfPoint::SetX
// Description     : Sets the X-Coordinate of point
// Return type     : void
// Argument        : const double& param_dXVal

void CDxfPoint::SetX(const double& param_dXVal)
{
	m_dXCoord = param_dXVal;
	MakeValid();
}


// Function name   : CDxfPoint::SetY
// Description     : Sets the Y-Cordinate of the point
// Return type     : void
// Argument        : const double& param_dYVal

void CDxfPoint::SetY(const double& param_dYVal)
{
	m_dYCoord = param_dYVal;
	MakeValid();
}


// Function name   : CDxfPoint::SetBulge
// Description     : Sets the bulge value for the point
// Return type     : void
// Argument        : const double& param_dBulge

void CDxfPoint::SetBulge(const double& param_dBulge)
{
	m_dBulge = param_dBulge;
	MakeValid();
}


// Function name   : CDxfPoint::GetX
// Description     : Retrives the X-Coordinate of the point
// Return type     : const double&
// Argument        : void

const double& CDxfPoint::GetX(void) const
{
	return m_dXCoord;
}


// Function name   : CDxfPoint::GetY
// Description     : Retrives the Y-Coordinate of the point
// Return type     : const double&
// Argument        : void

const double& CDxfPoint::GetY(void) const
{
	return m_dYCoord;
}



// Function name   : CDxfPoint::GetBulge
// Description     : Retrives the bulge value of the point
// Return type     : const double&
// Argument        : void

const double& CDxfPoint::GetBulge(void) const
{
	return m_dBulge;
}
