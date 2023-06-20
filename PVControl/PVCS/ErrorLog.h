#pragma once

class CErrorLog
{
public:
	CErrorLog(void);
	~CErrorLog(void);

	//function to write error entry into the file
	bool WriteError(CString FunctionName, CString Comment, CString ErrorMsg);

private:
	
};
