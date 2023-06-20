#pragma once
#include "dxfvalid.h"

// Class Name	: CDxfPoint
// Description	: Container class for 2D points in dxf layout.

class CDxfPoint : public CDxfValid
{
public:
	CDxfPoint(void);						// Default constructor
	CDxfPoint(const double& param_dXVal,	// Constructor
		const double& param_dYVal,
		const double& param_dBulge = 0.0f);
	~CDxfPoint(void);						// Destructor

private:
	double m_dXCoord;	// x-coordinate
	double m_dYCoord;	// y-coordinate

	double m_dBulge;	// the bulge factor if the object is a vertex of polyline

public:
	void SetX(const double& param_dXVal);		// Sets the X-Coordinate of point
	void SetY(const double& param_dYVal);		// Sets the Y-Coordinate of point
	void SetBulge(const double& param_dBulge);	// Sets the bulge value of point

	const double& GetX(void) const;				// Retrives the X-Coordinate of the point
	const double& GetY(void) const;				// Retrives the Y-Coordinate of the point
	const double& GetBulge(void) const;			// Retrives the bulge value of the point
};
