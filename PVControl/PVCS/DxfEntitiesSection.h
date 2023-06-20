#pragma once
#include ".\dxffile.h"
#include ".\cominc.h"
#include ".\dxfnamespaces.h"
#include "dxfline.h"
#include "dxfpolyline.h"
#include "dxfHatch.h"
#include "dxftext.h"
#include "dxfvalid.h"
#include "dxfmtext.h"

// Class name	: CDxfEntitiesSection
// Description	: Container for the Entities Section in Dxf

class CDxfEntitiesSection : public CDxfValid
{
public:
	CDxfEntitiesSection(CDxfFile& param_dxfFile);
	~CDxfEntitiesSection(void);

private:
	CDxfFile& m_dxfFile;		// The dxf file
	CDxfPolyLine m_dxfPolyLine;	// The polyline entities
    CDxfHatch m_dxfHatch;		// The boundry path data
	CDxfText m_dxfText;			// The text entities
	CDxfMText m_dxfMText;		// The multiline text entities

public:
	const CDxfLine& Line(void) const;
	const CDxfPolyLine& Polyline(void) const;
	const CDxfHatch& Hatch(void) const;
	const CDxfText& Text(void) const;
	const CDxfMText& MText(void) const;
	DxfErrorCodes::DxfError Parse(void);
};
