#include "StdAfx.h"
#include ".\backuplog.h"

CBackupLog::CBackupLog(void)
{
}

CBackupLog::~CBackupLog(void)
{
}

// Function to Write the Log To a new location on PVCS starts
bool CBackupLog::BackUpLog(CString param_source,CString param_backup)
{
	
	CFile cfMyFile;
	CFile cfMyWriteFile;
	cfMyFile.Open(param_source, CFile::modeRead | CFile::typeBinary);
	cfMyWriteFile.Open(param_backup,CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	
	UINT myFileLength = UINT(cfMyFile.GetLength());
	char* buf;
	buf=new char[myFileLength];
	
		cfMyFile.Read(buf,myFileLength);
		cfMyWriteFile.Write(buf,myFileLength);

	cfMyFile.Close();
	cfMyWriteFile.Close();
	delete [] buf;
	return true;
}

// Function to check the size of fiel is it exceeeds 2MB
bool CBackupLog::CheckFileSize(CString param_pcFileName)
{
	CFile cfMyFile;
	BOOL fileopen;
	fileopen = cfMyFile.Open(param_pcFileName, CFile::modeRead | CFile::typeBinary);
	if(fileopen==0)
	{
		return false;
	}
	else
	{
		UINT myFileLength = UINT(cfMyFile.GetLength());
		if(myFileLength>20000)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
