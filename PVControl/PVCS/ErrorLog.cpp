#include "StdAfx.h"
#include ".\errorlog.h"

CErrorLog::CErrorLog(void)
{
}

CErrorLog::~CErrorLog(void)
{	
}

//function that update Error Log file 
bool CErrorLog::WriteError(CString FunctionName, CString Comment, CString ErrorMsg)
{
	CStdioFile ObjErrorFile;
	bool res = false;

	char szPath[_MAX_PATH];
	CString FilePath = "";
	int loc = 0;

	::GetModuleFileName(NULL,szPath,_MAX_PATH);
	FilePath = szPath;
	FilePath.MakeLower();
	loc = FilePath.Find("pvcs v1.0.exe");
	FilePath = FilePath.Left(loc);
	
	FilePath += "PvcsErrorLog.txt";
	
	if(ObjErrorFile.Open(FilePath,CStdioFile::modeWrite |CStdioFile::modeCreate|CStdioFile::modeNoTruncate|CStdioFile::typeText))//open the file
	{
		CString Buffer = "";

		COleDateTime ObjDate;
		ObjDate = COleDateTime::GetCurrentTime();
				
		Buffer.Format("*****Error Description*****\nFunction Name = %s\nError Message = %s\nComment = %s\nDate and Time = %s\n\n\n",FunctionName,ErrorMsg,Comment,ObjDate.Format());
		
		ObjErrorFile.SeekToEnd();
		
		ObjErrorFile.Write(Buffer,Buffer.GetLength());

		ObjErrorFile.Close();

		res = true;
		
	}
	else
		res = false;

	return res;
			
}