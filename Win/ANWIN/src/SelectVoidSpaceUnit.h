//---------------------------------------------------------------------------

#ifndef SelectVoidSpaceUnitH
#define SelectVoidSpaceUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SelectTankUnit.h"
#include <ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TSelectPROVoidSpace : public TSelectTankForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TSelectPROVoidSpace(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectPROVoidSpace *SelectPROVoidSpace;
//---------------------------------------------------------------------------
#endif
