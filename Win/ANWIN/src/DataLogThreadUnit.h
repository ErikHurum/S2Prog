//---------------------------------------------------------------------------

#ifndef DataLogThreadUnitH
#define DataLogThreadUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class DataLogThread : public TThread
{
private:
	volatile int Delay;
protected:
	void __fastcall Execute();
public:
	__fastcall DataLogThread(bool CreateSuspended, int pDelay);
	void __fastcall SetDelay(int pDelay);
};
//---------------------------------------------------------------------------
#endif
