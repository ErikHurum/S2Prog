//---------------------------------------------------------------------------

#ifndef TankDetailsWashingMachinesH
#define TankDetailsWashingMachinesH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "ChildUnit.h"
#include "TSNIncludes.h"
#include "TankWashingMachineServiceUnit.h"
#include "DBAccess.hpp"
#include "LiteAccess.hpp"
#include "LiteCall.hpp"
#include "LiteConsts.hpp"
#include <Data.DB.hpp>
#include "MemDS.hpp"
#include <Vcl.DBGrids.hpp>
#include <Vcl.WinXPickers.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "AdvUtil.hpp"
#include "BaseGrid.hpp"
#include "AdvEdit.hpp"
#include <Vcl.Mask.hpp>
#include "RzEdit.hpp"
#include "DBAdvGrid.hpp"
#include <Vcl.Graphics.hpp>
#include "CalcEdit.hpp"
#include <Vcl.Samples.Spin.hpp>
#include "AdvSpin.hpp"
#include "AdvCombo.hpp"
#include "AdvDBComboBox.hpp"
#include "AdvDBLookupComboBox.hpp"
#include "AdvSearchEdit.hpp"
#include "AdvSmoothComboBox.hpp"
#include "AdvSmoothListBox.hpp"
#include "DBAdvSmoothComboBox.hpp"
#include <Vcl.DBCtrls.hpp>
#include "RzDBGrid.hpp"
#include "GradientLabel.hpp"
#include "RzLabel.hpp"

using namespace std;

class PROTankWashingMachine;

class TTankDetailsWashingMachinesForm_GridData : public TObject
{
public:
	int tankWashingMachineId;

    TankWashingMachineRun_Statuses runStatus;

	double washStartTime;
	double washEndTime;
	double washFlow;
	PROTankWashingMachine *TWMptr;
	inline TTankDetailsWashingMachinesForm_GridData() : TObject()
	{
		TWMptr = NULL;
	}

};


typedef vector<TTankDetailsWashingMachinesForm_GridData*> GridRowDataVector_t;



//---------------------------------------------------------------------------
class TTankDetailsWashingMachinesForm : public TChildForm
{
__published:	// IDE-managed Components
	TLabel *TankNameLabel;
	TLabel *TWMLabel;
	TLabel *StatusLabel;
	TLabel *TWStartTimeLabel;
	TLabel *TWStartTimeValueLabel;
	TLabel *TWEndTimeLabel;
	TLabel *TWEndTimeValueLabel;
	TLabel *StatusValueLabel;
	TGroupBox *TankStatusGroupBox;
	TGroupBox *WashingSetupGroupBox;
	TLabel *CleaningMediaLabel;
	TLabel *WashTypeLabel;
	TButton *ApplyWashSetupButton;
	TButton *PrepareWashingRunsButton;
	TTimer *GridRefreshTimer;
	TLabel *WaterFlowLabel;
	TLabel *EnergySpentLabel;
	TLabel *CostLabel;
	TLabel *VolumeValueLabel;
	TLabel *EnergySpentValueLabel;
	TLabel *CostValueLabel;
	TAdvStringGrid *WashingMachineStringGrid;
	TLabel *FlowValueLabel;
	TLabel *Label2;
	TButton *Button1;
	TLiteQuery *WashTrackLogLiteQuery;
	TLiteDataSource *WashTrackLogLiteDataSource;
	TLiteTable *CleaningMediaLiteTable;
	TLiteDataSource *CleaningMediaLiteDataSource;
	TLiteQuery *CleaningMediaLiteQuery;
	TDBComboBox *CleaningMediaComboBox;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TAdvSpinEdit *PresetTimeEdit;
	TButton *SetTimeButton;
	TAdvComboBox *WashTypeComboBox;
	void __fastcall OnFormPaint(TObject *Sender);
	void __fastcall OnFormResize(TObject *Sender);
	void __fastcall ApplyWashSetupButtonClick(TObject *Sender);
	void __fastcall PrepareWashingRunsButtonClick(TObject *Sender);
	void __fastcall OnCleaningTypeSelected(TObject *Sender);
	void __fastcall OnSelectWashingMachineCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
	void __fastcall OnGridRefreshTimerTick(TObject *Sender);
	void __fastcall DemoWarningButtonClicked(TObject *Sender);
	void __fastcall OnTankWashingMachineDblClick(TObject *Sender);
	void __fastcall OnMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall OnMouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall WashTypeComboBoxChange(TObject *Sender);
	void __fastcall PresetRunTimePickerChange(TObject *Sender);
	void __fastcall PresetTimeEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall PresetTimeEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall PresetTimeEdit2MaskComplete(TObject *Sender, UnicodeString Value, bool &accept);
	void __fastcall WashingMachineStringGridEditCellDone(TObject *Sender, int ACol, int ARow);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall PresetTimeEditMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall CleaningMediaComboBoxChange(TObject *Sender);
	void __fastcall CleaningMediaComboBoxEnter(TObject *Sender);
	void __fastcall WashingMachineStringGridClickCell(TObject *Sender, int ARow, int ACol);
	void __fastcall SetTimeButtonClick(TObject *Sender);


private:	// User declarations
	PROCargoTank* ptrCargoTank;
	PROCargoTank* PrevPtrCargoTank;

	/// Set this variable to true to ensure the Paint event refreshes the data in the form
	bool mustRefreshData;
	bool mustResizeGridCols;

	// vectors used for getting the values of things selected in comboboxes:
	vector<int> washTypeValues;
	vector<int> cleaningMediaIdValues;
	GridRowDataVector_t gridRowDataVector;

	int selectedGridRow;

	int RefreshCnt;
	bool RefreshAfterCreate;
	vector<int> createdTWMRunIds;
	void __fastcall FreeGridRowData();
	void __fastcall RefreshColumns(void);

	AnsiString emptyString;
	int EditDelayCount;
public:		// User declarations
	__fastcall TTankDetailsWashingMachinesForm(TComponent* Owner);
	__fastcall ~TTankDetailsWashingMachinesForm();
	void SetCargoTank(PROCargoTank* ptrTank);
	void RefreshData();
	void RefreshData_WholeTankInfo(TankWashingMachineRunCollection& twmRunCollection, TankWashingMachineCollection& twmCollection);
	void RefreshData_WashingMachineTable(UnitOfWork &unitOfWork, TankWashingMachineCollection& twmCollection);
	void RefreshData_WashingSetupControls(UnitOfWork &unitOfWork, TankWashingMachineRunCollection& twmRunCollection);
	void __fastcall InitializeGridColumns();
	void __fastcall CommonEditKeyPress(TObject *Sender, System::WideChar &Key, PRogramObjectBase *ObjPtr);

	static void CreateOrShowWindow(PROCargoTank* ptrTank);
};
//---------------------------------------------------------------------------
extern PACKAGE TTankDetailsWashingMachinesForm *TankDetailsWashingMachinesForm;
//---------------------------------------------------------------------------
#endif
