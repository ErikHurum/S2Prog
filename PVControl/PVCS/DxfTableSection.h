#pragma once
#include ".\dxffile.h"
#include ".\cominc.h"
#include ".\dxfnamespaces.h"
#include ".\acdblayertablerecord.h"
#include "dxflayer.h"
#include "dxfvalid.h"

// Class name	: CDxfTableSection
// Description	: Container class for the Table section in dxf
class CDxfTableSection : public CDxfValid
{
public:
	CDxfTableSection(CDxfFile& param_dxfFile);
	~CDxfTableSection(void);

private:
	CDxfFile& m_dxfFile; // The dxf file
	CDxfLayer m_dxfLayer;// The layer name

public:
	DxfErrorCodes::DxfError	Parse(void);
	const CDxfLayer&		Layer(void) const;
};
