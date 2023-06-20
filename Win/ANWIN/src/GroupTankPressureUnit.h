// ---------------------------------------------------------------------------

#ifndef GroupTankPressureUnitH
#define GroupTankPressureUnitH
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
#include <Vcl.Dialogs.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include "tmsAdvGridExcel.hpp"

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
class TGroupTableTankPressure : public TGroupTable {
__published: // IDE-managed Components
	void __fastcall OpModeComboBoxChange(TObject *Sender);
	void __fastcall StringGridAllTanksFixedCellClick(TObject *Sender, int ACol, int ARow);

private: // User declarations
	vector<int>__fastcall SetDefaultValTable(void);
	vector<int>__fastcall SetAlarmValTable(void);
	vector<int>__fastcall SetSensorValTable(void);
	PROXRefObject* __fastcall NewPartSum(void);


public: // User declarations

	static TGroupTableTankPressure *TankPressuresTable;

	__fastcall TGroupTableTankPressure(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TGroupTableTankPressure *GroupTableTankPressure;
// ---------------------------------------------------------------------------
#endif
