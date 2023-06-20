#pragma once
#include "dxftext.h"

// Class name	: CDxfMText
// Description	: Conatiner class for a set of multiline text in dxf file
class CDxfMText :
	public CDxfText
{
public:
	CDxfMText(CDxfFile& param_dxfFile);
	~CDxfMText(void);
};
