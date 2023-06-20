//---------------------------------------------------------------------------

#ifndef SelectCargoTankUnitH
#define SelectCargoTankUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SelectTankUnit.h"
#include <ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TSelectPROCargoTank : public TSelectTankForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TSelectPROCargoTank(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectPROCargoTank *SelectPROCargoTank;
//---------------------------------------------------------------------------
#endif
