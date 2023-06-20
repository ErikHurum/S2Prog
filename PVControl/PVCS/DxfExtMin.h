#include "dxfvalid.h"
#include "dxfnamespaces.h"
#include ".\dxffile.h"
// Class Name	: CDxfExtMin
// Description	: Container class for 2D points in dxf layout.

class CDxfExtMin : public CDxfValid
{
public:
	CDxfExtMin(CDxfFile& param_dxfFile);	// Default constructor
	~CDxfExtMin(void);						// Destructor

private:
	CDxfFile& m_dxfFile;		// The dxf file
	double m_MinX;	// x-coordinate
	double m_MinY;	// y-coordinate
	double m_MinZ;	// z-coordinate

public:
	void SetX(const double& param_MinX);		// Sets the X-Coordinate of point
	void SetY(const double& param_MinY);		// Sets the Y-Coordinate of point
	void SetZ(const double& param_MinZ);		// Sets the Z-Coordinate of point

	const double& GetX(void) const;				// Retrives the X-Coordinate of the point
	const double& GetY(void) const;				// Retrives the Y-Coordinate of the point
	const double& GetZ(void) const;				// Retrives the Z-Coordinate of the point
	DxfErrorCodes::DxfError Parse(void);
};
