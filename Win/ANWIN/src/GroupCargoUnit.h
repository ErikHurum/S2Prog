// ---------------------------------------------------------------------------

#ifndef GroupCargoUnitH
#define GroupCargoUnitH
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
#include <Vcl.Samples.Spin.hpp>
#include "asgprint.hpp"
#include <System.ImageList.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ImgList.hpp>
#include "frCoreClasses.hpp"
#include "frxSmartMemo.hpp"
#include "tmsAdvGridExcel.hpp"

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
class TGroupTableCargo : public TGroupTable {
__published: // IDE-managed Components
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall OpModeComboBoxChange(TObject *Sender);
	void __fastcall BargraphViewButtonClick(TObject *Sender);





protected:
	void __fastcall SetPopupMenuTanksCargoType(void);
	vector<int>__fastcall SetDefaultValTable(void);

public : // User declarations


	__fastcall TGroupTableCargo(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TGroupTableCargo *GroupTableCargo;
// ---------------------------------------------------------------------------
#endif
