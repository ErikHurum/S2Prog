#pragma once
#include ".\dxffile.h"
#include ".\cominc.h"
#include ".\dxfnamespaces.h"
#include ".\acdbpolyline.h"
#include ".\DxFPolyLine.h"
//#include "acdbHatch.h"
#include "dxfvalid.h"

// Class Name	: CDxfHatch
// Description	: Conatiner for set of polylines

class CDxfHatch : public CDxfPolyLine
{
public:
	CDxfHatch(CDxfFile& param_dxfFile);
	~CDxfHatch(void);
	vector <CAcDbPolyLine> m_acdbPolyline; // Array of polylines
    int GetCount(void) const;
	const CAcDbPolyLine& operator[](const int& param_nIndex) const;

public:
	virtual DxfErrorCodes::DxfError Parse(void);
};
