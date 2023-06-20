//---------------------------------------------------------------------------

#ifndef HartComUnitH
#define HartComUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class HartComThread : public TThread
{
private:
	set_data_struct RadarConfig;
	float RadarDistance;

protected:
	void __fastcall Execute();
public:
	__fastcall HartComThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
