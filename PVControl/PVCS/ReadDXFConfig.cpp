#include "StdAfx.h"
#include ".\readdxfconfig.h"

CReadDXFConfig::CReadDXFConfig(void)
{
}

CReadDXFConfig::~CReadDXFConfig(void)
{
}

// To get the File details
CString CReadDXFConfig::GetFileDetails(CString param_pcHeaderName, CString param_pcTagName)
{
	MSXML2::IXMLDOMNodeListPtr pNodeList;
	MSXML2::IXMLDOMNodePtr pTempChild;
	MSXML2::IXMLDOMNodePtr pTempChildVal;
	BSTR TagNames;
	CString pcRetValue;
	if(XMLFileLoadStatus==false)
	{
		return "NULL";
	}

	TagNames=CStrToBstr(param_pcTagName);
	pNodeList=GetNode(param_pcHeaderName);

	for(int j=0;j<pNodeList->length;j++)
	{
		pNodeList->get_item(j, &pTempChild);

		pTempChildVal=pTempChild->selectSingleNode(TagNames);
		if(pTempChildVal==NULL)
		{
			pcRetValue=" ";
		}
		else
		{
			pcRetValue.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
			::SysFreeString(TagNames);
			return pcRetValue;

		}
	}
		::SysFreeString(TagNames);
		return pcRetValue;
}

// To get the data from a specific tag
CString CReadDXFConfig::ReadTags(unsigned int param_uiTankNumber, CString param_pcTagName)
{
	MSXML2::IXMLDOMNodeListPtr pNodeList;
	MSXML2::IXMLDOMNodePtr pTempChild;
	MSXML2::IXMLDOMNodePtr pTempChildVal;
	_bstr_t m_strLegendIndex(IntToBstr(param_uiTankNumber),FALSE);
	BSTR TagNames;
	CString pcRetValue;
	CString uiLegendIndex;

	TagNames=CStrToBstr(param_pcTagName);
	pNodeList=GetNode("dxf");

	for(int j=0;j<pNodeList->length;j++)
	{
		pNodeList->get_item(j, &pTempChild);

		pTempChildVal=pTempChild->selectSingleNode("dxftankno");
		if(pTempChildVal==NULL)
		{
			::SysFreeString(m_strLegendIndex);
			::SysFreeString(TagNames);
			return " ";
		}
		else
		{
			pcRetValue.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
			if(!strcmp(pcRetValue,m_strLegendIndex))
			{
				pTempChildVal=pTempChild->selectSingleNode(TagNames);
				if(pTempChildVal==NULL)
				{
					pcRetValue=" ";
				}
				else
				{
					pcRetValue.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
					::SysFreeString(m_strLegendIndex);
					::SysFreeString(TagNames);
					return pcRetValue;
				}
			}

		}
	}
		::SysFreeString(TagNames);
		::SysFreeString(m_strLegendIndex);
		return pcRetValue;
}



// Function to return the Legend Index for the Tank Index Provided
int CReadDXFConfig::GetTankLegendIndex(unsigned int param_uiTankIndex)
{
	int iLegendIndex;
	CString pcTempLegendIndex;
	pcTempLegendIndex=ReadTags(param_uiTankIndex,"legendindex");
	iLegendIndex=atoi(pcTempLegendIndex);
	return iLegendIndex;
}


    // To get The background color of the dxf-drawing
int CReadDXFConfig::GetBackGroundColor(unsigned int param_uiTankIndex, bool *Success)
{
    CString pcTempBKColor   = ReadTags(param_uiTankIndex,"dxfBackground");
	if (Success) {
		*Success = pcTempBKColor.GetLength() > 2;
	}
	unsigned long BackGroundCol = unsigned(strtoul(pcTempBKColor, NULL, 0));
	return int(BackGroundCol);
}

    // To get The background color of the object whose index is provided
int CReadDXFConfig::GetObjectColor(unsigned int param_uiTankIndex, bool *Success)
{
    CString pcTempObjColor   = ReadTags(param_uiTankIndex,"dxfObjectColor");
	if (Success) {
		*Success = pcTempObjColor.GetLength() > 2;
	}
	unsigned long ObjectCol = int(strtoul (pcTempObjColor,NULL,0));
	return int(ObjectCol);
}

// To get The line color of the object whose index is provided
int CReadDXFConfig::GetLineColor(unsigned int param_uiTankIndex, bool *Success) {
	CString pcTempLineColor   = ReadTags(param_uiTankIndex, "dxfLineColor");
	if (Success) {
		*Success = pcTempLineColor.GetLength() > 2;
	}
	unsigned long LineCol = int(strtoul(pcTempLineColor, NULL, 0));
	return LineCol;
}

// To get The text color of the object whose index is provided
int CReadDXFConfig::GetTextColor(unsigned int param_uiTankIndex, bool *Success) {
	CString pcTempTextColor   = ReadTags(param_uiTankIndex, "dxfTextColor");
	if (Success) {
		*Success = pcTempTextColor.GetLength() > 2;
	}
	unsigned long TextCol = int(strtoul(pcTempTextColor, NULL, 0));
	return TextCol;
}

// To get The text color of the object whose index is provided
int CReadDXFConfig::GetUndefObjectColor(unsigned int param_uiTankIndex, bool *Success) {
	CString pcTempUndefObjectColor   = ReadTags(param_uiTankIndex, "dxfUndefObjectColor");
	if (Success) {
		*Success = pcTempUndefObjectColor.GetLength() > 2;
	}
	unsigned long UndefObjectCol = int(strtoul(pcTempUndefObjectColor, NULL, 0));
	return UndefObjectCol;
}


//Get X-scale
double CReadDXFConfig::GetScaleX(unsigned int param_uiTankIndex)
{
    CString strScale  = ReadTags(param_uiTankIndex,"ScaleX");
    double Scale      = atof(strScale);
    if (Scale < 1.0 || Scale >= 10.0 ) {
        Scale = 1.0;
    }
    return Scale;
}

//Get Y-scale
double CReadDXFConfig::GetScaleY(unsigned int param_uiTankIndex)
{
    CString strScale  = ReadTags(param_uiTankIndex,"ScaleY");
    double Scale      = atof(strScale);
    if (Scale < 1.0 || Scale >= 10.0 ) {
        Scale = 1.0;
    }
    return Scale;
}

// Function to return the DXF file name of the TAnk index provided
CString CReadDXFConfig::GetTankDXFFile(unsigned int param_uiTankIndex)
{
	CString pcDXFTankFile;
	pcDXFTankFile=ReadTags(param_uiTankIndex,"dxftankfile");
	return pcDXFTankFile;
}

// Function to get the Layer to display of teh given tank Index from Cargo or Ballast
CString CReadDXFConfig::GetTankLayer(unsigned int param_uiTankIndex)
{
	CString pcDXFTankFile;
	pcDXFTankFile=ReadTags(param_uiTankIndex,"dxflayer");
	return pcDXFTankFile;
}

// To get The Name of the tank whose index is provided
CString CReadDXFConfig::GetTankName(unsigned int param_uiTankIndex)
{
	CString pcTankName;
	pcTankName=ReadTags(param_uiTankIndex,"dxftankname");
	return pcTankName;
}

CString CReadDXFConfig::GetScreenTitle(int ScreenIndex)
{
	CString pcScreenTitle = "";
	CString HeaderName = "";
	HeaderName.Format("dxfS%d",ScreenIndex);
	pcScreenTitle = GetFileDetails(HeaderName,"dxfSTitle");
	return pcScreenTitle;
}
CString CReadDXFConfig::GetScreenFile(int ScreenIndex)
{
	CString pcScreenFile = "";
	CString HeaderName = "";
	HeaderName.Format("dxfS%d",ScreenIndex);
	pcScreenFile = GetFileDetails(HeaderName,"dxfScreenfile");
	return pcScreenFile;
}

CString CReadDXFConfig::GetScreenTankLayer(int ScreenIndex)
{
	CString pcScreenTankLayer;
	CString HeaderName;
	HeaderName.Format("dxfS%d",ScreenIndex);
	pcScreenTankLayer = GetFileDetails(HeaderName,"dxfSlayer");
	return pcScreenTankLayer;
}


int CReadDXFConfig::GetScreenColor(int ScreenIndex, bool *Success)
{
	CString HeaderName;
	HeaderName.Format("dxfS%d",ScreenIndex);
	CString pcTempObjColor = GetFileDetails(HeaderName,"dxfScreenObjectColor");
	if (Success) {
		*Success = pcTempObjColor.GetLength() > 2;
	}
	if (pcTempObjColor.GetLength() > 2) {
		unsigned long ObjectCol = int(strtoul (pcTempObjColor,NULL,0));
		return int(ObjectCol);
	}else {
		pcTempObjColor = GetFileDetails(HeaderName,"dxfObjectColor");
		if (Success) {
			*Success = pcTempObjColor.GetLength() > 2;
		}
		if (pcTempObjColor.GetLength() > 2) {
			unsigned long ObjectCol = int(strtoul (pcTempObjColor,NULL,0));
			return int(ObjectCol);
		}
	}
	return  0;
}

int CReadDXFConfig::GetScreenBckGndColor(int ScreenIndex, bool *Success)
{
	CString HeaderName;
	HeaderName.Format("dxfS%d",ScreenIndex);
	CString pcTempObjColor = GetFileDetails(HeaderName,"dxfScreenBackgroundColor");
	if (Success) {
		*Success = pcTempObjColor.GetLength() > 2;
	}
	if (pcTempObjColor.GetLength() > 2) {
		unsigned long ObjectCol = int(strtoul (pcTempObjColor,NULL,0));
		return int(ObjectCol);
	}else {
		pcTempObjColor = GetFileDetails(HeaderName,"dxfBackground");
		if (Success) {
			*Success = pcTempObjColor.GetLength() > 2;
		}
		if (pcTempObjColor.GetLength() > 2) {
			unsigned long ObjectCol = int(strtoul (pcTempObjColor,NULL,0));
			return int(ObjectCol);
		}
	}
	return  0;
}


// To get The line color of the object whose index is provided
int CReadDXFConfig::GetScreenLineColor(int ScreenIndex, bool *Success) {
	CString HeaderName;
	HeaderName.Format("dxfS%d",ScreenIndex);
	CString pcTempLineColor = GetFileDetails(HeaderName, "dxfLineColor");
	if (Success) {
		*Success = pcTempLineColor.GetLength() > 2;
	}
	unsigned long LineCol = int(strtoul(pcTempLineColor, NULL, 0));
	return LineCol;
}

// To get The text color of the object whose index is provided
int CReadDXFConfig::GetScreenTextColor(int ScreenIndex, bool *Success) {
	CString HeaderName;
	HeaderName.Format("dxfS%d",ScreenIndex);
	CString pcTempTextColor   = GetFileDetails(HeaderName, "dxfTextColor");
	if (Success) {
		*Success = pcTempTextColor.GetLength() > 2;
	}
	unsigned long TextCol = int(strtoul(pcTempTextColor, NULL, 0));
	return TextCol;
}

