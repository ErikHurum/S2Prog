//---------------------------------------------------------------------------

#ifndef SelectServiceTankUnitH
#define SelectServiceTankUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SelectTankUnit.h"
#include <ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TSelectPROServiceTank : public TSelectTankForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TSelectPROServiceTank(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectPROServiceTank *SelectPROServiceTank;
//---------------------------------------------------------------------------
#endif
