//---------------------------------------------------------------------------

#ifndef ANPRO10ThreadUnitH
#define ANPRO10ThreadUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "ANWinInc.h"

//---------------------------------------------------------------------------
class ANPR10ReceiveThread : public TThread
{
private:
	char NetRxBuf[UNPACK_BLOCK_SIZE];
	void __fastcall ANPRO10Receive(void);

protected:
	void __fastcall Execute();
public:
	__fastcall ANPR10ReceiveThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
