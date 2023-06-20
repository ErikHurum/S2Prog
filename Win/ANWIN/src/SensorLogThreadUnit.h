//---------------------------------------------------------------------------

#ifndef SensorLogThreadUnitH
#define SensorLogThreadUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class SensorLogThread : public TThread
{
private:
	volatile int Delay;
protected:
	void __fastcall Execute();
public:
	__fastcall SensorLogThread(bool CreateSuspended, int pDelay);
	void __fastcall SetDelay(int pDelay);
};
//---------------------------------------------------------------------------
#endif
