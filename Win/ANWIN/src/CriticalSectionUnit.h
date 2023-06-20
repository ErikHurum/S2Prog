//---------------------------------------------------------------------------

#ifndef CriticalSectionUnitH
#define CriticalSectionUnitH
//---------------------------------------------------------------------------
#include <System.SyncObjs.hpp>
class ANPRO10CriticalSection  {
private:
    TCriticalSection *MyLock;
public:
	ANPRO10CriticalSection(void);
	~ANPRO10CriticalSection(void);
	void Acquire(void);
	void Release(void);
};

#endif
