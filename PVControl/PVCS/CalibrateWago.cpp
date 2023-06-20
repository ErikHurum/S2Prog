#include "StdAfx.h"
#include ".\calibratewago.h"
#include <vector>

CCalibrateWago::CCalibrateWago(void)
{
}

CCalibrateWago::~CCalibrateWago(void)
{
}

CString CCalibrateWago::GetNodeData(CString param_psObjectName,CString param_pcTagName)
{
	MSXML2::IXMLDOMNodeListPtr pNodeList;
	MSXML2::IXMLDOMNodePtr pTempChild;
	MSXML2::IXMLDOMNodePtr pTempChildVal;
	//BSTR TagNames;
	_bstr_t strTagNames(CStrToBstr(param_pcTagName),FALSE);
	_bstr_t TagNames(CStrToBstr(param_psObjectName),FALSE);
	CString pcRetValue;
	
	//TagNames=_com_util::ConvertStringToBSTR(param_psObjectName);
	
	pNodeList=GetNode("Data");
	
	for(int j=0;j<pNodeList->length;j++)
	{
		pNodeList->get_item(j, &pTempChild);
	
		
		pTempChildVal=pTempChild->selectSingleNode("ObjectName");
		if(pTempChildVal==NULL)
		{
			::SysFreeString(strTagNames);
			::SysFreeString(TagNames);
			return " ";
		}
		else
		{
			pcRetValue.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
			if(!strcmp(pcRetValue,TagNames))
			{
				m_CData.ObjectName = pcRetValue;

				pTempChildVal=pTempChild->selectSingleNode("Channelnumber");
				pcRetValue.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
				m_CData.Channel=pcRetValue;

				pTempChildVal=pTempChild->selectSingleNode("Row");
				pcRetValue.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
				m_CData.Row=pcRetValue;

				pTempChildVal=pTempChild->selectSingleNode("Start");
				pcRetValue.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
				m_CData.Channel=pcRetValue;

				pTempChildVal=pTempChild->selectSingleNode("Stop");
				pcRetValue.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
				m_CData.Channel=pcRetValue;

				pTempChildVal=pTempChild->selectSingleNode(strTagNames);
				if(pTempChildVal==NULL)
				{
				::SysFreeString(strTagNames);
				::SysFreeString(TagNames);
				return " ";
				}
				pcRetValue.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
				::SysFreeString(strTagNames);
				::SysFreeString(TagNames);
				return pcRetValue;
			}
			CCalibrateWago::m_CalibrateData.push_back(m_CData);
			}
		}
			::SysFreeString(TagNames);
			::SysFreeString(strTagNames);
		return " ";
}

// to get start value of a object
CString CCalibrateWago::GetStartValue(CString param_pcObjectName)
{
	CString pcRetValue;
	pcRetValue=GetNodeData(param_pcObjectName,"Start");
	return pcRetValue;
}

// to get stop value of the calibration
CString CCalibrateWago::GetStopValue(CString param_pcObjectName)
{
	CString pcRetValue;
	pcRetValue=GetNodeData(param_pcObjectName,"Stop");
	return pcRetValue;
}

// To get the Name of the Object
CString CCalibrateWago::GetChannelNo(CString param_pcObjectName)
{
	CString pcRetValue;
	pcRetValue=GetNodeData(param_pcObjectName,"Channelnumber");
	return pcRetValue;
}

int CCalibrateWago::NumberOfNodes(void)
{
	int iNumber=0;
	MSXML2::IXMLDOMNodeListPtr pNodeList;
	pNodeList=GetNode("Data");
	iNumber = pNodeList->length;
	return iNumber;
}

void CCalibrateWago::GetCalibrationDataVector(void)
{
	MSXML2::IXMLDOMNodeListPtr pNodeList;
	MSXML2::IXMLDOMNodePtr pTempChild;
	MSXML2::IXMLDOMNodePtr pTempChildVal;

	CString pcRetValue;
	
	//TagNames=_com_util::ConvertStringToBSTR(param_psObjectName);
	
	pNodeList=GetNode("Data");
	
	for(int j=0;j<pNodeList->length;j++)
	{
		pNodeList->get_item(j, &pTempChild);

		pTempChildVal=pTempChild->selectSingleNode("ObjectName");
		if(pTempChildVal==NULL)
		{
			pcRetValue="";
		}
		else
		{
				pcRetValue.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
				m_CData.ObjectName = pcRetValue;

				pTempChildVal=pTempChild->selectSingleNode("Row");
				pcRetValue.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
				m_CData.Row=pcRetValue;
				
				pTempChildVal=pTempChild->selectSingleNode("Channelnumber");
				pcRetValue.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
				m_CData.Channel=pcRetValue;

				pTempChildVal=pTempChild->selectSingleNode("Start");
				pcRetValue.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
				m_CData.StartText=pcRetValue;

				pTempChildVal=pTempChild->selectSingleNode("Stop");
				pcRetValue.Format(_T("%s"), (LPCTSTR)pTempChildVal->text);
				m_CData.StopText=pcRetValue;
		}
			CCalibrateWago::m_CalibrateData.push_back(m_CData);
		}
		
	
}
