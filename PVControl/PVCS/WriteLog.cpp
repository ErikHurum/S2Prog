#include "StdAfx.h"
#include ".\writelog.h"

CWriteLog::CWriteLog(void)
: m_pcFilename(_T(""))
{

}

CWriteLog::~CWriteLog(void)
{
	// Deinitialize COM
	//::CoUninitialize();
}

// To Initialize the Log file and provide the name of file with the name it has to be logged
bool CWriteLog::InitLogHeader(CString param_pcFileName,CString param_strRootNodeName)
{
	InitCOM();
	Initialize();
	SetXMLHeader();
	WriteRootNode(param_strRootNodeName);
	m_pcFilename=param_pcFileName;
	return true;
}

// To write the error message generated to the log file along with date and time
bool CWriteLog::WriteLogData( const CString& param_strFile, const int& param_uiLine, const CString& param_strText )
{
	CString strLine;
	static int icount=0;
	icount++;
	strLine.Format("%d", param_uiLine );
	CreateElement("ErrorLog");
	CreateAttribute("Time",GetTime());
	CreateAttribute("SNo",IntToCStr(icount));
	CreateAttribute("FileName",param_strFile);
	CreateAttribute("LineNo",strLine);
	CreateNode( "FileName", param_strFile );
	CreateNode( "LineNo", strLine );
	CreateNode("ErrorText",param_strText);
	SaveXMLFile(m_pcFilename);
	return false;
}

CWriteLog::CWriteLog(const CString& param_strFileName)
{
	InitLogHeader( param_strFileName,"ERRORDATA" );
}

// Function to log the data about control object states
void CWriteLog::XMLLogControlObjectState(UINT param_strObjName,UINT param_uiNewValue,UINT param_uiChannelType)
{
		static UINT icount=0;
		icount++;
		CreateElement("LOG");
		CreateAttribute("DATE",GetTime());
		CreateAttribute("SNo",IntToCStr(icount));
		if(param_uiChannelType==0)
		{
			CreateNode("AnalogChannel",IntToCStr(param_strObjName));
		}
		else
		{
			CreateNode("DigitalChannel",IntToCStr(param_strObjName));
		}
		CreateNode("ChangedValue",IntToCStr(param_uiNewValue));
		SaveXMLFile("c:\\Windows\\Temp\\pvcslog.xml");
		bool res = SaveXMLFile(m_pcFilename);
		if (res==false)
		{
			;//AfxMessageBox("PROBLEM");
		}
}

#pragma warning (disable:4100)
void _XmlLogError( const CString& param_strFile, const int& param_uiLine, const CString& param_strText )
{
	
	static CWriteLog oLogFile("XMLErrorLog.xml");

	oLogFile.WriteLogData( param_strFile, param_uiLine, param_strText );
	
}


