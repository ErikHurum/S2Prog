// ---------------------------------------------------------------------------

#ifndef GroupServiceUnitH
#define GroupServiceUnitH
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
#include "asgprev.hpp"
#include <Vcl.Dialogs.hpp>
#include "asgprint.hpp"
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include "frCoreClasses.hpp"
#include "frxSmartMemo.hpp"
#include "tmsAdvGridExcel.hpp"

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
class TGroupTableService : public TGroupTable {
__published: // IDE-managed Components
	TAdvPreviewDialog *AdvPreviewDialog1;
	TPopupMenu *PopupMenu1;
	TPopupMenu *PopupMenu2;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall OpModeComboBoxChange(TObject *Sender);
	void __fastcall BargraphViewButtonClick(TObject *Sender);
protected:
	void __fastcall FindCargoTypeTanks(int Key);
	void __fastcall SetPopupMenuTanksCargoType(void);

private: // User declarations
		public : // User declarations

	static TGroupTableService *ServiceTanksTable;

	__fastcall TGroupTableService(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TGroupTableService *GroupTableService;
// ---------------------------------------------------------------------------
#endif
