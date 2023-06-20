#pragma once

#define IN
#define OUT
#include "convertdata.h"
#include <string>
//#include "afx.h"
using namespace std;
// XML DOM dll MSXML 4
#import <msxml6.dll> 
using namespace MSXML2;
class CCalibrationData: public CConvertData
{
public:
	CCalibrationData(void);
	virtual ~CCalibrationData(void);
	// TO initialize dom
	HRESULT InitializeXMLParcer(void);
	// pointer to the XML DOM Document
	MSXML2::IXMLDOMDocumentPtr m_plDomDocument;
	// to load xmlfile
	bool LoadXMLFile(CString param_pcXMLFileName);

	MSXML2::IXMLDOMElementPtr m_pDocRoot;

	MSXML2::IXMLDOMNodePtr m_pNode;
	MSXML2::IXMLDOMNodePtr m_pFileNode;
	MSXML2::IXMLDOMNodeListPtr pNodeList;
	bool SaveCalibrationFile(CString param_pcFileName);
	// to create node
	bool CreateNode(CString param_pcNodeName, CString param_pcNodeValue);
	// add root node
	bool WriteRootNode(CString param_pcRootNodeName);
	bool CreateElement(CString param_pcElementName);
	bool Remove_Node(CString param_ObjectName,CString param_ChannelNumber); 
	// to write data to calibration file
	bool WriteDataToFile(CString param_psObjName, CString param_psStartValue, CString param_psStopValue);
	bool SetXMLHeader(void);
private:
	CFile m_FileHandle;
};
