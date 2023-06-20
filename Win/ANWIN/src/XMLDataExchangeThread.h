//---------------------------------------------------------------------------

#ifndef XMLDataExchangeThreadH
#define XMLDataExchangeThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class XMLDataExchangeThread : public TThread
{
protected:
	void __fastcall Execute();
private:
	HANDLE m_hAccessMutex;			// Handle to Access Mutex
	char  *SharedMem;
	char* __fastcall AddAlarms(void);
	U8 __fastcall CheckSum(IN const void* param_pvData, const unsigned param_ulSize);
public:
    char  *BufPtr;
	__fastcall XMLDataExchangeThread(bool CreateSuspended);
	__fastcall ~XMLDataExchangeThread(void);
};
//---------------------------------------------------------------------------
#endif
