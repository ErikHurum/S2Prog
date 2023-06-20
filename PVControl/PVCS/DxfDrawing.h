#pragma once
#include "dxffile.h"
#include ".\dxfnamespaces.h"
#include "dxfheadersection.h"
#include "dxftablesection.h"
#include "dxfentitiessection.h"
#include "dxfvalid.h"


// Class name	: CDxfDrawing
// Description	: Container  for the drawing stored in dxf file

class CDxfDrawing : public CDxfValid
{
public:
	CDxfDrawing(void);
	~CDxfDrawing(void);

private:
	CDxfFile m_dxfFile;				// The dxf file
	CDxfHeaderSection 	m_dxfHeader;	// The header section
	CDxfTableSection 	m_dxfTable;	// The table section
	CDxfEntitiesSection m_dxfEntities;	// The entities section

	DxfErrorCodes::DxfError Parse(void);

public:
	DxfErrorCodes::DxfError Load(const string& param_strFileName);
	const CDxfEntitiesSection& Entity(void) const;
	const CDxfTableSection& Table(void) const;
	const double GetMaxX(void);
	const double GetMaxY(void);
	const double GetMinX(void);
	const double GetMinY(void);
};
