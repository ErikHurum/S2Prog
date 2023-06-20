//---------------------------------------------------------------------------

#ifndef NewCargoTypeUnitH
    #define NewCargoTypeUnitH
//---------------------------------------------------------------------------
    #include "ChildUnit.h"
    #include <Classes.hpp>
    #include <Controls.hpp>
    #include <Dialogs.hpp>
    #include <ExtCtrls.hpp>
    #include <StdCtrls.hpp>
#include "AdvSelectors.hpp"
#include "RzCommon.hpp"
#include "RzBorder.hpp"
#include "RzPanel.hpp"
#include "RzEdit.hpp"
#include <Vcl.Mask.hpp>
#include "DBAccess.hpp"
#include "LiteAccess.hpp"
#include "MemDS.hpp"
#include <Data.DB.hpp>

//---------------------------------------------------------------------------
class TNewCargoTypeSetupDlg : public TForm {
    __published:    // IDE-managed Components
    TPanel *Panel2;
    TLabel *DensValueLabel;
    TLabel *APILabel;
    TEdit *API;
    TLabel *APIUnit;
    TLabel *RefDensity1Unit;
    TEdit *RefDensity1;
    TLabel *RefDens1Label;
    TLabel *RefDens2Label;
    TEdit *RefDensity2;
    TLabel *RefDensity2Unit;
    TLabel *RefTemp1Unit;
    TEdit *RefTemp1;
    TLabel *RefTemp1Label;
    TLabel *RefTemp2Label;
    TEdit *RefTemp2;
    TLabel *RefTemp2Unit;
    TLabel *CoefficientUnit;
    TEdit *Coefficient;
    TLabel *CoeffLabel;
    TLabel *VCFLabel;
    TEdit *VCF;
    TLabel *VCFUnit;
    TLabel *CargoLabel;
    TEdit *CargoType;
    TEdit *BaseCargo;
    TLabel *BaseCargoLabel;
    TLabel *LowTempLabel;
    TLabel *HighTempLabel;
    TEdit *LowTemp;
    TEdit *HighTemp;
    TLabel *LowTempUnit;
    TLabel *HighTempUnit;
    TGroupBox *BaseTypeGroupBox;
    TListBox *SelectBaseCTListBox;
    TButton *ChooseCTButton;
    TCheckBox *LowTempCheckBox;
    TCheckBox *HighTempCheckBox;
    TButton *SaveNewButton;
	TButton *CancelButton;
    TButton *SaveButton;
	TLabel *MolWeightLabel;
	TEdit *MolWeight;
	TLabel *MolWeightUnit;
	TLabel *ViscosityLabel;
	TEdit *Viscosity;
	TLabel *ViscosityUnit;
	TColorDialog *CargoColorDialog;
	TRzCustomColors *RzCustomColors1;
	TRzRegIniFile *RzRegIniFile1;
	TRzPropertyStore *RzPropertyStore1;
	TShape *CargoShape;
	void __fastcall SelectBaseCTListBoxClick(TObject *Sender);
	void __fastcall ChooseCTButtonClick(TObject *Sender);
	void __fastcall EditExit(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ChBoxClick(TObject *Sender);
	void __fastcall EditKeyPress(TObject *Sender, char &Key);
	void __fastcall SaveNewButtonClick(TObject *Sender);
	void __fastcall SaveButtonClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall CancelButtonClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall CargoShapeMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);

private:    // User declarations
	TEdit *EditList[30];
	TLabel *LabelUnitList[30];
	int  EditListEntries;
	int  LabelUnitListEntries;
	String NameOfButton;
	AnsiString OrgCargoName;
	TCheckBox *ChBoxList[10];
	int  ChBoxListEntries;
	AnsiString	RegNameKey;
	CTOUser *CurrentCargoType;
    AnsiString OriginalCargoName;

//  TEdit *CurrentEditPtr;

	void __fastcall SetLabelList(void);
	void __fastcall FindBaseCargoTypes(void);
	void __fastcall UpdateValues(void);
	void __fastcall MakeNewCargoType(void);
	void __fastcall EnableDisableEdit(void);

public:     // User declarations
	__fastcall TNewCargoTypeSetupDlg(TComponent* AOwner);
	void __fastcall ReadRegistry(void);
	void __fastcall WriteRegistry(void);
	CTOUser* __fastcall GetCargoTypePtr(void);
	void __fastcall SetCargoTypePtr(CTOUser* CargoInfoPtr);


};
//---------------------------------------------------------------------------
extern PACKAGE TNewCargoTypeSetupDlg *NewCargoTypeSetupDlg;
//---------------------------------------------------------------------------
#endif
