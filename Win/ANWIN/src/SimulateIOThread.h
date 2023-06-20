//---------------------------------------------------------------------------

#ifndef SimulateIOThreadH
#define SimulateIOThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class SimulateIOThread : public TThread
{
protected:
	void __fastcall Execute();
public:
	__fastcall SimulateIOThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
