#pragma once
#include ".\dxffile.h"
#include ".\cominc.h"
#include ".\dxfnamespaces.h"
#include ".\acdblayertablerecord.h"
#include "dxfvalid.h"

// Class name	: CDxfLayer
// Descrption	: Conatiner class for Layer information in dxf

class CDxfLayer : public CDxfValid
{
public:
	CDxfLayer(CDxfFile& param_dxfFile);
	~CDxfLayer(void);

private:
	CDxfFile& m_dxfFile;
	vector <CAcDbLayerTableRecord> m_dxfLayerTable;

public:
	DxfErrorCodes::DxfError Parse(void);

	int						GetCount(void) const;
	CAcDbLayerTableRecord	GetLayer(const string& param_strLayerName) const;
	int	                    GetColor(const string& param_strLayerName) const;

	const CAcDbLayerTableRecord& operator[](const int& nIndex) const;
    static int GetRGBColor(int Index);
};
