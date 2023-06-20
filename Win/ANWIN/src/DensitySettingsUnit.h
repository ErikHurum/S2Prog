// ---------------------------------------------------------------------------

#ifndef DensitySettingsUnitH
#define DensitySettingsUnitH
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>

// ---------------------------------------------------------------------------
class TDensitySettingDlg : public TForm {
__published: // IDE-managed Components

	TPanel *Panel2;
	TLabel *DensValueLabel;
	TLabel *BallastUnit;
	TLabel *BallastLable;
	TEdit *Ballast;
	TButton *CancelButton;
	TButton *SaveButton;
	TLabel *HeavyFuelLabel;
	TEdit *HeavyFuel;
	TLabel *HeavyFuelUnit;
	TLabel *DieselOilLabel;
	TEdit *DieselOil;
	TLabel *DieselOilUnit;
	TLabel *LubricantLabel;
	TEdit *Lubricant;
	TLabel *LubricantUnit;
	TLabel *FreshWaterLabel;
	TEdit *FreshWater;
	TLabel *FreshWaterUnit;
	TLabel *SeaWaterLabel;
	TEdit *SeaWater;
	TLabel *SeaWaterUnit;

	void __fastcall EditExit(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall EditKeyPress(TObject *Sender, char &Key);
	void __fastcall SaveButtonClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);

private: // User declarations

	TEdit *EditList[6];
	TLabel *LabelUnitList[6];
	int EditListEntries;
	int LabelUnitListEntries;
	// TEdit *CurrentEditPtr;

	void SetLabelList(void);
	void UpdateValues(void);
	void SetNewValues(void);

public: // User declarations
	__fastcall TDensitySettingDlg(TComponent* AOwner);
	void ClearAllFields(void);

};

// ---------------------------------------------------------------------------
extern PACKAGE TDensitySettingDlg *DensitySettingDlg;
// ---------------------------------------------------------------------------
#endif
