#pragma once
#include ".\dxffile.h"
#include ".\cominc.h"
#include ".\dxfnamespaces.h"
#include ".\acdbpolyline.h"
#include ".\DxFPolyLine.h"
#include "dxfvalid.h"

// Class Name	: CDxfLine
// Description	: Conatiner for set of polylines

class CDxfLine : public CDxfPolyLine
{
public:
	CDxfLine(CDxfFile& param_dxfFile);
	~CDxfLine(void);
public:
	DxfErrorCodes::DxfError Parse(void);
};
