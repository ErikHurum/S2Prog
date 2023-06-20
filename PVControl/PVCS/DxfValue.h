#ifndef __DXFVALUE_H__
#define __DXFVALUE_H__
#pragma once

#include "cominc.h"
#include "./dxfvalid.h"

// Class Name	: CDxfValue : public CDxfValid
// Description	: Container for Group code and Value in the dxf file
class CDxfValue : public CDxfValid
{
friend ifstream& operator>>( ifstream& param_fin, CDxfValue& param_dxfValue );

public:
	CDxfValue(void);
	CDxfValue(const int& param_iCode, const string& param_strValue);
	~CDxfValue(void);

private:
	int m_iCode;		// The DXF group code
	string m_strValue;	// The corresponding value

public:
	const int&		Code(void) const;
	const string&	Value(void) const;

	bool operator==(const CDxfValue& param_dxfValue);
	bool operator!=(const CDxfValue& param_dxfValue);

	operator int()
	{
		return atoi( m_strValue.c_str() );
	}

	operator double()
	{
		return atof( m_strValue.c_str() );
	}
};

#endif //__DXFVALUE_H__