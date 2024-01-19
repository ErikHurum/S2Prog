//---------------------------------------------------------------------------

#ifndef GroupScratchUnitH
#define GroupScratchUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "GroupUnit.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ToolWin.hpp>
#include "RzButton.hpp"
#include "frxClass.hpp"
#include "frxCross.hpp"
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "AdvUtil.hpp"
#include "BaseGrid.hpp"
#include "asgprint.hpp"
#include <System.ImageList.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ImgList.hpp>
#include "frCoreClasses.hpp"
#include "tmsAdvGridExcel.hpp"
//---------------------------------------------------------------------------
class TGroupTableScratchPage : public TGroupTable
{
__published: // IDE-managed Components
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall OpModeComboBoxChange(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall StringGridAllTanksContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled);

private:	// User declarations
	TMenuItem *SubMenuTankPopUp;
	TMenuItem *SubMenuTankPressurePopUp;
	TMenuItem *SubMenuTemperaturePopUp;
	TMenuItem *SubMenuLinePressurePopUp;
	TMenuItem *SubMenuDraftPopUp;

protected:
	void __fastcall SetPopupMenuInsertTank(void);

public:		// User declarations
	__fastcall TGroupTableScratchPage(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGroupTableScratchPage *GroupTableScratchPage;
//---------------------------------------------------------------------------
#endif
