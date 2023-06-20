#pragma once
#include ".\dxffile.h"
#include ".\cominc.h"
#include ".\dxfnamespaces.h"
#include "acdbpolyline.h"
#include "dxfvalid.h"

// Class Name	: CDxfPolyline
// Description	: Conatiner for set of polylines

class CDxfPolyLine : public CDxfValid
{
public:
	CDxfPolyLine(CDxfFile& param_dxfFile);
	~CDxfPolyLine(void);

protected:
	CDxfFile& m_dxfFile;	// The dxf file
	vector <CAcDbPolyLine> m_acdbPolyline; // Array of polylines

public:
	virtual DxfErrorCodes::DxfError Parse(void);
	CDxfFile& GetDxfFile(void) const;
    vector <CAcDbPolyLine> GetPolyLineVector(void) const;
    void AddPolyLineVector(vector <CAcDbPolyLine> p_acdbPolyline);
    virtual int GetCount(void) const;
	virtual const CAcDbPolyLine& operator[](const int& param_nIndex) const;
};
