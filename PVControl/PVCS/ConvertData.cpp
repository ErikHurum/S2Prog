#include "StdAfx.h"
#include ".\convertdata.h"

CConvertData::CConvertData(void)
{
}

CConvertData::~CConvertData(void)
{
	
}

// Function to convert passed integer value to CString and return it
CString CConvertData::IntToCStr(IN int param_iValue)const
{
	
	CString pcTempStr=NULL;
	pcTempStr.Format("%d",param_iValue);
	return pcTempStr;
}

// Function to convert from CString to BStr and return Bstr
BSTR CConvertData::CStrToBstr(IN CString param_pcStringValue)
{
	return param_pcStringValue.AllocSysString();	
}

// To convert Integer value to BSTR
BSTR CConvertData::IntToBstr(int param_iIntValue)
{
	CString pcTempStr=NULL;
	pcTempStr.Format("%d",param_iIntValue);
	return pcTempStr.AllocSysString();
}
