#pragma once
#include "writexml.h"
////////////////////////////////////////////////////////////////////////
// Class To Create LOG file using XML writer class
//
////////////////////////////////////////////////////////////////////////
class CWriteLog :
	public CWriteXML
{
	
public:
	CWriteLog(void);
	virtual ~CWriteLog(void);
	// To Initialize the Log file and provide the name of file with the name it has to be logged
	bool InitLogHeader(CString param_pcFileName,CString param_strRootNodeName);
	// To store the file name
	CString m_pcFilename;
	// To write the error message generated to the log file along with date and time
	bool WriteLogData( const CString& param_strFile, const int& param_uiLine, const CString& param_strText );
	CWriteLog(const CString& param_strFileName);
	// Function to log the data about control object states
	void XMLLogControlObjectState(UINT param_strObjName,UINT param_uiNewValue,UINT param_uiChannelType);
};

void _XmlLogError( const CString& param_strFile, const int& param_uiLine, const CString& param_strText );

#define XmlLogError( txt )  _XmlLogError( __FILE__, __LINE__, txt )
