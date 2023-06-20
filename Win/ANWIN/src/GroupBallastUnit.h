// ---------------------------------------------------------------------------
#ifndef GroupBallastUnitH
#define GroupBallastUnitH
#include "GroupUnit.h"
#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
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
#include "tmsAdvGridExcel.hpp"

// ---------------------------------------------------------------------------
class TGroupTableBallast : public TGroupTable {
__published: // IDE-managed Components
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall OpModeComboBoxChange(TObject *Sender);
	void __fastcall BargraphViewButtonClick(TObject *Sender);
protected:
	void __fastcall FindCargoTypeTanks(int Key);
	void __fastcall SetPopupMenuTanksCargoType(void);



public : // User declarations
	__fastcall TGroupTableBallast(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TGroupTableBallast *GroupTableBallast;
// ---------------------------------------------------------------------------
#endif

