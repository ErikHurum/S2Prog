// ---------------------------------------------------------------------------
#include <vcl.h>
#include "TSNIncludes.h"
#pragma hdrstop
#include "ConfigWarningsForm.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma resource "*.dfm"

TConfigWarningForm *ConfigWarningForm;

// ---------------------------------------------------------------------------
__fastcall TConfigWarningForm::TConfigWarningForm(TComponent* Owner)
    : TForm(Owner) {
	CheckConfigWarnings(false);

}

// ---------------------------------------------------------------------------
void __fastcall TConfigWarningForm::CloseButtonClick(TObject *Sender) {
    Close();
}

// ---------------------------------------------------------------------------
void __fastcall TConfigWarningForm::PrintButtonClick(TObject *Sender) {
    /*
     PrintHWForm->HeadingQRPLabel->Caption = "Configuration file warnings report";
     PrintHWForm->OverviewQRPRichtext->Lines->Clear();
     PrintHWForm->OverviewQRPRichtext->Lines = ConfigWarningMemo->Lines;
     PrintHWForm->OverviewQRPQuickRep->Preview();
     */
}
// ---------------------------------------------------------------------------

void __fastcall TConfigWarningForm::CheckConfigWarnings(bool Show) {
	ConfigWarningMemo->Clear();
	ConfigWarningMemo->Lines->Text = ConfigWarningsString + HWOverviewWarningsString+RestoreSettingsWarningsString;
	if ( !ConfigWarningsString.IsEmpty() && !RestoreSettingsWarningsString.IsEmpty() ){
		ConfigWarningForm->Caption = "Configuration and Settings file warning";
		ConfigWarningMemo->Color = clMaroon;
	}else if ( !ConfigWarningsString.IsEmpty() ){
		ConfigWarningForm->Caption = "Configuration file warning";
		ConfigWarningMemo->Color = clYellow;
	} else if ( !RestoreSettingsWarningsString.IsEmpty()){
		ConfigWarningForm->Caption = "Settings file warning";
		ConfigWarningMemo->Color = clFuchsia;
	}
	Visible = true;
	BringToFront();
}

// ---------------------------------------------------------------------------
void __fastcall TConfigWarningForm::FormClose(TObject *Sender,
    TCloseAction &Action) {
    ConfigWarningForm = NULL;
}
// ---------------------------------------------------------------------------

