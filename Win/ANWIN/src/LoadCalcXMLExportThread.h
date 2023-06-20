// ---------------------------------------------------------------------------

#ifndef LoadCalcXMLExportThreadH
#define LoadCalcXMLExportThreadH
// ---------------------------------------------------------------------------
#include <Classes.hpp>

// ---------------------------------------------------------------------------
class LoadCalcXMLExportThread : public TThread {
protected:
	void __fastcall Execute();

private:
	//HANDLE m_hAccessMutex; // Handle to Access Mutex
	char *BufPtr;
	char *SharedMem;

public:
	__fastcall LoadCalcXMLExportThread(bool CreateSuspended);
	__fastcall ~LoadCalcXMLExportThread(void);
};
// ---------------------------------------------------------------------------
#endif
