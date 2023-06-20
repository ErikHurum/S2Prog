#pragma once
#include "dxffile.h"
#include ".\dxfnamespaces.h"
#include "DxfExtMin.h"
#include "DxfExtMax.h"

#include "dxfvalid.h"

// Class name	: CDxfHeaderSection
// Description	: Container class for the Header section in dxf

class CDxfHeaderSection : public CDxfValid
{
public:
	CDxfHeaderSection(CDxfFile& param_dxfFile);
	~CDxfHeaderSection(void);

private:
	CDxfFile&   m_dxfFile;
	CDxfExtMax	m_CDxfExtMax;
	CDxfExtMin	m_CDxfExtMin;
public:
	DxfErrorCodes::DxfError Parse(void);

	const double GetMaxX(void);
	const double GetMaxY(void);
	const double GetMinX(void);
	const double GetMinY(void);
};
