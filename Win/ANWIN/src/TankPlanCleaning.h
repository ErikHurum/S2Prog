//---------------------------------------------------------------------------

#ifndef TankPlanCleaningH
#define TankPlanCleaningH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Grids.hpp>
#include "TankPlanUnit.h"
#include "RzPanel.hpp"
#include "ES.BaseControls.hpp"
#include "ES.PaintBox.hpp"
#include "ES.Labels.hpp"
#include "AdvMenus.hpp"
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "AdvUtil.hpp"
#include "BaseGrid.hpp"
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>

using namespace std;

// Quick fixes - for now. Do a better solution in the future if necessary.
#define TTankPlanCleaningForm_StringColWidth 80
#define TTankPlanCleaningForm_LongStringColWidth 100
#define TTankPlanCleaningForm_DateColWidth 90

#define TTankPlanCleaningForm_ElapsedTimeColumnIndex 6

#define TTankPlanCleaningForm_MaxTableRefreshTime 5

//---------------------------------------------------------------------------


class PROTank;


class TTankPlanCleaningForm_GridRowData : public TObject
{
public:
	inline TTankPlanCleaningForm_GridRowData() : TObject()
	{
	}

	int tankWashingMachineId;

	TankWashingMachineRun_Statuses runStatus;

	double washStartTime;

	double washEndTime;
	double washFlow;
};


typedef vector<TTankPlanCleaningForm_GridRowData*> TankPlan_GridRowData_t;



class TTankPlanCleaningForm : public TTankPlanDrawingForm
{
__published:	// IDE-managed Components
	TPanel *TankDetailsPanel;
	TLabel *TankNameValueLabel;
	TTimer *TankPlanCleaningTimer;
	TGroupBox *GroupBox1;
	TLabel *ValueTypeLabel2;
	TLabel *ValueUnitLabel2;
	TButton *Button1;
	TAdvStringGrid *WashingMachineStringGrid;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall OnPlanMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall OnTankPlanCleaningTimerTick(TObject *Sender);
	void __fastcall OnFormPaint(TObject *Sender);
	void __fastcall OnTankDetailsResized(TObject *Sender);
	void __fastcall EsPaintBox1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);

private:	// User declarations
	long timeLastAnyRefresh;                // TODO: consider removing
	long timeLastFullRefresh;
	long timeLastFullGridUpdate;			// TODO: consider removing
	PROXRefObject *PreviousTankPtr;
	bool mustResizeGridCols;

	PROTank* FindTank(unsigned PROTankId);
	PROCargoTank* FindCargoTank(unsigned PROTankId);
	void __fastcall InitializeGridColumns();
	void __fastcall FreeGridRowData();

	// Overrides:
	void __fastcall UpdateValues(void);
	void __fastcall BlankValues(AnsiString Msg);

protected:
	TankPlan_GridRowData_t gridRowDataVector;
	void __fastcall RefreshElapsedTimeColumn(int columnIndex);

	// Overrides:
	void __fastcall GetTankDisplayColors(PROTank *pTank, System::Uitypes::TColor *backgroundColor, System::Uitypes::TColor *foregroundColor);

public:		// User declarations
	__fastcall TTankPlanCleaningForm(TComponent* Owner);

	void RefreshData();
	void RefreshData_WashingMachineTable(UnitOfWork &unitOfWork, TankWashingMachineCollection& twmCollection);
	void RefreshData_ClearWashingMachineTable();
};
//---------------------------------------------------------------------------
extern PACKAGE TTankPlanCleaningForm *TankPlanCleaningForm;
//---------------------------------------------------------------------------
#endif
