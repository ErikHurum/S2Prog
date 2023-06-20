#pragma once
//////////////////////////////////////////////////////////////////////
// Class to make conversions required by XML parser
//
////////////////////////////////////////////////////////////////////////
class CConvertData
{
public:
	CConvertData(void);
	virtual ~CConvertData(void);
	// Function to convert passed integer value to CString and return it
	CString IntToCStr(IN int param_iValue) const;
	// Function to convert from CString to BStr and return Bstr
	BSTR CStrToBstr(IN CString param_pcStringValue);
	// To convert Integer value to BSTR
	BSTR IntToBstr(int param_iIntValue);
};
