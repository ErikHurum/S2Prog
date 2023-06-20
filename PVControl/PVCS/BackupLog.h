#pragma once
//////////////////////////////////////////////////////////////
//Class to check the size of logfile and backup it if its above 
// 2MB
//////////////////////////////////////////////////////////////
class CBackupLog
{
public:
	CBackupLog(void);
	virtual ~CBackupLog(void);
	// Function to Write the Log To a new location on PVCS starts
	bool BackUpLog(CString param_source,CString param_backup);
	// Function to check the size of fiel is it exceeeds 2MB
	bool CheckFileSize(CString param_pcFileName);
};
