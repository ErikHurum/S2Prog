// ---------------------------------------------------------------------------

#ifndef CargoTypeUnitH
#define CargoTypeUnitH
#include "ChildUnit.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <StdCtrls.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "AdvUtil.hpp"
#include "BaseGrid.hpp"
#include <Vcl.Menus.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
class TCargoTypeSetupForm : public TChildForm {
__published: // IDE-managed Components

	TPanel *Panel1;
	TPanel *Panel3;
	TPanel *Panel4;
	TLabel *AvailableCTLabel;
	TPanel *Panel2;
	TLabel *DensValueLabel;
	TLabel *APILabel;
	TLabel *APIUnit;
	TLabel *RefDensity1Unit;
	TLabel *RefDens1Label;
	TLabel *RefDens2Label;
	TLabel *RefDensity2Unit;
	TLabel *RefTemp1Unit;
	TLabel *RefTemp1Label;
	TLabel *RefTemp2Label;
	TLabel *RefTemp2Unit;
	TLabel *CoefficientUnit;
	TLabel *CoeffLabel;
	TLabel *VCFLabel;
	TLabel *VCFUnit;
	TLabel *CargoLabel;
	TLabel *BaseCargoLabel;
	TLabel *LowTempLabel;
	TLabel *HighTempLabel;
	TLabel *LowTempUnit;
	TLabel *HighTempUnit;
	TShape *ColorShape;
	TEdit *API;
	TEdit *RefDensity1;
	TEdit *RefDensity2;
	TEdit *RefTemp1;
	TEdit *RefTemp2;
	TEdit *Coefficient;
	TEdit *VCF;
	TEdit *CargoType;
	TEdit *BaseCargo;
	TEdit *LowTemp;
	TEdit *HighTemp;
	TCheckBox *LowTempCheckBox;
	TCheckBox *HighTempCheckBox;
	TButton *EditButton;
	TButton *NewButton;
	TButton *DeleteButton;
	TGroupBox *GroupBox1;
	TLabel *CapacityLabel;
	TLabel *CapacityUnitLabel;
	TPanel *Panel5;
	TButton *SelectAllButton;
	TButton *DeselectButton;
	TButton *ApplyButton;
	TLabel *MolWeightLabel;
	TEdit *MolWeight;
	TLabel *MolWeightUnit;
	TAdvStringGrid *TankSelectStringGrid;
	TAdvStringGrid *CargoTypeStringGrid;
	TLabel *ViscosityLabel;
	TEdit *Viscosity;
	TLabel *ViscosityUnit;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall EditButtonClick(TObject *Sender);
	void __fastcall NewButtonClick(TObject *Sender);
	void __fastcall DeleteButtonClick(TObject *Sender);
	void __fastcall SelectAllButtonClick(TObject *Sender);
	void __fastcall DeselectButtonClick(TObject *Sender);
	void __fastcall TankSelectStringGridDrawCell(TObject *Sender, int ACol,
		int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall TankSelectStringGridKeyPress(TObject *Sender, char &Key);
	void __fastcall TankSelectStringGridMouseDown(TObject *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall ApplyButtonClick(TObject *Sender);
	void __fastcall CargoTypeStringGridDrawCell(TObject *Sender, int ACol,
		int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall CargoTypeStringGridSelectCell(TObject *Sender, int ACol,
		int ARow, bool &CanSelect);
	void __fastcall TankSelectStringGridTopLeftChanged(TObject *Sender);
	void __fastcall StringGridRefreshTimerTimer(TObject *Sender);
	void __fastcall TankSelectStringGridClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);

private: // User declarations

	TEdit *EditList[30];
	TLabel *LabelUnitList[30];
	int EditListEntries;
	int LabelUnitListEntries;
	TCheckBox *ChBoxList[10];
	int ChBoxListEntries;

	CTOUser *CurrentCargoType;
	vector<PRogramObjectBase*>CurrentTankVector;
	vector<TCheckBox*>TankChListBoxVect;
	int Type;

	void SetLabelList(void);
	void UpdateValues(void);
	void FindCargoTypes(void);
	void FindCargoTypeTanks(void);
	void UpdateCargoType(void);
	void UpdateAll(void);
	void __fastcall AddCheckboxToStringGrid(TObject *Sender, int Row,
		PROTank *TankPtr);
	void __fastcall InitiateTankStringGrid(TObject *Sender,
		vector<PRogramObjectBase*>TankVector);
	void __fastcall UpdateSelectCheckBox(TAdvStringGrid* StringGrid);

public: // User declarations
	__fastcall TCargoTypeSetupForm(TComponent* Owner);
	CTOUser* __fastcall GetCargoTypePtr(void);

};

// ---------------------------------------------------------------------------
extern PACKAGE TCargoTypeSetupForm *CargoTypeSetupForm;
// ---------------------------------------------------------------------------
#endif
