#pragma once
#include ".\dxffile.h"
#include ".\cominc.h"
#include ".\dxfnamespaces.h"
#include "acdbtext.h"
#include "dxfvalid.h"

// Class name	: CDxfText
// Description	: Conatiner class for a set of text in dxf file
class CDxfText: public CDxfValid
{
public:
	CDxfText(CDxfFile& param_dxfFile);
	~CDxfText(void);

protected:
	CDxfFile& m_dxfFile;			// The dxf file
	vector <CAcDbText> m_acdbText;  // Array of text entities

public:
	DxfErrorCodes::DxfError Parse(void);

	int		GetCount(void) const;

	const CAcDbText& operator[](const int& param_nIndex) const;
};
