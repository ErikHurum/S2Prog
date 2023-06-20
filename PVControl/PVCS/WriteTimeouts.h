#pragma once
#include "writexml.h"
#include "readxmltagnode.h"
#include "Mswsock.h"
#include ".\pvcs v1.0.h"
#include <comdef.h>
#include <comutil.h>
#include <vector>

struct WarningTimeout{
		CString ObjID;//ObjectName;
		CString TimeRaised;//Channel;
		CString MachineIP;//StartText;
		CString Message;//StopText;
	};

class CWriteTimeouts :public CWriteXML 
{
protected:
	MSXML2::IXMLDOMDocumentPtr mm_plDomDocument;
	MSXML2::IXMLDOMElementPtr mm_pDocRoot;
	MSXML2::IXMLDOMTextPtr mm_pTextPtr; 
	MSXML2::IXMLDOMNodeListPtr pNodeList;


public: 
	CWriteTimeouts(void);
	virtual ~CWriteTimeouts(void);
	void PreserveRootPointer(CString sNumber);
	//function to create element
	void Create_Element_Function(CString ElementName);
	bool InitTimeoutHeader(CString param_pcFileName, CString param_strRootNodeName);
	// To write the block to the XML file

	bool WriteWarningMessageToFile(CString objName , CString Message);
	//To load XML file if already exists
	bool LoadTimeOutXML(CString t_FileName);
	void GetRootPointer();
	bool ReadXMLFile(CString t_FileName);
	bool FindScreen(CString sno);
	MSXML2::IXMLDOMNodeListPtr GetNode(CString param_pcNodeName);
	CString m_pcFilename;
    //function to remove warning message object name node   
	bool Remove_ControlEntry_WarningMessage(CString param_screenNumber,CString node_name, CString controlName);
		
	////////////////////////////////////////////////////////////////////////////////////////////
	bool WriteTimeOutDataToFile(const CString& param_objectID, CString MachineIP);
	bool NodeName_TimeOut(CString node,CString param_ObjectName);
	//function to remove timeout details from XML file   
	bool Remove_ControlEntry_TimeOut(CString param_screenNumber , CString node_name, CString controlName);
	bool RemoveUpdateScreenNumberInBuffer(CString param_screenNumber,CString param_writeData);
	CString Get_Machine_IP();
		
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	CString ReadFileData(CString param_ScreenNumber); 
	////////////////////////////////////////////////////////////////////////////////////////////

	static vector <WarningTimeout> m_WarningTimeout;
	// to return object name and channels in a vector
	
	
	WarningTimeout m_CData;
	bool NodeName_WarningMessage(CString node,CString param_ObjectName,CString pram_Message);

	///////////////////////////////////////////////////////////////////////////////////////////////
	typedef struct WarningData{
		CString ObjectName;
		CString Message;
	}WarningData;

	typedef vector <WarningData> WarningDataList;
	// to return object name and channels in a vector
	
	WarningDataList m_WarningData;

	WarningData m1_CData;
 	void FillVector();
	void FillVector_TimeOut();
	bool LoadXMLData(CString param_pcXMLData);
	bool UpdateXMLFile( CString param_screenNumber,CString param_NewBufferData);
	CString GetDialogTimeOutFile();
	void CreateXMLFile(CString param_buffer);
	void CreateDialogTimeOutFile(CString param_buffer);  
	CString GetOnlyTimeOutsFromFile();
 	void Load_TimeOuts_FromFile_IN_XMLFormat(CString param_format); 
	bool Search_Replace(/*MSXML2::IXMLDOMNodePtr*/CString param_nodeName,MSXML2::IXMLDOMElementPtr);//,_bstr_t);
	bool LoadXML_ScreenNumberData(CString param_screenNumberData);
};