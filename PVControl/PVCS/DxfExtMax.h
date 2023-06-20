#pragma once
#include "dxfvalid.h"
#include ".\dxfnamespaces.h"
#include ".\dxffile.h"
// Class Name	: CDxfExtMax
// Description	: Container class for 2D points in dxf layout.

class CDxfExtMax : public CDxfValid
{
public:
	CDxfExtMax(CDxfFile& param_dxfFile);// Default constructor
	~CDxfExtMax(void);						// Destructor

private:
	CDxfFile& m_dxfFile;		// The dxf file
	double m_MaxX;	// x-coordinate
	double m_MaxY;	// y-coordinate
    double m_MaxZ;	// z-coordinate

public:
	void SetX(const double& param_MaxX);		// Sets the X-Coordinate of point
	void SetY(const double& param_MaxY);		// Sets the Y-Coordinate of point
    void SetZ(const double& param_MaxZ);		// Sets the Y-Coordinate of point

	const double& GetX(void) const;				// Retrives the X-Coordinate of the point
	const double& GetY(void) const;				// Retrives the Y-Coordinate of the point
    const double& GetZ(void) const;				// Retrives the Z-Coordinate of the point
	DxfErrorCodes::DxfError Parse(void);
};
