#include "StdAfx.h"
#include ".\readlegends.h"

CReadLegends::CReadLegends(void)
{
}

CReadLegends::~CReadLegends(void)
{

}



// TO read The tags and return the data of specified tag
CString CReadLegends::ReadTags(unsigned int param_uiLegendIndex, CString param_pcTagName)
{
	MSXML2::IXMLDOMNodeListPtr m_pNodeList;
	MSXML2::IXMLDOMNodePtr m_pTempChild;
	MSXML2::IXMLDOMNodePtr m_pTempChildVal;

	_bstr_t m_strLegendIndex(IntToBstr(param_uiLegendIndex),FALSE);
	BSTR m_bstrValue=NULL;
	BSTR TagNames;
	CString m_pcRetValue;
	
	TagNames=CStrToBstr(param_pcTagName);
	m_pNodeList=GetNode("legend");
	
	for(int j=0;j<m_pNodeList->length;j++)
	{
		m_pNodeList->get_item(j, &m_pTempChild);
		m_pTempChild->get_text(&m_bstrValue);
		
		m_pTempChildVal=m_pTempChild->selectSingleNode("lindex");
		if(m_pTempChildVal==NULL)
		{
			::SysFreeString(m_bstrValue);
			::SysFreeString(TagNames);
			::SysFreeString(m_strLegendIndex);
			m_pcRetValue=" ";
		}
		else
		{
			m_pcRetValue.Format(_T("%s"), (LPCTSTR)m_pTempChildVal->text);
			if(!strcmp(m_pcRetValue,m_strLegendIndex))
			{
				m_pTempChildVal=m_pTempChild->selectSingleNode(TagNames);
				if(m_pTempChildVal==NULL)
				{
					m_pcRetValue=" ";
				}
				else
				{
					m_pcRetValue.Format(_T("%s"), (LPCTSTR)m_pTempChildVal->text);
					::SysFreeString(m_strLegendIndex);
					::SysFreeString(m_bstrValue);
					::SysFreeString(TagNames);
					return m_pcRetValue;
				}
			}

		}
	}
	::SysFreeString(TagNames);
	::SysFreeString(m_strLegendIndex);
	::SysFreeString(m_bstrValue);
	return m_pcRetValue;
}

// To get The Name Of the Specified Legend Index
CString CReadLegends::GetLegendName(unsigned int param_uiLegendIndex)
{
	CString m_pcLegendName=ReadTags(param_uiLegendIndex,"lname");
	return m_pcLegendName;
}

// Function to return the colr of the specified Legend Index
COLORREF CReadLegends::GetLegendColor(unsigned int param_uiLegendIndex)
{
	int m_iRED=0,
		m_iGREEN=0,
		m_iBLUE=0;

	COLORREF m_colLegendColor=RGB(0,0,0);

		m_iRED=GetRED(param_uiLegendIndex);
		m_iGREEN=GetGREEN(param_uiLegendIndex);
		m_iBLUE=GetBLUE(param_uiLegendIndex);

	m_colLegendColor=RGB(m_iRED,m_iGREEN,m_iBLUE);

	return m_colLegendColor;
}

// To Read RED from The File 
int CReadLegends::GetRED(unsigned int param_uiLegendIndex)
{
	int m_iRED=0;
	CString m_pcRED=ReadTags(param_uiLegendIndex,"lRED");
	m_iRED=atoi(m_pcRED);
	return m_iRED;
}

// To Read GREEN from the File
int CReadLegends::GetGREEN(unsigned int param_uiLegendIndex)
{
	int m_iGREEN=0;
	CString m_pcGREEN=ReadTags(param_uiLegendIndex,"lGREEN");
	m_iGREEN=atoi(m_pcGREEN);
	return m_iGREEN;
}

// To get the Blue from the file
int CReadLegends::GetBLUE(unsigned int param_uiLegendIndex)
{
	int m_iBLUE=0;
	CString m_pcBLUE=ReadTags(param_uiLegendIndex,"lBLUE");
	m_iBLUE=atoi(m_pcBLUE);
	return m_iBLUE;
}

// To count the Number of legends
unsigned int CReadLegends::GetLegendCount(void)
{
	MSXML2::IXMLDOMNodeListPtr m_pNodeList;	
	unsigned int m_uiNodeCount=0;

	m_pNodeList=GetNode("legend");
	m_uiNodeCount=m_pNodeList->length;
	
	m_pNodeList=NULL;
	return m_uiNodeCount;
}
