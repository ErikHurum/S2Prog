//---------------------------------------------------------------------------

#ifndef SelectBallastTankUnitH
#define SelectBallastTankUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SelectTankUnit.h"
#include <ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
class TSelectPROBallastTank : public TSelectTankForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TSelectPROBallastTank(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectPROBallastTank *SelectPROBallastTank;
//---------------------------------------------------------------------------
#endif
