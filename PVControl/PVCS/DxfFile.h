#pragma once

#include ".\cominc.h"
#include ".\dxfvalue.h"
#include "dxfvalue.h"

// Class Name	: CDxfFile
// Description	: File handler for the dxf layout

class CDxfFile
{
public:
	CDxfFile(void);
	~CDxfFile(void);

private:
	ifstream	m_fstrFile;
	string		m_strFileName;
	CDxfValue	m_dxfValueLast;

public:
	bool				Open(const string& param_strFileName);
	void				Close(void);
	const CDxfValue&	GetLastValue(void) const;

	CDxfFile& operator>>(CDxfValue& param_dxfValue);
};
