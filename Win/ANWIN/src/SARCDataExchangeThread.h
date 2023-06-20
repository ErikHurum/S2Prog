//---------------------------------------------------------------------------

#ifndef SARCDataExchangeThreadH
#define SARCDataExchangeThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------

class SARCDataExchangeThread : public TThread
{
protected:
	void __fastcall Execute();

	bool __fastcall ExportData();
	int __fastcall FillOutputBuffer();
private:
	HANDLE m_hAccessMutex;			// Handle to Access Mutex
	char  *SharedMem;

	UnicodeString  outputDirPath;
	UnicodeString  outputFilePath;
	bool allowFileLinks;
	const double updateIntervalSecs;

	char *buffPtr;
	int outBufferSize;
	int maxLineLength;

public:
	__fastcall SARCDataExchangeThread(bool CreateSuspended);
	__fastcall ~SARCDataExchangeThread(void);
};
//---------------------------------------------------------------------------
#endif